// Priyanshu Shukla All Rights Reserved


#include "Widget/UICommonButtonBase.h"

#include "CommonTextBlock.h"
#include "Subsystems/FrontendUISubsystem.h"

void UUICommonButtonBase::SetButtonText(FText InText)
{
	if (CommonTextBlock_ButtonText && !InText.IsEmpty())
	{
		CommonTextBlock_ButtonText->SetText(bUserUpperCaseForButtonText ? InText.ToUpper() : InText);
	}
}

void UUICommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	SetButtonText(ButtonDisplayText);
}

void UUICommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();
	
	if (CommonTextBlock_ButtonText && GetCurrentTextStyleClass())
	{
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass() );
	}
}

void UUICommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();
	
	if (!ButtonDescriptionText.IsEmpty())
	{
		// Show text on Hover
		UFrontendUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, ButtonDescriptionText);
	}
}

void UUICommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();
	
	UFrontendUISubsystem::Get(this)->OnButtonDescriptionTextUpdated.Broadcast(this, FText::GetEmpty());
}
