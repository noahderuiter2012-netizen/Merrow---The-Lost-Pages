#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MerrowPlayerCharacter.generated.h"

class UCameraComponent;
class AMerrowLostPagePickup;
class AMerrowAncientGate;

UCLASS()
class MERROW_API AMerrowPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMerrowPlayerCharacter();

    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Camera")
    TObjectPtr<UCameraComponent> FirstPersonCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Progress")
    int32 PagesRecovered = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Progress")
    bool bChapterComplete = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Movement")
    float Stamina = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Merrow|Movement")
    float MaxStamina = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Merrow|Movement")
    float SprintDrainPerSecond = 28.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Merrow|Movement")
    float StaminaRecoveryPerSecond = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Merrow|Interaction")
    float InteractionDistance = 500.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Interaction")
    bool bCanInteract = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Interaction")
    FText CurrentInteractionPrompt;

    UFUNCTION(BlueprintCallable, Category="Merrow|Progress")
    void RecoverLostPage();

    UFUNCTION(BlueprintCallable, Category="Merrow|Progress")
    void CompleteChapter();

protected:
    virtual void BeginPlay() override;
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void StartSprint();
    void StopSprint();
    void TryInteract();

private:
    TWeakObjectPtr<AMerrowLostPagePickup> FocusedPage;
    TWeakObjectPtr<AMerrowAncientGate> FocusedGate;
    bool bWantsSprint = false;
};
