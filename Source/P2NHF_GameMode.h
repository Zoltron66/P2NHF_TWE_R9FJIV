// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_GameMode.h
* 
* [HU]
* Az osztaly leirasa:
* - Ez az osztaly osszesen annyit csinal, hogy az Enginnel "kozli",
*   hogy mely osztalyokat kell hasznalnia a jatekos karakterehez,
*   jatekos karakterenek iranyitasahoz es a HUD-hoz.
*   
* [EN]
* Class description:
* - All this class does is tell the Enginel which classes should be 
*   used for player character, player character control and HUD.
*
* Releated links:
* - UCLASS			https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/CoreUObject/UObject/UClass?application_version=5.3
* - AGameModeBase	https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/GameFramework/AGameModeBase?application_version=5.3
* - GENERATED_BODY	https://forums.unrealengine.com/t/what-do-generated-body-and-generated-uclass-body-do/420793/3
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P2NHF_GameMode.generated.h"

// ====================================================================================================== 
UCLASS()
class TWE_API AP2NHF_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AP2NHF_GameMode();

private:
	UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override final;   
};
// ======================================================================================================