// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/CharacterAnimInstance.h"
#include "WarriorHeroAnimInstance.generated.h"

enum class EWarriorState : uint8;
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
	float DeltaActorYaw;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|RotationData")
	float ActorYaw;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|RotationData")
	float AimPitch;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|CharaStateData")
	EWarriorState CharaWeaponState;
	
private:
	void SetVelocityData();
	void SetLocationData();
	void SetRotationData(float DeltaTime);
};
