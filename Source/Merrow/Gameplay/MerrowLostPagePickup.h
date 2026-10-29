#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MerrowLostPagePickup.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class AMerrowPlayerCharacter;

UCLASS()
class MERROW_API AMerrowLostPagePickup : public AActor
{
    GENERATED_BODY()

public:
    AMerrowLostPagePickup();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Page")
    TObjectPtr<UStaticMeshComponent> PageMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Merrow|Page")
    TObjectPtr<USphereComponent> InteractionSphere;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Merrow|Page")
    int32 PageNumber = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Merrow|Page")
    FText PageTitle = FText::FromString(TEXT("The First Missing Page"));

    UFUNCTION(BlueprintPure, Category="Merrow|Page")
    bool IsCollected() const { return bCollected; }

    UFUNCTION(BlueprintCallable, Category="Merrow|Page")
    void Collect(AMerrowPlayerCharacter* Collector);

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    bool bCollected = false;
    float FloatPhase = 0.0f;
};
