#version 430 core

in vec3 FragPos;
in vec3 Normal;
in vec3 VoxelColor;

out vec4 FragColor;

uniform vec3 lightDir; // Position of the "Sun"
uniform vec3 viewPos;  // Camera position

void main() {
    // Ambient lighting (so shadows aren't pitch black)
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * vec3(1.0);
  	
    // Diffuse lighting (shading based on angle to the sun)
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightDir);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * vec3(1.0);
            
    // Combine and apply to the voxel's color
    vec3 result = (ambient + diffuse) * VoxelColor;
    FragColor = vec4(result, 1.0);
}
