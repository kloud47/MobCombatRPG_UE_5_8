// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widget/OptionsMenu/ListDataObject_Base.h"
#include "ListDataObject_Collection.generated.h"

/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UListDataObject_Collection : public UListDataObject_Base
{
	GENERATED_BODY()
	
public:
	void AddChildListData(UListDataObject_Base* InChildListData);

	//~ Begin UListDataObject_Base Interface
	virtual TArray<UListDataObject_Base*> GetAllChildListData() const;
	virtual bool HasAnyChildListData() const;
	//~ End UListDataObject_Base Interface

private:
	// It contains all Child types list data like string, Enums, floats, etc.
	// And Collection here a bigger container like a Tab.
	UPROPERTY(Transient)
	TArray<UListDataObject_Base*> ChildListDataArray;
};
