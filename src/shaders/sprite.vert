attribute vec3 a_position;
attribute vec2 a_texCoord;

varying vec2 v_fragTexCoord;

uniform mat4 u_model;
uniform mat4 u_viewproj;

void main()
{
	vec4 pos=vec4(a_position,1.);
	gl_Position=u_viewproj*u_model*pos;
	// gl_Position=u_model*pos;
	
	v_fragTexCoord=a_texCoord;
}
