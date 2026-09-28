// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "HeroGameplayAbility_DashTeleport.generated.h"

/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UHeroGameplayAbility_DashTeleport : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()
	
protected:
	//~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Dash")
	float DashDuration = 0.3f;
	
	UPROPERTY(EditDefaultsOnly, Category="Dash")
	float MaxDashFloorDistance = 100.f;
};
