#include "MerrowGameMode.h"
#include "MerrowPlayerCharacter.h"
#include "MerrowLostPagePickup.h"
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

    // Temporary auto-bootstrap means an empty test level can still launch the first slice.
    // Once the authored level exists, disable this or remove these spawned actors.
    if (!GetWorld()) return;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    GetWorld()->SpawnActor<AMerrowForestSceneDirector>(
        AMerrowForestSceneDirector::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);

    GetWorld()->SpawnActor<AMerrowLostPagePickup>(
        AMerrowLostPagePickup::StaticClass(), FVector(1800.0f, 0.0f, 130.0f), FRotator::ZeroRotator, Params);
}
