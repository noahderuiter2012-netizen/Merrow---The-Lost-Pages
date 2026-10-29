#include "MerrowForestSceneDirector.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

AMerrowForestSceneDirector::AMerrowForestSceneDirector()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    ForestGround = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ForestGround"));
    ForestGround->SetupAttachment(RootComponent);
    ForestGround->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    ForestGround->SetCollisionProfileName(TEXT("BlockAll"));
    ForestGround->SetMobility(EComponentMobility::Static);

    TreeTrunks = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeTrunks"));
    TreeTrunks->SetupAttachment(RootComponent);
    TreeTrunks->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    TreeTrunks->SetCollisionProfileName(TEXT("BlockAll"));

    TreeCanopies = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TreeCanopies"));
    TreeCanopies->SetupAttachment(RootComponent);
    TreeCanopies->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    ForestRocks = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ForestRocks"));
    ForestRocks->SetupAttachment(RootComponent);
    ForestRocks->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    ForestRocks->SetCollisionProfileName(TEXT("BlockAll"));

    RuinBlocks = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("RuinBlocks"));
    RuinBlocks->SetupAttachment(RootComponent);
    RuinBlocks->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    RuinBlocks->SetCollisionProfileName(TEXT("BlockAll"));

    AncientPathStones = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("AncientPathStones"));
    AncientPathStones->SetupAttachment(RootComponent);
    AncientPathStones->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    AncientPathStones->SetCollisionProfileName(TEXT("BlockAll"));

    CorruptionCrystals = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("CorruptionCrystals"));
    CorruptionCrystals->SetupAttachment(RootComponent);
    CorruptionCrystals->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeMesh(TEXT("/Engine/BasicShapes/Cone.Cone"));

    if (PlaneMesh.Succeeded())
    {
        ForestGround->SetStaticMesh(PlaneMesh.Object);
    }
    if (CylinderMesh.Succeeded())
    {
        TreeTrunks->SetStaticMesh(CylinderMesh.Object);
    }
    if (SphereMesh.Succeeded())
    {
        TreeCanopies->SetStaticMesh(SphereMesh.Object);
        ForestRocks->SetStaticMesh(SphereMesh.Object);
    }
    if (CubeMesh.Succeeded())
    {
        RuinBlocks->SetStaticMesh(CubeMesh.Object);
        AncientPathStones->SetStaticMesh(CubeMesh.Object);
    }
    if (ConeMesh.Succeeded())
    {
        CorruptionCrystals->SetStaticMesh(ConeMesh.Object);
    }
}

void AMerrowForestSceneDirector::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    RebuildForest();
}

