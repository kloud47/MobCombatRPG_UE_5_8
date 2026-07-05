// Priyanshu Shukla All Rights Reserved


#include "DataAssets/Input/DA_InputConfig.h"

const UInputAction* UDA_InputConfig::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FWarriorInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}
