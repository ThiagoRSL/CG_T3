#include "Managers/CollisionManager.h"
#include "Entities/Character/Character.h"

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
void CollisionManager::addWall(Curve2d* wall)
{
    Walls.push_back(wall);
}
Character* CollisionManager::VerifyCollisionNPCs(float x, float y)
{
    int i;
    Character* actual;
    for(i = 0; i < npcs.size(); i++)
    {
        actual = npcs.at(i);
        if(!actual->IsDead() && !actual->IsDying() && actual->HasCollisionOnParts(x, y))
        {
            return actual;
        }
    }
    return nullptr;
}
Character* CollisionManager::VerifyCollisionPlayer(float x, float y)
{
    if(player_character->HasCollisionOnParts(x, y))
    {
        return player_character;
    }
}


bool CollisionManager::VerifyCollisionWalls(Character* character, int distance)
{
    Pnt2* nearest_left = Walls.at(0)->NearPoint(character->GetPosition(), distance);
    Pnt2* nearest_right = Walls.at(1)->NearPoint(character->GetPosition(), distance);
    Pnt2* nearest_bottom = Walls.at(2)->NearPoint(character->GetPosition(), distance);

    if(nearest_left != nullptr)
    {
        if(character->HasCollisionOnParts(nearest_left->x, nearest_left->y))
        {
            return true;
        }
    }

    if(nearest_right != nullptr)
    {
        if(character->HasCollisionOnParts(nearest_right->x, nearest_right->y))
        {
            return true;
        }
    }

    if(nearest_bottom != nullptr)
    {
        if(character->HasCollisionOnParts(nearest_bottom->x, nearest_bottom->y))
        {
            return true;
        }
    }

    return false;
}
