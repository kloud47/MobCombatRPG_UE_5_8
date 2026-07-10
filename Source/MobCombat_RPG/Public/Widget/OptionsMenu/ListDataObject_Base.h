// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "UObject/SoftObjectPtr.h"
#include "ListDataObject_Base.generated.h"

// Created a Helper Getter Setter MACRO
#define LIST_DATA_ACCESSOR(DataType, PropertyName)\
	FORCEINLINE DataType Get##PropertyName() const { return PropertyName; }\
	void Set##PropertyName(DataType In##PropertyName) { PropertyName = In##PropertyName; } 
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UListDataObject_Base : public UObject
{
	GENERATED_BODY()
	
public:
	LIST_DATA_ACCESSOR(FName,DataID)
	LIST_DATA_ACCESSOR(FText,DataDisplayName)
	LIST_DATA_ACCESSOR(FText,DescriptionRichText)
	LIST_DATA_ACCESSOR(FText,DisabledRichText)
	LIST_DATA_ACCESSOR(TSoftObjectPtr<UTexture2D>,SoftDescriptionImage)
	LIST_DATA_ACCESSOR(UListDataObject_Base*,ParentData)
	
	//Empty in the base class. Child class ListDataObject_Collection should override it. The function should return all the child data a tab has
	virtual TArray<UListDataObject_Base*> GetChildSettingData() const { return TArray<UListDataObject_Base*>();}
	
private:
	FName DataID;
	FText DataDisplayName;
	FText DescriptionRichText;
	FText DisabledRichText;
	TSoftObjectPtr<UTexture2D> SoftDescriptionImage;

	UPROPERTY(Transient)
	UListDataObject_Base* ParentData;
	
};
