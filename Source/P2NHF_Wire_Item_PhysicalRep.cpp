// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_Wire_Item_PhysicalRep.cpp
*/

#include "P2NHF_Wire_Item_PhysicalRep.h"
#include "P2NHF_Player_Character.h"
#include "P2NHF_InventorySystem.h"
#include "P2NHF_HUD.h"

// ======================================================================================================
AP2NHF_Wire_Item_PhysicalRep::AP2NHF_Wire_Item_PhysicalRep()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Construction_VOL1/Meshes/SM_Spool_01a"));
	if (MeshAsset.Succeeded())
		InternalMesh->SetStaticMesh(MeshAsset.Object);
	else UE_LOG(LogTemp, Fatal, TEXT("MeshAsset failed in AP2NHF_Wire_Item_PhysicalRep.cpp[17]"));

	WireData.SetType(EItemType::I_wire);
}

void AP2NHF_Wire_Item_PhysicalRep::BeginPlay()
{
	Super::BeginPlay();

	WireData.SetupSelf();
}

// Special functions
void AP2NHF_Wire_Item_PhysicalRep::Interact()
{
	if (PlayerCharacter)
	{
		P2NHF_InventorySystem* PlayerCharacterInventory = PlayerCharacter->GetPlayerCharacterInventory();
		if (PlayerCharacterInventory)
		{
			if (PlayerCharacterHUD)
				PlayerCharacterInventory->SetPlayerCharacterHUD(PlayerCharacterHUD);
			else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Wire_Item_PhysicalRep.cpp[39]"));
			PlayerCharacterInventory->AddItem(&WireData, EItemType::I_wire);
		}
		else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterInventory invalid in AP2NHF_Wire_Item_PhysicalRep.cpp[37]"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter pointer invalid in AP2NHF_Wire_Item_PhysicalRep.cpp[34]"));
	Destroy();
}

void AP2NHF_Wire_Item_PhysicalRep::DisplayInfo()
{
	if (PlayerCharacterHUD)
		PlayerCharacterHUD->SetItemInfo(ESupportItemType::I_wire, WireData.GetData(), WireData.GetWeight());
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Wire_Item_PhysicalRep.cpp[52]"));
}

void AP2NHF_Wire_Item_PhysicalRep::HideInfo()
{
	if (PlayerCharacterHUD)
		PlayerCharacterHUD->SetItemInfo(ESupportItemType::I_none);
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Wire_Item_PhysicalRep.cpp[59]"));
}
// ======================================================================================================