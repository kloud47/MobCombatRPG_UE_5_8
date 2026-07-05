// Priyanshu Shukla All Rights Reserved


#include "Components/UI/EnemyUIComponent.h"

#include "Widget/WarriorWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidgets(UWarriorWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty())
	{
		return;
	}
	
	for (UWarriorWidgetBase* DrawnWidget: EnemyDrawnWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}
	EnemyDrawnWidgets.Empty();
}
