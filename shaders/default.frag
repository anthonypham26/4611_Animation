#version 330 core

in vec3 fragColor;   // Received color from vertex shader
in vec2 TexCoord;    // Received texture coordinates from vertex shader

uniform sampler2D basicTexture; // Texture sampler
uniform float u_time; // Time variable for animation

out vec4 FinalColor; // Output final color

// Function to animate texture coordinates
vec2 animateTexCoords(vec2 coords) {
    coords.x += sin(u_time + coords.y * 2.0) * 0.03;  // Wavy distortion
    coords.y += cos(u_time + coords.x * 3.0) * 0.02;  // Wavy distortion
    return coords;
}

void main() {
    vec2 animatedCoords = animateTexCoords(TexCoord);  // Modify texture coordinates
    vec4 texColor = texture(basicTexture, animatedCoords);  // Sample the texture
    FinalColor = vec4(fragColor, 1.0) * texColor;  // Apply texture
}
