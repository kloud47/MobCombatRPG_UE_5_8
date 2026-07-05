// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "WarriorHeroController.generated.h"

/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API AWarriorHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AWarriorHeroController();
    
    //~ Begin IGenericTeamAgentInterface Interface.
    virtual FGenericTeamId GetGenericTeamId() const override;
    //~ End IGenericTeamAgentInterface Interface.

	//~ Begin APlayerController Interface.
	virtual void OnPossess(APawn* InPawn) override;
	//~ End APlayerController Interface.
    
private:
    FGenericTeamId HeroTeamID;
};
