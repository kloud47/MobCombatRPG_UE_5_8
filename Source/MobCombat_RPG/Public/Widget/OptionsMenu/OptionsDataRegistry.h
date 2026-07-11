// Priyanshu Shukla All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OptionsDataRegistry.generated.h"

class UListDataObject_Collection;
/**
 * Contains all Options Tabs and Data Inside them:
 */
UCLASS()
class MOBCOMBAT_RPG_API UOptionsDataRegistry : public UObject
{
	GENERATED_BODY()
	
public:
	//Gets called by options screen right after the object of type UOptionsDataRegistry is created
	void InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer);

	const TArray<UListDataObject_Collection*>& GetRegisteredOptionsTabCollections() const { return RegisteredOptionsTabCollections;}
private:
	void InitGameplayCollectionTab();
	void InitAudioCollectionTab();
	void InitVideoCollectionTab();
	void InitControlCollectionTab();

	UPROPERTY(Transient) // List of All Tab collections:
	TArray<UListDataObject_Collection*> RegisteredOptionsTabCollections;
};
