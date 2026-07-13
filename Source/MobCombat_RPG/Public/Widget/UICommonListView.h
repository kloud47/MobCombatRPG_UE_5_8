// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonListView.h"
#include "UICommonListView.generated.h"

class UDataAsset_DataListEntryMapping;
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UUICommonListView : public UCommonListView
{
	GENERATED_BODY()
public:
	//~ Begin UWidget Interface
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif
	//~ End UWidget Interface
	
protected:
	//~ Begin UCommonListView Interface
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;
	//~ End UCommonListView Interface
	
private:
	UPROPERTY(EditAnywhere, Category="Frontend List View Settings")
	TObjectPtr<UDataAsset_DataListEntryMapping> DataListEntryMapping;
};
