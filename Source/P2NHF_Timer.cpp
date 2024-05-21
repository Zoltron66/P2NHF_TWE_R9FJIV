// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Timer.cpp
*/

#include "P2NHF_Timer.h"
#include "P2NHF_HUD.h"
#include "P2NHF_Player_Controller.h"

// ======================================================================================================
P2NHF_Timer::P2NHF_Timer() :
	P2NHF_Timer(5.f)
{}

P2NHF_Timer::P2NHF_Timer(const float Param) :
	PlayerCharacterHUD(nullptr),
	PlayerController(nullptr),
	TimerMinutes(Param)
{
	CountDownSeconds = TimerMinutes * 60;
}

void P2NHF_Timer::UpdateTimer()
{
	if (CountDownSeconds <= 0)
		CallSwitchToResultAction();
	CallSetTimerTime();
	CountDownSeconds--;
}

void P2NHF_Timer::CallSwitchToResultAction()
{
	if (PlayerController)
		PlayerController->SwitchToResultAction();
	else UE_LOG(LogTemp, Warning, TEXT("PlayerController invalid in P2NHF_Timer.cpp[34]"));
}

void P2NHF_Timer::CallSetTimerTime()
{
	if (PlayerCharacterHUD)
		PlayerCharacterHUD->SetTimerTime(CountDownSeconds);
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in P2NHF_Timer.cpp[41]"));
}
// ======================================================================================================