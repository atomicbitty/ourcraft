#version 330 

uniform sampler2D u_tex;
in vec2 f_texcoord;

out vec4 frag_color;

void main() {
  frag_color = texture(u_tex, f_texcoord);
}

