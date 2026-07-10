// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Widget/Widget_ActivatableWidget.h"
#include "Widget_OptionsScreen.generated.h"

/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UWidget_OptionsScreen : public UWidget_ActivatableWidget
{
	GENERATED_BODY()
	
protected:
	//~ Begin UUserWidget Interface:
	virtual void NativeOnInitialized() override;
	//~ End UUserWidget Interface:
	
private:
	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();
	
	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;
	
	FUIActionBindingHandle ResetActionHandle;
};
