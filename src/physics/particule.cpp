#include "particule.hpp"
#include <cstdlib>
#include <vector>

static_assert(
        std::size(MATERIAL) == static_cast<std::size_t>(MaterialType::_Count),
        "MATERIAL table out of sync with materialType"
);


void ParticlePool::change(std::size_t x,std::size_t y,std::size_t z, MaterialType t, uint8_t den) {
    type[z*X*Y+y*X+x] = t;
    density[z*X*Y+y*X+x] = den;
}

const MaterialProperties& ParticlePool::properties(std::size_t i) const {
    return MATERIAL[static_cast<uint8_t>(type[i])];
}

ParticlePool::ParticlePool(std::size_t x, std::size_t y, std::size_t z) : X{x}, Y{y}, Z{z}, type(z*y*x), density(z*y*x) {}
