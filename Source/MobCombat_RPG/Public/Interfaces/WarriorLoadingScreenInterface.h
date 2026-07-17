// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WarriorLoadingScreenInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWarriorLoadingScreenInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOBCOMBAT_RPG_API IWarriorLoadingScreenInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnLoadingScreenActivated();
	/*virtual void OnLoadingScreenActivated_Implementation();*/
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnLoadingScreenDeactivated();
	/*virtual void OnLoadingScreenDeactivated_Implementation();*/
};
