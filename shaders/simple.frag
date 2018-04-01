#version 330

out vec4 fragmentColor;
in vec4 fColor;

void main() {
    fragmentColor = fColor;
}
