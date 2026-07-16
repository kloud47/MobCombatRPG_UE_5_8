// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widget/OptionsMenu/ListDataObject_Value.h"
#include "ListDataObject_String.generated.h"

/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UListDataObject_String : public UListDataObject_Value
{
	GENERATED_BODY()
	
public:
	void AddDynamicOptions(const FString& InStringValue, const FText& InDisplayText);
	void AdvanceToNextOption();
	void BackToPreviousOption();
	
protected:
	//~ Begin UListDataObject_Base Interface
	virtual void OnDataObjectInitialized() override;
	//~ End UListDataObject_Base Interface
	
	bool TrySetDisplayTextFromStringValue(const FString& InStringValue);
	
	FString CurrentStringValue;
	FText CurrentDisplayText;
	TArray<FString> AvailableOptionsStringArray;
	TArray<FText> AvailableOptionsTextArray;
	
public:
	FORCEINLINE const TArray<FText>& GetAvailableOptionsTextArray() const { return AvailableOptionsTextArray; };
	FORCEINLINE FText GetCurrentDisplayText() const { return CurrentDisplayText; };
};
