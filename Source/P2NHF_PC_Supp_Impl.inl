// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_PC_Supp_Impl.inl
*/

// ======================================================================================================
template<class Ptr>
Ptr P2NHF_PC_Supp::CheckPointer(const Ptr Param)
{
	if (Param)
		return Param;
	UE_LOG(LogTemp, Warning, TEXT("Invalid pointer! from AP2NHF_Player_Character.cpp"));
	return nullptr;
}
// ======================================================================================================