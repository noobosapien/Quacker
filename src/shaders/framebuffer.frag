precision highp float;

varying vec2 v_fragTexCoord;

uniform sampler2D uTexture;

void main()
{
    float Gamma=.95;
    vec4 color=texture2D(uTexture,v_fragTexCoord);
    // gl_FragColor=vec4(pow(vec3(color),vec3(1./Gamma)),color.a);
    gl_FragColor = vec4(vec3(1.0 - color), 1.0);
}