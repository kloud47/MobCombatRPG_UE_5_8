// Priyanshu Shukla All Rights Reserved


#include "Subsystems/FrontendUISubsystem.h"

#include "WarriorFunctionLibrary.h"
#include "WarriorGamePlayTags.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Widget_PrimaryLayout.h"
#include "Engine/AssetManager.h"
#include "Widget/Widget_ActivatableWidget.h"
#include "Widget/Widget_ConfirmScreen.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UFrontendUISubsystem* UFrontendUISubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

		return UGameInstance::GetSubsystem<UFrontendUISubsystem>(World->GetGameInstance());
	}
	return nullptr;
}

bool UFrontendUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{	
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(),FoundClasses);

		return FoundClasses.IsEmpty();
	}

	return false;
}

// Registering PrimaryLayout to the Subsystem:
void UFrontendUISubsystem::RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget)
{
	check(InCreatedWidget);

	CreatedPrimaryLayout = InCreatedWidget;
}

void UFrontendUISubsystem::PushSoftWidgetToStackAynsc(const FGameplayTag& InWidgetStackTag,
	TSoftClassPtr<UWidget_ActivatableWidget> InSoftWidgetClass,
	TFunction<void(EAsyncPushWidgetState, UWidget_ActivatableWidget*)> AysncPushStateCallback)
{
	check(!InSoftWidgetClass.IsNull());

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[InSoftWidgetClass,this,InWidgetStackTag,AysncPushStateCallback]()
			{
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();

				check(LoadedWidgetClass && CreatedPrimaryLayout)

				UCommonActivatableWidgetContainerBase* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);
				
				UWidget_ActivatableWidget* CreatedWidget = FoundWidgetStack->AddWidget<UWidget_ActivatableWidget>(
					LoadedWidgetClass,
					[AysncPushStateCallback](UWidget_ActivatableWidget& CreatedWidgetInstance)
					{
						AysncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush,&CreatedWidgetInstance);
					}
				);
				AysncPushStateCallback(EAsyncPushWidgetState::AfterPush,CreatedWidget);
			}
		)
	);
}

void UFrontendUISubsystem::PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType,
	const FText& InScreenTitle, const FText& InScreenMsg,
	TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	UConfirmScreenInfoObject* CreatedInfoObject = nullptr;

	switch (InScreenType)
	{
	case EConfirmScreenType::Ok:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOKScreen(InScreenTitle,InScreenMsg);
		break;

	case EConfirmScreenType::YesNo:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle,InScreenMsg);
		break;

	case EConfirmScreenType::OKCancel:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOkCancelScreen(InScreenTitle,InScreenMsg);
		break;

	case EConfirmScreenType::Unkown:
		break;
	default:
		break;
	}
	
	check(CreatedInfoObject);
	
	// Asynchronously Load and Push to stack widget:
	PushSoftWidgetToStackAynsc(
		WarriorGamePlayTags::UI_WidgetStack_Modal,
		UWarriorFunctionLibrary::GetFrontendSOftWidgetClassByTag(WarriorGamePlayTags::UI_Widget_ConfirmScreen),
		[CreatedInfoObject, ButtonClickedCallback] (EAsyncPushWidgetState InPushState, UWidget_ActivatableWidget* PushedWidget)
		{
			if (InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UWidget_ConfirmScreen* CreatedConfirmScreen = CastChecked<UWidget_ConfirmScreen>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject,ButtonClickedCallback);
			}
		}
	);
	
}


