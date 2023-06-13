#include "Entities/Weapon/Weapon.h"
#include "Entities/Character/Character.h"
#include "Slot.h"

Weapon::Weapon()
    :Poly()
{
    Poly::AddVertex(- 5, - 25);
    Poly::AddVertex(+ 5, - 25);
    Poly::AddVertex(+ 5, + 5);
    Poly::AddVertex(- 5, + 5);

    shot_cooldown_base = 15;
    damage_base = 10;
    energy_cost_base = 10;
    accuracy_base = 2;
    ammo_max = 5;
    shot_speed = 1500;
    shot_max_distance = 1000;

    shot_cooldown_val = 0;
    ammo_val = ammo_max;

    this->SetAnchor(nullptr);
}

void Weapon::EquipOn(WeaponSlot* slot)
{
    this->Wielder = slot->SlotOf()->PartOf();
    this->SlottedOn = slot;
    Renderable::SetAnchor(Wielder->GetAnchor());
    Pnt2* wielderAimPoint = Wielder->GetAimPoint();
    this->OrientationVector = new Vec2(wielderAimPoint->x, wielderAimPoint->y);
}

void Weapon::Shoot()
{
    if(shot_cooldown_val <= 0)
    {
        Projectile* shotPoly = new Projectile(this->Anchor->x + this->Offset.x, this->Anchor->y + this->Offset.y, this->CalcShotDamage(), this->CalcShotSpeed(), this->CalcShotMaxDistance(), this->shot_RGB, this->Wielder);
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

float Weapon::CalcShotSpeed()
{
    return this->shot_speed;
}

float Weapon::CalcShotMaxDistance()
{
    return this->shot_max_distance;
}

void Weapon::SetShotColor(float *RGB)
{
    this->shot_RGB[0] = RGB[0];
    this->shot_RGB[1] = RGB[1];
    this->shot_RGB[2] = RGB[2];
}

