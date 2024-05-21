// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Generator_InteractBox.h
*/

//#define DebugMode

#include "P2NHF_Generator_InteractBox.h"
#include "P2NHF_Player_Controller.h"
#include "P2NHF_Player_Character.h"
#include "P2NHF_InventorySystem.h"
#include "P2NHF_HUD.h"
#include "Engine/Engine.h"

// ====================================================================================================== 
void AP2NHF_Generator_InteractBox::Interact()
{
	if (PlayerCharacter && MissionItemsCollected)
	{
		AP2NHF_Player_Controller* PlayerController = PlayerCharacter->GetPlayerController();
		if (PlayerController)
			PlayerController->SwitchToResultAction();
		else UE_LOG(LogTemp, Warning, TEXT("PlayerController invalid in AP2NHF_Generator_InteractBox.cpp[22]"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter or MissionItemsCollected invalid in AP2NHF_Generator_InteractBox.cpp[19]"));
}

void AP2NHF_Generator_InteractBox::DisplayInfo()
{
	if (PlayerCharacter)
	{
		P2NHF_InventorySystem* PlayerCharacterInventory = PlayerCharacter->GetPlayerCharacterInventory();
		if (PlayerCharacterInventory)
		{
			if (PlayerCharacterHUD)
				PlayerCharacterInventory->SetPlayerCharacterHUD(PlayerCharacterHUD);
			else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Generator_InteractBox.cpp[19]"));

			PlayerCharacterInventory->CheckTheList();

			if
				(
					PlayerCharacterInventory->GetBestBatteryCharge() >= 0.7f &&
					PlayerCharacterInventory->GetHasUseableFuse() &&
					PlayerCharacterInventory->GetTotalWireLength() >= 20 &&
					PlayerCharacterInventory->GetTotalFuelLiter() >= 25 &&
					PlayerCharacterHUD
				)
			{
				MissionItemsCollected = true;
				PlayerCharacterHUD->SetMissionItemsCollected(true);
			}
			else UE_LOG(LogTemp, Log, TEXT("GetBestBatteryCharge() or GetHasUseableFuse() or GetTotalWireLength() or GetTotalFuelLiter() or PlayerCharacterHUD invalid in AP2NHF_Generator_InteractBox.cpp[44-48]"));
			if (PlayerCharacterHUD)
				PlayerCharacterHUD->SetInGeneratorRange(true);
			else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Generator_InteractBox.cpp[55]"));
		}
		else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterInventory invalid in AP2NHF_Generator_InteractBox.cpp[34]"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter invalid in AP2NHF_Generator_InteractBox.cpp[31]"));
	#ifdef DebugMode
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("#debug: player in generator range"));
	#endif
}

void AP2NHF_Generator_InteractBox::HideInfo()
{
	if (PlayerCharacterHUD)
		PlayerCharacterHUD->SetInGeneratorRange(false);
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Generator_InteractBox.cpp[70]"));
}
// ====================================================================================================== 