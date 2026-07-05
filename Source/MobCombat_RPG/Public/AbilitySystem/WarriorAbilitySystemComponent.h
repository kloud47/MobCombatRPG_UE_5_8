// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WarriorAbilitySystemComponent.generated.h"

struct FWarriorHeroSpecialAbilitySet;
struct FWarriorHeroAbilitySet;
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UWarriorAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	// On Equip grant Hero weapon abilities: ----------------------------------
	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability", meta = (ApplyLevel = 1))
	void GrantHeroWeaponAbilities(const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities, const TArray<FWarriorHeroSpecialAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel,
		TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	// On Unequip remove Hero weapon abilities: ----------------------------------
	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	void RemoveGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandleToRemove);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability") // Code used in trying to activate Melee ability  of enemies:
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);
};