// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_GameMode.cpp
*/

#include "P2NHF_GameMode.h"
#include "P2NHF_Player_Character.h"
#include "P2NHF_Player_Controller.h"
#include "P2NHF_HUD.h"

// ======================================================================================================
AP2NHF_GameMode::AP2NHF_GameMode()
{
    DefaultPawnClass = AP2NHF_Player_Character::StaticClass();
    PlayerControllerClass = AP2NHF_Player_Controller::StaticClass();
    HUDClass = AP2NHF_HUD::StaticClass();
}

UClass* AP2NHF_GameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	return DefaultPawnClass;
}
// ======================================================================================================