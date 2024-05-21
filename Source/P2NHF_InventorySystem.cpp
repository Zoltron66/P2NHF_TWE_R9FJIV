// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_InventorySystem.cpp
*/

//#define DebugMode

#include "P2NHF_InventorySystem.h"
#include "P2NHF_Item.h"
#include "P2NHF_Battery_Item.h"
#include "P2NHF_Fuse_Item.h"
#include "P2NHF_Wire_Item.h"
#include "P2NHF_Fuel_Item.h"
#include "P2NHF_HUD.h"
#ifdef DebugMode
#include "Engine/Engine.h" 
#endif

// ======================================================================================================
P2NHF_InventorySystem::P2NHF_InventorySystem() :
	ItemListHead(nullptr),
	TotalWeight(0.f),
	BestBatteryCharge(0.f),
	TotalWireLength(0),
	TotalFuelLiter(0),
	HasUseableFuse(false),
	BatteryCount(0), 
	WireCount(0), 
	FuelCanCount(0), 
	FuseCount(0)
{}

P2NHF_InventorySystem::~P2NHF_InventorySystem()
{
	CleanUpMemory();
}


bool P2NHF_InventorySystem::AddItem(const P2NHF_Item* Param, const EItemType ItemType)
{
	P2NHF_Item* ActualItem = ItemListHead;
	
	if (ActualItem)
	{
		#ifdef DebugMode
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("#debug: actual item exist"));
		#endif
		while (ActualItem->GetNext())
		{
			ActualItem = ActualItem->GetNext();
		}
		#ifdef DebugMode
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("#debug: actual item weight: %.1f"), ActualItem->GetWeight()));
		#endif
		ActualItem->SetNext(ItemSelector(Param, ItemType));
		CheckTheList();
		return true;
	}
	else if (!ItemListHead)
	{
		#ifdef DebugMode
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("#debug: inventory was empty"));
		#endif
		ItemListHead = ItemSelector(Param, ItemType);
		CheckTheList();
		return true;
	}
	else UE_LOG(LogTemp, Error, TEXT("ActualItem or/and ItemListHead invalid in P2NHF_InventorySystem.cpp[44,62]"));
	return false;
}

P2NHF_Item* P2NHF_InventorySystem::ItemSelector(const P2NHF_Item* Param, const EItemType ItemType)
{
	switch (ItemType)
	{
	case EItemType::I_battery:
		return AddBatteryItem(Param);
	case EItemType::I_fuse:
		return AddFuseItem(Param);
	case EItemType::I_wire:
		return AddWireItem(Param);
	case EItemType::I_fuel:
		return AddFuelItem(Param);
	default:
		UE_LOG(LogTemp, Warning, TEXT("Switch ItemType invalid in P2NHF_InventorySystem.cpp[78]"));
		return nullptr;
	}
}

P2NHF_Item* P2NHF_InventorySystem::AddBatteryItem(const P2NHF_Item* Param)
{
	return new P2NHF_Battery_Item(Param);
}

P2NHF_Item* P2NHF_InventorySystem::AddFuseItem(const P2NHF_Item* Param)
{
	return new P2NHF_Fuse_Item(Param);
}

P2NHF_Item* P2NHF_InventorySystem::AddWireItem(const P2NHF_Item* Param)
{
	return new P2NHF_Wire_Item(Param);
}

void P2NHF_InventorySystem::SetPlayerCharacterHUD(AP2NHF_HUD* Param)
{
	if (Param)
	{
		PlayerCharacterHUD = Param;
		#ifdef DebugMode
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("#debug: HUD added"));
		#endif
	}
	else UE_LOG(LogTemp, Warning, TEXT("Param invalid in P2NHF_InventorySystem.cpp[111]"));
}

P2NHF_Item* P2NHF_InventorySystem::AddFuelItem(const P2NHF_Item* Param)
{
	return new P2NHF_Fuel_Item(Param);
}


P2NHF_InventorySystem* P2NHF_InventorySystem::CreateDefaultInventory()
{
	return new P2NHF_InventorySystem();
}


