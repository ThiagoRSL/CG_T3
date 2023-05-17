#ifndef CHARACTER_H
#define CHARACTER_H

#include <math.h>
#include <vector>
#include "Utils/Pnt2.h"
#include "Entities/Entity.h"
#include "ShipPart.h"
#include "Entities/Weapon/Weapon.h"
#include "Entities/Weapon/Projectile.h"


class WeaponSlot : public Renderable
{
    public:
        Weapon* EquippedWeapon;
        Pnt2 Position;

    public:
        WeaponSlot()
        {
            EquippedWeapon = nullptr;
        }
        void SetOffset(float x, float y)
        {
            this->Position.x = x;
            this->Position.y = y;
        }
        void SetWeapon(Weapon* weapon)
        {
            this->EquippedWeapon = weapon;
            this->EquippedWeapon->SetOffset(Position.x, Position.y);
        }
        bool HasWeapon()
        {
            if(EquippedWeapon != nullptr) return true;
            return false;
        }
        void Render()
        {
            if(HasWeapon()) EquippedWeapon->Render();
        }
};

class Character : public Entity
{
    public:
        Character(float x, float y, float RGB[3]);

        void AimTo(float x, float y);
        void SetRotating(float degree);
        void SetMoving(float movement);
        void Shoot();
        void ReceiveDamage(float damage);
        void AnimateDeath();
        void Die();

        bool HasCollisionOnParts(float x, float y);


        void RefreshWeaponsCooldown();
        void ResetControls();

        void Render();
        void RenderBody();
        void RenderWeapons();

        void AppendPart(ShipPart* part);
        bool EquipWeapon(Weapon* weapon);

        void CreateWeaponSlot(Pnt2 offset);
        void UpdateWeaponPosition();

        void MoveDirection(Vec2* directionVector, float speed);

    protected:
        std::vector<WeaponSlot*> WeaponSlots;
        Vec2* AimVector;
        //Control Variables
        float rotating;
        float moving;

        //Base stats
        float movement_speed;
        float rotation_speed;
        float speed;
        float energy_max;
        float energy;

        // Life
        float hit_points_max;
        float hit_points;
        bool dying;
        bool dead;

        //Autonomy
        float aim_accuracy;
        Character* Target;
        Pnt2* target_last_known_location;
        bool autonomous;
        float view_range;

        // Death Animation
        int death_frame;
        float death_rgb_save[3];
        float last_death_frame;

        void AutonomousThinking();
    //Getters e Setters
    public:
        bool IsDying() {return this->dying;}
        bool IsDead() {return this->dead;}
        Vec2* GetAimVector() {return this->AimVector;}

        void SetAutonomous(bool autonomous){this->autonomous = autonomous;}
        bool SetTarget(Character* target) {this->Target = target;}
    //Autonomy
    public:
        void AutonomyAdjustAim();
};

#endif // CHARACTER_H
