#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MerrowForestSceneDirector.generated.h"

class UInstancedStaticMeshComponent;
class UStaticMeshComponent;

/**
 * Runtime/editor blockout generator for Merrow's first Ancient Forest test area.
 * Uses engine primitive meshes as replaceable placeholders, not final art.
 */
UCLASS(Blueprintable)
class MERROW_API AMerrowForestSceneDirector : public AActor
{
    GENERATED_BODY()

public:
    AMerrowForestSceneDirector();

    /** Rebuilds the deterministic forest blockout when edited in the editor. */
    virtual void OnConstruction(const FTransform& Transform) override;

    /** Rebuild the layout from C++ or Blueprint. */
    UFUNCTION(BlueprintCallable, Category = "Merrow|World")
    void RebuildForest();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Merrow|World")
    TObjectPtr<UStaticMeshComponent> ForestGround;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Merrow|World")
    TObjectPtr<UInstancedStaticMeshComponent> TreeTrunks;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Merrow|World")
    TObjectPtr<UInstancedStaticMeshComponent> TreeCanopies;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Merrow|World")
    TObjectPtr<UInstancedStaticMeshComponent> ForestRocks;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Merrow|World")
    TObjectPtr<UInstancedStaticMeshComponent> RuinBlocks;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Merrow|World")
    TObjectPtr<UInstancedStaticMeshComponent> AncientPathStones;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Merrow|World")
    TObjectPtr<UInstancedStaticMeshComponent> CorruptionCrystals;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|World", meta = (ClampMin = "0", ClampMax = "100"))
    int32 TreeCount = 90;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|World", meta = (ClampMin = "0", ClampMax = "100"))
    int32 RockCount = 42;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|World", meta = (ClampMin = "0", ClampMax = "80"))
    int32 RuinBlockCount = 24;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|World", meta = (ClampMin = "0", ClampMax = "30"))
    int32 CrystalCount = 9;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|World", meta = (ClampMin = "0", ClampMax = "48"))
    int32 PathStoneCount = 28;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|World", meta = (ClampMin = "1000", ClampMax = "30000"))
    float ForestRadius = 9000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|World")
    int32 RandomSeed = 7319;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|World", meta = (ClampMin = "0", ClampMax = "1"))
    float CorruptionIntensity = 0.65f;
};
