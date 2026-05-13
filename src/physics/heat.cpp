#include "particule.hpp"
#include "heat.hpp"
#include <cstdint>
#include <vector>
#include <utility>

// Heat equation (3D, constant k):
// ∂T/∂t = α·∇²T + Q/(ρ·cₚ)
//
// Where:
//   T        = temperature (Kelvin)          — what you're solving for
//   α        = k / (ρ·cₚ)                   — thermal diffusivity (m²/s)
//   k        = heat conductivity (W/m·K)     — from your MATERIAL table
//   ρ        = density (kg/m³)               — from your MATERIAL table
//   cₚ       = specific heat capacity (J/kg·K) — from your MATERIAL table
//   Q        = heat source (W/m³)            — energy added per volume per second
//
// Laplacian (scalar, second order):
//   ∇²T = ∂²T/∂x² + ∂²T/∂y² + ∂²T/∂z²
//   ∂²T/∂x² ≈ (T[i+1] - 2·T[i] + T[i-1]) / Δx²
//
// Gradient (vector, first order — NOT the Laplacian):
//   ∇T = (∂T/∂x)i + (∂T/∂y)j + (∂T/∂z)k

inline std::size_t getIdx(std::size_t x, std::size_t y, std::size_t z) {
    return z*(X*Y)+y*X+x;
}

HeatSource::HeatSource(std::size_t x, std::size_t y, std::size_t z, float Q) : x{x}, y{y}, z{z}, Q{Q} {}

void initTemp(const std::size_t x, const std::size_t y, const std::size_t z) {
    X = x;
    Y = y;
    Z = z;
    T = new float[x*y*z];
    oldT = new float[x*y*z];
}

void endTemp() {
    delete[] T;
    delete[] oldT;
}

float Laplacian(std::size_t x, std::size_t y, std::size_t z) {
    float dx = 1.0f, dy = 1.0f, dz = 1.0f;
    float d2T_dx2=.0f, d2T_dy2=.0f, d2T_dz2=0.0f;
    std::size_t ax, bx, ay, by, az, bz;
    ax = (x+1 < X) ? x+1 : x;
    bx = (x > 0) ? x-1 : x;
    ay = (y+1 < Y) ? y+1 : y;
    by = (y > 0) ? y-1 : y;
    az = (z+1 < Z) ? z+1 : z;
    bz = (z > 0) ? z-1 : z;
    d2T_dx2 = (oldT[getIdx(ax,y,z)] - 2*oldT[getIdx(x,y,z)] + oldT[getIdx(bx,y,z)]) / (dx*dx);
    d2T_dy2 = (oldT[getIdx(x,ay,z)] - 2*oldT[getIdx(x,y,z)] + oldT[getIdx(x,by,z)]) / (dy*dy);
    d2T_dz2 = (oldT[getIdx(x,y,az)] - 2*oldT[getIdx(x,y,z)] + oldT[getIdx(x,y,bz)]) / (dz*dz);

    return d2T_dx2+d2T_dy2+d2T_dz2;
}

float fouriersLaw(float k, float p, float c) {
    return k/(p*c);
}

void HeatStep(const ParticlePool& pool, float dt) {
    std::swap(T,oldT);
    for (std::size_t x = 0; x < X; ++x) {
        for (std::size_t y = 0; y < Y; ++y) {
            for (std::size_t z = 0; z < Z; ++z) {
                if (pool.type[getIdx(x,y,z)] == MaterialType::Void) {
                    oldT[getIdx(x,y,z)] = -1; 
                    continue;
                }
                auto particuleProperties = pool.properties(getIdx(x,y,z));
                T[getIdx(x,y,z)] = oldT[getIdx(x,y,z)] + dt 
                * (fouriersLaw(particuleProperties.heatConductivity,particuleProperties.density,particuleProperties.heatCapacity) 
                * Laplacian(x,y,z));
            }
        }
    }
    for (const HeatSource& hs : heatSources) {
        auto particuleProperties = pool.properties(getIdx(hs.x,hs.y,hs.z));
        T[getIdx(hs.x,hs.y,hs.z)] += dt * (hs.Q / (particuleProperties.density * particuleProperties.heatCapacity));
    }
}
