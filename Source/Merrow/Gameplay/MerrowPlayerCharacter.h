#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MerrowPlayerCharacter.generated.h"

class UCameraComponent;
class AMerrowLostPagePickup;

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Merrow|Interaction")
    float InteractionDistance = 350.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Interaction")
    bool bCanInteract = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Interaction")
    FText CurrentInteractionPrompt;

    UFUNCTION(BlueprintCallable, Category="Merrow|Progress")
    void RecoverLostPage();

protected:
    virtual void BeginPlay() override;
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void TryInteract();

private:
    TWeakObjectPtr<AMerrowLostPagePickup> FocusedPage;
};
