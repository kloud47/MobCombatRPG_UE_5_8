// Priyanshu Shukla All Rights Reserved


#include "DeveloperSettings/UILoadingScreenSettings.h"
#include "Blueprint/UserWidget.h"


TSubclassOf<UUserWidget> UUILoadingScreenSettings::GetLoadingScreenWidgetClassChecked() const
{
	checkf(!SoftLoadingScreenWidgetClass.IsNull(),TEXT("Forgot to assign a valid widget blueprint in the project settings as loading screen"));

	TSubclassOf<UUserWidget> LoadedLoadingScreenWidget = SoftLoadingScreenWidgetClass.LoadSynchronous();

	return LoadedLoadingScreenWidget;
}
