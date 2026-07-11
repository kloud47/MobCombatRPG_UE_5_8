// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Widget/Widget_ActivatableWidget.h"
#include "Widget_OptionsScreen.generated.h"

class UUUITabListWidgetBase;
class UOptionsDataRegistry;
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
	
	//~ Begin UCommonActivatableWidget Interface
	virtual void NativeOnActivated() override;
	//~ End UCommonActivatableWidget Interface

private:
	UOptionsDataRegistry* GetOrCreateDataRegistry();
	
	void OnResetBoundActionTriggered();
	void OnBackBoundActionTriggered();
	
	UFUNCTION()
	void OnOptionsTabSelected(FName TabId);
	
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UUUITabListWidgetBase* TabListWidget_OptionsTabs;
	//***** Bound Widgets ***** //
	
	//Handle the creation of data in the options screen. Direct access to this variable is forbidden
	UPROPERTY(Transient)
	UOptionsDataRegistry* CreatedOwningDataRegistry;
	
	UPROPERTY(EditDefaultsOnly, Category = "Frontend Options Screen", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle ResetAction;
	
	FUIActionBindingHandle ResetActionHandle;
};
