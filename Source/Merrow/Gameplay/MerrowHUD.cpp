#include "MerrowHUD.h"
#include "MerrowPlayerCharacter.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "UObject/ConstructorHelpers.h"

void AMerrowHUD::DrawHUD()
{
    Super::DrawHUD();
    if (!Canvas) return;

    static UFont* Font = nullptr;
    if (!Font)
    {
        static ConstructorHelpers::FObjectFinder<UFont> FontAsset(TEXT("/Engine/EngineFonts/Roboto"));
        if (FontAsset.Succeeded()) Font = FontAsset.Object;
    }
    if (!Font) return;

    const float X = 28.0f;
    float Y = 26.0f;
    DrawText(TEXT("MERROW  /  THE LOST PAGES"), FLinearColor(0.65f, 0.9f, 0.68f), X, Y, Font, 1.15f);
    Y += 28.0f;
    DrawText(TEXT("OBJECTIVE 01  -  FIND THE FIRST LOST PAGE"), FLinearColor::White, X, Y, Font, 0.9f);
    Y += 22.0f;

    if (const AMerrowPlayerCharacter* Player = Cast<AMerrowPlayerCharacter>(GetOwningPawn()))
    {
        DrawText(FString::Printf(TEXT("PAGES RECOVERED: %d / 7"), Player->PagesRecovered),
            FLinearColor(0.7f, 0.95f, 0.72f), X, Y, Font, 0.9f);
        if (Player->bCanInteract)
            DrawText(TEXT("[ E ]  RECOVER PAGE"), FLinearColor(0.75f, 1.0f, 0.78f),
                Canvas->ClipX * 0.5f - 90.0f, Canvas->ClipY * 0.72f, Font, 1.0f);
    }
}
