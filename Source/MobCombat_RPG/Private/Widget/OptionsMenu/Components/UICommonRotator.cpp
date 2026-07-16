// Priyanshu Shukla All Rights Reserved


#include "Widget/OptionsMenu/Components/UICommonRotator.h"

#include "CommonTextBlock.h"

void UUICommonRotator::SetSelectedOptionByText(const FText& InTextOption)
{
	// FText cannot be compared with simple == or used directly in IndexOfByKey the way FString can — 
	// FText is a rich type designed around localization
	const int32 FoundIndex = TextLabels.IndexOfByPredicate(
		[InTextOption](const FText& TextItem)->bool
		{
			return TextItem.EqualTo(InTextOption);
		}
	);

	if (FoundIndex != INDEX_NONE)
	{
		SetSelectedItem(FoundIndex);
	}
	else
	{
		MyText->SetText(InTextOption);
	}
}
