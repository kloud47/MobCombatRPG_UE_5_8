// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "UICommonButtonBase.generated.h"

class UCommonTextBlock;
/** NOTE ---
 * UI elements like a button — which typically just sits there waiting for click events and doesn't need per-frame logic — ticking every frame is wasted overhead.
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class MOBCOMBAT_RPG_API UUICommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InText);
	
protected:
	// ~ Begin UUserWidget Interface 
	virtual void NativePreConstruct() override;
	// ~ End UUserWidget Interface 
	
	// ~ Begin UCommonButtonBase Interface 
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	// ~ End UCommonButtonBase Interface 
	
private:
	//**** Bound Widgets ****//
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ButtonText;
	//**** Bound Widgets ****//
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	bool bUserUpperCaseForButtonText = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Button", meta = (AllowPrivateAccess = "true"))
	FText ButtonDescriptionText;
};
