// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widget_ActivatableWidget.generated.h"

class AWarriorHeroController;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class MOBCOMBAT_RPG_API UWidget_ActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintPure)
	AWarriorHeroController* GetOwningPlayerController();
	
private:
	// f it's been destroyed — no dangling pointer risk, no manual "did anyone tell me this was destroyed" bookkeeping needed.
	TWeakObjectPtr<AWarriorHeroController> CachedOwningPC;
};
