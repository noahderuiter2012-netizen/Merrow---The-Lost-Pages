#include "MerrowGameMode.h"
#include "MerrowPlayerCharacter.h"
#include "MerrowHUD.h"

AMerrowGameMode::AMerrowGameMode()
{
    DefaultPawnClass = AMerrowPlayerCharacter::StaticClass();
    HUDClass = AMerrowHUD::StaticClass();
}
