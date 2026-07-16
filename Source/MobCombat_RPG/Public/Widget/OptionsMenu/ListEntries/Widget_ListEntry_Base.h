// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "WarriorTypes/WarriorEnumsType.h"
#include "Widget_ListEntry_Base.generated.h"

class UListDataObject_Base;
class UCommonTextBlock;
/**
 * IUserObjectListEntry is an interface (not a full base class) in Unreal's UMG list system — 
 * implemented by row widgets used inside UListView/UTileView/similar list-based widgets. 
 * It's the bridge between "generic data object" and "the actual widget row that displays that data."
 * 
 * This is a required interface for creating any kind of List Item inside listView:
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class MOBCOMBAT_RPG_API UWidget_ListEntry_Base : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On List Entry Widget Hovered"))
	void BP_OnListEntryWidgetHovered(bool bWasHovered,bool bIsEntryWidgetStillSelected);
	void NativeOnListEntryWidgetHovered(bool bWasHovered);
	
protected:
	//~ Begin IUserObjectListEntry Interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	//~ End IUserObjectListEntry Interface
	
	// The Child class should override this function to handle the initialization needed. Super call is expected 
	virtual void OnOwningListDataObjectSet(UListDataObject_Base* InOwningListDataObject);
	
	virtual void OnOwningListDataObjectModified(UListDataObject_Base* OwningModifiedData, EOptionsListDataModifyReason ModifyReason);
	
	void SelectThisEntryWidget();
	
private:
	//***** Bound Widgets ***** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional,AllowPrivateAccess = "true"))
	UCommonTextBlock* CommonText_SettingDisplayName;
	//***** Bound Widgets ***** //
};
