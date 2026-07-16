// Priyanshu Shukla All Rights Reserved


#include "Widget/OptionsMenu/ListEntries/Widget_ListEntry_Base.h"

#include "CommonTextBlock.h"
#include "Components/ListView.h"
#include "Widget/OptionsMenu/ListDataObject_Base.h"

void UWidget_ListEntry_Base::NativeOnListEntryWidgetHovered(bool bWasHovered)
{
	BP_OnListEntryWidgetHovered(bWasHovered,IsListItemSelected());
}

void UWidget_ListEntry_Base::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	// Important for any Hover or Selected actions:
	SetVisibility(ESlateVisibility::Visible);
	
	// Initialize the Widget With Data:
	OnOwningListDataObjectSet(CastChecked<UListDataObject_Base>(ListItemObject));
}

void UWidget_ListEntry_Base::OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject)
{
	if (CommonText_SettingDisplayName)
	{
		CommonText_SettingDisplayName->SetText(InOwningListDataObject->GetDataDisplayName());
	}
	
	// Checks to see if any functions are bound to the given user object.
	if (!InOwningListDataObject->OnListDataModified.IsBoundToObject(this))
	{
		InOwningListDataObject->OnListDataModified.AddUObject(this, &ThisClass::OnOwningListDataObjectModified);
	}
}

void UWidget_ListEntry_Base::OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData,
	EOptionsListDataModifyReason ModifyReason)
{
}

// ListView Widget Manual Sselection and Highlight Code:
void UWidget_ListEntry_Base::SelectThisEntryWidget()
{
	// Returns the UObject item in the owning UListView that this entry currently represents
	CastChecked<UListView>(GetOwningListView())->SetSelectedItem(GetListItem());
}
