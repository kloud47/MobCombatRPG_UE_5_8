// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "UObject/SoftObjectPtr.h"
#include "UIDeveloperSettings.generated.h"

class UWidget_ActivatableWidget;
/**
 *
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "MobCombat UI Settings"))
class MOBCOMBAT_RPG_API UUIDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (ForceInlineRow, Categories = "UI.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<UWidget_ActivatableWidget>> FrontendWidgetMap;
	
};
