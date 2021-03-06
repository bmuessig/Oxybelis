#version 430

in vec3 aVertex;
in vec3 aNormal;

uniform mat4 uPerspective;
uniform mat4 uModel;

out vec4 vClipPos;
out vec3 vNormal;
out vec3 vVertex;

void main() {
    gl_Position = uPerspective * uModel * vec4(aVertex, 1.0);
    vClipPos = gl_Position;
    vNormal = aNormal;
    vVertex = aVertex;
}