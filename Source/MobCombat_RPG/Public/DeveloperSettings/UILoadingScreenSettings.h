// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Templates/SubclassOf.h"
#include "UObject/SoftObjectPtr.h"
#include "UILoadingScreenSettings.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS(Config = Game, DefaultConfig)
class MOBCOMBAT_RPG_API UUILoadingScreenSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	// Because Loading Screen Widget Can be of any child Class of UserWidget:
	TSubclassOf<UUserWidget> GetLoadingScreenWidgetClassChecked() const;

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	TSoftClassPtr<UUserWidget> SoftLoadingScreenWidgetClass;

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	float HoldLoadingScreenExtraSeconds = 3.f;

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen Settings")
	bool bShouldShowLoadingScreenInEditor = false;
};
