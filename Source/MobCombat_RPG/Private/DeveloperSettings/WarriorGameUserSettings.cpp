// Priyanshu Shukla All Rights Reserved


#include "DeveloperSettings/WarriorGameUserSettings.h"

UWarriorGameUserSettings* UWarriorGameUserSettings::Get()
{
	if (GEngine)
	{
		return CastChecked<UWarriorGameUserSettings>(GEngine->GetGameUserSettings());
	}
	
	return nullptr;
}