void AMerrowForestSceneDirector::RebuildForest()
{
    if (!ForestGround || !TreeTrunks || !TreeCanopies || !ForestRocks ||
        !RuinBlocks || !AncientPathStones || !CorruptionCrystals)
    {
        return;
    }

    TreeTrunks->ClearInstances();
    TreeCanopies->ClearInstances();
    ForestRocks->ClearInstances();
    RuinBlocks->ClearInstances();
    AncientPathStones->ClearInstances();
    CorruptionCrystals->ClearInstances();

    const float SafeRadius = FMath::Max(1000.0f, ForestRadius);
    const float ClearingRadius = SafeRadius * 0.17f;
    const float ClearingRadiusSq = FMath::Square(ClearingRadius);

    // The plane gives the blockout a walkable visual base. Replace it with a
    // sculpted Landscape and layered ground materials during the art pass.
    if (ForestGround->GetStaticMesh())
    {
        ForestGround->SetRelativeLocation(FVector(0.0f, 0.0f, -24.0f));
        ForestGround->SetRelativeScale3D(FVector(SafeRadius / 50.0f, SafeRadius / 50.0f, 1.0f));
    }

    FRandomStream Random(RandomSeed);

    // Keep the centre open for a discovery space or a later encounter arena.
    for (int32 Index = 0; Index < TreeCount; ++Index)
    {
        FVector Position;
        int32 Attempts = 0;
        do
        {
            Position = FVector(
                Random.FRandRange(-SafeRadius, SafeRadius),
                Random.FRandRange(-SafeRadius, SafeRadius),
                0.0f);
            ++Attempts;
        }
        while ((Position.SizeSquared2D() > SafeRadius * SafeRadius ||
                Position.SizeSquared2D() < ClearingRadiusSq) && Attempts < 40);

        const float Height = Random.FRandRange(7.0f, 13.0f);
        const float Width = Random.FRandRange(0.55f, 1.15f);
        const FRotator YawOnly(0.0f, Random.FRandRange(0.0f, 360.0f), 0.0f);

        TreeTrunks->AddInstance(FTransform(YawOnly, Position + FVector(0, 0, Height * 50.0f),
            FVector(Width, Width, Height)));

        const float CanopyScale = Random.FRandRange(3.2f, 5.8f);
        const FVector CanopyPosition = Position + FVector(
            Random.FRandRange(-80.0f, 80.0f),
            Random.FRandRange(-80.0f, 80.0f),
            Height * 100.0f + Random.FRandRange(100.0f, 260.0f));

        TreeCanopies->AddInstance(FTransform(FRotator::ZeroRotator, CanopyPosition,
            FVector(CanopyScale, CanopyScale, CanopyScale * Random.FRandRange(0.8f, 1.25f))));
    }

    for (int32 Index = 0; Index < RockCount; ++Index)
    {
        const float Angle = Random.FRandRange(0.0f, UE_TWO_PI);
        const float Radius = Random.FRandRange(ClearingRadius * 0.75f, SafeRadius);
        const FVector Position(FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius, 0.0f);
        const FVector Scale(
            Random.FRandRange(0.6f, 2.4f),
            Random.FRandRange(0.7f, 2.0f),
            Random.FRandRange(0.5f, 1.5f));

        ForestRocks->AddInstance(FTransform(
            FRotator(0.0f, Random.FRandRange(0.0f, 360.0f), Random.FRandRange(-18.0f, 18.0f)),
            Position + FVector(0, 0, Scale.Z * 35.0f), Scale));
    }

    for (int32 Index = 0; Index < RuinBlockCount; ++Index)
    {
        const float Angle = Random.FRandRange(0.0f, UE_TWO_PI);
        const float Radius = Random.FRandRange(ClearingRadius * 1.1f, SafeRadius * 0.82f);
        const FVector Position(FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius, 45.0f);
        const FVector Scale(
            Random.FRandRange(0.8f, 2.3f),
            Random.FRandRange(0.8f, 2.3f),
            Random.FRandRange(0.7f, 2.8f));

        RuinBlocks->AddInstance(FTransform(
            FRotator(0.0f, Random.FRandRange(0.0f, 360.0f), Random.FRandRange(-8.0f, 8.0f)),
            Position, Scale));
    }

    // A broken, slightly winding old road leads out of the clearing.
    for (int32 Index = 0; Index < PathStoneCount; ++Index)
    {
        const float Alpha = (static_cast<float>(Index) + 0.5f) / FMath::Max(1, PathStoneCount);
        const float Distance = FMath::Lerp(ClearingRadius * 1.08f, SafeRadius * 0.84f, Alpha);
        const float Curve = FMath::Sin(Alpha * UE_TWO_PI * 0.65f) * 150.0f;
        const FVector Position(Distance, Curve + Random.FRandRange(-24.0f, 24.0f), 1.0f);
        const FVector Scale(Random.FRandRange(0.85f, 1.3f), Random.FRandRange(0.5f, 0.85f), 0.12f);

        AncientPathStones->AddInstance(FTransform(
            FRotator(0.0f, Random.FRandRange(-8.0f, 8.0f), 0.0f), Position, Scale));
    }

    // Crystal clusters favour the outer ring, suggesting corruption is
    // advancing toward the still-protected clearing.
    const float CorruptionScale = FMath::Clamp(CorruptionIntensity, 0.0f, 1.0f);
    for (int32 Index = 0; Index < CrystalCount; ++Index)
    {
        const float Angle = Random.FRandRange(0.0f, UE_TWO_PI);
        const float Radius = Random.FRandRange(SafeRadius * 0.48f, SafeRadius * 0.94f);
        const FVector Position(FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius, 90.0f);
        const float Scale = FMath::Lerp(0.7f, 2.0f, CorruptionScale);

        CorruptionCrystals->AddInstance(FTransform(
            FRotator(Random.FRandRange(-10.0f, 10.0f),
                Random.FRandRange(0.0f, 360.0f),
                Random.FRandRange(-12.0f, 12.0f)),
            Position,
            FVector(Scale, Scale, Scale * Random.FRandRange(1.5f, 3.2f))));
    }
}
