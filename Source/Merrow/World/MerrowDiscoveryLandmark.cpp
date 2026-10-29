#include "MerrowDiscoveryLandmark.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

AMerrowDiscoveryLandmark::AMerrowDiscoveryLandmark()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    LandmarkBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LandmarkBase"));
    LandmarkBase->SetupAttachment(RootComponent);
    LandmarkBase->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    LandmarkBase->SetCollisionProfileName(TEXT("BlockAll"));

    LandmarkMarker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LandmarkMarker"));
    LandmarkMarker->SetupAttachment(RootComponent);
    LandmarkMarker->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeMesh(TEXT("/Engine/BasicShapes/Cone.Cone"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));

    if (CubeMesh.Succeeded())
    {
        CubeMarkerMesh = CubeMesh.Object;
    }
    if (SphereMesh.Succeeded())
    {
        SphereMarkerMesh = SphereMesh.Object;
    }
    if (ConeMesh.Succeeded())
    {
        ConeMarkerMesh = ConeMesh.Object;
    }
    if (CylinderMesh.Succeeded())
    {
        CylinderMarkerMesh = CylinderMesh.Object;
        LandmarkBase->SetStaticMesh(CylinderMesh.Object);
    }
}

void AMerrowDiscoveryLandmark::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    LandmarkBase->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
    LandmarkBase->SetRelativeScale3D(FVector(2.4f, 2.4f, 0.6f));
    LandmarkMarker->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f));

    switch (SiteType)
    {
        case EMerrowDiscoverySiteType::LostPageShrine:
            LandmarkMarker->SetStaticMesh(ConeMarkerMesh);
            LandmarkMarker->SetRelativeScale3D(FVector(0.45f, 0.45f, 0.9f));
            break;

        case EMerrowDiscoverySiteType::LoreRelic:
            LandmarkMarker->SetStaticMesh(SphereMarkerMesh);
            LandmarkMarker->SetRelativeScale3D(FVector(0.85f, 0.85f, 0.85f));
            break;

        case EMerrowDiscoverySiteType::CorruptionScar:
            LandmarkMarker->SetStaticMesh(ConeMarkerMesh);
            LandmarkMarker->SetRelativeScale3D(FVector(0.55f, 0.55f, 1.7f));
            break;

        case EMerrowDiscoverySiteType::AncientGate:
            LandmarkMarker->SetStaticMesh(CubeMarkerMesh);
            LandmarkBase->SetRelativeScale3D(FVector(3.5f, 0.8f, 0.6f));
            LandmarkMarker->SetRelativeLocation(FVector(0.0f, 0.0f, 185.0f));
            LandmarkMarker->SetRelativeScale3D(FVector(1.5f, 0.35f, 1.5f));
            break;

        case EMerrowDiscoverySiteType::BossArena:
            LandmarkMarker->SetStaticMesh(CylinderMarkerMesh);
            LandmarkBase->SetRelativeScale3D(FVector(5.0f, 5.0f, 0.35f));
            LandmarkMarker->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
            LandmarkMarker->SetRelativeScale3D(FVector(1.8f, 1.8f, 0.35f));
            break;

        default:
            LandmarkMarker->SetStaticMesh(CubeMarkerMesh);
            LandmarkMarker->SetRelativeScale3D(FVector(0.5f));
            break;
    }
}
