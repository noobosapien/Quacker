const float PI=3.14159265;

vec2 hash2(vec2 p)
{
    return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

vec3 voronoi(in vec2 x)
{
    vec2 n=floor(x);
    vec2 f=fract(x);
    
    vec2 mg,mr;
    
    float md=8.;
    for(int j=-1;j<=1;j++)
    for(int i=-1;i<=1;i++)
    {
        vec2 g=vec2(float(i),float(j));
        vec2 o=hash2(n+g);
        o=.5+.5*sin(iTime+6.2831*o);
        vec2 r=g+o-f;
        float d=dot(r,r);
        
        if(d<md)
        {
            md=d;
            mr=r;
            mg=g;
        }
    }
    
    md=8.;
    for(int j=-2;j<=2;j++)
    for(int i=-2;i<=2;i++)
    {
        vec2 g=mg+vec2(float(i),float(j));
        vec2 o=hash2(n+g);
        o=.5+.5*sin(iTime+6.2831*o);
        vec2 r=g+o-f;
        
        if(dot(mr-r,mr-r)>.00001)
        md=min(md,dot(.5*(mr+r),normalize(r-mr)));
    }
    
    return vec3(md,mr);
}

float sphere(float t,float k)
{
    float d=1.+t*t-t*t*k*k;
    if(d<=0.)
    return-1.;
    float x=(k-sqrt(d))/(1.+t*t);
    return asin(x*t);
}

void main()
{
    // bg texture
    // vec4 texColor = texture(iChannel0, fragCoord.xy / iResolution.xy);
    
    vec2 uv=fragCoord.xy-.5*iResolution.xy;
    float v=iResolution.x;
    
    if(v>iResolution.y)
    v=iResolution.y;
    
    uv/=v;
    uv*=3.;
    
    float len=length(uv);
    float k=1.;
    float len2;
    
    len2=sphere(len*k,sqrt(2.))/sphere(1.*k,sqrt(2.));
    uv=uv*len2*.5/len;
    uv=uv+.5;
    
    vec2 pos=uv;
    float t=iTime/1.;
    float scale1=40.;
    float scale2=20.;
    float val=0.;
    
    val+=sin((pos.x*scale1+t));
    val+=sin((pos.y*scale1+t)/2.);
    val+=sin((pos.x*scale2+pos.y*scale2+sin(t))/2.);
    val+=sin((pos.x*scale2-pos.y*scale2+t)/2.);
    val/=2.;
    
    vec3 c=voronoi(64.*pos);
    
    // isolines
    val+=2.*sin(t)*c.x*(.5+.5*sin(64.*c.x));
    
    float glow=.020/(.015+distance(len,1.));
    
    val=(cos(PI*val)+1.)*.5;
    vec4 col2=vec4(.3,.7,1.,1.);
    
    fragColor=step(len,1.)*.5*col2*val+glow*col2+.5*texColor;
}