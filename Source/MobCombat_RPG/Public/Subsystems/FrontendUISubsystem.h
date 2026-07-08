// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/SoftObjectPtr.h"
#include "FrontendUISubsystem.generated.h"

struct FGameplayTag;
class UWidget_PrimaryLayout;
class UWidget_ActivatableWidget;
class UUICommonButtonBase;

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush
};

// When on button hover:
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate,UUICommonButtonBase*,BroadcastingButton,FText,DescriptionText);
/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UFrontendUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UFrontendUISubsystem* Get(const UObject* WorldContextObject);

	// Begin~ USubsystem Interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	// End~ USubsystem Interface

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(UWidget_PrimaryLayout* InCreatedWidget);

	void PushSoftWidgetToStackAynsc(const FGameplayTag& InWidgetStackTag,TSoftClassPtr<UWidget_ActivatableWidget> InSoftWidgetClass,
		TFunction<void(EAsyncPushWidgetState,UWidget_ActivatableWidget*)> AysncPushStateCallback);

	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;
	
private:
	UPROPERTY(Transient)
	UWidget_PrimaryLayout* CreatedPrimaryLayout;
};
