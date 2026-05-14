#ifndef PARTICULE_HPP
#define PARTICULE_HPP

#include <vector>
#include <cstdint>
#include <cassert>

enum class MaterialType : uint8_t {
    Void = 0,
    Air = 1,
    Water = 2,
    Stone = 3,
    Iron = 4,
    _Count
};

struct MaterialProperties {
    float heatConductivity;
    float heatCapacity;
    float density;
};

constexpr MaterialProperties MATERIAL[] = {
    {0.0f,      0.0f,       0.0f},
    {0.026f,    1005.0f,    1.204f},
    {0.6089f,   4184.0f,    1000.0f},
    {2.0f,      840.0f,     2700.0f},
    {80.4f,     449.458f,   7874.0f}
};

struct ParticlePool {
    std::size_t X;
    std::size_t Y;
    std::size_t Z;
    
    std::vector<MaterialType> type;
    std::vector<uint8_t> density; //relative
    
    ParticlePool(std::size_t x, std::size_t y, std::size_t z);
    void change(std::size_t x,std::size_t y,std::size_t z, MaterialType t, uint8_t den);
    const MaterialProperties& properties(std::size_t i) const;
};

#endif
