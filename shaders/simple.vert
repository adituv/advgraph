#version 330

in vec3 vPos;
in vec4 vColor;

out vec4 fColor;

void main() {
    gl_Position = vec4(vPos, 1.0);
    fColor = vColor;
}
