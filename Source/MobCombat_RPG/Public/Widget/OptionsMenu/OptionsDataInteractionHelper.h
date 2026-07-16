// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PropertyPathHelpers.h"

class UWarriorGameUserSettings;
/**
 * 
 */
class MOBCOMBAT_RPG_API FOptionsDataInteractionHelper
{
public:
	FOptionsDataInteractionHelper(const FString& InSetterOrGetterFuncPath);
	
	FString GetValueAsString() const;
	void SetValueFromString(const FString& InStringValue);
	
private:
	FCachedPropertyPath CachedDynamicFunctionPath;
	
	// TWeakObjectPtr detects if the object has been destroyed. You can safely call .IsValid() or .Get() on it. 
	// If the object is gone, it returns nullptr instead of crashing.
	TWeakObjectPtr<UWarriorGameUserSettings> CachedWeakGameUserSettings;
};
