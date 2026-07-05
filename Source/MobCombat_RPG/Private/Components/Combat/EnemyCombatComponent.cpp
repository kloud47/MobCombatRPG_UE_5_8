// Priyanshu Shukla All Rights Reserved


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGamePlayTags.h"
#include "Characters/EnemyCharacterBase.h"
#include "Components/BoxComponent.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);

	// Implement block check
    bool bIsValidBlock = false;

	// Activation Owned Tag => Player_Status_Blocking:
    const bool bIsPlayerBlocking = UWarriorFunctionLibrary::NativeDoesActorHaveGameplayTag(HitActor, WarriorGamePlayTags::Player_Status_Blocking);
    const bool bIsMyAttackUnblockable = UWarriorFunctionLibrary::NativeDoesActorHaveGameplayTag(GetOwningPawn(), WarriorGamePlayTags::Enemy_Status_Unblockable);

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
    {
		// valid only if both are facing each-other:
		bIsValidBlock = UWarriorFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
    }

	FGameplayEventData EventDataPayload;
	EventDataPayload.Instigator = GetOwningPawn();
	EventDataPayload.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			WarriorGamePlayTags::Player_Event_SuccessfulBlock,
			EventDataPayload
		);
	} else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			WarriorGamePlayTags::Shared_Event_MeleeHit,
			EventDataPayload
		);
	}
}

void UEnemyCombatComponent::ToggleBodyBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AEnemyCharacterBase* OwningEnemyCharacter = GetOwningPawn<AEnemyCharacterBase>();
	check(OwningEnemyCharacter);

	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();
	check(LeftHandCollisionBox && RightHandCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}
