#include "MerrowAtmosphereDirector.h"

#include "Components/ExponentialHeightFogComponent.h"
#include "Merrow.h"

AMerrowAtmosphereDirector::AMerrowAtmosphereDirector()
{
    PrimaryActorTick.bCanEverTick = false;
    HeightFog = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("HeightFog"));
    SetRootComponent(HeightFog);
}

void AMerrowAtmosphereDirector::BeginPlay()
{
    Super::BeginPlay();
    ApplyAtmosphere();

    UE_LOG(LogMerrow, Log, TEXT("Atmosphere initialized. Corruption intensity: %.2f"), CorruptionIntensity);
}

void AMerrowAtmosphereDirector::SetCorruptionIntensity(float NewIntensity)
{
    CorruptionIntensity = FMath::Clamp(NewIntensity, 0.0f, 1.0f);
    ApplyAtmosphere();
}

void AMerrowAtmosphereDirector::ApplyAtmosphere()
{
    if (!HeightFog)
    {
        return;
    }

    HeightFog->FogDensity = FMath::Lerp(CleanFogDensity, CorruptedFogDensity, CorruptionIntensity);
    HeightFog->FogInscatteringColor = FLinearColor::LerpUsingHSV(
        CleanFogColor,
        CorruptedFogColor,
        CorruptionIntensity
    );
}