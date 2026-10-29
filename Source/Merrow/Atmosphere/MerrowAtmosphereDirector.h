#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MerrowAtmosphereDirector.generated.h"

class UExponentialHeightFogComponent;

/** Blends Merrow's fog from its natural look toward emerald corruption. */
UCLASS(Blueprintable)
class MERROW_API AMerrowAtmosphereDirector : public AActor
{
    GENERATED_BODY()

public:
    AMerrowAtmosphereDirector();

    UFUNCTION(BlueprintCallable, Category = "Merrow|Atmosphere")
    void SetCorruptionIntensity(float NewIntensity);

    UFUNCTION(BlueprintPure, Category = "Merrow|Atmosphere")
    float GetCorruptionIntensity() const { return CorruptionIntensity; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UExponentialHeightFogComponent> HeightFog;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Merrow|Atmosphere", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float CorruptionIntensity = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Merrow|Atmosphere", meta = (ClampMin = "0.0"))
    float CleanFogDensity = 0.012f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Merrow|Atmosphere", meta = (ClampMin = "0.0"))
    float CorruptedFogDensity = 0.035f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Merrow|Atmosphere")
    FLinearColor CleanFogColor = FLinearColor(0.34f, 0.40f, 0.43f, 1.0f);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Merrow|Atmosphere")
    FLinearColor CorruptedFogColor = FLinearColor(0.035f, 0.20f, 0.095f, 1.0f);

private:
    void ApplyAtmosphere();
};