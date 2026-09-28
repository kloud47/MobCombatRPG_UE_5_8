// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/CharacterAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "WarriorTypes/WarriorEnumsType.h"
#include "WarriorHeroAnimInstance.generated.h"

class AWarriorCharacter;
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UWarriorHeroAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable, Category="AnimData|YawOffsetData")
	void SetRootYawOffset(float RYO);
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	AWarriorCharacter* OwningHeroCharacter;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	UCharacterMovementComponent* OwningHeroCharacterMovementComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;

	float IdleElapsedTime;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|VelocityData")
	FVector CharacterVelocity;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|VelocityData")
	FVector CharacterVelocity2D;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocationData")
	FVector WorldLocation;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocationData")
	FVector LastFrameWorldLocation;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocationData")
	float DeltaLocation;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|RotationData")
	FRotator WorldRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|RotationData")
	float LeanAngle;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|RotationData")
	float LastActorYaw;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|RotationData")
	float DeltaActorYaw; // used for Lean Angle and Camera and root bone rotation:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|RotationData")
	float ActorYaw;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|RotationData")
	float AimPitch;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|AccelerationData")
	bool IsAccelerating;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|AccelerationData")
	FVector Acceleration;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|AccelerationData")
	FVector Acceleration2D;
	
	// UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|AccelerationData")
	// FVector PivotAcceleration2D;  -------------> Created in BP
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|GateData")
	EWarriorGate CurrentGait;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|GateData")
	EWarriorGate LastFrameGate;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|GateData")
	EWarriorGate IncomingGait;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|GateData")
	bool IsGateChanged;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float VelocityLocomotionAngle;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	EWarriorLocomotionDirection VelocityLocomotionDirection;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float VelocityLocomotionAngleWithOffset;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	EWarriorLocomotionDirection AccelerationLocomotionDirection;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float AccelerationLocomotionAngle;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	EWarriorLocomotionDirection LastFrameLocomotionDirection;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|YawOffsetData")
	float RootYawOffset;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|YawOffsetData")
	float LastFrameRootYawOffset;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|YawOffsetData")
	EYawOffset RootYawOffsetMode;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|YawOffsetData")
	float TurnYawCurveValue;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|YawOffsetData")
	float LastFrameTurnYawCurveValue;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|YawOffsetData")
	FFloatSpringState RootYawOffsetSpringState;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|JumpData")
	bool IsJumping;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|JumpData")
	bool IsCharaFalling;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|JumpData")
	bool IsOnAir;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|JumpData")
	float GroundDistance;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|JumpData")
	float TimeToJumpApex;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|JumpData")
	float TimeFalling;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(BlueprintReadWrite, Category="AnimData|CharaStateData")
	EWarriorState CharaWeaponState;
	
private:
	void SetVelocityData();
	void SetLocationData();
	void SetRotationData(float DeltaTime);
	void SetAccelerationData();
	void SetGaitData(float DeltaTime);
	void UpdateOrientationData();
	// The whole point of hysteresis is: if you're already Forward, the Forward zone should get wider (harder to leave).
	EWarriorLocomotionDirection CalculateLocomotionDirection(float Angle, EWarriorLocomotionDirection CurrentDirection, float DeadZone);
	bool IsAngleInRange(float Angle, float MinAngle, float MaxAngle, float Buffer, bool IsCurrentlyInThisZone);
	void UpdateRootYawOffset(float DeltaTime);
};
