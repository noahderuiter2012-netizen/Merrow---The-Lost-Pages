#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MerrowAncientGate.generated.h"

class UStaticMeshComponent;
class AMerrowPlayerCharacter;

UCLASS()
class MERROW_API AMerrowAncientGate : public AActor
{
    GENERATED_BODY()

public:
    AMerrowAncientGate();

    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Gate")
    TObjectPtr<UStaticMeshComponent> LeftPillar;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Gate")
    TObjectPtr<UStaticMeshComponent> RightPillar;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Gate")
    TObjectPtr<UStaticMeshComponent> Lintel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Gate")
    TObjectPtr<UStaticMeshComponent> DoorPanel;

    UFUNCTION(BlueprintPure, Category="Merrow|Gate")
    bool IsOpen() const { return bOpen; }

    UFUNCTION(BlueprintCallable, Category="Merrow|Gate")
    void OpenGate(AMerrowPlayerCharacter* Player);

private:
    bool bOpen = false;
    bool bAnimating = false;
    float OpenAngle = 0.0f;
};
