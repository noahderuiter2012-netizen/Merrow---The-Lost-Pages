#include "MerrowPlayerCharacter.h"
#include "MerrowLostPagePickup.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
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
    bCanInteract = false;
    CurrentInteractionPrompt = FText::GetEmpty();

    if (!FirstPersonCamera || !GetWorld()) return;

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
                CurrentInteractionPrompt = FText::FromString(TEXT("Press E to recover the lost page"));
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
    if (AMerrowLostPagePickup* Page = FocusedPage.Get())
    {
        if (!Page->IsCollected())
        {
            Page->Collect(this);
            FocusedPage.Reset();
            bCanInteract = false;
        }
    }
}

void AMerrowPlayerCharacter::RecoverLostPage()
{
    ++PagesRecovered;
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor(120, 235, 150),
            FString::Printf(TEXT("Lost page recovered: %d / 7"), PagesRecovered));
    }
}
