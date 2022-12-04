precision mediump float;

varying vec4 v_position;
uniform float u_time;

vec3 random3(vec3 c){
    float j=4096.*sin(dot(c,vec3(17.,59.4,15.)));
    vec3 r;
    r.z=fract(512.*j);
    j*=.125;
    r.x=fract(512.*j);
    j*=.125;
    r.y=fract(512.*j);
    return r-.5;
}

/* skew constants for 3d simplex functions */
const float F3 =  0.3333333;
const float G3 =  0.1666667;

/* 3d simplex noise */
float simplex3d(vec3 p) {
    /* 1. find current tetrahedron T and it's four vertices */
    /* s, s+i1, s+i2, s+1.0 - absolute skewed (integer) coordinates of T vertices */
    /* x, x1, x2, x3 - unskewed coordinates of p relative to each of T vertices*/
    
    /* calculate s and x */
    vec3 s = floor(p + dot(p, vec3(F3)));
    vec3 x = p - s + dot(s, vec3(G3));
    
    /* calculate i1 and i2 */
    vec3 e = step(vec3(0.0), x - x.yzx);
    vec3 i1 = e*(1.0 - e.zxy);
    vec3 i2 = 1.0 - e.zxy*(1.0 - e);
    
    /* x1, x2, x3 */
    vec3 x1 = x - i1 + G3;
    vec3 x2 = x - i2 + 2.0*G3;
    vec3 x3 = x - 1.0 + 3.0*G3;
    
    /* 2. find four surflets and store them in d */
    vec4 w, d;
    
    /* calculate surflet weights */
    w.x = dot(x, x);
    w.y = dot(x1, x1);
    w.z = dot(x2, x2);
    w.w = dot(x3, x3);
    
    /* w fades from 0.6 at the center of the surflet to 0.0 at the margin */
    w = max(0.6 - w, 0.0);
    
    /* calculate surflet components */
    d.x = dot(random3(s), x);
    d.y = dot(random3(s + i1), x1);
    d.z = dot(random3(s + i2), x2);
    d.w = dot(random3(s + 1.0), x3);
    
    /* multiply d by w^4 */
    w *= w;
    w *= w;
    d *= w;
    
    /* 3. return the sum of the four surflets */
    return dot(d,vec4(52.));
}

float simplex_noise(vec3 m){
    return.5333333*simplex3d(m)
    +.2666667*simplex3d(2.*m)
    +.1333333*simplex3d(4.*m)
    +.0666667*simplex3d(8.*m);
    
    // return simplex3d(m);
}

//////////////////////////////////////////////////////////////////////////////////

float rand2D(vec2 co){
    // return fract(sin(dot(co.xy,vec2(12.9898,78.233)))*43758.5453);
    return sin(dot(co.xy,vec2(50.,0.)));
}

float rand3D(in vec3 co){
    return fract(sin(dot(co.xyz,vec3(12.9898,78.233,144.7272)))*43758.5453);
}

float simple_interpolate(float a,float b,float x)
{
    return a+smoothstep(0.,1.,x)*(b-a);
}
float interpolatedNoise3D(float x,float y,float z)
{
    float integer_x=x-fract(x);
    float fractional_x=x-integer_x;
    
    float integer_y=y-fract(y);
    float fractional_y=y-integer_y;
    
    float integer_z=z-fract(z);
    float fractional_z=z-integer_z;
    
    float v1=rand3D(vec3(integer_x,integer_y,integer_z));
    float v2=rand3D(vec3(integer_x+1.,integer_y,integer_z));
    float v3=rand3D(vec3(integer_x,integer_y+1.,integer_z));
    float v4=rand3D(vec3(integer_x+1.,integer_y+1.,integer_z));
    
    float v5=rand3D(vec3(integer_x,integer_y,integer_z+1.));
    float v6=rand3D(vec3(integer_x+1.,integer_y,integer_z+1.));
    float v7=rand3D(vec3(integer_x,integer_y+1.,integer_z+1.));
    float v8=rand3D(vec3(integer_x+1.,integer_y+1.,integer_z+1.));
    
    float i1=simple_interpolate(v1,v5,fractional_z);
    float i2=simple_interpolate(v2,v6,fractional_z);
    float i3=simple_interpolate(v3,v7,fractional_z);
    float i4=simple_interpolate(v4,v8,fractional_z);
    
    float ii1=simple_interpolate(i1,i2,fractional_x);
    float ii2=simple_interpolate(i3,i4,fractional_x);
    
    return simple_interpolate(ii1,ii2,fractional_y);
}

float perlin_noise(vec3 coord,float wavelength)
{
    return interpolatedNoise3D(coord.x/wavelength,coord.y/wavelength,coord.z/wavelength);
}

/////////////////////////////////////////////////////////////////////////////////

void main()
{
    vec2 uv=v_position.xy;
    
    vec2 p=v_position.xy;
    vec3 p3=vec3(p,u_time*.4);
    
    // float intensity=perlin_noise(vec3(p3*4.+4.), .5);
    float intensity=simplex_noise(vec3(p3));
    // float intensity=simplex_noise(vec3(p3*4.+4.));
    
    // intensity += rand2D(uv);
    
    float t=clamp((uv.x*-uv.x*.16)+.15,0.,1.);
    // float t=clamp((uv.x*-uv.x*.08)+.15,0.,1.);
    float y=abs(intensity*-t+uv.y);
    
    float g=pow(y,.2);
    
    vec3 col=vec3(.70,1.48,1.78);
    col=col*-g+col;
    col=col*col;
    col=col*col;
    col=col*col;
    
    if(col.b < 0.1){
        discard;
    }
    
    gl_FragColor=vec4(col,1.);
}