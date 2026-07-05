// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameModeBase.generated.h"

enum class EWarriorGameplayDifficulty : uint8;
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API ARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ARPGGameModeBase();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Game Setting")
	EWarriorGameplayDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE EWarriorGameplayDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
};