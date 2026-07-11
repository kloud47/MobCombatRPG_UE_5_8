// Priyanshu Shukla All Rights Reserved


#include "Widget/UUITabListWidgetBase.h"

#include "Editor/WidgetCompilerLog.h"
#include "Widget/UICommonButtonBase.h"

#if WITH_EDITOR	
void UUUITabListWidgetBase::RequestRegisterTab(const FName& InTabID, const FText& InTabDisplayName)
{
	RegisterTab(InTabID, TabButtonEntryWidgetClass, nullptr);
	
	// Once we Created/Registered the Tab button now we Name it:
	if (UUICommonButtonBase* FoundButton = Cast<UUICommonButtonBase>(GetTabButtonBaseByID(InTabID)))
	{
		FoundButton->SetButtonText(InTabDisplayName);
	}
}

void UUUITabListWidgetBase::ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);
	
	if (!TabButtonEntryWidgetClass)
	{
		CompileLog.Error(FText::FromString(
			TEXT("The variable TabButtonEntryWidgetClass has no valid entry specified. ") +
			GetClass()->GetName() + 
			TEXT(" needs a valid entry widget class to function properly")
		));
	}
}
#endif
