// Priyanshu Shukla All Rights Reserved


#include "Widget/OptionsMenu/ListEntries/Widget_ListEntry_String.h"

#include "WarriorDebugHelper.h"
#include "Widget/UICommonButtonBase.h"
#include "Widget/OptionsMenu/ListDataObject_Base.h"
#include "Widget/OptionsMenu/ListDataObject_String.h"
#include "Widget/OptionsMenu/Components/UICommonRotator.h"

void UWidget_ListEntry_String::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	CommonButton_NextOption->OnClicked().AddUObject(this, &ThisClass::OnNextOptionButtonClicked);
	CommonButton_PreviousOption->OnClicked().AddUObject(this, &ThisClass::OnPreviousOptionButtonClicked);
	
	CommonRotator_AvailableOptions->OnClicked().AddLambda([this](){ SelectThisEntryWidget(); });
}

void UWidget_ListEntry_String::OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject)
{
	Super::OnOwningListDataObjectSet(InOwningListDataObject);
	
	CachedOwningStringDataObject = CastChecked<UListDataObject_String>(InOwningListDataObject);
	
	// This is the code for Displaying the Values in Widget:
	CommonRotator_AvailableOptions->PopulateTextLabels(CachedOwningStringDataObject->GetAvailableOptionsTextArray());
	CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentDisplayText());
}

void UWidget_ListEntry_String::OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData,
	EOptionsListDataModifyReason ModifyReason)
{
	if (CachedOwningStringDataObject)
	{
		// Modifying the current display Text after receiving a notify broadcast in Base class
		CommonRotator_AvailableOptions->SetSelectedOptionByText(CachedOwningStringDataObject->GetCurrentDisplayText());
	}
}

void UWidget_ListEntry_String::OnPreviousOptionButtonClicked()
{
	// Debug::Print(TEXT("Previous Option Button Clicked"));
	
	if (CachedOwningStringDataObject) CachedOwningStringDataObject->BackToPreviousOption();
	SelectThisEntryWidget();
}

void UWidget_ListEntry_String::OnNextOptionButtonClicked()
{
	// Debug::Print(TEXT("Next Option Button Clicked"));
	
	if (CachedOwningStringDataObject) CachedOwningStringDataObject->AdvanceToNextOption();
	SelectThisEntryWidget();
}
