// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Player_Character.h
*
* [HU]
* Az osztaly leirasa:
* - Ez az osztaly kepezi a karakterunk fizikai tulajdonsagait, mint a test vagy a 
*   kamera (latasert felelos).
* - Ezeken felul a test es kamera mozgatasat vegzo fuggvenyek is itt vannak. 
* - Nem utolso sorban pedig a jatekos leltara is a karakterben kap helyet.
* 
* [EN]
* Class description:
* - This class forms the physical properties of our character, such as the body or 
*   the camera (responsible for vision).
* - In addition to these, the functions for moving the body and camera are also here.
* - Last but not least, the player's inventory is also included in the character.
*
* Releated links:
* - UCLASS			https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/CoreUObject/UObject/UClass?application_version=5.3
* - ACharacter		https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/GameFramework/ACharacter?application_version=5.3
* - GENERATED_BODY	https://forums.unrealengine.com/t/what-do-generated-body-and-generated-uclass-body-do/420793/3
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "P2NHF_Player_Character.generated.h"

// ======================================================================================================
UCLASS()
class TWE_API AP2NHF_Player_Character : public ACharacter
{
	GENERATED_BODY()

private:
	class UCameraComponent* PlayerCharacterCamera;
	class UCharacterMovementComponent* PlayerCharacterMovement;
	class P2NHF_InventorySystem* PlayerCharacterInventory;
	class AP2NHF_HUD* PlayerCharacterHUD;
	class AP2NHF_Player_Controller* PlayerController;
	bool PickEventFlag;

public:
	AP2NHF_Player_Character();

private:
	void BeginPlay() override final;

public:
	// Getter for Inventory, required for items
	P2NHF_InventorySystem* GetPlayerCharacterInventory() const;

	// HUD access provider functions, required for items
	AP2NHF_HUD* GetPlayerCharacterHUD() const;
	void SetPlayerCharacterHUD(AP2NHF_HUD* Param);

	// Player Conroller access provider functions, required for Generator Interact Box
	AP2NHF_Player_Controller* GetPlayerController() const;
	void SetPlayerController(AP2NHF_Player_Controller* Param);

	// Setters for character speed, functionality depends on parameters
	void SetPlayerCharacterSpeed(const float Param);
	void SetPlayerCharacterSpeed();

	// Flag setter and getter for PickUp event, required for items
	bool GetPickEventFlag() const { return PickEventFlag; }
	void SetPickEventFlag(const bool Param) { PickEventFlag = Param; }

	// Character movements
	void MoveX(const float Param);
	void MoveY(const float Param);
	void Tilt(const float Param);
	void Turn(const float Param);
	void Jump();
};
// ======================================================================================================