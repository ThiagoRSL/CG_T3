#include "CollisionManager.h"
#include "Character.h"

CollisionManager::CollisionManager()
{
    //ctor
}
Character* CollisionManager::GetPlayerCharacter()
{
    return this->player_character;
}
void CollisionManager::SetPlayerCharacter(Character* player_character)
{
    this->player_character = player_character;
}
void CollisionManager::AddNPC(Character* character)
{
    this->npcs.push_back(character);
}
void CollisionManager::RemoveNPC(Character* character)
{
    int i;
    for(i = 0; i < npcs.size(); i++)
    {
        if(npcs.at(i) == character)
        {
            npcs.erase(npcs.begin()+i);
        }
    }
}
Character* CollisionManager::VerifyCollisionNPCs(float x, float y)
{
    int i;
    Character* actual;
    for(i = 0; i < npcs.size(); i++)
    {
        actual = npcs.at(i);
        if(!actual->IsDead() && !actual->IsDying() && actual->HasCollision(x, y))
        {
            return actual;
        }
    }
    return nullptr;
}
Character* CollisionManager::VerifyCollisionPlayer(float x, float y)
{
    if(player_character->HasCollision(x, y))
    {
        return player_character;
    }
}
