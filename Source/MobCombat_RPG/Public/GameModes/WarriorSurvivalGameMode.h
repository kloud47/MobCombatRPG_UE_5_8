// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameModes/RPGGameModeBase.h"
#include "WarriorSurvivalGameMode.generated.h"

class UDataTable;
class AEnemyCharacterBase;

UENUM(BlueprintType)
enum class EWarriorSurvivalGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesDone,
	PlayerDied
};

USTRUCT(BlueprintType)
struct FWarriorEnemyWaveSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AEnemyCharacterBase> SoftEnemyclassToSpawn;

	UPROPERTY(EditAnywhere)
    int32 MinPerSpawnCount = 1;

    UPROPERTY(EditAnywhere)
    int32 MaxPerSpawnCount = 3;
};

USTRUCT()
struct FWarriorSurvivalGameModeSpawnerRowTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FWarriorEnemyWaveSpawnerInfo> EnemyWaveSpawnerDefinitions;

	UPROPERTY(EditAnywhere)
	int32 TotalEnemyToSpawnThisWave = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivalGameModeStateChanged, EWarriorSurvivalGameModeState, CurrentState);
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API AWarriorSurvivalGameMode : public ARPGGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState InState);
	bool HasFinishedAllWaves() const;
	void PreLoadNextWaveEnemies();
	FWarriorSurvivalGameModeSpawnerRowTable* GetCurrentSpawnerRowTable() const;
	int32 TrySpawnWaveEnemies();
	bool ShouldKeepSpawnEnemies() const;

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);
	
	UPROPERTY()
	EWarriorSurvivalGameModeState CurrentSurvivalGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeStateChanged OnSurvivalGameModeStateChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WaveDefinitions", meta=(AllowPrivateAccess=true))
	UDataTable* EnemyWaveSpawnerDataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
    int32 TotalWavesToSpawn;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
    int32 CurrentWaveCount = 1;

	UPROPERTY()
    int32 CurrentSpawnedEnemiesCounter = 0;

    UPROPERTY()
    int32 TotalSpawnedEnemiesThisWaveCounter = 0;

    UPROPERTY()
    TArray<AActor*> TargetPointsArray; // Array of points where spawning will take place:

    UPROPERTY()
    float TimePassedSinceStart = 0.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
    float SpawnNewWaveWaitTime = 5.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
    float SpawnEnemiesDelayTime = 2.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
    float WaveCompletedWaitTime = 5.f;

	// Async loaded class can be called using Enemy Class type:
	UPROPERTY()
	TMap<TSoftClassPtr<AEnemyCharacterBase>, UClass*> PreloadedEnemyClassMap; 
};