void P2NHF_InventorySystem::CheckTheList()
{
	TotalWeight = 0.f;
	TotalWireLength = 0;
	TotalFuelLiter = 0;
	HasUseableFuse = false;
	BatteryCount = 0;
	WireCount = 0;
	FuelCanCount = 0;
	FuseCount = 0;

	P2NHF_Item* ActualItem = ItemListHead;
	if (ActualItem)
	{
		RegisterChaneges(ActualItem);
		while (ActualItem->GetNext())
		{
			ActualItem = ActualItem->GetNext();
			RegisterChaneges(ActualItem);
		}
		RefreshHUD();
		return;
	}
	else UE_LOG(LogTemp, Warning, TEXT("ActualItem invalid in P2NHF_InventorySystem.cpp[146]"));
}

void P2NHF_InventorySystem::RegisterChaneges(const P2NHF_Item* ActualItem)
{
	if (ActualItem)
	{
		switch (ActualItem->GetType())
		{
		case EItemType::I_battery:
			SetBestBatteryCharge(ActualItem->GetData());
			BatteryCount++;
			break;
		case EItemType::I_fuse:
			SetHasUseableFuse(bool(ActualItem->GetData()));
			FuseCount++;
			break;
		case EItemType::I_wire:
			AddToTotalWireLength(ActualItem->GetData());
			WireCount++;
			break;
		case EItemType::I_fuel:
			AddToTotalFuelLiter(ActualItem->GetData());
			FuelCanCount++;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Switch ActualItem->GetType() invalid in P2NHF_InventorySystem.cpp[164]"));
		}
		AddToTotalWeight(ActualItem->GetWeight());
		#ifdef DebugMode
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("#debug: total weight: %.1f"), TotalWeight));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("#debug: top battery charge: %.1f"), BestBatteryCharge));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("#debug: hase useable fuse: %d"), int(HasUseableFuse)));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("#debug: total wire length: %d"), int(TotalWireLength)));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("#debug: total fuel level: %d"), int(TotalFuelLiter)));
		}
		#endif
	}
	else UE_LOG(LogTemp, Warning, TEXT("ActualItem invalid in P2NHF_InventorySystem.cpp[162]"));
}

void P2NHF_InventorySystem::AddToTotalWeight(const float Param)
{
	TotalWeight += Param;
}

void P2NHF_InventorySystem::SetBestBatteryCharge(const float Param)
{
	if (Param > BestBatteryCharge)
		BestBatteryCharge = Param;
}

void P2NHF_InventorySystem::SetHasUseableFuse(const bool Param)
{
	if (!HasUseableFuse && Param)
		HasUseableFuse = true;
}

void P2NHF_InventorySystem::RefreshHUD() const
{
	if (PlayerCharacterHUD)
	{
		PlayerCharacterHUD->SetItem(ESupportItemType::I_battery, BestBatteryCharge * 100.f, BatteryCount);
		PlayerCharacterHUD->SetItem(ESupportItemType::I_wire, TotalWireLength, WireCount);
		PlayerCharacterHUD->SetItem(ESupportItemType::I_fuel, TotalFuelLiter, FuelCanCount);
		PlayerCharacterHUD->SetItem(ESupportItemType::I_fuse, HasUseableFuse, FuseCount);
		PlayerCharacterHUD->SetWeight(TotalWeight);
	}
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in P2NHF_InventorySystem.cpp[218]"));
}


void P2NHF_InventorySystem::CleanUpMemory()
{
	P2NHF_Item* ActualItem = ItemListHead;
	while (ActualItem && ActualItem->GetNext())
	{
		while (ActualItem->GetNext())
		{
			ActualItem = ActualItem->GetNext();
		}
		delete ActualItem;
		ActualItem = ItemListHead;
	}
	ActualItem = nullptr;
	if (ItemListHead)
	{
		delete ItemListHead;
		ItemListHead = nullptr;
		UE_LOG(LogTemp, Log, TEXT("Memory cleared successfully in P2NHF_InventorySystem.cpp[246]"));
		return;
	}
	else UE_LOG(LogTemp, Error, TEXT("Something went wrong with the memory clean up in P2NHF_InventorySystem.cpp[230]"));
}
// ======================================================================================================