// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widget/OptionsMenu/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_String.generated.h"

class UUICommonRotator;
class UUICommonButtonBase;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class MOBCOMBAT_RPG_API UWidget_ListEntry_String : public UWidget_ListEntry_Base
{
	GENERATED_BODY()
	
private:
	//**** Bound WidgetS ****//
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UUICommonButtonBase* CommonButton_Decrease;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UUICommonRotator* CommonRotator_AvailableOptions;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UUICommonButtonBase* CommonButton_Increase;
};
