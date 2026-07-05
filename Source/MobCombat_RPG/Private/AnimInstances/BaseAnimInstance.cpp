// Priyanshu Shukla All Rights Reserved


#include "AnimInstances/BaseAnimInstance.h"

#include "GameplayTagContainer.h"
#include "WarriorFunctionLibrary.h"

bool UBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UWarriorFunctionLibrary::NativeDoesActorHaveGameplayTag(OwningPawn,TagToCheck);
	}

	return false;
}
