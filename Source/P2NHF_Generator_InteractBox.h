// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Generator_InteractBox.h
*
* [HU]
* Az osztaly leirasa:
* - Ez az osztaly leszarmazottja a AP2NHF_Item_PhysicalRep osztalynak.
* - Tovabba felulirja az ososztalya virtualis fuggvenyeit, amivel kepes adott
*   esemenyre reagalni.
*
* Esemenyek:
* - Interakcio:
*   Ezzel az esemennyel "el lehet inditani a generatort", de csak akkor,
*   ha megvan minden szukseges komponens.
* - Informacio Mutatasa:
*   Ennel az esemenynel az osztaly a jatekos HUD-jara kiirja azt, hogy kepes-e
*   elinditani a generatort vagy sem.
* - Informacio Elrejtese:
*   Ennel az esemenynel eltunteti a mar a jatekos HUD-jan levo informacios ablakot.
*
* [EN]
* Class description:
* - This class is a derived class from the AP2NHF_Item_PhysicalRep class.
* - Furthermore, it overrides the virtual functions of its parent class, which can
*   be used to react to a given event.
*
* Events:
* - Interaction:
*   This event can be used to "start the generator", but only if you have all the 
*   necessary components.
* - Show Information:
*   In this event, the class displays on the player's HUD whether the player 
*   can start the generator or not.
* - Hide Information:
*   In this event, the information window on the player's HUD will disappear.
*
* Releated links:
* - UCLASS			https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/CoreUObject/UObject/UClass?application_version=5.3
* - GENERATED_BODY	https://forums.unrealengine.com/t/what-do-generated-body-and-generated-uclass-body-do/420793/3
*/

#pragma once

#include "CoreMinimal.h"
#include "P2NHF_Item_PhysicalRep.h"
#include "P2NHF_Generator_InteractBox.generated.h"

// ====================================================================================================== 
UCLASS()
class TWE_API AP2NHF_Generator_InteractBox : public AP2NHF_Item_PhysicalRep
{
	GENERATED_BODY()

private:
	bool MissionItemsCollected;

public:
	AP2NHF_Generator_InteractBox() : MissionItemsCollected(false) {}

private:
	void Interact() override final;
	void DisplayInfo() override final;
	void HideInfo() override final;
};
// ====================================================================================================== 