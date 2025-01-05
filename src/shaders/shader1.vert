#version 330 core

layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 TexCoord;
uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//exercise stuff
out vec3 position;
uniform float displace;

void main()
{
    mat4 transform = projection * view * model;
    //set position to the vertex positions position = aPos;
    gl_Position = transform * vec4(aPos, 1.0f);
    //I MADE IT MOVE!!!!  gl_Position = vec4(aPos.x + displace, aPos.yz, 1.0f);
    vertexColor = aPos;
    TexCoord = aTexCoord;
}