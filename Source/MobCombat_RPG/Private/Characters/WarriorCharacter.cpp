// Priyanshu Shukla All Rights Reserved

#include "Characters/WarriorCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "WarriorDebugHelper.h"
#include "WarriorGamePlayTags.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/Input/WarriorInputComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "DataAssets/Input/DA_InputConfig.h"
#include "DataAssets/StartupData/DA_StartupHeroData.h"
#include "DeveloperSettings/WarriorGameUserSettings.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameModes/RPGGameModeBase.h"
#include "WarriorTypes/WarriorEnumsType.h"

AWarriorCharacter::AWarriorCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	CameraKun = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraKun->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraKun->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
	
	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));
}

UPawnCombatComponent* AWarriorCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* AWarriorCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* AWarriorCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void AWarriorCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (WarriorAbilitySystemComponent && WarriorAttributeSet)
	{
		// const FString AscText = FString::Printf(TEXT("Owner Actor: %s, Avatar Actor: %s"), *WarriorAbilitySystemComponent->GetOwnerActor()->GetActorLabel(), *WarriorAbilitySystemComponent->GetAvatarActor()->GetActorLabel());
		// Debug::Print(TEXT("Ability System Component Valid.") + AscText, FColor::Green);
		// Debug::Print(TEXT("AttributeSet Valid.") + AscText, FColor::Green);

		if (UDA_StartupHeroData* LoadedData = Cast<UDA_StartupHeroData>(CharacterStartupData.LoadSynchronous()))
		{
			int32 AbilityApplyLevel = 1;

			if (UWarriorGameUserSettings* UserSettings = UWarriorGameUserSettings::Get())
			{
				const FString CurrentDifficulty = UserSettings->GetCurrentGameDifficulty();

				if (CurrentDifficulty.Equals(TEXT("Easy"), ESearchCase::IgnoreCase))
				{
					AbilityApplyLevel = 4;
				}
				else if (CurrentDifficulty.Equals(TEXT("Normal"), ESearchCase::IgnoreCase))
				{
					AbilityApplyLevel = 3; 
				}
				else if (CurrentDifficulty.Equals(TEXT("Hard"), ESearchCase::IgnoreCase))
				{
					AbilityApplyLevel = 2;
				}
				else if (CurrentDifficulty.Equals(TEXT("Extreme"), ESearchCase::IgnoreCase))
				{
					AbilityApplyLevel = 1;
				}
			}
			
			LoadedData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent, AbilityApplyLevel);
		}
	}
}

void AWarriorCharacter::BeginPlay()
{
	Super::BeginPlay();

	Debug::Print("Started");
}

void AWarriorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfig->DefaultMappingContext, 0);

	UWarriorInputComponent* WarriorInputComponent = CastChecked<UWarriorInputComponent>(PlayerInputComponent);

	// Binding on basis of Tags:
	WarriorInputComponent->BindNativeInputAction(InputConfig, WarriorGamePlayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	WarriorInputComponent->BindNativeInputAction(InputConfig, WarriorGamePlayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	WarriorInputComponent->BindNativeInputAction(InputConfig, WarriorGamePlayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);
	WarriorInputComponent->BindNativeInputAction(InputConfig, WarriorGamePlayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	WarriorInputComponent->BindNativeInputAction(InputConfig, WarriorGamePlayTags::InputTag_PickUp_Stones, ETriggerEvent::Started, this, &ThisClass::Input_PickUp_StonesStarted);
	
	// Binding on basis of Events:
	WarriorInputComponent->BindAbilityInputAction(InputConfig, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);	
}

void AWarriorCharacter::Input_Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.0f);

	// if (MovementVector.Y != 0.f)
	// {
	// 	const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
	// 	AddMovementInput(ForwardDirection, MovementVector.Y);
	// }
	//
	// if (MovementVector.X != 0.f)
	// {
	// 	const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
	// 	AddMovementInput(RightDirection, MovementVector.X);
	// }
	
	const FVector ForwardDirection = FRotationMatrix(MovementRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	
	const FVector RightDirection = FRotationMatrix(MovementRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AWarriorCharacter::Input_Look(const FInputActionValue& Value)
{
	const FVector2D LookDirection = Value.Get<FVector2D>();

	if (LookDirection.X != 0.f)
	{
		AddControllerYawInput(LookDirection.X);
	}
	if (LookDirection.Y != 0.f)
	{
		AddControllerPitchInput(LookDirection.Y);
	}
}

void AWarriorCharacter::Input_SwitchTargetTriggered(const FInputActionValue& Value)
{
	SwitchDirection = Value.Get<FVector2D>();
}

void AWarriorCharacter::Input_SwitchTargetCompleted(const FInputActionValue& Value)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X>0.f ? WarriorGamePlayTags::Player_Event_SwitchTarget_Right : WarriorGamePlayTags::Player_Event_SwitchTarget_Left,
		Data
	);
}

void AWarriorCharacter::Input_PickUp_StonesStarted(const FInputActionValue& Value)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		WarriorGamePlayTags::Player_Event_ConsumeStones,
		Data
	);
}

void AWarriorCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	WarriorAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AWarriorCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	WarriorAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

