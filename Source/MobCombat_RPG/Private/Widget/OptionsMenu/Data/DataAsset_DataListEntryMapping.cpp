// Priyanshu Shukla All Rights Reserved


#include "Widget/OptionsMenu/Data/DataAsset_DataListEntryMapping.h"

#include "Widget/OptionsMenu/ListDataObject_Base.h"

TSubclassOf<UWidget_ListEntry_Base> UDataAsset_DataListEntryMapping::FindEntryWidgetClassByDataObject(
	UListDataObject_Base* InDataObject) const
{
	check(InDataObject);
	
	// We are just finding the ListEntry_Widget Class associated here not the data inside:
	for (UClass* DataObjectClass = InDataObject->GetClass(); DataObjectClass; DataObjectClass = DataObjectClass->GetSuperClass())
	{
		if (TSubclassOf<UListDataObject_Base> ConvertedDataObjectClass = TSubclassOf<UListDataObject_Base>(DataObjectClass))
		{
			if (DataObjectListEntryMap.Contains(ConvertedDataObjectClass))
			{
				return DataObjectListEntryMap.FindRef(ConvertedDataObjectClass);
			}
		}
	}
	
	return TSubclassOf<UWidget_ListEntry_Base>();
}
