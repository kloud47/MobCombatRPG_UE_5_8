// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "LatentActions.h"
#include "WarriorEnumsType.h"
#include "Engine/LatentActionManager.h"

class FWarriorCountdownAction : public FPendingLatentAction
{
public:
	FWarriorCountdownAction(float InTotalCountdownTime,float InUpdateInterval,float& InOutRemainingTime,EWarriorCountDownActionOutput& InCountDownOutput,const FLatentActionInfo& LatentInfo)
		: bNeedToCancel(false)
		, TotalCountDownTime(InTotalCountdownTime)
		, UpdateInterval(InUpdateInterval)
		, OutRemainingTime(InOutRemainingTime)
		, CountDownOutput(InCountDownOutput)
		, ExecutionFunction(LatentInfo.ExecutionFunction)
		, OutputLink(LatentInfo.Linkage)
		, CallbackTarget(LatentInfo.CallbackTarget)
		, ElapsedInterval(0.f)
		, ElapsedTimeSinceStart(0.f)
	{
	}

	virtual void UpdateOperation(FLatentResponse& Response) override; // FLatentResponse => An engine struct used to evaluate and control the lifecycle of the latent action.
	
	void CancelAction();

private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	EWarriorCountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};
