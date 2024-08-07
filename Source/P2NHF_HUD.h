// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_HUD.h
* 
* [HU]
* Az osztaly leirasa:
* - Ez az osztaly a jatek "kepernyore rogzitett" elemeit kezeli.
* - A szokasosnal tobb funkcioja van, mivel nem megszokott mond tartalmaz
*   szinhelyeket (scene), amik a jatek bizonyos fazisait hivatottak reprezentalni.
* 
* Szinhelyek:
* - Kezdo kepernyo:
*   Ezen a kepernyon lehet latni a jatek terkepet, tovabba a jatek elinditasahoz 
*   szukseges gomb megnyomasat javaslo szoveget.
* - Bevezeto kepernyo:
*   Ezen a kepernyon olvashato, hogy mi a feladat, es, hogy milyen gombokkal lehet
*   vezerelni a jatekot.
* - Jatek kepernyo:
*   Ezen a kepernyon jatszhatova valik a jatek teljes egesze. Tobb komonenst is
*   tartalmaz ez a kepernyo: 
*                           - Kuldetes:
*                             Az osszegyujtendo targyak listajat mutatja.
*                           - Targy Informaciok:
*                             Az epp adott targynak (aminek az aktivacios zonajaban
*                             vagy) latszodnak az adatai.
*                           - Generator Informacio:
*                             A generator aktivacios zonajaba erve jelenik meg,
*                             es azt mutatja, hogy be tudod inditani a generatort vagy sem
*                           - Idozito:
*                             Hatralevo idot mutatja.
* - Vegeredmeny kepernyo:
*   Ezen a kepernyon latszik a jelenlegi rekordod, az eddigi legmagasabb rekord es a
*   vegen az indikator szoveg, ami mutatja, hogy nyertel vagy vesztettel.
* 
* [EN]
* Class description:
* - This class handles the "fixed to screen" elements of the game.
* - It contains unusual scenes that are meant to represent certain phases of the game.
*
* Locations:
* - Start scene:
*   On this scene, you can see the game map, as well as the text recommending pressing
*   the button to start the game.
* - Introduction scene:
*   On this scene, you can read what the task is and what buttons can be used to 
*   control the game.
* - Game scene:
*   The entire game becomes playable on this scene. This scene contains several 
*   components:
*               - Mission:
*                 Shows a list of items to collect.
*               - Item Information:
*                 The data of the currently given item are visible.
*               - Generator Information:                 
*                 The generator activation zone argument is displayed and shows 
*                 whether or not you can start the generator
*               - Timer:
*                 Shows remaining time.
* - Result scene:
*   This scene shows your current record, the highest record so far and the indicator text
*   at the end, which shows whether you won or lost.
* 
* Releated links:
* - UCLASS			https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/CoreUObject/UObject/UClass?application_version=5.3
* - AHUD			https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/GameFramework/AHUD?application_version=5.3
* - GENERATED_BODY	https://forums.unrealengine.com/t/what-do-generated-body-and-generated-uclass-body-do/420793/3
* - UPROPERTY		https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-uproperties?application_version=5.3
*
* Table of Contents:
* [0] - Global
* [1] - Start Scene
* [2] - Introduction Scene
* [3] - Game Scene
* [4] - Result Scene
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "P2NHF_HUD.generated.h"

// [0] Global
// ====================================================================================================== 
enum class EHUDState : uint8
{
    S_start,
    S_introduction,
    S_game,
    S_result
};

enum class ESupportItemType : uint8
{
    I_battery,
    I_fuel,
    I_wire,
    I_fuse,
    I_none
};

UCLASS()
class TWE_API AP2NHF_HUD : public AHUD
{
	GENERATED_BODY()

private:
    EHUDState HUDState;
    UPROPERTY()
    FLinearColor DebugBoxColor;
    UPROPERTY()
    FLinearColor BoxColor;

public:
    AP2NHF_HUD();

    void DrawHUD() override final;

