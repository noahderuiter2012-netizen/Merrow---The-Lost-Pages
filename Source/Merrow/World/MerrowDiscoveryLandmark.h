#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MerrowDiscoveryLandmark.generated.h"

class UStaticMesh;
class UStaticMeshComponent;

UENUM(BlueprintType)
enum class EMerrowDiscoverySiteType : uint8
{
    LostPageShrine UMETA(DisplayName = "Lost Page Shrine"),
    LoreRelic UMETA(DisplayName = "Lore Relic"),
    CorruptionScar UMETA(DisplayName = "Corruption Scar"),
    AncientGate UMETA(DisplayName = "Ancient Gate"),
    BossArena UMETA(DisplayName = "Boss Arena")
};

/**
 * Editor-placeable marker for story and exploration locations.
 * The mesh is a greybox visual; interaction and saving are separate future systems.
 */
UCLASS(Blueprintable)
class MERROW_API AMerrowDiscoveryLandmark : public AActor
{
    GENERATED_BODY()

public:
    AMerrowDiscoveryLandmark();

    virtual void OnConstruction(const FTransform& Transform) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Merrow|Discovery")
    TObjectPtr<UStaticMeshComponent> LandmarkBase;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Merrow|Discovery")
    TObjectPtr<UStaticMeshComponent> LandmarkMarker;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|Discovery")
    EMerrowDiscoverySiteType SiteType = EMerrowDiscoverySiteType::LostPageShrine;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|Discovery")
    FText SiteTitle = FText::FromString(TEXT("Forgotten Page Shrine"));

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|Discovery", meta = (MultiLine = "true"))
    FText DiscoveryClue = FText::FromString(TEXT("A page was taken from this place. Something disturbed the old roots."));

    /** Use -1 for landmarks that are not tied to a numbered page. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Merrow|Discovery", meta = (ClampMin = "-1", ClampMax = "99"))
    int32 LostPageIndex = -1;

protected:
    UPROPERTY(Transient)
    TObjectPtr<UStaticMesh> CubeMarkerMesh;

    UPROPERTY(Transient)
    TObjectPtr<UStaticMesh> SphereMarkerMesh;

    UPROPERTY(Transient)
    TObjectPtr<UStaticMesh> ConeMarkerMesh;

    UPROPERTY(Transient)
    TObjectPtr<UStaticMesh> CylinderMarkerMesh;
};
