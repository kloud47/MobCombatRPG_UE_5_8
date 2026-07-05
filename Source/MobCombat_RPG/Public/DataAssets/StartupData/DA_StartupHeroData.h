// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "DA_StartupHeroData.generated.h"

class UWarriorHeroGameplayAbility;
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UDA_StartupHeroData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData", meta = (TitleProperty = "InputTag"))
	TArray<FWarriorHeroAbilitySet> HeroStartupAbilitySets;
};
