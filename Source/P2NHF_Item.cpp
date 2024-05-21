// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_Item.cpp
*/

#include "P2NHF_Item.h"

// ======================================================================================================
void P2NHF_Item::SetWeight(const float Param)
{
	if (Param >= 0.0f && Param <= 40.0f)
		Weight = Param;
	else UE_LOG(LogTemp, Log, TEXT("Invalid value encountered: %d, The value must be between 0.f and 40.f in P2NHF_Item.cpp[12]"), Param);
}

bool P2NHF_Item::SetNext(P2NHF_Item* Param)
{
	if (!Next) {
		Next = Param;
		return true;
	}
	return false;
}
// ======================================================================================================