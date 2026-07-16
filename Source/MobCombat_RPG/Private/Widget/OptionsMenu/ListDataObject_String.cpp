// Priyanshu Shukla All Rights Reserved


#include "Widget/OptionsMenu/ListDataObject_String.h"

#include "WarriorDebugHelper.h"
#include "Widget/OptionsMenu/OptionsDataInteractionHelper.h"

void UListDataObject_String::AddDynamicOptions(const FString& InStringValue, const FText& InDisplayText)
{
	AvailableOptionsStringArray.Add(InStringValue);
	AvailableOptionsTextArray.Add(InDisplayText);
}

void UListDataObject_String::AdvanceToNextOption()
{
	if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty()) return;
	
	const int32 CurrentDisplayIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 NextIndexTODisplay = CurrentDisplayIndex + 1;
	
	if (AvailableOptionsStringArray.IsValidIndex(NextIndexTODisplay))
	{
		CurrentStringValue = AvailableOptionsStringArray[NextIndexTODisplay];
	} else
	{
		CurrentStringValue = AvailableOptionsStringArray[0];
	}
	
	TrySetDisplayTextFromStringValue(CurrentStringValue);
	
	if (DataDynamicSetter)
	{
		// Notify the Dynamic Setter to set the Value in User Settings:
		DataDynamicSetter->SetValueFromString(CurrentStringValue);
		
		// Broadcast notifying the widget class that Data has been modified:
		NotifyListDataModified(this);
	}
}

void UListDataObject_String::BackToPreviousOption()
{
	if (AvailableOptionsStringArray.IsEmpty() || AvailableOptionsTextArray.IsEmpty()) return;

	const int32 CurrentDisplayIndex = AvailableOptionsStringArray.IndexOfByKey(CurrentStringValue);
	const int32 PreviousIndexToDisplay = CurrentDisplayIndex - 1;

	if (AvailableOptionsStringArray.IsValidIndex(PreviousIndexToDisplay))
	{
		CurrentStringValue = AvailableOptionsStringArray[PreviousIndexToDisplay];
	}
	else
	{
		CurrentStringValue = AvailableOptionsStringArray.Last();
	}

	TrySetDisplayTextFromStringValue(CurrentStringValue);
	if (DataDynamicSetter)
	{
		// Notify the Dynamic Setter to set the Value in User Settings:
		DataDynamicSetter->SetValueFromString(CurrentStringValue);
		
		// Broadcast notifying the widget class that Data has been modified:
		NotifyListDataModified(this);
	}
}

void UListDataObject_String::OnDataObjectInitialized()
{
	if (!AvailableOptionsStringArray.IsEmpty())
	{
		CurrentStringValue = AvailableOptionsStringArray[0];
	}
	
	// TODO::Read from the saved string value and use it to set the CurrentStringValue
	if (DataDynamicGetter)
	{
		if (!DataDynamicGetter->GetValueAsString().IsEmpty())
		{
			CurrentStringValue = DataDynamicGetter->GetValueAsString();
		}
	}
	
	if (!TrySetDisplayTextFromStringValue(CurrentStringValue))
	{
		CurrentDisplayText = FText::FromString(TEXT("Invalid Option"));
	}
}

bool UListDataObject_String::TrySetDisplayTextFromStringValue(const FString& InStringValue)
{
	const int32 CurrentFoundIndex = AvailableOptionsStringArray.IndexOfByKey(InStringValue);
	
	if (AvailableOptionsStringArray.IsValidIndex(CurrentFoundIndex))
	{
		CurrentDisplayText = AvailableOptionsTextArray[CurrentFoundIndex];
		return true;
	}
	
	return false;
}
