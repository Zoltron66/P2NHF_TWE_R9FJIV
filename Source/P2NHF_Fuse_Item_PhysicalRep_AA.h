// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Fuse_Item_PhysicalRep_AA.h
*
* [HU]
* Az osztaly leirasa:
* - Ez az osztaly leszarmazik a AP2NHF_Fuse_Item_PhysicalRep osztalybol,
*   ezert a fizikai es funkcionalis tulajdonsagai adottak.
* - Viszont ez az osztaly egy specialis verziot kepes letrehozni az ososztalyabol, 
*   ami egy mindig aktiv biztositekot eredmenyez. (Ez a jatek minden esetben 
*   teljesithetoseget segiti elo.)
*
* [EN]
* Class description:
* - This class derives from the AP2NHF_Fuse_Item_PhysicalRep class, 
*   so its physical and functional properties are given.
* - However, this class can create a special version of its parent class, which 
*   results in an always active fuse. (This helps the game to be completeable in any case.)
*
* Releated links:
* - UCLASS			https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/CoreUObject/UObject/UClass?application_version=5.3
* - GENERATED_BODY	https://forums.unrealengine.com/t/what-do-generated-body-and-generated-uclass-body-do/420793/3
*/

#pragma once

#include "CoreMinimal.h"
#include "P2NHF_Fuse_Item_PhysicalRep.h"
#include "P2NHF_Fuse_Item_PhysicalRep_AA.generated.h"

// ======================================================================================================
UCLASS()
class TWE_API AP2NHF_Fuse_Item_PhysicalRep_AA : public AP2NHF_Fuse_Item_PhysicalRep
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override final;
};
// ======================================================================================================