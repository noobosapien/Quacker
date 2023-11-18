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

float circle2(){

    vec2 st = (gl_FragCoord.xy/v_res);
    float width = v_act_size/5.;

    float rsq = pow(v_act_size,2.0);
    float xmina = pow((st.x - v_act_pos.x), 2.0);
    float yminb = pow((st.y - v_act_pos.y), 2.0);
    float a = v_act_pos.x;
    float b = v_act_pos.y;

    float x = a + sqrt(rsq - yminb);
    float y = b + sqrt(rsq - xmina);

    if(st.x < v_act_pos.x && st.y < v_act_pos.y){
        if(st.x < (x - v_act_size) && st.y < (y - v_act_size)){
            return 1.0;
        }
    }else{
        if(st.x < x && st.y < y){
            return 1.0;
        }
    }

    return 0.0;
}

void main()
{
    
    float color = circle();

	gl_FragColor = vec4(color);
	
}