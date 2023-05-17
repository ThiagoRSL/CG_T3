#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
    //ctor
}

void PlayerManager::SetPlayerCharacter(Character* character)
{
    this->PlayerCharacter = character;
}

void PlayerManager::CheckInteraction()
{
    float mouseX = MouseManager::shared_instance().PosX - PlayerCharacter->GetAnchor()->x;
    float mouseY = MouseManager::shared_instance().PosY - PlayerCharacter->GetAnchor()->y;
    PlayerCharacter->AimTo(mouseX, mouseY);
}
