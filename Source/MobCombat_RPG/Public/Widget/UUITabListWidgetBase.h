// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "UUITabListWidgetBase.generated.h"

class UUICommonButtonBase;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class MOBCOMBAT_RPG_API UUUITabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()
	
public:
	void RequestRegisterTab(const FName& InTabID,const FText& InTabDisplayName);
	
	//~ Begin UWidget Interface
#if WITH_EDITOR	
	virtual void ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const override;
#endif
	//~ End UWidget Interface
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Tab List Settings", meta = (AllowPrivateAccess = "true", ClampMin = "1", ClampMax = "10"))
	int32 DebugEditorPreviewTabCount = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontend Tab List Settings", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUICommonButtonBase> TabButtonEntryWidgetClass;
};
