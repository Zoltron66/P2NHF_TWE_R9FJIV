// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_Fuel_Item_PhysicalRep.cpp
*/

#include "P2NHF_Fuel_Item_PhysicalRep.h"
#include "P2NHF_Player_Character.h"
#include "P2NHF_InventorySystem.h"
#include "P2NHF_HUD.h"

// ======================================================================================================
AP2NHF_Fuel_Item_PhysicalRep::AP2NHF_Fuel_Item_PhysicalRep()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Construction_VOL2/Meshes/SM_Canister"));
	if (MeshAsset.Succeeded())
		InternalMesh->SetStaticMesh(MeshAsset.Object);
	else UE_LOG(LogTemp, Fatal, TEXT("MeshAsset failed in AP2NHF_Fuel_Item_PhysicalRep.cpp[16]"));

	FuelData.SetType(EItemType::I_fuel);
}

void AP2NHF_Fuel_Item_PhysicalRep::BeginPlay()
{
	Super::BeginPlay();

	FuelData.SetupSelf();
}

// Special functions
void AP2NHF_Fuel_Item_PhysicalRep::Interact()
{
	if (PlayerCharacter)
	{
		P2NHF_InventorySystem* PlayerCharacterInventory = PlayerCharacter->GetPlayerCharacterInventory();
		if (PlayerCharacterInventory)
		{
			if (PlayerCharacterHUD)
				PlayerCharacterInventory->SetPlayerCharacterHUD(PlayerCharacterHUD);
			else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Fuel_Item_PhysicalRep.cpp[38]"));
			PlayerCharacterInventory->AddItem(&FuelData, EItemType::I_fuel);
		}
		else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterInventory invalid in AP2NHF_Fuel_Item_PhysicalRep.cpp[36]"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter pointer invalid in AP2NHF_Fuel_Item_PhysicalRep.cpp[33]"))
	Destroy();
}

void AP2NHF_Fuel_Item_PhysicalRep::DisplayInfo()
{
	if (PlayerCharacterHUD)
		PlayerCharacterHUD->SetItemInfo(ESupportItemType::I_fuel, FuelData.GetData(), FuelData.GetWeight());
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Fuel_Item_PhysicalRep.cpp[51]"))
}

void AP2NHF_Fuel_Item_PhysicalRep::HideInfo()
{
	if (PlayerCharacterHUD)
		PlayerCharacterHUD->SetItemInfo(ESupportItemType::I_none);
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Fuel_Item_PhysicalRep.cpp[58]"))
}
// ======================================================================================================