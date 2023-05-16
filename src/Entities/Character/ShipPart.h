#ifndef SHIPPART_H
#define SHIPPART_H

#include <Poly.h>
#include <vector>


class ShipPart : public Poly
{
    public:
        ShipPart(float x, float y, float* RGB);
        void AddModifier(int modifier_id);

    protected:

    private:
        std::vector<int> modifiers;
};

#endif // SHIPPART_H
