// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widget/OptionsMenu/ListEntries/Widget_ListEntry_Base.h"
#include "Widget_ListEntry_String.generated.h"

class UListDataObject_String;
class UUICommonRotator;
class UUICommonButtonBase;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class MOBCOMBAT_RPG_API UWidget_ListEntry_String : public UWidget_ListEntry_Base
{
	GENERATED_BODY()
	
protected:
	//~ Begin UUserWidget Interface
	virtual void NativeOnInitialized() override;
	//~ End UUserWidget Interface
	
	//~ Begin UWidget_ListEntry_Base Interface
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject) override;
	virtual void OnOwningListDataObejectModified(UListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason) override;
	//~ End UWidget_ListEntry_Base Interface
	
private:
	void OnPreviousOptionButtonClicked();
	void OnNextOptionButtonClicked();
	
	//**** Bound WidgetS ****//
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UUICommonButtonBase* CommonButton_PreviousOption;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UUICommonRotator* CommonRotator_AvailableOptions;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UUICommonButtonBase* CommonButton_NextOption;
	
	UPROPERTY(Transient)
	TObjectPtr<UListDataObject_String> CachedOwningStringDataObject;
};
