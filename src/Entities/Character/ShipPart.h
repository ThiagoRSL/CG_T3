#ifndef SHIPPART_H
#define SHIPPART_H

#include <Poly.h>
#include <vector>
#include "Slot.h"


class ShipPart : public Poly
{
    public:
        ShipPart(float x, float y, float* RGB);

        void AddModifier(int modifier_id);
        void AddWeaponSlot(Pnt2 offset);
        void AddMotorSlot(Pnt2 offset);


    private:
        Character* AttachedTo;
        std::vector<WeaponSlot*> WeaponSlots;
        std::vector<int> modifiers;
        //std::vector<Modifier*> Modifiers;
        //std::vector<MotorSlot*> MotorSlots;

    public:
        void AppendToCharacter(Character* character);
        Character* PartOf(){ return this->AttachedTo;}
        std::vector<WeaponSlot*> GetWeaponSlots() {return this->WeaponSlots;}
};

#endif // SHIPPART_H
