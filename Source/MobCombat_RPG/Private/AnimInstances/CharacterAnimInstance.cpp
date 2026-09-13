// Priyanshu Shukla All Rights Reserved


#include "AnimInstances/CharacterAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	
	if (OwningCharacter)
	{
		OwningCharacterMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningCharacterMovementComponent) return;
	
	GroundSpeed = UKismetMathLibrary::VSizeXY(OwningCharacterMovementComponent->Velocity);
	bHasAcceleration = OwningCharacterMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	IsFalling = OwningCharacterMovementComponent->IsFalling();
}
