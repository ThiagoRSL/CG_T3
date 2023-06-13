#ifndef WEAPON_H
#define WEAPON_H

#include <Entities/Poly.h>
#include <Entities/Weapon/Projectile.h>

class Character;
class WeaponSlot;

class Weapon : public Poly
{
    public:
        Weapon();
        void AdjustWeapon();

        void EquipOn(WeaponSlot* slot);
        void Shoot();

        float CalcShotDamage();
        float CalcShotSpeed();
        float CalcShotMaxDistance();

        void RefreshShotCooldown();

        void SetShotColor(float *RGB);
    protected:

    private:
        Character* Wielder;
        WeaponSlot* SlottedOn;

        float energy_cost_base;
        float accuracy_base;
        float damage_base;

        float shot_cooldown_base;
        float shot_cooldown_val;
        float shot_speed;
        float shot_max_distance;
        float shot_RGB[3];

        float ammo_max;
        float ammo_val;

        float last_shot_frame;
};

#endif // WEAPON_H
