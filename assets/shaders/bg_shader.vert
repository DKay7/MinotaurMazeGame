uniform vec2 offset;

void main() {
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_TexCoord[0].xy = gl_TexCoord[0].xy + offset; // magic
    gl_FrontColor = gl_Color;
}