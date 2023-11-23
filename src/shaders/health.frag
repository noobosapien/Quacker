precision highp float;

uniform vec3 u_pos;
uniform vec2 u_res;



float rect(){
    float dist = 0.0;

    vec2 st = (gl_FragCoord.xy/u_res);
    dist = distance(u_pos.y, st.y);

    if(dist < 0.02){
        return 1.0;
    }

    return 0.0;
}

float rect2(){
    float dist = 0.0;

    vec2 st = (gl_FragCoord.xy/u_res);
    dist = distance(u_pos.y, st.y);

    return step(0.07, dist);
}

void main()
{
    gl_FragColor=vec4(rect2());
}