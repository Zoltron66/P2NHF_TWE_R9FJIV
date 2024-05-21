// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Timer.h
* 
* [HU]
* Az osztaly leirasa:
* - Ez az osztaly kepes egy megadott szamtol kezdve visszaszamolni es ezt kijelezni a HUD-on.
* - A visszaszamlalashoz nem hasznal belso ciklust, hanem a meghivo felnek a feladata,
*   hogy masodpercenkent meghivja az Idozito Frissitese fuggvenyt.
* 
* 
* [EN]
* Class description:
* - This class can count down from a given number and display it on the HUD.
* - It does not use an internal loop for the countdown, but the functions that use it 
*   are responsible for its operation.
*/

#pragma once

#include "CoreMinimal.h"

// ======================================================================================================
class TWE_API P2NHF_Timer
{
private:
	class AP2NHF_HUD* PlayerCharacterHUD;
	class AP2NHF_Player_Controller* PlayerController;
	float TimerMinutes;
	unsigned CountDownSeconds;

	P2NHF_Timer(const P2NHF_Timer& Param) = delete;
public:
	P2NHF_Timer();
	explicit P2NHF_Timer(const float Param);

	void SetPlayerCharacterHUD(AP2NHF_HUD* Param) { PlayerCharacterHUD = Param; }
	void SetPlayerController(AP2NHF_Player_Controller* Param) { PlayerController = Param; }
	
	void UpdateTimer();

	unsigned GetCountDownSeconds() const { return CountDownSeconds; }

private:
	void CallSwitchToResultAction(); // Player Controller function
	void CallSetTimerTime();		 // HUD function
};
// ======================================================================================================