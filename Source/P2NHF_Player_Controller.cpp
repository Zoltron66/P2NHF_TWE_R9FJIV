// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_Player_Controller.cpp
*
*
* Table of Contents:
* [0] - Global
* [1] - Actions & Calls
* [2] - Bindings
*/

//#define DebugMode

#include "Kismet/GameplayStatics.h"
#include "P2NHF_Player_Controller.h"
#include "P2NHF_Player_Character.h"
#include "P2NHF_InventorySystem.h"
#include "P2NHF_HUD.h"
#include "P2NHF_File_ReadWrite.h"

// [0] Global
// ======================================================================================================
AP2NHF_Player_Controller::AP2NHF_Player_Controller() :
    PlayerCharacter(nullptr),
    PlayerCharacterHUD(nullptr)
{
    PrimaryActorTick.bCanEverTick = true;
}

void AP2NHF_Player_Controller::BeginPlay()
{
	Super::BeginPlay();

    APawn* CurrentPawn = GetPawn();
    if (!PlayerCharacter && CurrentPawn)
        PlayerCharacter = Cast<AP2NHF_Player_Character>(CurrentPawn);

    AHUD* CurrentHUD = GetHUD();
    if (!PlayerCharacterHUD && CurrentHUD)
        PlayerCharacterHUD = Cast<AP2NHF_HUD>(CurrentHUD);
    P2NHF_File_ReadWrite File;
    File.ReadFromFile("TextDocs/GameTime.txt");
    GameTimer = P2NHF_Timer(File);
    #ifdef DebugMode
    if (GEngine)
    {
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("#debug: [begin play] player character memory address %d"), PlayerCharacter));  // OK
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("#debug: [begin play] player character HUD memory address %d"), PlayerCharacterHUD)); // OK
    }
    #endif
    if (PlayerCharacterHUD)
    {
        if (PlayerCharacter)
            PlayerCharacter->SetPlayerCharacterHUD(PlayerCharacterHUD);
            GameTimer.SetPlayerCharacterHUD(PlayerCharacterHUD);
    }
    if (PlayerCharacter)
        PlayerCharacter->SetPlayerController(this);
    GameTimer.SetPlayerController(this);
}

void AP2NHF_Player_Controller::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);

    APawn* CurrentPawn = GetPawn();
    if (!PlayerCharacter && CurrentPawn)
        PlayerCharacter = Cast<AP2NHF_Player_Character>(CurrentPawn); //else Log spam...

    AHUD* CurrentHUD = GetHUD();
    if (!PlayerCharacterHUD && CurrentHUD)
        PlayerCharacterHUD = Cast<AP2NHF_HUD>(CurrentHUD); //else Log spam...
}


void AP2NHF_Player_Controller::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    SetGameSceneState(EGameSceneState::Start);
}