    void SetHUDState(const EHUDState Param) { HUDState = Param; }
    EHUDState GetHUDState() const { return HUDState; }

private:
    FVector2D AlignRelativeToCenterTop(const FVector2D& Param);
    FVector2D AlignRelativeToCenterBottom(const FVector2D& Param);
    FVector2D AlignRelativeToCenter(const FVector2D& Param);
// ====================================================================================================== 

// [1] Start Scene
// ====================================================================================================== 
private:
    UPROPERTY()
    FVector2D ImageSize;
    UPROPERTY()
    FVector2D ImageRelativePosition; // Relaive to center
    UPROPERTY()
    UTexture2D* ImageTexture;
    UPROPERTY()
    FVector2D StartTextRelativePosition; // Relative to center bottom

    void DisplayStartScene();
// ====================================================================================================== 

// [2] Introduction Scene
// ====================================================================================================== 
    UPROPERTY()
    FVector2D IntrTitleRelativePosition; // Relative to IntrBackgroundBoxRelativePosition center
    UPROPERTY()
    FString IntrText;
    UPROPERTY()
    FVector2D IntrtextRelativePosition; // Relative to IntrBackgroundBoxRelativePosition center

public:
    void SetIntrText(const FString& Param) { IntrText = Param; }

private:
    void DisplayIntroductionScene();
// ====================================================================================================== 

// [3] Game Scene
// ====================================================================================================== 
    // Mission
    // ------------------------------------------------------------
    UPROPERTY()
    FVector2D MissionBoxSize;
    UPROPERTY()
    FVector2D MissionBoxPosition; // Default -> to top left
    UPROPERTY()
    FString Items[4];
    UPROPERTY()
    FLinearColor ItemsColor[4];
    UPROPERTY()
    FString Weight;

public:
    void SetItem(const ESupportItemType& Type, const float Param, const int32 Qt = 1);
    void SetWeight(const float Param);

private:
    void RenderMission();
    // ------------------------------------------------------------

    // Item infos
    // ------------------------------------------------------------
    ESupportItemType ItemType;
    UPROPERTY()
    FString ItemInfo;
    UPROPERTY()
    FString Infos[2];
    UPROPERTY()
    FVector2D ItemBoxSize;
    UPROPERTY()
    FVector2D ItemBoxRelativePosition; // Relative to center

public:
    void SetItemInfo(const ESupportItemType& Type, const float Data = 0.f, const float Weight = 0.f);

private:
    void RenderInfos();
    // ------------------------------------------------------------
    
    // Generator infos
    // ------------------------------------------------------------
    UPROPERTY()
    bool InGeneratorRange;
    UPROPERTY()
    bool MissionItemsCollected;
    UPROPERTY()
    FVector2D GeneratorResponseTextRelativeLocation; // Relative to center

public:
    void SetInGeneratorRange(const bool Param) { InGeneratorRange = Param; }
    void SetMissionItemsCollected(const bool Param) { MissionItemsCollected = Param; }

private:
    void RenderGeneratorInfo();
    // ------------------------------------------------------------

    // Timer
    // ------------------------------------------------------------
    UPROPERTY()
    FString TimerTime;
    UPROPERTY()
    FVector2D TimerRelativePosition; // Relative to center top

public:
    void SetTimerTime(const unsigned Param);

private:
    void RenderTimer();
    // ------------------------------------------------------------
    void DisplayGameScene();
// ====================================================================================================== 

// [4] Result Scene
// ====================================================================================================== 
    UPROPERTY()
    FString ResultScoreText;
    UPROPERTY()
    FVector2D ResultScoreTextRelativePosition; // Relative to center
    UPROPERTY()
    FString HighScoreText;
    UPROPERTY()
    FVector2D HighScoreTextRelativePosition; // Relative to center
    UPROPERTY()
    FVector2D WinOrLoseRelativePosition; // Relative to center top

public:
    void SetResultScoreText(const unsigned Param);
    void SetHighScoreText(const unsigned Param);

private:
    void DisplayResultScene();
};
// ====================================================================================================== 