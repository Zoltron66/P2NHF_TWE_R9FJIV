// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Battery_Item.cpp
*/

#include "P2NHF_Battery_Item.h"

// ======================================================================================================
P2NHF_Battery_Item::P2NHF_Battery_Item(const P2NHF_Item* Param) :
	P2NHF_Item(EItemType::I_battery, Param->GetWeight()),
	Charge(Param->GetData())
{}

void P2NHF_Battery_Item::SetCharge(const float Param)
{
	if (Param >= 0.0f && Param <= 1.0f)
		Charge = Param;
	else UE_LOG(LogTemp, Log, TEXT("Invalid value encountered: %f, The value must be between 0.f and 1.f in P2NHF_Battery_Item.cpp[17]"), Param);
}

void P2NHF_Battery_Item::SetupSelf()
{
	float RandomNum = FMath::RandRange(0.7f, 1.f);
	SetCharge(RandomNum);
	SetWeight(RandomNum * 25);
}
// ======================================================================================================