// Priyanshu Shukla All Rights Reserved


#include "WarriorTypes/AsyncAction_PushConfirmScreen.h"

#include "Engine/Engine.h"
#include "Subsystems/FrontendUISubsystem.h"

UAsyncAction_PushConfirmScreen* UAsyncAction_PushConfirmScreen::PushConfirmScreen(const UObject* WorldContextObject,
                                                                                  EConfirmScreenType ScreenType, FText InScreenTitle, FText InScreenMessage)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushConfirmScreen* Node = NewObject<UAsyncAction_PushConfirmScreen>();
			Node->CachedOwningWorld = World;
			Node->CachedScreenType = ScreenType;
			Node->CachedScreenTitle = InScreenTitle;
			Node->CachedScreenMessage = InScreenMessage;
			return Node;
		}
	}
	
	return nullptr; 
}

void UAsyncAction_PushConfirmScreen::Activate()
{
	UFrontendUISubsystem* FrontendUISubsystem = UFrontendUISubsystem::Get(CachedOwningWorld.Get());
	
	FrontendUISubsystem->PushConfirmScreenToModalStackAsync(
		CachedScreenType,
		CachedScreenTitle,
		CachedScreenMessage,
		[this] (EConfirmScreenButtonType ClickedButtonType)
		{
			OnClickedButton.Broadcast(ClickedButtonType);
			
			SetReadyToDestroy();
		}
	);
}


