#include "Entities/Weapon/Projectile.h"
#include "Entities/Character/Character.h"

Projectile::Projectile(float x, float y, float damage, Character* Owner)
    :Poly(x, y)
{
    this->Owner = Owner;
    this->damage = damage;
}

void Projectile::Render()
{
    this->Move(1000/FPSManager::shared_instance().GetFrames());
    if(this->Owner->HasCollision(this->Anchor->x, this->Anchor->y))
    {
        return;
    }
    CV::color(1,1,1);
    CV::circleFill(this->Anchor->x, this->Anchor->y, 5, 30);

    Character* target = CollisionManager::shared_instance().VerifyCollisionNPCs(this->Anchor->x, this->Anchor->y);

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
