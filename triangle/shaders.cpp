#include <string>

extern "C" const char *vshader = R"(
#version 330 core

in vec3 a_pos;
in vec4 a_color;
out vec4 v_color;

void main() {
	gl_Position = vec4(a_pos, 1.0);
	v_color = a_color;
}
)";

extern "C" const char *fshader = R"(
#version 330 core

in vec4 v_color;
out vec4 f_color;

void main() {
	f_color = v_color;
}
)";
