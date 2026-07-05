// Priyanshu Shukla All Rights Reserved


#include "Controllers/WarriorHeroController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "WarriorDebugHelper.h"

AWarriorHeroController::AWarriorHeroController()
{
	HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId AWarriorHeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}

void AWarriorHeroController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Debug::Print(TEXT("Warrior Hero Controller OnPossess"));
	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), FoundCameras);


	if (!FoundCameras.IsEmpty())
	{
		SetViewTarget(FoundCameras[0]);
		// Debug::Print(TEXT("Camera Possessed"));
	}
}
