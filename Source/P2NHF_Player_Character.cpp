// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Player_Character.cpp
*/

#include "P2NHF_Player_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "P2NHF_InventorySystem.h"
#include "P2NHF_HUD.h"
#include "P2NHF_Player_Controller.h"
#include "P2NHF_PC_Supp.hpp"

// ======================================================================================================
AP2NHF_Player_Character::AP2NHF_Player_Character() :
	PlayerCharacterCamera(nullptr),
	PlayerCharacterMovement(nullptr),
	PlayerCharacterInventory(nullptr),
	PlayerCharacterHUD(nullptr),
	PlayerController(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
	
	PlayerCharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCharacterCamera"));
	if (PlayerCharacterCamera)
	{
		PlayerCharacterCamera->SetupAttachment(GetCapsuleComponent());
		PlayerCharacterCamera->SetRelativeLocation(FVector(-20, 0, 50));
		PlayerCharacterCamera->bUsePawnControlRotation = true;
	}
	else UE_LOG(LogTemp, Fatal, TEXT("PlayerCharacterCamera invalid in AP2NHF_Player_Character.cpp[28]"));

	PlayerCharacterMovement = GetCharacterMovement();
	SetPlayerCharacterSpeed(500);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AP2NHF_Player_Character::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacterInventory = P2NHF_InventorySystem::CreateDefaultInventory();
	PickEventFlag = false;
}

// Getter for Inventory, required for items
P2NHF_InventorySystem* AP2NHF_Player_Character::GetPlayerCharacterInventory() const
{
	return P2NHF_PC_Supp::CheckPointer(PlayerCharacterInventory);
}

// HUD access provider functions, required for items
AP2NHF_HUD* AP2NHF_Player_Character::GetPlayerCharacterHUD() const
{
	return P2NHF_PC_Supp::CheckPointer(PlayerCharacterHUD);
}

void AP2NHF_Player_Character::SetPlayerCharacterHUD(AP2NHF_HUD* Param)
{
	PlayerCharacterHUD = P2NHF_PC_Supp::CheckPointer(Param);
}

// Player Conroller access provider functions, required for Generator Interact Box
AP2NHF_Player_Controller* AP2NHF_Player_Character::GetPlayerController() const
{
	return P2NHF_PC_Supp::CheckPointer(PlayerController);
}

void AP2NHF_Player_Character::SetPlayerController(AP2NHF_Player_Controller* Param)
{
	PlayerController = P2NHF_PC_Supp::CheckPointer(Param);
}

// Setters for character speed, functionality depends on parameters
void AP2NHF_Player_Character::SetPlayerCharacterSpeed(const float Param)
{
	if (PlayerCharacterMovement && Param >= 10.0f && Param <= 1000.0f)
		PlayerCharacterMovement->MaxWalkSpeed = Param;
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterMovement or Param(must be between 10.f and 1000.f) invalid in AP2NHF_Player_Character.cpp[81]"));
}

void AP2NHF_Player_Character::SetPlayerCharacterSpeed()
{
	if (PlayerCharacterInventory)
		SetPlayerCharacterSpeed(500 - PlayerCharacterInventory->GetTotalWeight() * 2);
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterInventory invalid in AP2NHF_Player_Character.cpp[88]"));
}

// Character movements
void AP2NHF_Player_Character::MoveX(const float Param)
{
	if (Param != 0)
		AddMovementInput(GetActorForwardVector(), Param);
	else UE_LOG(LogTemp, Warning, TEXT("Param is 0 (must be greater than or less than 0) in AP2NHF_Player_Character.cpp[96]"));
	SetPlayerCharacterSpeed();
}

void AP2NHF_Player_Character::MoveY(const float Param)
{
	if (Param != 0)
		AddMovementInput(GetActorRightVector(), Param);
	else UE_LOG(LogTemp, Warning, TEXT("Param is 0 (must be greater than or less than 0) in AP2NHF_Player_Character.cpp[104]"));
	SetPlayerCharacterSpeed();
}

void AP2NHF_Player_Character::Tilt(const float Param)
{
	if (Param != 0)
		AddControllerPitchInput(Param);
	else UE_LOG(LogTemp, Warning, TEXT("Param is 0 (must be greater than or less than 0) in AP2NHF_Player_Character.cpp[112]"));
}

void AP2NHF_Player_Character::Turn(const float Param)
{
	if (Param != 0)
		AddControllerYawInput(Param);
	else UE_LOG(LogTemp, Warning, TEXT("Param is 0 (must be greater than or less than 0) in AP2NHF_Player_Character.cpp[119]"));
}

void AP2NHF_Player_Character::Jump()
{
	if (CanJump())
		ACharacter::Jump();
}
// ======================================================================================================