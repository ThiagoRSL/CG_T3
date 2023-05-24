#ifndef SLOT_H
#define SLOT_H

#include "Weapon/Weapon.h"

class ShipPart;

class Slot : public Renderable
{
    public:
        Slot();
        void SlotOf(ShipPart* part);
        ShipPart* SlotOf();

    protected:

    private:
        ShipPart* AttachedTo;
};

class WeaponSlot : public Slot
{
    public:
        Weapon* EquippedWeapon;
        Pnt2 Position;

    public:
        WeaponSlot()
        {
            EquippedWeapon = nullptr;
        }
        void SetPosition(float x, float y)
        {
            this->Position.x = x;
            this->Position.y = y;
        }
        Pnt2 GetPosition(){return this->Position;}

        void SetWeapon(Weapon* weapon)
        {
            this->EquippedWeapon = weapon;
            weapon->EquipOn(this);
            this->EquippedWeapon->SetOffset(Position.x, Position.y);
        }
        bool HasWeapon()
        {
            if(EquippedWeapon != nullptr) return true;
            return false;
        }
        void Render()
        {
            if(HasWeapon())
            {
                EquippedWeapon->Render();
            }
        }
};

#endif // SLOT_H
