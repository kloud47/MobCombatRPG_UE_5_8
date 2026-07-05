// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_OrientToTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class MOBCOMBAT_RPG_API UBTService_OrientToTargetActor : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_OrientToTargetActor();

	//~ Begin UBTNode InterfaceAdd commentMore actions
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	//~ End UBTNode Interface

	UPROPERTY(EditAnywhere, Category = "Target")
	float RotationInterpSpeed;

	UPROPERTY(EditAnywhere, Category = "Target")
	FBlackboardKeySelector InTargetActorKey;
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
