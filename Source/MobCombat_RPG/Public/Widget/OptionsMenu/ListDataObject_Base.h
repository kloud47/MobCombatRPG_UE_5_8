// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "UObject/SoftObjectPtr.h"
#include "WarriorTypes/WarriorEnumsType.h"
#include "ListDataObject_Base.generated.h"

// Created a Helper Getter Setter MACRO
#define LIST_DATA_ACCESSOR(DataType, PropertyName)\
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName; }\
	void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName; } 
/**
 * 
 */
UCLASS(Abstract)
class MOBCOMBAT_RPG_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()
	
public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnListDataModifiedDelegate, UListDataObject_Base*, EOptionsListDataModifyReason)
	FOnListDataModifiedDelegate OnListDataModified;
	
	LIST_DATA_ACCESSOR(FName,DataID)
	LIST_DATA_ACCESSOR(FText,DataDisplayName)
	LIST_DATA_ACCESSOR(FText,DescriptionRichText)
	LIST_DATA_ACCESSOR(FText,DisabledRichText)
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>,SoftDescriptionImage)
	LIST_DATA_ACCESSOR(UListDataObject_Base*,ParentData)
	
	void InitDataObject();
	
	//Empty in the base class. Child class ListDataObject_Collection should override it. The function should return all the child data a tab has
	virtual TArray<UListDataObject_Base*> GetAllChildListData() const { return TArray<UListDataObject_Base*>();}
	virtual bool HasAnyChildListData() const { return false; }
	
	void SetShouldApplySettingsImmediately(bool bShouldApplyRightAway) { bShouldApplyChangeImmediately = bShouldApplyRightAway; }
	
	//The child class should override them to provide implementations for resetting the data
	virtual bool HasDefaultValue() const { return false;}
	virtual bool CanResetBackToDefaultValue() const { return false;}
	virtual bool TryResetBackToDefaultValue() const { return false;}
	
protected:
	//Empty in base class. The child classes should override it to handle the initialization needed accordingly
	virtual void OnDataObjectInitialized();
	
	virtual void NotifyListDataModified(UListDataObject_Base* ModifiedData,EOptionsListDataModifyReason ModifyReason = EOptionsListDataModifyReason::DirectlyModified);
	
private:
	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	UListDataObject_Base* ParentData;

	// This for Saving or applying the User settings immediately:
	bool bShouldApplyChangeImmediately = false;
};
