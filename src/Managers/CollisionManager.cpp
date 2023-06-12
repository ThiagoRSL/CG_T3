#include "Managers/CollisionManager.h"
#include "Entities/Character/Character.h"

CollisionManager::CollisionManager()
{

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
    this->Characters.push_back(character);
    int i;
    for(i = 0; i < CharactersWallNearestPoint.size();i++)
    {
        CharactersWallNearestPoint.at(i)->operator[](character) = 0;
    }
}
void CollisionManager::RemoveNPC(Character* character)
{
    int i;
    for(i = 0; i < Characters.size(); i++)
    {
        if(Characters.at(i) == character)
        {
            Characters.erase(Characters.begin()+i);
        }
    }
}
void CollisionManager::addWall(Curve2d* wall)
{
    Walls.push_back(wall);
    std::map<Character*, int>* newMap = new std::map<Character*, int>();
    CharactersWallNearestPoint.push_back(newMap);
}
Character* CollisionManager::VerifyCollisionNPCs(float x, float y)
{
    int i;
    Character* actual;
    for(i = 0; i < Characters.size(); i++)
    {
        actual = Characters.at(i);
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

void CollisionManager::CheckCollisions()
{
    int i, j, nearestPointIndex, nearestPointNextIndex, nearestPointPreviousIndex;
    Pnt2 *nearestPoint, *nearestPointNext, *nearestPointPrevious;
    Character* actualCharacter;
    Pnt2* actualCharacterPoint;

    float distanceNext, distanceActual, distancePrevious;
    for(i = 0; i < Characters.size(); i++)
    {
        for(j = 0; j < CharactersWallNearestPoint.size(); j++)
        {
            actualCharacter = Characters.at(i);
            actualCharacterPoint = actualCharacter->GetAnchor();

            nearestPointIndex = CharactersWallNearestPoint.at(j)->operator[](actualCharacter);
            nearestPointNextIndex = nearestPointIndex+1;
            nearestPointPreviousIndex = nearestPointIndex-1;

            CV::color(6);
            CV::line(actualCharacter->GetAnchor()->x - CameraManager::shared_instance().GetCameraOffsetRef()->x,
                     actualCharacter->GetAnchor()->y - CameraManager::shared_instance().GetCameraOffsetRef()->y,
                     Walls.at(j)->GetCurvePoint(CharactersWallNearestPoint.at(j)->operator[](actualCharacter))->x - CameraManager::shared_instance().GetCameraOffsetRef()->x,
                     Walls.at(j)->GetCurvePoint(CharactersWallNearestPoint.at(j)->operator[](actualCharacter))->y - CameraManager::shared_instance().GetCameraOffsetRef()->y);

            //Garante a atualiza��o do ponto mais pr�ximo.
            while(true)
            {
                nearestPoint = Walls[0]->GetCurvePoint(nearestPointIndex);
                nearestPointNext = Walls[0]->GetCurvePoint(nearestPointNextIndex);
                nearestPointPrevious = Walls[0]->GetCurvePoint(nearestPointPreviousIndex);

                distanceActual = GeometryAux::DistanceBetween(actualCharacterPoint, nearestPoint);

                if(nearestPointNext != nullptr) distanceNext = GeometryAux::DistanceBetween(actualCharacterPoint, nearestPointNext);
                else distanceNext = 2000000.0;

                if(nearestPointPrevious != nullptr) distancePrevious = GeometryAux::DistanceBetween(actualCharacterPoint, nearestPointPrevious);
                else distancePrevious = 2000000.0;

                while(distanceActual == distanceNext)
                {
                    nearestPointNextIndex+=1;
                    nearestPointNext = Walls[0]->GetCurvePoint(nearestPointNextIndex);
                    if(nearestPointNext != nullptr) distanceNext = GeometryAux::DistanceBetween(actualCharacterPoint, nearestPointNext);
                    else distanceNext = 2000000.0;
                }
                while(distanceActual == distancePrevious)
                {
                    nearestPointPreviousIndex-=1;
                    nearestPointPrevious = Walls[0]->GetCurvePoint(nearestPointPreviousIndex);
                    if(nearestPointPrevious != nullptr) distancePrevious = GeometryAux::DistanceBetween(actualCharacterPoint, nearestPointPrevious);
                    else distancePrevious = 2000000.0;
                }
                if(distanceActual < distanceNext && distanceActual < distancePrevious)
                {
                    break;
                }
                else if(distanceActual > distanceNext)
                {
                    nearestPointIndex = nearestPointNextIndex;
                }
                else if(distanceActual > distancePrevious)
                {
                    nearestPointIndex = nearestPointPreviousIndex;
                }
            }
            CharactersWallNearestPoint.at(j)->operator[](actualCharacter) = nearestPointIndex;

            if(CollisionManager::shared_instance().VerifyCollisionWalls(actualCharacter))
            {
                actualCharacter->ReceiveDamage(10000);
            }
        }
    }
}

bool CollisionManager::VerifyCollisionWalls(Character* character)
{
    Pnt2* CameraOffset = CameraManager::shared_instance().GetCameraOffsetRef();

    int i;
    for(i = 0; i < Walls.size(); i++)
    {
        Pnt2* nearest = Walls.at(i)->GetCurvePoint(CharactersWallNearestPoint.at(i)->operator[](character));
        if(nearest != nullptr)
        {
            if(character->HasCollisionOnParts(nearest->x - CameraOffset->x, nearest->y - CameraOffset->y))
            {
                return true;
            }
        }
    }

    return false;
}
