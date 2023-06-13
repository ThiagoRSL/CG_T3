#include "Entities/Weapon/Projectile.h"
#include "Entities/Character/Character.h"

Projectile::Projectile(float x, float y, float damage, float speed, float maxDistance, Character* Owner)
    :Poly(x, y)
{
    this->Owner = Owner;
    this->damage = damage;
    this->speed = speed;
    this->max_distance = maxDistance;
    this->CreatedAt = Pnt2(x, y);
}

void Projectile::Render()
{
    if(GeometryAux::DistanceBetween(&CreatedAt, this->Anchor) > max_distance)
    {
        DestroyProjectile();
        return;
    }

    Pnt2 position = Pnt2(this->Anchor->x - CameraOffsetRef->x, this->Anchor->y - CameraOffsetRef->y);

    this->Move(speed/FPSManager::shared_instance().GetFrames());

    CV::color(1,1,1);
    CV::circleFill(position.x, position.y, 5, 30);

    Character* target = CollisionManager::shared_instance().VerifyCollisionNPCs(position.x, position.y);

    if(target != this->Owner)
    {
        if(target != nullptr)
        {
            target->ReceiveDamage(this->damage);
            DestroyProjectile();
        }
    }
}

void Projectile::DestroyProjectile()
{
    RenderManager::shared_instance().RemoveRenderableFromList(this);
    delete this;
}
