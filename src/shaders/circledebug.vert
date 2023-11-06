attribute vec3 a_position;

varying vec3 v_position;
varying vec3 v_act_pos;
varying float v_act_size;
varying vec2 v_res;

uniform mat4 u_model;
uniform mat4 u_viewproj;
uniform vec3 u_position;
uniform float u_size;
uniform vec2 u_res;

void main()
{
    vec4 pos=vec4(a_position,1.);
    
    gl_Position=u_viewproj*u_model*pos;
    v_position=a_position;
    v_act_pos=u_position;
    v_act_size=u_size;
    v_res=u_res;
}

