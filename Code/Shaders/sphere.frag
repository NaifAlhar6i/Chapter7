#version 410

in vec4 vertColor;
out vec4 fragColor;

float getDiffuse()
{
    vec3 lightDir=vec3(0.3,0.2,0.9);

    vec3 Normal;
    Normal.xy = gl_PointCoord * 2.0 - vec2(1.0);
    float mag = dot( Normal.xy, Normal.xy );
    if (mag > 1.0) discard;   // kill pixels outside circle

    Normal.z = sqrt(1.0-mag);

    // calculate lighting
    float diffuse = max(0.0, dot(lightDir, Normal));

    return diffuse;
}

void main()
{
    fragColor = vertColor * getDiffuse();
}
