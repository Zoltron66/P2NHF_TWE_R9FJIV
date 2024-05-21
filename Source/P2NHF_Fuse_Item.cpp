// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Fuse_Item.cpp
*/

#include "P2NHF_Fuse_Item.h"

// ======================================================================================================
P2NHF_Fuse_Item::P2NHF_Fuse_Item(const P2NHF_Item* Param) :
	P2NHF_Item(EItemType::I_fuse, Param->GetWeight()),
	Useable(bool(Param->GetData()))
{}

void P2NHF_Fuse_Item::SetupSelf()
{
	bool RandomState = bool(FMath::RandRange(0, 1));
	SetUseable(RandomState);
	SetWeight(RandomState ? 0.5f : 0.2f);
}
// ======================================================================================================