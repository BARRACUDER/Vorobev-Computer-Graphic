    #version 460 core
    out vec4 FragColor;
    uniform float uTime;
    void main() {
        float red = 0.2f + (sin(uTime) * 0.3f);
        float green = 0.4f + (cos(uTime * 1.3f) * 0.3f);
        float blue = 1.0f;
        FragColor = vec4(red, green, blue, 1.0);
    }