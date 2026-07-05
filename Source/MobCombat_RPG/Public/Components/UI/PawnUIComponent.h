// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate, float, NewPercent);
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UPawnUIComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable) // This is an Event-Dispatcher:
	FOnPercentChangedDelegate OnCurrentHealthChanged;
};
