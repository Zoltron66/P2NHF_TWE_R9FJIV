// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_HUD.cpp
* 
* Table of Contents:
* [0] - Global
* [1] - Start Scene
* [2] - Introduction Scene
* [3] - Game Scene
* [4] - Result Scene
*/

//#define DebugMode

#include "P2NHF_HUD.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"

// [0] Global
// ====================================================================================================== 
AP2NHF_HUD::AP2NHF_HUD() :
    HUDState(EHUDState::S_start),
    DebugBoxColor(FLinearColor::Green),
    BoxColor(0.01f, 0.01f, 0.01f, 0.9f),
    ImageTexture(nullptr),
    StartTextRelativePosition(-80.f, 80.f),
    IntrTitleRelativePosition(-50.f, 10.f),
    IntrtextRelativePosition(-100.f, 40.f),
    MissionBoxSize(210.f, 150.f), // Debug box
    MissionBoxPosition(10.f, 10.f),
    ItemType(ESupportItemType::I_none),
    ItemBoxSize(200.f, 100.f), // Debug box
    ItemBoxRelativePosition(100.f, -100.f),
    InGeneratorRange(false),
    MissionItemsCollected(false),
    TimerRelativePosition(-20.f, 10.f),
    ResultScoreTextRelativePosition(0.f, -100.f),
    HighScoreTextRelativePosition(0.f, 40.f),
    WinOrLoseRelativePosition(0.f, 30.f)
{
    SetItem(ESupportItemType::I_battery, 0.f, 0);
    SetItem(ESupportItemType::I_fuel, 0.f, 0);
    SetItem(ESupportItemType::I_wire, 0.f, 0);
    SetItem(ESupportItemType::I_fuse, 0.f, 0);
    SetWeight(0.f);

    FString PackagePath = TEXT("/Game/Images/GameMap");
    UPackage* Package = LoadPackage(nullptr, *PackagePath, LOAD_None);
    if (Package)
        ImageTexture = LoadObject<UTexture2D>(Package, *PackagePath);
    else UE_LOG(LogTemp, Warning, TEXT("Package invalid in AP2NHF_HUD.cpp[50]"));
}

void AP2NHF_HUD::DrawHUD()
{
    Super::DrawHUD();

    switch (HUDState)
    {
    case EHUDState::S_start:
        DisplayStartScene();
        return;
    case EHUDState::S_introduction:
        DisplayIntroductionScene();
        return;
    case EHUDState::S_game:
        DisplayGameScene();
        return;
    case EHUDState::S_result:
        DisplayResultScene();
    default:
        UE_LOG(LogTemp, Warning, TEXT("Switch HUDState invalid in AP2NHF_HUD.cpp[59]"));
    }
}

FVector2D AP2NHF_HUD::AlignRelativeToCenterTop(const FVector2D& Param)
{
    return FVector2D(Canvas->SizeX / 2 + Param.X, Param.Y);
}

FVector2D AP2NHF_HUD::AlignRelativeToCenterBottom(const FVector2D& Param)
{
    return FVector2D(Canvas->SizeX / 2 + Param.X, Canvas->SizeY - Param.Y);
}

FVector2D AP2NHF_HUD::AlignRelativeToCenter(const FVector2D& Param)
{
    return FVector2D(Canvas->SizeX / 2 + Param.X, Canvas->SizeY / 2 + Param.Y);
}
// ====================================================================================================== 

// [1] Start Scene
// ====================================================================================================== 
void AP2NHF_HUD::DisplayStartScene()
{
    // Background
    DrawRect(FLinearColor(0.f, 0.f, 0.f, 1.f), 0.f, 0.f, Canvas->SizeX, Canvas->SizeY);

    // Image
    ImageSize = FVector2D(Canvas->SizeY * 0.9f, Canvas->SizeY * 0.9f);
    FVector2D ImagePosition = AlignRelativeToCenter(FVector2D(-ImageSize.X / 2, -ImageSize.Y / 2));
    if (ImageTexture)
    {
        #ifdef DebugMode
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("#debug: image loaded"));
        #endif
        FCanvasTileItem PictureItem(ImagePosition, ImageTexture->GetResource(), ImageSize, FLinearColor::White);
        Canvas->DrawItem(PictureItem);
    }
    else UE_LOG(LogTemp, Warning, TEXT("ImageTexture invalid in AP2NHF_HUD.cpp[103]"));

    // Start Text
    FVector2D StartTextPosition = AlignRelativeToCenterBottom(StartTextRelativePosition);
    DrawText(TEXT("Press SPACE to continue..."), FLinearColor::White, StartTextPosition.X, StartTextPosition.Y, nullptr, 1.2f, false);
}
// ====================================================================================================== 

