// Matus Zoltan - R9FJIV

/*
* TWE - P2NHF_Item_PhysicalRep.cpp
*/

#include "P2NHF_Item_PhysicalRep.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "P2NHF_Player_Character.h"
#include "P2NHF_HUD.h"

// ======================================================================================================
AP2NHF_Item_PhysicalRep::AP2NHF_Item_PhysicalRep()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	InternalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	InternalMesh->SetupAttachment(RootComponent);

	DetectionZone = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionZone"));
	DetectionZone->SetupAttachment(RootComponent);
	DetectionZone->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	DetectionZone->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	DetectionZone->OnComponentBeginOverlap.AddDynamic(this, &AP2NHF_Item_PhysicalRep::OnPlayerEnterDetectionZone);
	DetectionZone->OnComponentEndOverlap.AddDynamic(this, &AP2NHF_Item_PhysicalRep::OnPlayerLeaveDetectionZone);
}

void AP2NHF_Item_PhysicalRep::BeginPlay()
{
	Super::BeginPlay();
}

void AP2NHF_Item_PhysicalRep::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerCharacter)
	{
		if (PlayerInsideDetectionZone && PlayerCharacter->GetPickEventFlag())
			Interact();
	}
	else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter invalid in AP2NHF_Item_PhysicalRep.cpp[42]"));
}

void AP2NHF_Item_PhysicalRep::OnPlayerEnterDetectionZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
		PlayerCharacter = Cast<AP2NHF_Player_Character>(OtherActor);
		if (PlayerCharacter)
		{
			AP2NHF_HUD* CurrentHUD = PlayerCharacter->GetPlayerCharacterHUD();
			if (CurrentHUD)
			{
				PlayerCharacterHUD = Cast<AP2NHF_HUD>(CurrentHUD);
				PlayerInsideDetectionZone = true;
				DisplayInfo();
			}
			else UE_LOG(LogTemp, Warning, TEXT("CurrentHUD invalid in AP2NHF_Item_PhysicalRep.cpp[57]"));
		}
		else UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter invalid in AP2NHF_Item_PhysicalRep.cpp[53]"));
}

void AP2NHF_Item_PhysicalRep::OnPlayerLeaveDetectionZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	HideInfo();
	PlayerInsideDetectionZone = false;
	PlayerCharacter = nullptr;
	PlayerCharacterHUD = nullptr;
}
// ======================================================================================================