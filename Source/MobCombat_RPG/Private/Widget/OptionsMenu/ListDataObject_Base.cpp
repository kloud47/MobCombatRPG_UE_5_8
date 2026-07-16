// Priyanshu Shukla All Rights Reserved


#include "Widget/OptionsMenu/ListDataObject_Base.h"

#include "DeveloperSettings/WarriorGameUserSettings.h"

void UListDataObject_Base::InitDataObject()
{
	OnDataObjectInitialized();
}

void UListDataObject_Base::OnDataObjectInitialized()
{
}

// Broadcast whenever Data is Modified in Options Screen:
void UListDataObject_Base::NotifyListDataModified(UListDataObject_Base* ModifiedData,
	EOptionsListDataModifyReason ModifyReason)
{
	OnListDataModified.Broadcast(ModifiedData,ModifyReason);
	
	if (bShouldApplyChangeImmediately)
	{
		UWarriorGameUserSettings::Get()->ApplySettings(true);
	}
}
