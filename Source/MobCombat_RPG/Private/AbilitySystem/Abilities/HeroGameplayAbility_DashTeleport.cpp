// Priyanshu Shukla All Rights Reserved


#include "AbilitySystem/Abilities/HeroGameplayAbility_DashTeleport.h"

#include "Characters/WarriorCharacter.h"
#include "Widgets/Text/ISlateEditableTextWidget.h"

void UHeroGameplayAbility_DashTeleport::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	
}

void UHeroGameplayAbility_DashTeleport::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

FVector UHeroGameplayAbility_DashTeleport::GetDashDirectionVector()
{
	AWarriorCharacter* Character = GetWarriorCharacterFromActorInfo();
	FVector Direction = Character->GetLastMovementInputVector() ;
	if (Direction.IsNearlyZero()) Direction = Character->GetActorForwardVector();
	return Direction;
}

FVector UHeroGameplayAbility_DashTeleport::CalculateDashTargetLocation()
{
	AWarriorCharacter* Character = GetWarriorCharacterFromActorInfo();
	const FVector DashDirection = Character->GetActorLocation() + GetDashDirectionVector() * MaxDashFloorDistance;
	
	return DashDirection;
}

EWarriorLocomotionDirection UHeroGameplayAbility_DashTeleport::GetActorDashDirection()
{
	const AWarriorCharacter* Character = GetWarriorCharacterFromActorInfo();
	const FVector DashDirection = GetDashDirectionVector();
	const FVector Forward = Character->GetActorForwardVector().GetSafeNormal2D();
	const FVector Right = Character->GetActorRightVector().GetSafeNormal2D();
	
	const float Angle = FMath::RadiansToDegrees(
		FMath::Atan2(FVector::DotProduct(DashDirection, Right), FVector::DotProduct(DashDirection, Forward))	
	);
	
	if (Angle >= -45.f && Angle <= 45.f)   return EWarriorLocomotionDirection::ELD_Forward;
	if (Angle > 45.f && Angle <= 135.f)    return EWarriorLocomotionDirection::ELD_Right;
	if (Angle < -45.f && Angle >= -135.f)  return EWarriorLocomotionDirection::ELD_Left;

	return EWarriorLocomotionDirection::ELD_Backward;
}
