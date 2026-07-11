// Priyanshu Shukla All Rights Reserved


#include "Widget/Widget_OptionsScreen.h"

#include "ICommonInputModule.h"
#include "WarriorDebugHelper.h"
#include "Input/CommonUIInputTypes.h"
#include "Widget/UUITabListWidgetBase.h"
#include "Widget/OptionsMenu/ListDataObject_Collection.h"
#include "Widget/OptionsMenu/OptionsDataRegistry.h"

void UWidget_OptionsScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (!ResetAction.IsNull())
	{
		ResetActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
				ResetAction,
				true,
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnResetBoundActionTriggered)
			)	
		);
	}
	
	RegisterUIActionBinding(
			FBindUIActionArgs(
				ICommonInputModule::GetSettings().GetDefaultBackAction(),
				true,
				FSimpleDelegate::CreateUObject(this, &ThisClass::OnBackBoundActionTriggered)
			)
	);
	
	TabListWidget_OptionsTabs->OnTabSelected.AddUniqueDynamic(this, &ThisClass::UWidget_OptionsScreen::OnOptionsTabSelected);
}

void UWidget_OptionsScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	for (UListDataObject_Collection* TabCollection : GetOrCreateDataRegistry()->GetRegisteredOptionsTabCollections())
	{
		if (!TabCollection) continue;
		// On Widget Activated Create the Tabs from Code here:
		const FName TabID = TabCollection->GetDataID();
		
		if (TabListWidget_OptionsTabs->GetTabButtonBaseByID(TabID) != nullptr) continue;
		
		TabListWidget_OptionsTabs->RequestRegisterTab(TabID, TabCollection->GetDataDisplayName());
	}
}

UOptionsDataRegistry* UWidget_OptionsScreen::GetOrCreateDataRegistry()
{
	if (!CreatedOwningDataRegistry)
	{
		CreatedOwningDataRegistry = NewObject<UOptionsDataRegistry>();
		CreatedOwningDataRegistry->InitOptionsDataRegistry(GetOwningLocalPlayer());
	}
	
	checkf(CreatedOwningDataRegistry, TEXT("Data registry for options screen is not valid"));
	
	return CreatedOwningDataRegistry;
}

void UWidget_OptionsScreen::OnResetBoundActionTriggered()
{
	Debug::Print(TEXT("Reset bound action triggered"));
}

void UWidget_OptionsScreen::OnBackBoundActionTriggered()
{
	DeactivateWidget();
}

void UWidget_OptionsScreen::OnOptionsTabSelected(FName TabId)
{
	Debug::Print(TEXT("New Tab Selected. Tab ID: ") + TabId.ToString());
}
