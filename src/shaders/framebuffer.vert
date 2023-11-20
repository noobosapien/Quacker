attribute vec3 a_position;
attribute vec2 a_texCoord;

varying vec2 v_fragTexCoord;

void main()
{
    vec4 pos=vec4(a_position.x,a_position.y,0.,1.);
    gl_Position=pos;
    
    v_fragTexCoord=a_texCoord;
}
