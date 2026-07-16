// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "WarriorGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UWarriorGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:
	static UWarriorGameUserSettings* Get();
	
	// ********** Gameplay Collection Tab ********** //
	UFUNCTION()
	FString GetCurrentGameDifficulty() const { return CurrentGameDifficulty; };
	
	UFUNCTION()
	void SetCurrentGameDifficulty(const FString& InCurrentGameDifficulty) { CurrentGameDifficulty = InCurrentGameDifficulty; };
	// ********** Gameplay Collection Tab ********** //
	
private:
	UPROPERTY(Config)
	FString CurrentGameDifficulty;
};