void AP2NHF_Player_Controller::SetGameSceneState(const EGameSceneState Param)
{
    ClearAllBindings();

    if (InputComponent)
        InputComponent->BindAction("ExitEventTrigger", IE_Pressed, this, &AP2NHF_Player_Controller::ExitAction);
    else UE_LOG(LogTemp, Warning, TEXT("InputComponent invalid in AP2NHF_Player_Controller.cpp[88]"));

    #ifdef DebugMode
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("#debug: [set game scene state] input component memory address %d"), InputComponent)); // OK
    #endif

    switch (Param)
    {
    case EGameSceneState::Start:
        BindStartState();
        if (PlayerCharacterHUD)
            PlayerCharacterHUD->SetHUDState(EHUDState::S_start);
        else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Player_Controller.cpp[100]"));
        return;

    case EGameSceneState::Introduction:
        BindIntroductionState();
        if (PlayerCharacterHUD)
        {
            P2NHF_File_ReadWrite File;
            File.ReadFromFile("TextDocs/Introduction.txt");
            PlayerCharacterHUD->SetIntrText(File);
            PlayerCharacterHUD->SetHUDState(EHUDState::S_introduction);
        }
        else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Player_Controller.cpp[106]"));
        return;

    case EGameSceneState::Game:
        BindGameState();
        if (UWorld* CurrentWorld = GetWorld())
        {
            if (FTimerManager* TimerManager = &CurrentWorld->GetTimerManager())
                TimerManager->SetTimer(TimerHandle, this, &AP2NHF_Player_Controller::RunTimerAction, 1.f, true, 0.f);
            else UE_LOG(LogTemp, Warning, TEXT("TimerManager invalid in AP2NHF_Player_Controller.cpp[123]"));
        }
        else UE_LOG(LogTemp, Warning, TEXT("CurrentWorld invalid in AP2NHF_Player_Controller.cpp[121]"));
        if (PlayerCharacterHUD)
            PlayerCharacterHUD->SetHUDState(EHUDState::S_game);
        else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterHUD invalid in AP2NHF_Player_Controller.cpp[129]"));
        return;

    case EGameSceneState::Result:
        BindResultState();
        if (PlayerCharacterHUD)
        {
            unsigned ResultScore = 0;
            if (PlayerCharacter)
            {
                P2NHF_InventorySystem* PlayerCharacterInventory = PlayerCharacter->GetPlayerCharacterInventory();
                if (PlayerCharacterInventory)
                {
                    ResultScore = PlayerCharacterInventory->GetBestBatteryCharge() * 100 * GameTimer.GetCountDownSeconds();
                    PlayerCharacterHUD->SetResultScoreText(ResultScore);
                }
                else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterInventory invalid in AP2NHF_Player_Controller.cpp[140]"));
            }
            else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter invalid in AP2NHF_Player_Controller.cpp[137]"));
            unsigned HighScore = ProcessTheHighest(ResultScore);
            PlayerCharacterHUD->SetHighScoreText(HighScore);
            PlayerCharacterHUD->SetHUDState(EHUDState::S_result);
        }

        if (UWorld* CurrentWorld = GetWorld())
        {
            if (FTimerManager* TimerManager = &CurrentWorld->GetTimerManager())
                TimerManager->ClearTimer(TimerHandle);
            else UE_LOG(LogTemp, Warning, TEXT("TimerManager invalid in AP2NHF_Player_Controller.cpp[155]"));
        }
        else UE_LOG(LogTemp, Warning, TEXT("CurrentWorld invalid in AP2NHF_Player_Controller.cpp[153]"));
        return;

    default:
        UE_LOG(LogTemp, Warning, TEXT("Switch Param invalid in AP2NHF_Player_Controller.cpp[97]"));
        return;
    }
}
// ======================================================================================================

// [1] Actions & Calls
// ======================================================================================================
// Common Actions
void AP2NHF_Player_Controller::RestartAction()
{
    UWorld* CurrentWorld = GetWorld();
    if (CurrentWorld)
    {
        FString CurrentMapName = *CurrentWorld->GetMapName();
        UGameplayStatics::OpenLevel(this, FName(*CurrentMapName));
    }
    else UE_LOG(LogTemp, Warning, TEXT("CurrentWorld invalid in AP2NHF_Player_Controller.cpp[175]"));
}

void AP2NHF_Player_Controller::ExitAction()
{
    ConsoleCommand("quit");
}

void AP2NHF_Player_Controller::RunTimerAction()
{
    GameTimer.UpdateTimer();
}

// Special Actions
void AP2NHF_Player_Controller::SwitchToIntroductionAction()
{
    SetGameSceneState(EGameSceneState::Introduction);
}

void AP2NHF_Player_Controller::SwitchToGameAction()
{
    SetGameSceneState(EGameSceneState::Game);
}

void AP2NHF_Player_Controller::SwitchToResultAction()
{
    SetGameSceneState(EGameSceneState::Result);
}

// Movement Calls
void AP2NHF_Player_Controller::CallMoveX(const float Param)
{
    if (PlayerCharacter)
        PlayerCharacter->MoveX(Param);
    else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter invalid in AP2NHF_Player_Controller.cpp[212]"));
}

void AP2NHF_Player_Controller::CallMoveY(const float Param)
{
    if (PlayerCharacter)
        PlayerCharacter->MoveY(Param);
    else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter invalid in AP2NHF_Player_Controller.cpp[221]"));
}

void AP2NHF_Player_Controller::CallTilt(const float Param)
{
    if (PlayerCharacter)
        PlayerCharacter->Tilt(Param);
    else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter invalid in AP2NHF_Player_Controller.cpp[226]"));
}

void AP2NHF_Player_Controller::CallTurn(const float Param)
{
    if (PlayerCharacter)
        PlayerCharacter->Turn(Param);
    else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter invalid in AP2NHF_Player_Controller.cpp[233]"));
}

