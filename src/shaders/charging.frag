precision mediump float;

varying vec2 v_fragTexCoord;

uniform float iTime;
float seed=.80;
const float particles=460.;
float res=100.;
float direction=1.;

void main()

{
    vec2 uv=(vec2(-.5,-.5)+1.*v_fragTexCoord.xy)/1.;
    float clr=0.;
    
    //seed = (seed+floor(iTime));
    
    float iSphere=1.05-length(uv);
    if(iSphere>0.)//remove tests outside of influence sphere
    {
        
        for(float i=0.;i<particles;i+=1.)
        {
            seed+=i+tan(seed);
            vec2 tPos=(vec2(cos(seed),sin(seed)));
            
            vec2 pPos=vec2(0.,0.);
            float speed=i/particles+.4713*(cos(seed)+1.5)/1.5;
            float timeOffset=iTime*speed+(speed);
            float timecycle=timeOffset-floor(timeOffset);
            
            pPos=mix(tPos,pPos,1.+direction-timecycle);
            
            // pPos=floor(pPos*res)/res;//-----------------------------------------comment this out for smooth version
            
            vec2 p1=pPos;
            vec4 r1=vec4(vec2(step(p1,uv)),1.-vec2(step(p1+1./res+i/particles/res,uv)));
            float px1=r1.x*r1.y*r1.z*r1.w*speed;
            
            clr+=px1;
        }
    }
    gl_FragColor=(vec4(clr)*vec4(0.,.9686,1.,1.))*(1.-length(uv));
}