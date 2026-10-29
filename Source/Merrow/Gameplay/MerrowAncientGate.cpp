#include "MerrowAncientGate.h"
#include "MerrowPlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

AMerrowAncientGate::AMerrowAncientGate()
{
    PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    const auto MakeBlock = [this, &CubeMesh](const TCHAR* Name, const FVector& Location, const FVector& Scale)
    {
        UStaticMeshComponent* Part = CreateDefaultSubobject<UStaticMeshComponent>(Name);
        Part->SetupAttachment(RootComponent);
        Part->SetRelativeLocation(Location);
        Part->SetRelativeScale3D(Scale);
        Part->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        Part->SetCollisionResponseToAllChannels(ECR_Block);
        if (CubeMesh.Succeeded()) Part->SetStaticMesh(CubeMesh.Object);
        return Part;
    };

    LeftPillar = MakeBlock(TEXT("LeftPillar"), FVector(0.0f, -260.0f, 300.0f), FVector(0.6f, 0.6f, 6.0f));
    RightPillar = MakeBlock(TEXT("RightPillar"), FVector(0.0f, 260.0f, 300.0f), FVector(0.6f, 0.6f, 6.0f));
    Lintel = MakeBlock(TEXT("Lintel"), FVector(0.0f, 0.0f, 610.0f), FVector(0.6f, 5.8f, 0.55f));
    DoorPanel = MakeBlock(TEXT("DoorPanel"), FVector(0.0f, 0.0f, 220.0f), FVector(0.18f, 4.7f, 2.2f));
}

void AMerrowAncientGate::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (bAnimating && DoorPanel)
    {
        OpenAngle = FMath::FInterpTo(OpenAngle, 92.0f, DeltaSeconds, 1.4f);
        DoorPanel->SetRelativeRotation(FRotator(0.0f, OpenAngle, 0.0f));
        if (OpenAngle >= 90.0f)
        {
            bAnimating = false;
            DoorPanel->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }
    }
}

void AMerrowAncientGate::OpenGate(AMerrowPlayerCharacter* Player)
{
    if (bOpen || !IsValid(Player)) return;
    if (Player->PagesRecovered < 7)
    {
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor(180, 210, 180),
            TEXT("The ancient gate requires all seven lost pages."));
        return;
    }
    bOpen = true;
    bAnimating = true;
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor(150, 255, 170),
        TEXT("The seven pages awaken the gate."));
    Player->CompleteChapter();
}
