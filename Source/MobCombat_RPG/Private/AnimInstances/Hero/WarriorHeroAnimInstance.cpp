// Priyanshu Shukla All Rights Reserved


#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"

#include "Characters/WarriorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "WarriorTypes/WarriorEnumsType.h"

void UWarriorHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AWarriorCharacter>(OwningCharacter);
		OwningHeroCharacterMovementComp = OwningHeroCharacter->GetCharacterMovement();
	}
	
}

void UWarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!OwningHeroCharacter || !OwningHeroCharacterMovementComp)
	{
		return;
	}
	
	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	} else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
	
	SetVelocityData();
	SetLocationData();
	SetRotationData(DeltaSeconds);
}


void UWarriorHeroAnimInstance::SetVelocityData()
{
	CharacterVelocity = OwningHeroCharacterMovementComp->Velocity;
	CharacterVelocity2D = FVector(CharacterVelocity.X, CharacterVelocity.Y, 0.f);
}

void UWarriorHeroAnimInstance::SetLocationData()
{
	LastFrameWorldLocation = WorldLocation;
	WorldLocation = OwningHeroCharacter->GetActorLocation();
	DeltaLocation = (WorldLocation - LastFrameWorldLocation).Length();
}

void UWarriorHeroAnimInstance::SetRotationData(float DeltaTime)
{
	WorldRotation = OwningHeroCharacter->GetActorRotation();
	
	LastActorYaw = ActorYaw;
	// Saving current Yaw
	ActorYaw = WorldRotation.Yaw;
	
	DeltaActorYaw = ActorYaw - LastActorYaw;
	
	// Yaw rate (degrees per second)
	const float YawRate = DeltaActorYaw / DeltaTime;

	// Scale down by tuning constant
	const float ScaledRate = YawRate / 5.0f;
	
	float DirectionMultiplier = 0.f;
	switch (VelocityLocomotionDirection)
	{
	case EWarriorLocomotionDirection::ELD_Forward:
		DirectionMultiplier = 0.0f;
		break;
	case EWarriorLocomotionDirection::ELD_Backward:
		DirectionMultiplier = -1.0f;
		break;
	case EWarriorLocomotionDirection::ELD_Left:
		DirectionMultiplier = 0.0f;
		break;
	case EWarriorLocomotionDirection::ELD_Right:
		DirectionMultiplier = 0.0f;
		break;
	default:
		DirectionMultiplier = 0.0f;
		break;
	}
	
	const float RawLean = ScaledRate * DirectionMultiplier;
	LeanAngle = FMath::ClampAngle(RawLean, -90.0f, 90.0f);
	
	// Aim Direction used for Head Movements:
	AimPitch = TryGetPawnOwner()->GetBaseAimRotation().Pitch;
}
