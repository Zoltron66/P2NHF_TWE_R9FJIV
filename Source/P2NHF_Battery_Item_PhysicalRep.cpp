// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_Battery_Item_PhysicalRep.cpp
*/

#include "P2NHF_Battery_Item_PhysicalRep.h"
#include "P2NHF_Player_Character.h"
#include "P2NHF_InventorySystem.h"
#include "P2NHF_HUD.h"
#include "Engine/Engine.h"

// ======================================================================================================
AP2NHF_Battery_Item_PhysicalRep::AP2NHF_Battery_Item_PhysicalRep()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Battery/battery/source/Battery"));
	if (MeshAsset.Succeeded())
		InternalMesh->SetStaticMesh(MeshAsset.Object);
	else UE_LOG(LogTemp, Fatal, TEXT("MeshAsset failed in AP2NHF_Battery_Item_PhysicalRep.cpp[17]"));

	BatteryData.SetType(EItemType::I_battery);
}

void AP2NHF_Battery_Item_PhysicalRep::BeginPlay()
{
	Super::BeginPlay();
	
	BatteryData.SetupSelf();
}

// Special functions
void AP2NHF_Battery_Item_PhysicalRep::Interact()
{
	if (PlayerCharacter)
	{
		P2NHF_InventorySystem* PlayerCharacterInventory = PlayerCharacter->GetPlayerCharacterInventory();
		if (PlayerCharacterInventory)
		{
			if (PlayerCharacterHUD)
				PlayerCharacterInventory->SetPlayerCharacterHUD(PlayerCharacterHUD);
			else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Battery_Item_PhysicalRep.cpp[39]"));
			PlayerCharacterInventory->AddItem(&BatteryData, EItemType::I_battery);
		}
		else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterInventory invalid in AP2NHF_Battery_Item_PhysicalRep.cpp[37]"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter pointer invalid in AP2NHF_Battery_Item_PhysicalRep.cpp[34]"));
	Destroy();
}

void AP2NHF_Battery_Item_PhysicalRep::DisplayInfo()
{
	if (PlayerCharacterHUD)
		PlayerCharacterHUD->SetItemInfo(ESupportItemType::I_battery, 100 * BatteryData.GetData(), BatteryData.GetWeight());
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Battery_Item_PhysicalRep.cpp[52]"));
}

void AP2NHF_Battery_Item_PhysicalRep::HideInfo()
{
	if (PlayerCharacterHUD)
		PlayerCharacterHUD->SetItemInfo(ESupportItemType::I_none);
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Battery_Item_PhysicalRep.cpp[59]"));
}
// ======================================================================================================