// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DA_InputConfig.h"
#include "WarriorInputComponent.generated.h"


UCLASS()
class MOBCOMBAT_RPG_API UWarriorInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDA_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserObject* ContextObj, CallbackFunc Callback);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDA_InputConfig* InputConfig, UserObject* ContextObj, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
void UWarriorInputComponent::BindNativeInputAction(const UDA_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent,
	UserObject* ContextObj, CallbackFunc Callback)
{
	checkf(InputConfig, TEXT("InputConfig data asset was NULL, cannot proceed with Input Binding"));

	if (const UInputAction* InputAction = InputConfig->FindInputActionByTag(InputTag))
	{
		BindAction(InputAction, TriggerEvent, ContextObj, Callback);
	}
}

template <class UserObject, typename CallbackFunc>
void UWarriorInputComponent::BindAbilityInputAction(const UDA_InputConfig* InputConfig, UserObject* ContextObj, 
	CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InputConfig, TEXT("InputConfig data asset was NULL, cannot proceed with Input "));

	for (const FWarriorInputActionConfig& AbilityInputActionConfig : InputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;
		// This Input-Tag is passed for the callback function to use:
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObj, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObj, InputReleasedFunc, AbilityInputActionConfig.InputTag);
	}
}


