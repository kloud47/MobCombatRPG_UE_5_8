// Priyanshu Shukla All Rights Reserved


#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "WarriorDebugHelper.h"
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
		
		if (OwningHeroCharacter && OwningHeroCharacterMovementComp)
		{
			// Seed rotation/location so the first frame doesn't compute garbage deltas
			WorldLocation = OwningHeroCharacter->GetActorLocation();
			LastFrameWorldLocation = WorldLocation;

			WorldRotation = OwningHeroCharacter->GetActorRotation();
			ActorYaw = WorldRotation.Yaw;
			LastActorYaw = ActorYaw;

			// Seed locomotion direction using the character's actual starting velocity/rotation,
			// rather than leaving it at the enum's default value
			VelocityLocomotionAngle = UKismetAnimationLibrary::CalculateDirection(
				FVector(OwningHeroCharacterMovementComp->Velocity.X, OwningHeroCharacterMovementComp->Velocity.Y, 0.f),
				WorldRotation);

			VelocityLocomotionDirection = CalculateLocomotionDirection(VelocityLocomotionAngle, EWarriorLocomotionDirection::ELD_Forward, 20.f);
			AccelerationLocomotionDirection = VelocityLocomotionDirection;
			LastFrameLocomotionDirection = VelocityLocomotionDirection;
		}
	}
}

// there's no attribute, macro, or UFUNCTION specifier that marks a C++ function as "thread safe." 
// It's purely on you to write code inside it that's actually safe to run off the game thread
void UWarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!OwningHeroCharacter || !OwningHeroCharacterMovementComp)
	{
		return;
	}
	
	// if (bHasAcceleration)
	// {
	// 	IdleElapsedTime = 0.f;
	// 	bShouldEnterRelaxState = false;
	// } else
	// {
	// 	IdleElapsedTime += DeltaSeconds;
	// 	bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	// }
	
	SetVelocityData();
	SetLocationData();
	SetRotationData(DeltaSeconds);
	SetAccelerationData();
	SetGaitData(DeltaSeconds);
	UpdateOrientationData();
	UpdateRootYawOffset(DeltaSeconds);
	Debug::Print("DEg : ", RootYawOffset, 1);
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
		DirectionMultiplier = 1.0f;
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
	AimPitch = OwningHeroCharacter->GetBaseAimRotation().Pitch;
}

void UWarriorHeroAnimInstance::SetAccelerationData()
{
	Acceleration = OwningHeroCharacterMovementComp->GetCurrentAcceleration();
	Acceleration2D = FVector(Acceleration.X, Acceleration.Y, 0.f);
	IsAccelerating = Acceleration2D.Length() > 0.f;
}

void UWarriorHeroAnimInstance::SetGaitData(float DeltaTime)
{
	// Walk and Jog
	LastFrameGate = CurrentGait;
	CurrentGait = IncomingGait;
	IsGateChanged = CurrentGait != LastFrameGate;
	
	// Jump
	IsOnAir = OwningHeroCharacterMovementComp->MovementMode == EMovementMode::MOVE_Falling;
	IsJumping = (CharacterVelocity.Z > 0.f) & IsOnAir;
	IsCharaFalling = (CharacterVelocity.Z < 0.f) & IsOnAir;
	
	if (IsJumping)
	{
		TimeToJumpApex = (CharacterVelocity.Z*-1) / (OwningHeroCharacterMovementComp->GetGravityZ() * OwningHeroCharacterMovementComp->GravityScale);
	}
}

void UWarriorHeroAnimInstance::UpdateOrientationData()
{
	LastFrameLocomotionDirection = VelocityLocomotionDirection;
	
	// Required for Orientation warping:
	VelocityLocomotionAngle = UKismetAnimationLibrary::CalculateDirection(CharacterVelocity2D, WorldRotation);
	AccelerationLocomotionAngle = CalculateDirection(Acceleration2D, WorldRotation);
	VelocityLocomotionAngleWithOffset = UKismetMathLibrary::NormalizeAxis(VelocityLocomotionAngle - RootYawOffset); // Compensating for the New RootOffsetYaw in the Root Bone:
	VelocityLocomotionDirection = CalculateLocomotionDirection(VelocityLocomotionAngle, VelocityLocomotionDirection, 20.f);
	AccelerationLocomotionDirection = CalculateLocomotionDirection(AccelerationLocomotionAngle, AccelerationLocomotionDirection, 20.f);
}

