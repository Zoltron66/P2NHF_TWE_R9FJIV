// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Wire_Item.cpp
*/

#include "P2NHF_Wire_Item.h"

// ======================================================================================================
P2NHF_Wire_Item::P2NHF_Wire_Item(const P2NHF_Item* Param) :
	P2NHF_Item(EItemType::I_wire, Param->GetWeight()),
	Length(Param->GetData())
{}

void P2NHF_Wire_Item::SetLength(const unsigned& Param)
{
	if (Param >= 0 && Param <= 25)
		Length = Param;
	else UE_LOG(LogTemp, Log, TEXT("Invalid value encountered: %d, The value must be between 0 and 25 in P2NHF_Wire_Item.cpp[17]"), Param);
}

void P2NHF_Wire_Item::SetupSelf()
{
	unsigned RandomNumber = FMath::RandRange(5, 20);
	SetLength(RandomNumber);
	SetWeight(RandomNumber * 1);
}
// ======================================================================================================