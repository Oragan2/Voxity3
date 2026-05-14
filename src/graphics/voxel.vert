#version 430 core

// Layout 0: The vertices of the "template" cube (same for all voxels)
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

// Layout 2 & 3: The data from your ParticlePool (different for every voxel)
layout (location = 2) in vec3 aInstancePos;
layout (location = 3) in vec3 aColor;

out vec3 FragPos;
out vec3 Normal;
out vec3 VoxelColor;

// Uniforms for the camera
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    VoxelColor = aColor;
    Normal = mat3(transpose(inverse(model))) * aNormal; 
    
    // We add the instance position to the local cube vertex position
    // This effectively "moves" the template cube to its place in the world
    FragPos = vec3(model * vec4(aPos + aInstancePos, 1.0));
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
