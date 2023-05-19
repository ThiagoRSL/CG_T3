#ifndef SHIPPART_H
#define SHIPPART_H

#include <Poly.h>
#include <vector>


class ShipPart : public Poly
{
    public:
        ShipPart(float x, float y, float* RGB);
        void AddModifier(int modifier_id);

        void AddWeaponSlot(Pnt2 offset);
        std::vector<int> modifiers;
    protected:

    private:
};

#endif // SHIPPART_H
