// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Characters/BaseCharacter.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "WarriorTypes/WarriorEnumsType.h"
#include "WarriorCharacter.generated.h"

class UHeroUIComponent;
class UHeroCombatComponent;
struct FInputActionValue;
class UDA_InputConfig;
class UCameraComponent;
class USpringArmComponent;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API AWarriorCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AWarriorCharacter();

	//~ Begin PawnCombatInterface Interface.Add commentMore actions
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombatInterface Interface

	//~ Begin PawnUIInterface Interface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UHeroUIComponent* GetHeroUIComponent() const override;
	//~ End PawnUIInterface Interface
	
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface.
	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraKun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UHeroUIComponent* HeroUIComponent;
#pragma endregion

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDA_InputConfig> InputConfig;
	
	FVector2D SwitchDirection = FVector2D::ZeroVector;

	void Input_Move(const FInputActionValue& Value);
	void Input_WalkStart(const FInputActionValue& Value);
	void Input_WalkEnd(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_Jump_Start(const FInputActionValue& Value);
	void Input_Jump_End(const FInputActionValue& Value);

	void Input_SwitchTargetTriggered(const FInputActionValue& Value);
	void Input_SwitchTargetCompleted(const FInputActionValue& Value);

	void Input_PickUp_StonesStarted(const FInputActionValue& Value);
	
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
#pragma endregion
	
	void UpdateMovementGateFunction();
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void WalkingGateStateChange(EWarriorGate Gate);
	
	UFUNCTION(BlueprintPure)
	float GetGroundDistance(); // For Calculating Jump landings and Ground Distance: 
	
	UFUNCTION(BlueprintPure)
	FVector GetFurthestValidLocationAlongPath(FVector Start, FVector End);
	
	bool IsValidDashLocation(const FVector& Location, const TArray<FHitResult>& HitResults, const TArray<AActor*>& ActorToIgnore);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	EWarriorGate CurrentGate;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	TMap<EWarriorGate, FWarriorMovementGateData> GateSettings;
	
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }
};