// [2] Introduction Scene
// ====================================================================================================== 
void AP2NHF_HUD::DisplayIntroductionScene()
{
    // Background Box
    FVector2D IntrBackgroundBoxSize = FVector2D(Canvas->SizeY * 0.7f, Canvas->SizeY * 0.7f);
    FVector2D IntrBackgroundBoxRelativePosition = FVector2D(-IntrBackgroundBoxSize.X / 2, -IntrBackgroundBoxSize.Y / 2);
    FVector2D IntrBackgroundBoxPosition = AlignRelativeToCenter(IntrBackgroundBoxRelativePosition);
    DrawRect(BoxColor, IntrBackgroundBoxPosition.X, IntrBackgroundBoxPosition.Y, IntrBackgroundBoxSize.X, IntrBackgroundBoxSize.Y);
    
    // Title
    FVector2D IntrTitlePosition = IntrBackgroundBoxPosition + FVector2D(IntrBackgroundBoxSize.X / 2 + IntrTitleRelativePosition.X, IntrTitleRelativePosition.Y);
    DrawText(TEXT("Introduction"), FLinearColor::Green, IntrTitlePosition.X, IntrTitlePosition.Y, nullptr, 1.4f, false);
    
    // Text
    FVector2D IntrtextPosition = IntrTitlePosition + IntrtextRelativePosition;
    DrawText(IntrText, FLinearColor::White, IntrtextPosition.X, IntrtextPosition.Y, nullptr, 1.2f, false);
}
// ====================================================================================================== 

// [3] Game Scene:
// ====================================================================================================== 
// Mission
void AP2NHF_HUD::SetItem(const ESupportItemType& Type, const float Param, const int32 Qt)
{
    switch (Type)
    {
    case ESupportItemType::I_battery:
        Items[0] = FString::Printf(TEXT("Battery[%d] - %d%%"), Qt, int(Param));
        ItemsColor[0] = Param >= 0.7f ? FLinearColor::Green : FLinearColor::White;
        return;
    case ESupportItemType::I_fuel:
        Items[1] = FString::Printf(TEXT("Fuel[%d] - %.1fl"), Qt, Param);
        ItemsColor[1] = Param >= 25.f ? FLinearColor::Green : FLinearColor::White;
        return;
    case ESupportItemType::I_wire:
        Items[2] = FString::Printf(TEXT("Wire[%d] - %.1fm"), Qt, Param);
        ItemsColor[2] = Param >= 20.f ? FLinearColor::Green : FLinearColor::White;
        return;
    case ESupportItemType::I_fuse:
        Items[3] = FString::Printf(TEXT("Fuse[%d] - "), Qt) + FString(bool(Param) ? TEXT("useable") : TEXT("unuseable"));
        ItemsColor[3] = bool(Param) ? FLinearColor::Green : FLinearColor::White;
    default:
        UE_LOG(LogTemp, Warning, TEXT("Switch Type invalid in AP2NHF_HUD.cpp[145]"));
    }
}

void AP2NHF_HUD::SetWeight(const float Param)
{
    Weight = FString::Printf(TEXT("%.1fkg"), Param);
}

void AP2NHF_HUD::RenderMission()
{
    // Mission Box (Debug) + Mission Title 
    #ifdef DebugMode
    if (GEngine)
        DrawRect(BoxColor, MissionBoxPosition.X, MissionBoxPosition.Y, MissionBoxSize.X, MissionBoxSize.Y);
    #endif
    FVector2D MissionTitlePosition = MissionBoxPosition + FVector2D(10.f, 10.f);
    DrawText(TEXT("Collectibles"), FLinearColor::White, MissionTitlePosition.X, MissionTitlePosition.Y, nullptr, 1.5f, false);
    
    // Mission Items
    FVector2D TextPosition = MissionBoxPosition + FVector2D(10.f, 40.f);
    for (int i = 0; i < 4; i++)
    {
        DrawText(Items[i], ItemsColor[i], TextPosition.X, TextPosition.Y, nullptr, 1.f, false);
        TextPosition.Y += 20.f;
    }

    // Inventory Weight
    FVector2D WeightPosition = MissionBoxPosition + FVector2D(10.f, 120.f);
    DrawText(Weight, FLinearColor::Gray, WeightPosition.X, WeightPosition.Y, nullptr, 1.2f);
}

// Item info
void AP2NHF_HUD::SetItemInfo(const ESupportItemType& Type, const float Data, const float WeightParam)
{
    ItemType = Type;
    if (!(Type == ESupportItemType::I_none)) {
        switch (Type)
        {
        case ESupportItemType::I_battery:
            ItemInfo = TEXT("Battery");
            Infos[0] = FString::Printf(TEXT("Charge: %d%%"), int(Data));
            break;
        case ESupportItemType::I_fuel:
            ItemInfo = TEXT("Fuel");
            Infos[0] = FString::Printf(TEXT("Petrol: %.1fl"), Data);
            break;
        case ESupportItemType::I_wire:
            ItemInfo = TEXT("Wire");
            Infos[0] = FString::Printf(TEXT("Length: %.1fm"), Data);
            break;
        case ESupportItemType::I_fuse:
            ItemInfo = TEXT("Fuse");
            Infos[0] = FString(TEXT("Condition: ")) + FString(bool(Data) ? TEXT("useable") : TEXT("unuseable"));
        default:
            UE_LOG(LogTemp, Warning, TEXT("Switch Type invalid in AP2NHF_HUD.cpp[200]"));
        }
        Infos[1] = FString::Printf(TEXT("Weight: %.1fkg"), WeightParam);
    }
}

