#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(float x, float y, float RGB[3])
   :Character(x, y, RGB)
{

}

void PlayerCharacter::AdjustAim()
{
    float mouseX = MouseManager::shared_instance().PosX;
    float mouseY = MouseManager::shared_instance().PosY;

    this->AimVector->x = (float) MouseManager::shared_instance().PosX - this->Anchor->x;
    this->AimVector->y = (float) MouseManager::shared_instance().PosY - this->Anchor->y;
    this->AimVector->Normalize();

    this->UpdateWeaponPosition();
}
