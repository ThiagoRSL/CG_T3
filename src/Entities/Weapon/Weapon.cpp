#include "Entities/Weapon/Weapon.h"
#include "Entities/Character/Character.h"

Weapon::Weapon(Character* Wielder)
    :Poly()
{
    this->Wielder = Wielder;
    this->Anchor = Wielder->GetAnchor();
    Vec2* wielderAim = Wielder->GetAimVector();
    this->OrientationVector = new Vec2(wielderAim->x, wielderAim->y);
    Poly::AddVertex(- 5, - 25);
    Poly::AddVertex(+ 5, - 25);
    Poly::AddVertex(+ 5, + 5);
    Poly::AddVertex(- 5, + 5);
    Poly::Render();

    shot_cooldown_base = 15;
    damage_base = 10;
    energy_cost_base = 10;
    accuracy_base = 2;
    max_ammo_base = 5;

    shot_cooldown_val = 0;
    ammo_temp = max_ammo_base;
}

void Weapon::Shoot()
{
    if(shot_cooldown_val <= 0)
    {
        Projectile* shotPoly = new Projectile(this->Anchor->x + this->Offset.x, this->Anchor->y + this->Offset.y, this->CalcShotDamage(), this->Wielder);
        shotPoly->SetOrientation(this->OrientationVector->x, this->OrientationVector->y);
        RenderManager::shared_instance().AddRenderableToList(shotPoly);
        shot_cooldown_val = shot_cooldown_base;
    }
}

void Weapon::RefreshShotCooldown()
{
    if(shot_cooldown_val == 0)
        return;

    float frames = FPSManager::shared_instance().GetFrames();
    if(last_shot_frame != frames)
    {
        shot_cooldown_val--;
        last_shot_frame = frames;
    }
}

float Weapon::CalcShotDamage()
{
    return this->damage_base;
}