void AP2NHF_HUD::RenderInfos()
{
    // Found Item Box (Debug)
    FVector2D ItemBoxPosition = FVector2D(Canvas->SizeX / 2 + ItemBoxRelativePosition.X, Canvas->SizeY / 2 + ItemBoxRelativePosition.Y);
    #ifdef DebugMode
    if (GEngine)
        DrawRect(BoxColor, ItemBoxPosition.X, ItemBoxPosition.Y, ItemBoxSize.X, ItemBoxSize.Y);
    #endif

    // Found Item Title
    FVector2D ItemInfoPosition = ItemBoxPosition + FVector2D(10.f, 10.f);
    DrawText(ItemInfo, FLinearColor::Red, ItemInfoPosition.X, ItemInfoPosition.Y, nullptr, 1.4f, false);

    // Found Item Data
    FVector2D TextPosition = ItemBoxPosition + FVector2D(10.f, 40.f);
    for (const FString& Item : Infos)
    {
        DrawText(Item, FLinearColor::Yellow, TextPosition.X, TextPosition.Y, nullptr, 1.f, false);
        TextPosition.Y += 20.f;
    }
}

// Generator infos
void AP2NHF_HUD::RenderGeneratorInfo()
{
    FString GeneratorResponseMessage;
    MissionItemsCollected ? GeneratorResponseMessage = TEXT("You have the components, you can start the generator at any time.") : GeneratorResponseMessage = TEXT("You don't have the necessary components to start the generator...");
    FLinearColor GeneratorResponseColor;
    MissionItemsCollected ? GeneratorResponseColor = FLinearColor::Green : GeneratorResponseColor = FLinearColor::Red;
    GeneratorResponseTextRelativeLocation = FVector2D(-(6.5f * GeneratorResponseMessage.Len() / 2), 200.f);
    FVector2D GeneratorResponseTextLocation = AlignRelativeToCenter(GeneratorResponseTextRelativeLocation);
    DrawText(GeneratorResponseMessage, GeneratorResponseColor, GeneratorResponseTextLocation.X, GeneratorResponseTextLocation.Y, nullptr, 1.1f, false);
}

// Timer
void AP2NHF_HUD::SetTimerTime(const unsigned Param)
{
    TimerTime = FString::Printf(TEXT("%d:%d"), Param / 60, Param % 60);
}

void AP2NHF_HUD::RenderTimer()
{
    FVector2D TimerPosition = AlignRelativeToCenterTop(TimerRelativePosition);
    DrawText(TimerTime, FLinearColor::White, TimerPosition.X, TimerPosition.Y, nullptr, 1.5f, false);
}

void AP2NHF_HUD::DisplayGameScene()
{
    RenderMission();
    if (ItemType != ESupportItemType::I_none)
        RenderInfos();
    if (InGeneratorRange)
        RenderGeneratorInfo();
    RenderTimer();
}
// ====================================================================================================== 

// [4] Result Scene
// ======================================================================================================
void AP2NHF_HUD::SetResultScoreText(const unsigned Param)
{
    ResultScoreText = FString::Printf(TEXT("%d"), Param);
}

void AP2NHF_HUD::SetHighScoreText(const unsigned Param)
{
    HighScoreText = FString::Printf(TEXT("%d"), Param);
}

void AP2NHF_HUD::DisplayResultScene()
{
    // Background
    DrawRect(FLinearColor(0.f, 0.f, 0.f, 0.8f), 0.f, 0.f, Canvas->SizeX, Canvas->SizeY);

    // Score
    FString CurrentScoreTxt = TEXT("Score: ") + ResultScoreText;
    FVector2D CurrentScorePos = AlignRelativeToCenter(FVector2D(-(6.5f * CurrentScoreTxt.Len() / 2), ResultScoreTextRelativePosition.Y));
    DrawText(CurrentScoreTxt, FLinearColor::White, CurrentScorePos.X, CurrentScorePos.Y, nullptr, 1.5f, false);

    // High Score
    FString HighScoreTxt = TEXT("High Score: ") + HighScoreText;
    FVector2D HighScorePos = AlignRelativeToCenter(FVector2D(-(6.5f * HighScoreTxt.Len() / 2), ResultScoreTextRelativePosition.Y + HighScoreTextRelativePosition.Y));
    DrawText(HighScoreTxt, FLinearColor::White, HighScorePos.X, HighScorePos.Y, nullptr, 1.5f, false);

    // Win or Lose
    FString WinOrLoseTxt = MissionItemsCollected ? TEXT("You Won!!") : TEXT("You Lost...");
    FLinearColor WinOrLoseClr = MissionItemsCollected ? FLinearColor::Green : FLinearColor::Red;
    FVector2D WinOrLosePos = AlignRelativeToCenter(FVector2D(-(9.5f * WinOrLoseTxt.Len() / 2), WinOrLoseRelativePosition.Y));
    DrawText(WinOrLoseTxt, WinOrLoseClr, WinOrLosePos.X, WinOrLosePos.Y, nullptr, 2.f, false);
}
// ====================================================================================================== 