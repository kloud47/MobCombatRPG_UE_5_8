// Priyanshu Shukla All Rights Reserved


#include "WarriorTypes/AsyncAction_PushSoftWidget.h"

#include "Engine/Engine.h"

UAsyncAction_PushSoftWidget* UAsyncAction_PushSoftWidget::PushSoftWidget(UObject* WorldContextObject,
                 APlayerController* OwningPlayerController, TSoftClassPtr<UWidget_ActivatableWidget> InSoftWidgetClass,
                 UPARAM(meta = (Categories = "UI.WidgetStack")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(),TEXT("PushSoftWidgetToStack was passed a null soft widget class "));

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UAsyncAction_PushSoftWidget* Node = NewObject<UAsyncAction_PushSoftWidget>();

			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}

void UAsyncAction_PushSoftWidget::Activate()
{
	Super::Activate();
}
