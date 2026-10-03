// Priyanshu Shukla All Rights Reserved


#include "WarriorFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "StaticMeshResources.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "WarriorGamePlayTags.h"
#include "Components/StaticMeshComponent.h"
#include "DeveloperSettings/UIDeveloperSettings.h"
#include "Engine/LatentActionManager.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetMathLibrary.h"
#include "WarriorTypes/WarriorCountdownAction.h"

UWarriorAbilitySystemComponent* UWarriorFunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UWarriorAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UWarriorFunctionLibrary::NativeDoesActorHaveGameplayTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UWarriorFunctionLibrary::BP_DoesActorHaveGameplayTag(AActor* InActor, FGameplayTag TagToCheck,
                                                          EWarriorConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveGameplayTag(InActor, TagToCheck) ? EWarriorConfirmType::Yes : EWarriorConfirmType::No;
}

UPawnCombatComponent* UWarriorFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* UWarriorFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	EWarriorValidType& OutValidType)
{
	UPawnCombatComponent* PawnCombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = PawnCombatComponent ? EWarriorValidType::Valid : EWarriorValidType::Invalid;

	return PawnCombatComponent;
}

bool UWarriorFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

float UWarriorFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UWarriorFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim,
	float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if (OutAngleDifference>=-45.f && OutAngleDifference <=45.f)
        {
            return WarriorGamePlayTags::Shared_Status_HitReact_Front;
        }
        else if (OutAngleDifference<-45.f && OutAngleDifference>=-135.f)
        {
            return WarriorGamePlayTags::Shared_Status_HitReact_Left;
        }
        else if (OutAngleDifference<-135.f || OutAngleDifference>135.f)
        {
            return WarriorGamePlayTags::Shared_Status_HitReact_Back;
        }
        else if(OutAngleDifference>45.f && OutAngleDifference<=135.f)
        {
            return WarriorGamePlayTags::Shared_Status_HitReact_Right;
        }
    
        return WarriorGamePlayTags::Shared_Status_HitReact_Front;
}

bool UWarriorFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(),InDefender->GetActorForwardVector());

	// Valid block when defender is generally facing attacker
	// ~95°-180° angle between their forward vectors
	return DotResult<-0.1f;
}

bool UWarriorFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	UWarriorAbilitySystemComponent* SourceASC = NativeGetWarriorASCFromActor(InInstigator);
	UWarriorAbilitySystemComponent* TargetASC = NativeGetWarriorASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data,TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UWarriorFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
	float& OutRemainingTime, EWarriorCountDownActionInput CountDownInput,
	EWarriorCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(
			WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		FLatentActionManager& Manager = World->GetLatentActionManager();

		FWarriorCountdownAction* FoundAction = Manager.FindExistingAction<FWarriorCountdownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);

		if (CountDownInput == EWarriorCountDownActionInput::Start){
			// Prevent duplicate actions on the same node
			if (FoundAction == nullptr)
			{
				Manager.AddNewAction(LatentInfo.CallbackTarget, 
									 LatentInfo.UUID,
									 new FWarriorCountdownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo));
			}
		}
		else if (CountDownInput == EWarriorCountDownActionInput::Cancel)
		{
			if (FoundAction) FoundAction->CancelAction();	
		}
	}
}

TSoftClassPtr<UWidget_ActivatableWidget> UWarriorFunctionLibrary::GetFrontendSOftWidgetClassByTag(UPARAM(meta = (Categories = "UI.Widget")) FGameplayTag InWidgetTag)
{
	const UUIDeveloperSettings* UIDeveloperSettings = GetDefault<UUIDeveloperSettings>();
	
	checkf(UIDeveloperSettings->FrontendWidgetMap.Contains(InWidgetTag),TEXT("Could not find the corresponding widget under the tag %s"),*InWidgetTag.ToString());
	
	return UIDeveloperSettings->FrontendWidgetMap.FindRef(InWidgetTag);
}

TSoftObjectPtr<UTexture2D> UWarriorFunctionLibrary::GetOptionsSoftImageByTag(UPARAM(meta = (Categories = "UI.Image")) FGameplayTag InImageTag)
{
	const UUIDeveloperSettings* UIDeveloperSettings = GetDefault<UUIDeveloperSettings>();
	
	checkf(UIDeveloperSettings->OptionsScreenSoftImageMap.Contains(InImageTag),TEXT("Could not find an image associated with tag %s"),*InImageTag.ToString());
	
	return UIDeveloperSettings->OptionsScreenSoftImageMap.FindRef(InImageTag);
}

// ---------------------( Niagara Particles )--------------------------------------------------------------------------------------------------------------------------------

/* 
 * The problem this function solves

Niagara's Mesh Data Interface lets you sample a static mesh's vertices/triangles to spawn particles from its surface (which is how the Disintegration effect works — particles 
spawn from the mesh's own geometry as it crumbles). But by default, when you sample "give me a random triangle from this mesh," Niagara doesn't know or care which material slot that 
triangle belongs to — it just picks from the whole mesh.
If your mesh has, say, 3 material slots (skin, armor, cloth), and you want each part to disintegrate with a different particle material 
(so armor crumbles into metal sparks, cloth crumbles into ash), you need a way to ask: "give me only the triangles that belong to material slot 2." 
A Static Mesh's triangle data doesn't expose that in an easy, Niagara-friendly way out of the box — that's the gap this function fills.

How it replaces manual multi-emitter setup

Without this function, the manual workaround is: create a separate Niagara emitter per material slot, and somehow manually tell each one "only use this subset 
of the mesh." That's painful and doesn't scale if an artist changes the mesh's material count later.

With this function: you call it once per material slot (passing MaterialSlotIndex), and it does the filtering in C++ instead of requiring separate manual emitter setups.
You can then feed each returned triangle list into Niagara (via a Data Interface or a Niagara array parameter) so a single emitter (or a small number of emitters, one per slot but auto-populated) 
knows exactly which triangles to sample from for that material.
*/

TArray<int32> UWarriorFunctionLibrary::GetTriangleIndicesForMaterialSlot(UStaticMeshComponent* MeshComponent,
	int32 MaterialSlotIndex, int32 LODIndex)
{
	TArray<int32> Triangles;
	
	if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponent))
	{
		if (UStaticMesh* StaticMesh = StaticMeshComponent->GetStaticMesh())
		{
			if (StaticMesh->GetRenderData() && StaticMesh->GetRenderData()->LODResources.IsValidIndex(LODIndex))
			{
				FStaticMeshLODResources& LOD = StaticMesh->GetRenderData()->LODResources[LODIndex];
				for (const FStaticMeshSection& Section : LOD.Sections) // LOD contain Sections of meshes which have diff slot index
				{
					if (Section.MaterialIndex == MaterialSlotIndex) // Check for the exact Material Slots
					{
						for (int32 TriangleIndex = 0; TriangleIndex < Section.NumTriangles; TriangleIndex++)
						{
							Triangles.Add(Section.FirstIndex / 3 + TriangleIndex); // Triangle First Indexes are in multiple of 3s
						}
					}
				}
			}
		}
	}
	return Triangles;
}

// ---------------------( Niagara Particles )--------------------------------------------------------------------------------------------------------------------------------
