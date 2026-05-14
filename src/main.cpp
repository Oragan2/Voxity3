#include "physics/particule.hpp"
#include "physics/heat.hpp"

int main() {
    std::size_t x=20, y=8, z=1;
    initTemp(x,y,z);
    ParticlePool pool{x,y,z};
    for (std::size_t i = 0; i < x; ++i) {
        for (std::size_t j = 0; j < y; ++j) {
            if (i%2 == 0) {
                MaterialType t;
                switch (i) {
                    case 0:
                        t = MaterialType::Air;
                        break;
                    case 2:
                        t = MaterialType::Iron;
                        break;
                    case 4:
                        t = MaterialType::Stone;
                        break;
                    case 6:
                        t = MaterialType::Water;
                        break;
                }
                pool.change(j,i,1,t,1);
            }
            else pool.change(j,i,1,MaterialType::Void,1);
        }
    } 
    HeatStep(pool,1);
    endTemp();
}
