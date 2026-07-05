// Priyanshu Shukla All Rights Reserved


#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"

#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"

void UDataAsset_StartupDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive,
                                                              int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);

	ApplyGameplayEffectOnStartup(InASCToGive, ApplyLevel);
}

void UDataAsset_StartupDataBase::GrantAbilities(TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive,
	UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;

	for (const TSubclassOf<UWarriorGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}

void UDataAsset_StartupDataBase::ApplyGameplayEffectOnStartup(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (!StartupGameplayEffect.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& GE_Class : StartupGameplayEffect)
		{
			if (!GE_Class) continue;

			UGameplayEffect* GE_Class_CDO = GE_Class->GetDefaultObject<UGameplayEffect>();

			InASCToGive->ApplyGameplayEffectToSelf(
				GE_Class_CDO,
				ApplyLevel,
				InASCToGive->MakeEffectContext()
			);
		}
	}
}