// Priyanshu Shukla All Rights Reserved


#include "Characters/EnemyCharacterBase.h"

#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "DataAssets/StartupData/DA_StartupEnemyData.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameModes/RPGGameModeBase.h"
#include "Widget/WarriorWidgetBase.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,180.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));

	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());

	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftHandCollisionBox");
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightHandCollisionBox");
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
}

UPawnCombatComponent* AEnemyCharacterBase::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AEnemyCharacterBase::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AEnemyCharacterBase::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (UWarriorWidgetBase* HealthWidget = Cast<UWarriorWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject())) // Returns the user widget object displayed by this component
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void AEnemyCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// if (WarriorAttributeSet && WarriorAbilitySystemComponent)
	// {
	// }
		InitEnemyStartupData();
}

#if WITH_EDITOR
void AEnemyCharacterBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxAttachBoneName);
	}
}
#endif

void AEnemyCharacterBase::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UWarriorFunctionLibrary::IsTargetPawnHostile(this, HitPawn)) // Decides using AIController Generic TeamID
		{
			EnemyCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

void AEnemyCharacterBase::InitEnemyStartupData() const
{
	if (!CharacterStartupData.IsNull())
	{
		// Configuring the Game difficulty level:

		int32 AbilityApplyLevel = 1;

		if (ARPGGameModeBase* BaseGameMode = GetWorld()->GetAuthGameMode<ARPGGameModeBase>())
		{
			switch (BaseGameMode->GetCurrentGameDifficulty())
			{
			case EWarriorGameplayDifficulty::Easy:
				AbilityApplyLevel = 1;
				break;
			case EWarriorGameplayDifficulty::Normal:
				AbilityApplyLevel = 2;	
				break;
			case EWarriorGameplayDifficulty::Hard:
				AbilityApplyLevel = 3;
				break;
			case EWarriorGameplayDifficulty::VeryHard:
				AbilityApplyLevel = 4;
				break;
			default:
				break;	
			}
		}
		
		// Capturing a weak pointer to 'this' safely
		TWeakObjectPtr<const AEnemyCharacterBase> WeakThis(this);
		
		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			CharacterStartupData.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[AbilityApplyLevel, WeakThis]()
				{

					const AEnemyCharacterBase* StrongThis = WeakThis.Get();
				   if (!StrongThis)
				   {
					   return;
				   }
					// 2. Safely access the data through the StrongThis pointer
					if (UDA_StartupEnemyData* LoadedData = Cast<UDA_StartupEnemyData>(StrongThis->CharacterStartupData.Get()))
					{
						LoadedData->GiveToAbilitySystemComponent(StrongThis->WarriorAbilitySystemComponent, AbilityApplyLevel);
						// Debug::Print("Enemy startup data Loaded", FColor::Green);
					}
					else
					{
						Debug::Print("Failed to load Enemy startup data", FColor::Green);
					}
				})
		);
	}
}
