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
void CollisionManager::addWall(BSpline* wall)
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
    Pnt2* nearest = Walls.at(0)->NearPoint(character->GetPosition(), distance);

    if(nearest == nullptr)
        return false;

    if(character->HasCollisionOnParts(nearest->x, nearest->y))
    {
        character->ReceiveDamage(1000);
    }
    /*
    int i;
    for(i = 0; i < nearest_points.size(); i++)
    {
        Pnt2* p = nearest_points.at(i);
        if(character->HasCollisionOnParts(p->x, p->y))
        {
            return p;
        }
    }*/
}
