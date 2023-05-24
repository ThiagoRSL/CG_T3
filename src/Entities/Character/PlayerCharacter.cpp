#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(float x, float y, float RGB[3])
   :Character(x, y, RGB)
{

}

void PlayerCharacter::AdjustAim()
{
    this->AimPoint->x = (float) MouseManager::shared_instance().PosX;
    this->AimPoint->y = (float) MouseManager::shared_instance().PosY;

    this->UpdateWeaponAim();
}