EWarriorLocomotionDirection UWarriorHeroAnimInstance::CalculateLocomotionDirection(
    float Angle,
    EWarriorLocomotionDirection CurrentDirection,
    float DeadZone)
{
    const float Buffer = DeadZone * 1.f;
    const float MaxForward = 45.f;
    const float MinForward = -MaxForward;
    const float MaxBackward = 135.f;
    const float MinBackward = -MaxBackward;

    // 1. Maintain current direction if Angle remains inside its expanded buffer zone
    switch (CurrentDirection)
    {
    case EWarriorLocomotionDirection::ELD_Forward:
        if (IsAngleInRange(Angle, MinForward, MaxForward, Buffer, true))
        {
            return EWarriorLocomotionDirection::ELD_Forward;
        }
        break;

    case EWarriorLocomotionDirection::ELD_Right:
        if (IsAngleInRange(Angle, MaxForward, MaxBackward, Buffer, true))
        {
            return EWarriorLocomotionDirection::ELD_Right;
        }
        break;

    case EWarriorLocomotionDirection::ELD_Left:
        if (IsAngleInRange(Angle, MinBackward, MinForward, Buffer, true))
        {
            return EWarriorLocomotionDirection::ELD_Left;
        }
        break;

    case EWarriorLocomotionDirection::ELD_Backward:
        if (Angle >= (MaxBackward - Buffer) || Angle <= (MinBackward + Buffer))
        {
            return EWarriorLocomotionDirection::ELD_Backward;
        }
        break;
    }

    // 2. Angle exited the active buffer zone; fall back to exact base boundaries
    const float ZeroBuffer = 0.f;

    if (IsAngleInRange(Angle, MinForward, MaxForward, ZeroBuffer, false))
    {
        return EWarriorLocomotionDirection::ELD_Forward;
    }

    if (IsAngleInRange(Angle, MaxForward, MaxBackward, ZeroBuffer, false))
    {
        return EWarriorLocomotionDirection::ELD_Right;
    }

    if (IsAngleInRange(Angle, MinBackward, MinForward, ZeroBuffer, false))
    {
        return EWarriorLocomotionDirection::ELD_Left;
    }

    return EWarriorLocomotionDirection::ELD_Backward;
}

bool UWarriorHeroAnimInstance::IsAngleInRange(
    float Angle,
    float MinAngle,
    float MaxAngle,
    float Buffer,
    bool IsCurrentlyInThisZone)
{
    // Expand the zone only when active (creates sticky hysteresis).
    // Inactive zones stay at their base boundaries so no dead-zone gaps are created.
    const float AdjustedMin = IsCurrentlyInThisZone ? (MinAngle - Buffer) : MinAngle;
    const float AdjustedMax = IsCurrentlyInThisZone ? (MaxAngle + Buffer) : MaxAngle;

    return UKismetMathLibrary::InRange_FloatFloat(Angle, AdjustedMin, AdjustedMax);
}

void UWarriorHeroAnimInstance::UpdateRootYawOffset(float DeltaTime)
{
	if (RootYawOffsetMode == EYawOffset::EYO_Accumulate)
	{
		float RYOffset = UKismetMathLibrary::NormalizeAxis(RootYawOffset + (DeltaActorYaw*-1));
		SetRootYawOffset(RYOffset);
	}
	if (RootYawOffsetMode == EYawOffset::EYO_BlendOut)
	{
		float InterpRootYaw = UKismetMathLibrary::FloatSpringInterp(RootYawOffset, 0.f, RootYawOffsetSpringState, 
			80.f, 1.f, DeltaTime, 1.f, .5f);
		SetRootYawOffset(InterpRootYaw);
	}
	RootYawOffsetMode = EYawOffset::EYO_BlendOut;
}


void UWarriorHeroAnimInstance::SetRootYawOffset(float RYO)
{
	LastFrameRootYawOffset = RootYawOffset;
	RootYawOffset = UKismetMathLibrary::NormalizeAxis(RYO);
}
