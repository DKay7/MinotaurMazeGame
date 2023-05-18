uniform vec2 u_lightPosition;
uniform float u_radius;

// TODO Fix it!

void main()                             
{
    float distance  = length( u_lightPosition - gl_FragCoord.xy );

    float maxDistance = pow( u_radius, 0.23);
    float quadDistance = pow( distance, 0.23);

    float quadIntensity = 1.0 - min( quadDistance, maxDistance )/maxDistance;

    gl_FragColor = vec4(quadIntensity, quadIntensity, quadIntensity, 1.0);
}   