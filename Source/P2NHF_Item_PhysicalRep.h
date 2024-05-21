// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_Item_PhysicalRep.h
*
* [HU]
* Az osztaly leirasa:
* - Alapveto celja ennek az osztalynak az, hogy egy fizikai testet adjon a
*   mar meglevo tulajdonsagainknak, viszont ez csak egy altalanos osztaly,
*   tehat meg ez onmagaban csak egy vaz, amire lehet epitkezni.
* - Fizikai testen kivul egy erzekelo zonaval is rendelkezik, ami ketto allapottal
*   rendelkezik, az egyik amikor a jatekos belép a zonaba, a masik pedig amikor
*   a jatekos kilep a zonabol. Ezekhez az allapotokhoz tartozik egy-egy virtualis
*   fuggveny is, amik az adott eseménykor meghivodnak. Tovabba egy interakcio
*   fuggveny is van, ami akkor hivodik meg, ha a jatekos a zonan belul tartozkodik
*   es megnyomja az interakciohoz szukseges gombot.
*   
* [EN]
* Class description:
* - The basic purpose of this class is to give a physical body to our existing
*   properties, but this is only a general class, so it is only a framework on which 
*   to build.
* - In addition to a physical body, it also has a sensor zone, which has two states, 
*   one when the player enters the zone, and the other when the player leaves the zone.
*   Each of these states also has a virtual function that is called upon the given event.
*   There is also an interaction function, which is called when the player is inside the 
*   zone and presses the button required for interaction.
* 
* Releated links:
* - UCLASS			https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/CoreUObject/UObject/UClass?application_version=5.3
* - AActor			https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/GameFramework/AActor?application_version=5.3
* - GENERATED_BODY	https://forums.unrealengine.com/t/what-do-generated-body-and-generated-uclass-body-do/420793/3
* - UPROPERTY		https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-uproperties?application_version=5.3
* - UFUNCTION		https://dev.epicgames.com/documentation/en-us/unreal-engine/ufunctions-in-unreal-engine?application_version=5.3
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P2NHF_Item_PhysicalRep.generated.h"

// ======================================================================================================
UCLASS()
class TWE_API AP2NHF_Item_PhysicalRep : public AActor
{
	GENERATED_BODY()

private:
	bool PlayerInsideDetectionZone;

protected:
	class AP2NHF_Player_Character* PlayerCharacter;
	class AP2NHF_HUD* PlayerCharacterHUD;
	UPROPERTY()
	class UStaticMeshComponent* InternalMesh;
	UPROPERTY()
	class UBoxComponent* DetectionZone;

public:	
	AP2NHF_Item_PhysicalRep();

protected:
	virtual void BeginPlay() override;

	// Special functions
	virtual void Interact() {}
	virtual void DisplayInfo() {}
	virtual void HideInfo() {}

public:	
	void Tick(const float DeltaTime) override final;

	// Detection Zone related functions
	UFUNCTION()
	void OnPlayerEnterDetectionZone(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	UFUNCTION()
	void OnPlayerLeaveDetectionZone(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};
// ======================================================================================================