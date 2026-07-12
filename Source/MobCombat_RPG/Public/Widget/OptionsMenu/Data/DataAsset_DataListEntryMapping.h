// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_DataListEntryMapping.generated.h"

class UListDataObject_Base;
class UWidget_ListEntry_Base;
/**
 * A Data Map Store for [UWidget_ListEntry_Base] & [UListDataObject_Base]
 */
UCLASS()
class MOBCOMBAT_RPG_API UDataAsset_DataListEntryMapping : public UDataAsset
{
	GENERATED_BODY()
	
public:
	TSubclassOf<UWidget_ListEntry_Base> FindEntryWidgetClassByDataObject(UListDataObject_Base* InDataObject) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TMap< TSubclassOf<UListDataObject_Base>, TSubclassOf<UWidget_ListEntry_Base> > DataObjectListEntryMap;
};
