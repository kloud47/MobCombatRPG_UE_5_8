// Priyanshu Shukla All Rights Reserved


#include "Widget/Widget_ActivatableWidget.h"
#include "Controllers/WarriorHeroController.h"


AWarriorHeroController* UWidget_ActivatableWidget::GetOwningPlayerController()
{
	if (!CachedOwningPC.IsValid())
	{
		CachedOwningPC = GetOwningPlayer<AWarriorHeroController>();
	}
	
	return CachedOwningPC.IsValid() ? CachedOwningPC.Get() : nullptr;
}
