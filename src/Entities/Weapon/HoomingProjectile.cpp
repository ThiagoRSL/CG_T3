#include "HoomingProjectile.h"
#include "Character.h"

HoomingProjectile::HoomingProjectile(float x, float y, float damage, float speed, float maxDistance, float *RGB, Character* Owner)
    :Projectile::Projectile(x, y, damage, speed, maxDistance, RGB, Owner)
{
    speed = 0;
}

void HoomingProjectile::Render()
{
    float frames = FPSManager::shared_instance().GetFrames();
    Character* closestEnemy = CollisionManager::shared_instance().GetClosestEnemy(this->Anchor);


    if(lastFrame != frames)
    {
        if(this->speed < 1000)
            speed += 20;
        lastFrame = frames;
        if(closestEnemy != nullptr)
        {
            Pnt2* closestEnemyAnchor = closestEnemy->GetAnchor();
            //printf("\nHOOMIE X %f, Y %f", this->Anchor->x, this->Anchor->y);
            //printf("\CHAR X %f, Y %f", closestEnemyAnchor->x, closestEnemyAnchor->y);
            SetOrientation(OrientationVector->x + (OrientationVector->x + closestEnemyAnchor->x - this->Anchor->x)/frames, OrientationVector->y + (OrientationVector->y + closestEnemyAnchor->y - this->Anchor->y)/frames);
            OrientationVector->Normalize();
        }
    }
    Projectile::Render();
}
