#include "MerrowLostPagePickup.h"
#include "MerrowPlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"

AMerrowLostPagePickup::AMerrowLostPagePickup()
{
    PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    PageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PageMesh"));
    PageMesh->SetupAttachment(RootComponent);
    PageMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    PageMesh->SetCollisionResponseToAllChannels(ECR_Block);
    PageMesh->SetRelativeScale3D(FVector(0.08f, 0.12f, 0.015f));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));
    if (PlaneMesh.Succeeded()) PageMesh->SetStaticMesh(PlaneMesh.Object);

    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->SetupAttachment(RootComponent);
    InteractionSphere->SetSphereRadius(150.0f);
    InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AMerrowLostPagePickup::BeginPlay()
{
    Super::BeginPlay();
    FloatPhase = FMath::FRandRange(0.0f, UE_TWO_PI);
}

void AMerrowLostPagePickup::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!bCollected && PageMesh)
    {
        FloatPhase += DeltaSeconds;
        PageMesh->AddLocalRotation(FRotator(0.0f, DeltaSeconds * 28.0f, 0.0f));
        PageMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 18.0f + FMath::Sin(FloatPhase * 1.5f) * 8.0f));
    }
}

void AMerrowLostPagePickup::Collect(AMerrowPlayerCharacter* Collector)
{
    if (bCollected || !IsValid(Collector)) return;
    bCollected = true;
    Collector->RecoverLostPage();
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
}
