#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MerrowHUD.generated.h"

UCLASS()
class MERROW_API AMerrowHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;
};
