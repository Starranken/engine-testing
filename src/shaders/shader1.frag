#version 330 core

in vec3 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

//exercise stuff
in vec3 position;
uniform vec4 myColor;
uniform float mixValue;

uniform sampler2D texture1;
uniform sampler2D texture2;



void main()
{
    //make the vertex colors the vertex positions FragColor = vec4(position, 1.0f);
    //FragColor = vec4(vertexColor, 1.0f);
    vec4 color1 = texture(texture1, TexCoord)* vec4(vertexColor, 1.0f);
    vec4 color2 = texture(texture2, vec2(1.0f - TexCoord.x, 1.0f - TexCoord.y));
    FragColor = mix(color1, color2, mixValue);
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
}