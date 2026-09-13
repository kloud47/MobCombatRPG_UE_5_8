	// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/BaseAnimInstance.h"
#include "CharacterAnimInstance.generated.h"

	enum class EWarriorLocomotionDirection : uint8;
class ABaseCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UCharacterAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY()
	ABaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningCharacterMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|VelocityData")
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bHasAcceleration;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float LocomotionDirection;
	
	EWarriorLocomotionDirection VelocityLocomotionDirection;
	
	UPROPERTY(BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool IsFalling;
	
};
