#include "MerrowHUD.h"
#include "MerrowPlayerCharacter.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/Font.h"

void AMerrowHUD::DrawHUD()
{
    Super::DrawHUD();
    if (!Canvas || !GEngine) return;
    UFont* Font = GEngine->GetSmallFont();
    if (!Font) return;

    const AMerrowPlayerCharacter* Player = Cast<AMerrowPlayerCharacter>(GetOwningPawn());
    const float X = 28.0f;
    float Y = 26.0f;
    DrawText(TEXT("MERROW  /  THE LOST PAGES"), FLinearColor(0.65f, 0.9f, 0.68f), X, Y, Font, 1.35f);
    Y += 30.0f;

    if (Player && Player->bChapterComplete)
    {
        DrawText(TEXT("CHAPTER COMPLETE"), FLinearColor(0.72f, 1.0f, 0.75f), X, Y, Font, 1.25f);
        Y += 28.0f;
        DrawText(TEXT("The gate is open. The next trail lies beyond."), FLinearColor::White, X, Y, Font, 1.0f);
        DrawText(TEXT("PROTOTYPE END"), FLinearColor(0.72f, 1.0f, 0.75f),
            Canvas->ClipX * 0.5f - 65.0f, Canvas->ClipY * 0.5f, Font, 1.2f);
        return;
    }

    const int32 Pages = Player ? Player->PagesRecovered : 0;
    const FString Objective = Pages < 7
        ? FString::Printf(TEXT("OBJECTIVE: RECOVER THE LOST PAGES  (%d / 7)"), Pages)
        : FString(TEXT("OBJECTIVE: RETURN TO THE ANCIENT GATE"));
    DrawText(Objective, FLinearColor::White, X, Y, Font, 1.0f);
    Y += 24.0f;
    DrawText(FString::Printf(TEXT("PAGES RECOVERED: %d / 7"), Pages),
        FLinearColor(0.7f, 0.95f, 0.72f), X, Y, Font, 1.0f);
    Y += 22.0f;
    if (Player)
        DrawText(FString::Printf(TEXT("STAMINA: %d%%"), FMath::RoundToInt(Player->Stamina)),
            FLinearColor(0.65f, 0.9f, 0.68f), X, Y, Font, 0.95f);

    if (Player && Player->bCanInteract)
        DrawText(Player->CurrentInteractionPrompt.ToString(), FLinearColor(0.75f, 1.0f, 0.78f),
            Canvas->ClipX * 0.5f - 180.0f, Canvas->ClipY * 0.72f, Font, 1.1f);
}
