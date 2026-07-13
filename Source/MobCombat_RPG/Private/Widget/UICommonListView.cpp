// Priyanshu Shukla All Rights Reserved


#include "Widget/UICommonListView.h"

#include "Editor/WidgetCompilerLog.h"
#include "Widget/OptionsMenu/ListDataObject_Base.h"
#include "Widget/OptionsMenu/Data/DataAsset_DataListEntryMapping.h"
#include "Widget/OptionsMenu/ListEntries/Widget_ListEntry_Base.h"

/**
 * Overrides CommonUI's default entry-widget generation to support multiple row widget
 * types within a single list, chosen dynamically per data item rather than using one
 * fixed Entry Widget Class for every row.
 *
 * Normally a list view uses the same widget class for every entry. Here, each row's
 * widget class is looked up based on the runtime type of its data object (via
 * DataListEntryMapping), so e.g. a string setting can render as a text row while a
 * slider setting renders as a slider row, all within the same list.
 *
 * Falls back to the default entry generation in the Designer preview, since the
 * data-to-widget mapping relies on runtime game data that isn't available at design time.
 */
// UListDataObject_String    → WBP_ListEntry_TextRow
// UListDataObject_Bool      → WBP_ListEntry_Toggle
// UListDataObject_Slider    → WBP_ListEntry_Slider

UUserWidget& UUICommonListView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass,
	const TSharedRef<STableViewBase>& OwnerTable)
{
	if (IsDesignTime()) return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	
	if (TSubclassOf<UWidget_ListEntry_Base> FoundWidgetClass =  DataListEntryMapping->FindEntryWidgetClassByDataObject(CastChecked<UListDataObject_Base>(Item)))
	{
		return GenerateTypedEntry<UWidget_ListEntry_Base>(FoundWidgetClass,OwnerTable);
	} else
	{
		return Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	}
	
}

#if WITH_EDITOR	
void UUICommonListView::ValidateCompiledDefaults(class IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);
	
	if (!DataListEntryMapping)
	{
		CompileLog.Error(FText::FromString(
		TEXT("The variable DataListEntryMapping has no valid data asset assigned ") +
		GetClass()->GetName() +
		TEXT(" needs a valid data asset to function properly")	
		));
	}
}
#endif
