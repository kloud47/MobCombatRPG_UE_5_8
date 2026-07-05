// Priyanshu Shukla All Rights Reserved


#include "AbilitySystem/AbilityTasks/MyAbilityTask_ExecuteTaskOnTick.h"

UMyAbilityTask_ExecuteTaskOnTick::UMyAbilityTask_ExecuteTaskOnTick()
{
	bTickingTask = true;
}

UMyAbilityTask_ExecuteTaskOnTick* UMyAbilityTask_ExecuteTaskOnTick::ExecuteTaskOnTick(UGameplayAbility* OwningAbility)
{
	UMyAbilityTask_ExecuteTaskOnTick* Node = NewAbilityTask<UMyAbilityTask_ExecuteTaskOnTick>(OwningAbility);
	return Node;	
}

void UMyAbilityTask_ExecuteTaskOnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTaskTick.Broadcast(DeltaTime);
	} else
	{
		EndTask();
	}
}
