// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_Wire_Item_PhysicalRep.h
*
* [HU]
* Az osztaly leirasa:
* - Ez az osztaly leszarmazottja a AP2NHF_Item_PhysicalRep osztalynak,
*   ami azt jelenti, hogy van egy belso komponense, ami egy modell. Ezt
*   a modellt allitja be ez az osztaly es parositja a vezetek adataival.
* - Tovabba felulirja az ososztalya virtualis fuggvenyeit, amivel kepes adott
*   esemenyre reagalni.
*
* Esemenyek:
* - Interakcio:
*   Ennel az esemenynel az osztaly hozzaadja az adatait a jatekos belso leltarjahoz
*   majd megszunteti a maga letezeset.
* - Informacio Mutatasa:
*   Ennel az esemenynel az osztaly a jatekos HUD-jara kiirja az adatait (tulajdonsagat).
* - Informacio Elrejtese:
*   Ennel az esemenynel eltunteti a mar a jatekos HUD-jan levo informacios ablakot.
*
* [EN]
* Class description:
* - This class is a derived class from the AP2NHF_Item_PhysicalRep class,
*   which means it has an internal component that is a model. This model is set by this class
*   and matched with the wire data.
* - Furthermore, it overrides the virtual functions of its parent class, which can
*   be used to react to a given event.
*
* Events:
* - Interaction:
*   In this event, the class adds its data to the player's internal inventory and
*   then destroys itself.
* - Show Information:
*   In this event, the class displays its data (property) on the player's HUD.
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
#include "P2NHF_Wire_Item.h"
#include "P2NHF_Wire_Item_PhysicalRep.generated.h"

// ======================================================================================================
UCLASS()
class TWE_API AP2NHF_Wire_Item_PhysicalRep : public AP2NHF_Item_PhysicalRep
{
	GENERATED_BODY()

private:
	P2NHF_Wire_Item WireData;

public:
	AP2NHF_Wire_Item_PhysicalRep();

private:
	void BeginPlay() override final;

	// Special functions
	void Interact() override final;
	void DisplayInfo() override final;
	void HideInfo() override final;
};
// ======================================================================================================