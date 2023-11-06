precision highp float;

varying vec3 v_position;
varying vec3 v_act_pos;
varying float v_act_size;
varying vec2 v_res;

float circle(){

    float width = v_act_size/5.;
    float dist = 0.0;

    vec2 st = (gl_FragCoord.xy/v_res);
    

    dist = distance(v_act_pos.xy, st);

    if(dist <= v_act_size && dist > v_act_size - width){
    
        return 1.0;
    }

    return 0.;
}

void main()
{
    
    float color = circle();

	gl_FragColor = vec4(color);
	
}