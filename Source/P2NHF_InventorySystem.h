// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_InventorySystem.h
* 
* [HU]
* Az osztaly leirasa:
* - Ebben az osztalyban lehet eltarolni az P2NHF_Item tipusu elemeket egy lista
*   alapu heterogen kollekcioban.
* - Csak a szukseges muveleteket tartalmazza, igy peldaul a jatek szempontjabol nem
*   fontos leltarbol kivetel funkciot vagy a leltar rendezese stb. muveleteket 
*   nem tartalmazza.
*
* [EN]
* Class description:
* - P2NHF_Item type elements can be stored in this class in a list-based
*   heterogeneous collection.
* - It contains only the necessary actions, nothing more,
*   especially not unnecessary actions.
*/

#pragma once

#include "CoreMinimal.h" 
#include "P2NHF_Item.h"

// ======================================================================================================
class AP2NHF_HUD;

class TWE_API P2NHF_InventorySystem
{
private:
	AP2NHF_HUD* PlayerCharacterHUD;
	P2NHF_Item* ItemListHead;
	float TotalWeight, BestBatteryCharge;
	unsigned TotalWireLength, TotalFuelLiter;
	bool HasUseableFuse;
	int32 BatteryCount, WireCount, FuelCanCount, FuseCount;

	P2NHF_InventorySystem();
	P2NHF_InventorySystem(const P2NHF_InventorySystem& Param) = delete;
	auto operator=(const P2NHF_InventorySystem& Param) = delete;

public:
	~P2NHF_InventorySystem();

	bool AddItem(const P2NHF_Item* Param, const EItemType ItemType);

private:
	P2NHF_Item* ItemSelector(const P2NHF_Item* Param, const EItemType ItemType);
	P2NHF_Item* AddFuelItem(const P2NHF_Item* Param);
	P2NHF_Item* AddBatteryItem(const P2NHF_Item* Param);
	P2NHF_Item* AddFuseItem(const P2NHF_Item* Param);
	P2NHF_Item* AddWireItem(const P2NHF_Item* Param);

public:
	void SetPlayerCharacterHUD(AP2NHF_HUD* Param);

	float GetTotalWeight() const { return TotalWeight; }
	float GetBestBatteryCharge() const { return BestBatteryCharge; }
	unsigned GetTotalWireLength() const { return TotalWireLength; }
	unsigned GetTotalFuelLiter() const { return TotalFuelLiter; }
	bool GetHasUseableFuse() const { return HasUseableFuse; }
	
	void CheckTheList();

	static P2NHF_InventorySystem* CreateDefaultInventory();

private:
	void RegisterChaneges(const P2NHF_Item* ActualItem);
	void AddToTotalWeight(const float Param);
	void SetBestBatteryCharge(const float Param);
	void AddToTotalWireLength(const unsigned Param) { TotalWireLength += Param; }
	void AddToTotalFuelLiter(const unsigned Param) { TotalFuelLiter += Param; }
	void SetHasUseableFuse(const bool Param);
	void RefreshHUD() const;

	void CleanUpMemory();
};
// ======================================================================================================