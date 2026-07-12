// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget_ListEntry_Base.generated.h"

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
	
protected:
	//~ Begin IUserObjectListEntry Interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	//~ End IUserObjectListEntry Interface
	
private:
	//***** Bound Widgets ***** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional,AllowPrivateAccess = "true"))
	UCommonTextBlock* CommonText_SettingDisplayName;
	//***** Bound Widgets ***** //
};
