// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CommonRotator.h"
#include "UICommonRotator.generated.h"

/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UUICommonRotator : public UCommonRotator
{
	GENERATED_BODY()
	
public:
	void SetSelectedOptionByText(const FText& InTextOption);
};
