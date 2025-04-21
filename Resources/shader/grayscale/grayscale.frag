#version 130

in vec4 v_color;
in vec2 v_texCoords;

uniform sampler2D u_texture;

out vec4 FragColor;

void main()
{
    vec4 ori_color=texture(u_texture, v_texCoords);
    float gray=dot(ori_color.rgb,vec3(0.299,0.587,0.114));
    FragColor =vec4(gray, gray, gray, ori_color.a);
}
