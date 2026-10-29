#include "MerrowPlayerCharacter.h"
#include "MerrowLostPagePickup.h"
#include "MerrowAncientGate.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"

AMerrowPlayerCharacter::AMerrowPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
    bUseControllerRotationYaw = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->MaxWalkSpeed = 420.0f;
    GetCharacterMovement()->BrakingDecelerationWalking = 1600.0f;

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
    FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
    FirstPersonCamera->bUsePawnControlRotation = true;
}

void AMerrowPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->SetInputMode(FInputModeGameOnly());
        PC->bShowMouseCursor = false;
    }
}

void AMerrowPlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    FocusedPage.Reset();
    FocusedGate.Reset();
    bCanInteract = false;
    CurrentInteractionPrompt = FText::GetEmpty();

    if (!FirstPersonCamera || !GetWorld() || bChapterComplete) return;

    const FVector Start = FirstPersonCamera->GetComponentLocation();
    const FVector End = Start + FirstPersonCamera->GetForwardVector() * InteractionDistance;
    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(MerrowInteraction), false, this);

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
    {
        if (AMerrowLostPagePickup* Page = Cast<AMerrowLostPagePickup>(Hit.GetActor()))
        {
            if (!Page->IsCollected())
            {
                FocusedPage = Page;
                bCanInteract = true;
                CurrentInteractionPrompt = FText::FromString(FString::Printf(
                    TEXT("Press E to recover page %d"), Page->PageNumber));
                return;
            }
        }

        if (AMerrowAncientGate* Gate = Cast<AMerrowAncientGate>(Hit.GetActor()))
        {
            if (!Gate->IsOpen())
            {
                FocusedGate = Gate;
                bCanInteract = true;
                CurrentInteractionPrompt = PagesRecovered >= 7
                    ? FText::FromString(TEXT("Press E to open the ancient gate"))
                    : FText::FromString(FString::Printf(TEXT("The gate needs all 7 pages (%d / 7)"), PagesRecovered));
            }
        }
    }
}

void AMerrowPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMerrowPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMerrowPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMerrowPlayerCharacter::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMerrowPlayerCharacter::LookUp);
    PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AMerrowPlayerCharacter::TryInteract);
}

void AMerrowPlayerCharacter::MoveForward(float Value)
{
    if (Controller && !FMath::IsNearlyZero(Value))
        AddMovementInput(FRotationMatrix(FRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), Value);
}

void AMerrowPlayerCharacter::MoveRight(float Value)
{
    if (Controller && !FMath::IsNearlyZero(Value))
        AddMovementInput(FRotationMatrix(FRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), Value);
}

void AMerrowPlayerCharacter::Turn(float Value) { AddControllerYawInput(Value); }
void AMerrowPlayerCharacter::LookUp(float Value) { AddControllerPitchInput(Value); }

void AMerrowPlayerCharacter::TryInteract()
{
    if (bChapterComplete) return;

    if (AMerrowLostPagePickup* Page = FocusedPage.Get())
    {
        if (!Page->IsCollected()) Page->Collect(this);
        FocusedPage.Reset();
        bCanInteract = false;
        return;
    }

    if (AMerrowAncientGate* Gate = FocusedGate.Get())
    {
        if (PagesRecovered >= 7) Gate->OpenGate(this);
        else if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor(180, 210, 180),
            FString::Printf(TEXT("The gate remains sealed. Recover all pages: %d / 7"), PagesRecovered));
    }
}

void AMerrowPlayerCharacter::RecoverLostPage()
{
    PagesRecovered = FMath::Clamp(PagesRecovered + 1, 0, 7);
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor(120, 235, 150),
            FString::Printf(TEXT("Lost page recovered: %d / 7"), PagesRecovered));
    }
}

void AMerrowPlayerCharacter::CompleteChapter()
{
    if (bChapterComplete) return;
    bChapterComplete = true;
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->SetIgnoreMoveInput(true);
        PC->SetIgnoreLookInput(true);
    }
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 12.0f, FColor(150, 255, 170),
            TEXT("CHAPTER COMPLETE - The first seven pages are recovered. The next trail awaits."));
}
