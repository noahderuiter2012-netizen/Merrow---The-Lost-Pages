#include "MerrowGameMode.h"
#include "MerrowPlayerCharacter.h"
#include "MerrowLostPagePickup.h"
#include "MerrowAncientGate.h"
#include "MerrowHUD.h"
#include "MerrowForestSceneDirector.h"
#include "Engine/World.h"

AMerrowGameMode::AMerrowGameMode()
{
    DefaultPawnClass = AMerrowPlayerCharacter::StaticClass();
    HUDClass = AMerrowHUD::StaticClass();
}

void AMerrowGameMode::StartPlay()
{
    Super::StartPlay();
    if (!GetWorld()) return;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    GetWorld()->SpawnActor<AMerrowForestSceneDirector>(
        AMerrowForestSceneDirector::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

    // Seven pages are placed along the broken ancient path, with the gate behind the starting clearing.
    const FVector PageLocations[7] =
    {
        FVector(2100.0f, 0.0f, 130.0f),
        FVector(3000.0f, 130.0f, 130.0f),
        FVector(4050.0f, -150.0f, 130.0f),
        FVector(5100.0f, 20.0f, 130.0f),
        FVector(6100.0f, 160.0f, 130.0f),
        FVector(7000.0f, -100.0f, 130.0f),
        FVector(7750.0f, 80.0f, 130.0f)
    };

    for (int32 Index = 0; Index < 7; ++Index)
    {
        if (AMerrowLostPagePickup* Page = GetWorld()->SpawnActor<AMerrowLostPagePickup>(
            AMerrowLostPagePickup::StaticClass(), PageLocations[Index], FRotator(90.0f, 0.0f, 0.0f), Params))
        {
            Page->PageNumber = Index + 1;
            Page->PageTitle = FText::FromString(FString::Printf(TEXT("Missing Page %d"), Index + 1));
        }
    }

    GetWorld()->SpawnActor<AMerrowAncientGate>(
        AMerrowAncientGate::StaticClass(), FVector(-850.0f, 0.0f, 0.0f), FRotator::ZeroRotator, Params);
}
