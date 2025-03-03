#version 330 core

layout(location = 0) in vec3 aPos;      // Vertex position
layout(location = 1) in vec3 aColor;    // Vertex color
layout(location = 2) in vec2 aTexCoord; // Texture coordinates

out vec3 fragColor;    // Pass color to fragment shader
out vec2 TexCoord;     // Pass texture coordinates to fragment shader

void main() {
    gl_Position = vec4(aPos, 1.0);
    fragColor = aColor;
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);  // Flip texture coordinates if needed
}
