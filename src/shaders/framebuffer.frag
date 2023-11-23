precision highp float;

varying vec2 v_fragTexCoord;

uniform sampler2D uTexture;

void main()
{
    vec4 color=texture2D(uTexture,v_fragTexCoord);
    gl_FragColor = color;
}