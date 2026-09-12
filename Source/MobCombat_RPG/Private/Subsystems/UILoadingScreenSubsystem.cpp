// Priyanshu Shukla All Rights Reserved


#include "Subsystems/UILoadingScreenSubsystem.h"

#include "PreLoadScreenManager.h"
#include "Blueprint/UserWidget.h"
#include "DeveloperSettings/UILoadingScreenSettings.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/WarriorLoadingScreenInterface.h"
#include "UObject/Linker.h"

bool UUILoadingScreenSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClass;
		GetDerivedClasses(GetClass(), FoundClass);
		
		return FoundClass.IsEmpty();
	}
	return false;
}

void UUILoadingScreenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	FCoreUObjectDelegates::PreLoadMapWithContext.AddUObject(this,&ThisClass::OnMapPreLoaded);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this,&ThisClass::OnMapPostLoaded);
}

void UUILoadingScreenSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::PreLoadMapWithContext.RemoveAll(this);
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
}

UWorld* UUILoadingScreenSubsystem::GetTickableGameObjectWorld() const
{
	if (UGameInstance* OwningGameInstance = GetGameInstance())
	{
		return OwningGameInstance->GetWorld();
	}
	return nullptr;
}

void UUILoadingScreenSubsystem::Tick(float DeltaTime)
{
	TryUpdateLoadingScreen();
}

ETickableTickType UUILoadingScreenSubsystem::GetTickableTickType() const
{
	if (IsTickable())
	{
		return ETickableTickType::Never;
	}
	return ETickableTickType::Conditional; // Checks for is IsTickable( ):
}

bool UUILoadingScreenSubsystem::IsTickable() const
{
	return GetGameInstance() && GetGameInstance()->GetGameViewportClient();
}

TStatId UUILoadingScreenSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UFrontendLoadingScreenSubsystem,STATGROUP_Tickables);
}

void UUILoadingScreenSubsystem::OnMapPreLoaded(const FWorldContext& WorldContext, const FString& MapName)
{
	if (WorldContext.OwningGameInstance != GetGameInstance())
	{
		return;
	}
	
	SetTickableTickType(ETickableTickType::Conditional);
	
	bIsCurrentlyLoadingMap = true;
	
	TryUpdateLoadingScreen();
}

void UUILoadingScreenSubsystem::OnMapPostLoaded(UWorld* LoadedWorld)
{
	if (LoadedWorld && LoadedWorld->GetGameInstance() == GetGameInstance())
	{
		bIsCurrentlyLoadingMap = false;
	}
	
}

void UUILoadingScreenSubsystem::TryUpdateLoadingScreen()
{
	//Check if there's any start up loading screen that's currently active
	if (IsPreLoadScreenActive())
	{
		return;
	}
	// Check if there is a need to show the loading screen:
	if (ShouldShowLoadingScreen())
	{
		//Try display the loading screen here
		TryDisplayLoadingScreenIfNone();
		
		OnLoadingReasonUpdated.Broadcast(CurrentLoadingReason);
	}
	else
	{
		// Try removing the current active loading screen
		TryRemoveLoadingScreen();
		HoldLoadingScreenStartUpTime = -1.f;
		
		// Notify the loading is complete
		NotifyLoadingScreenVisibilityChanged(false);\
		
		// Disable the Ticking
		SetTickableTickType(ETickableTickType::Never);
		
		// the object doesn't burn cycles ticking every frame during normal gameplay; it only actively ticks during the loading window.
	}
}

bool UUILoadingScreenSubsystem::IsPreLoadScreenActive() const
{
	if (FPreLoadScreenManager* PreLoadScreenManager = FPreLoadScreenManager::Get())
	{
		return PreLoadScreenManager->HasValidActivePreLoadScreen();
	}
	return false;
}

