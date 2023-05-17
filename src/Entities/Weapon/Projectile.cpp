#include "Entities/Weapon/Projectile.h"
#include "Entities/Character/Character.h"

Projectile::Projectile(float x, float y, float damage, Character* Owner)
    :Poly(x, y)
{
    //Pnt2 CameraOffset = CameraManager::shared_instance().GetWindowOffset();
    this->Owner = Owner;
    this->damage = damage;
}

void Projectile::Render()
{
    Pnt2 position = Pnt2(this->Anchor->x - CameraOffsetRef->x, this->Anchor->y - CameraOffsetRef->y);

    this->Move(1000/FPSManager::shared_instance().GetFrames());
    if(this->Owner->HasCollisionOnParts(position.x, position.y))
    {
        return;
    }
    CV::color(1,1,1);

    CV::circleFill(position.x, position.y, 5, 30);

    Character* target = CollisionManager::shared_instance().VerifyCollisionNPCs(position.x, position.y);

    if(target == this->Owner)
    {
        printf("Vasco");
    }
    else
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
}
