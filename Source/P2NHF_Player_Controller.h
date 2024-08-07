// Matus Zoltan - R9FJIV 

/*
* TWE - P2NHF_Player_Controller.h
* 
* [HU]
* Az osztaly leirasa:
* - Ez az osztaly felelos elsosorban a jatekos mozgatasaert, es nem utolso sorban
*   a teljes jatekmenet vezerleseert.
* - Kulonbozo bemenetekhez csatol fuggvenyeket az adott jelenethez megfeleloen.
* 
* [EN]
* Class description:
* - This class is primarily responsible for moving the player, and not least for 
*   controlling the entire gameplay.
* - Attaches functions to different inputs according to the given scene.
* 
* * Releated links:
* - UCLASS				https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/CoreUObject/UObject/UClass?application_version=5.3
* - APlayerController	https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/GameFramework/APlayerController?application_version=5.3
* - GENERATED_BODY		https://forums.unrealengine.com/t/what-do-generated-body-and-generated-uclass-body-do/420793/3
*
* Table of Contents:
* [0] - Global
* [1] - Actions & Calls
* [2] - Bindings
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P2NHF_Timer.h"
#include "P2NHF_Player_Controller.generated.h"

// [0] Global
// ======================================================================================================
enum class EGameSceneState : uint8
{
	Start,
	Introduction,
	Game,
	Result
};

UCLASS()
class TWE_API AP2NHF_Player_Controller : public APlayerController
{
	GENERATED_BODY()

private:
	class AP2NHF_Player_Character* PlayerCharacter;
	class AP2NHF_HUD* PlayerCharacterHUD;
	P2NHF_Timer GameTimer;
	FTimerHandle TimerHandle;

public:
	AP2NHF_Player_Controller();
	
private:
	void BeginPlay() override final;

public:
	void Tick(const float DeltaTime) override;
	void SetupInputComponent() override;
	void SetGameSceneState(const EGameSceneState Param);
// ======================================================================================================

// [1] Actions & Calls
// ======================================================================================================
private:
	// Common Actions
	void ExitAction();
	void RestartAction();

	// Special Actions
	void RunTimerAction();
	void SwitchToIntroductionAction();
	void SwitchToGameAction();
public:
	void SwitchToResultAction();

private:
	// Movement Calls
	void CallMoveX(const float Param);
	void CallMoveY(const float Param);
	void CallTilt(const float Param);
	void CallTurn(const float Param);
	void CallJump();
	
	// Other Call-Likes
	void PickEventFlagOn();
	void PickEventFlagOff();

	// Process
	unsigned ProcessTheHighest(const unsigned Param);
// ======================================================================================================

// [2] Bindings
// ======================================================================================================
	void BindStartState();
	void BindIntroductionState();
	void BindGameState();
	void BindResultState();
	void ClearAllBindings();
};
// ======================================================================================================