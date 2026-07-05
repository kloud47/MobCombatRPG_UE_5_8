// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "WarriorEnemyGameplayAbility.generated.h"


class AEnemyCharacterBase;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UWarriorEnemyGameplayAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AEnemyCharacterBase* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(const TSubclassOf<UGameplayEffect>& EffectClass,const FScalableFloat& InDamageScalableFloat);
private:
	TWeakObjectPtr<AEnemyCharacterBase> CachedWarriorEnemyCharacter;
};
