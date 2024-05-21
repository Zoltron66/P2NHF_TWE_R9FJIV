// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_Fuel_Item.cpp
*/

#include "P2NHF_Fuel_Item.h"

// ======================================================================================================
P2NHF_Fuel_Item::P2NHF_Fuel_Item(const P2NHF_Item* Param) :
	P2NHF_Item(EItemType::I_fuel, Param->GetWeight()),
	Liter(Param->GetData())
{}

void P2NHF_Fuel_Item::SetLiter(const unsigned Param)
{
	if (Param >= 0 && Param <= 20)
		Liter = Param;
	else UE_LOG(LogTemp, Log, TEXT("Invalid value encountered: %d, The value must be between 0 and 20 in P2NHF_Fuel_Item.cpp[17]"), Param);
}

void P2NHF_Fuel_Item::SetupSelf()
{
	unsigned RandomNumber = FMath::RandRange(7, 20);
	SetLiter(RandomNumber);
	SetWeight(RandomNumber * 2);
}
// ======================================================================================================