void AP2NHF_Player_Controller::CallJump()
{
    if (PlayerCharacter)
        PlayerCharacter->Jump();
    else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter invalid in AP2NHF_Player_Controller.cpp[240]"));
}

// Other Call-Likes
void AP2NHF_Player_Controller::PickEventFlagOn()
{
    if (PlayerCharacter)
        PlayerCharacter->SetPickEventFlag(true);
    else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter invalid in AP2NHF_Player_Controller.cpp[248]"));
}

void AP2NHF_Player_Controller::PickEventFlagOff()
{
    if (PlayerCharacter)
        PlayerCharacter->SetPickEventFlag(false);
    else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter invalid in AP2NHF_Player_Controller.cpp[255]"));
}

unsigned AP2NHF_Player_Controller::ProcessTheHighest(const unsigned Param)
{
    P2NHF_File_ReadWrite File;
    if (!File.ReadFromFile("TextDocs/HighScore.txt"))
        UE_LOG(LogTemp, Fatal, TEXT("Problem with: HighScore.txt in AP2NHF_Player_Controller.cpp[263]"));
    unsigned UnsignedParam = File;
    if (Param > UnsignedParam)
    {
        File = Param;
        if (!File.WriteToFile("TextDocs/HighScore.txt"))
            UE_LOG(LogTemp, Fatal, TEXT("Problem with: HighScore.txt in AP2NHF_Player_Controller.cpp[268]"));
    }
    return File;
}
// ======================================================================================================

// [2] Bindings
// ======================================================================================================
void AP2NHF_Player_Controller::BindStartState()
{
    if (InputComponent)
        InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AP2NHF_Player_Controller::SwitchToIntroductionAction);
    else UE_LOG(LogTemp, Warning, TEXT("InputComponent invalid in AP2NHF_Player_Controller.cpp[279]"));
}

void AP2NHF_Player_Controller::BindIntroductionState()
{
    if (InputComponent)
        InputComponent->BindAction(TEXT("Pick"), IE_Pressed, this, &AP2NHF_Player_Controller::SwitchToGameAction);
    else UE_LOG(LogTemp, Warning, TEXT("InputComponent invalid in AP2NHF_Player_Controller.cpp[286]"));
}

void AP2NHF_Player_Controller::BindGameState()
{
    if (InputComponent)
    {
        InputComponent->BindAxis(TEXT("MoveXF"), this, &AP2NHF_Player_Controller::CallMoveX);
        InputComponent->BindAxis(TEXT("MoveXB"), this, &AP2NHF_Player_Controller::CallMoveX);
        InputComponent->BindAxis(TEXT("MoveYL"), this, &AP2NHF_Player_Controller::CallMoveY);
        InputComponent->BindAxis(TEXT("MoveYR"), this, &AP2NHF_Player_Controller::CallMoveY);
        InputComponent->BindAxis(TEXT("Tilt"), this, &AP2NHF_Player_Controller::CallTilt);
        InputComponent->BindAxis(TEXT("Turn"), this, &AP2NHF_Player_Controller::CallTurn);

        InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AP2NHF_Player_Controller::CallJump);
        InputComponent->BindAction(TEXT("Pick"), IE_Pressed, this, &AP2NHF_Player_Controller::PickEventFlagOn);
        InputComponent->BindAction(TEXT("Pick"), IE_Released, this, &AP2NHF_Player_Controller::PickEventFlagOff);
    }
    else UE_LOG(LogTemp, Warning, TEXT("InputComponent invalid in AP2NHF_Player_Controller.cpp[293]"));
}

void AP2NHF_Player_Controller::BindResultState()
{
    if (InputComponent)
        InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AP2NHF_Player_Controller::RestartAction);
    else UE_LOG(LogTemp, Warning, TEXT("InputComponent invalid in AP2NHF_Player_Controller.cpp[311]"));
}

void AP2NHF_Player_Controller::ClearAllBindings()
{
    if (InputComponent)
    {
        InputComponent->ClearActionBindings();
        InputComponent->ClearAxisBindings();
    }
    else UE_LOG(LogTemp, Warning, TEXT("InputComponent invalid in AP2NHF_Player_Controller.cpp[318]"));
}
// ======================================================================================================