bool UUILoadingScreenSubsystem::ShouldShowLoadingScreen()
{
	const UUILoadingScreenSettings* LoadingScreenSettings = GetDefault<UUILoadingScreenSettings>();
	
	// We can show or not show in editor:
	if (GIsEditor && !LoadingScreenSettings->bShouldShowLoadingScreenInEditor) return false;
	
	// Check if the objects in world need a loading screen:
	if (CheckTheNeedToShowLoadingScreen())
	{
		GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = true;
		return true;
	}
	
	CurrentLoadingReason = TEXT("Waiting for Texture Streaming");
	// There's no need to show the loading screen. Allow the world to be rendered to our viewport here
	GetGameInstance()->GetGameViewportClient()->bDisableWorldRendering = false;
	
	// Below Code is wait extra time to get rid of the Blurry Textures:
	const float CurrentTime = FPlatformTime::Seconds();
	
	if (HoldLoadingScreenStartUpTime < 0.f)
	{
		HoldLoadingScreenStartUpTime = CurrentTime;
	}

	if (const float ElapsedTime = CurrentTime - HoldLoadingScreenStartUpTime; 
		ElapsedTime < LoadingScreenSettings->HoldLoadingScreenExtraSeconds)
	{
		return true;
	}
	return false;
}

bool UUILoadingScreenSubsystem::CheckTheNeedToShowLoadingScreen()
{
	if (bIsCurrentlyLoadingMap)
	{
		CurrentLoadingReason = TEXT("Loading Level");

		return true;
	}

	UWorld* OwningWorld = GetGameInstance()->GetWorld();

	if (!OwningWorld)
	{
		CurrentLoadingReason = TEXT("Initializing World");

		return true;
	}

	if (!OwningWorld->HasBegunPlay())
	{
		CurrentLoadingReason = TEXT("World hasn't begun play yet");

		return true;
	}

	if (!OwningWorld->GetFirstPlayerController())
	{
		CurrentLoadingReason = TEXT("Player Controller is not valid yet");

		return true;
	}

	//Check if the game states, player states, or player character, actor component are ready

	return false;
}

void UUILoadingScreenSubsystem::TryDisplayLoadingScreenIfNone()
{
	// If there's already active loading screen, return early if yes:
	if (CachedCreatedLoadingScreenWidget) return;
	
	const UUILoadingScreenSettings* LoadingScreenSettings = GetDefault<UUILoadingScreenSettings>();
	
	TSubclassOf<UUserWidget> LoadingWidgetClass = LoadingScreenSettings->GetLoadingScreenWidgetClassChecked();
	
	UUserWidget* CreatedWidget = UUserWidget::CreateWidgetInstance(*GetGameInstance(), LoadingWidgetClass, NAME_None);
	
	check(CreatedWidget);
	
	CachedCreatedLoadingScreenWidget = CreatedWidget->TakeWidget();
	
	GetGameInstance()->GetGameViewportClient()->AddViewportWidgetContent(
		CachedCreatedLoadingScreenWidget.ToSharedRef(),
		1000
	);
	
	NotifyLoadingScreenVisibilityChanged(true);
}

void UUILoadingScreenSubsystem::TryRemoveLoadingScreen()
{
	if (!CachedCreatedLoadingScreenWidget) return;
	
	GetGameInstance()->GetGameViewportClient()->RemoveViewportWidgetContent(CachedCreatedLoadingScreenWidget.ToSharedRef());
	CachedCreatedLoadingScreenWidget.Reset(); // Free the memory Allocated to it: otherwise it will always be present in this GameInstance class:
}

void UUILoadingScreenSubsystem::NotifyLoadingScreenVisibilityChanged(bool bIsVisible)
{
	for (ULocalPlayer* ExistingPlayer : GetGameInstance()->GetLocalPlayers())
	{
		if (!ExistingPlayer) continue;;
		
		if (APlayerController* PC = ExistingPlayer->GetPlayerController(GetGameInstance()->GetWorld()))
		{
			if (PC->Implements<UWarriorLoadingScreenInterface>())
			{
				if (bIsVisible)
				{
					IWarriorLoadingScreenInterface::Execute_OnLoadingScreenActivated(PC);
				}
				else
				{
					IWarriorLoadingScreenInterface::Execute_OnLoadingScreenDeactivated(PC);
				}
			}
			
			if (APawn* OwningPawn = PC->GetPawn())
			{
				if (OwningPawn->Implements<UWarriorLoadingScreenInterface>())
				{
					if (bIsVisible)
					{
						IWarriorLoadingScreenInterface::Execute_OnLoadingScreenActivated(PC);
					}
					else
					{
						IWarriorLoadingScreenInterface::Execute_OnLoadingScreenDeactivated(PC);
					}
				}
			}
			
			//The code for notifying other objects in the world goes here
		}
	}
}
