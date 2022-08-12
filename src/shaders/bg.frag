precision mediump float;

varying vec2 v_fragTexCoord;
varying vec4 v_position;

uniform sampler2D uTexture;

void main()
{
	vec4 newColor = texture2D(uTexture, v_fragTexCoord);

	gl_FragColor = newColor;
}