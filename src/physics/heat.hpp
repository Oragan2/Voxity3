#ifndef HEAT_HPP
#define HEAT_HPP

#include <vector>
#include "particule.hpp"

struct HeatSource {
    std::size_t x, y, z;
    float Q; // in W/m3
    HeatSource(std::size_t x, std::size_t y, std::size_t z, float Q);
};


extern float* T;
extern float* oldT;
extern std::vector<HeatSource> heatSources;
extern std::size_t X;
extern std::size_t Y;
extern std::size_t Z;

void initTemp(const std::size_t x, const std::size_t y, const std::size_t z);
void endTemp();
float fouriersLaw(float k, float p, float c);
float Laplacian(std::size_t x, std::size_t y, std::size_t z); 
void HeatStep(const ParticlePool& pool, float dt);

#endif
