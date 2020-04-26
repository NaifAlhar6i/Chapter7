#version 410

layout(points) in;
layout(points, max_vertices = 1) out;//386

in vec4 vertPosition[];
in vec4 vertColor[];

in mat4 MVP[];
in vec3 CenterOfMass[];
in float Radius[];

out gl_PerVertex {
    vec4 gl_Position;
    float gl_PointSize;
};
out vec4 geomColor;

float getPointSize(  )
{

    float pointSize;
    float dist;
    vec4 camera_pos = vec4( 0.0f, 0.3f, -0.7f, 1.0 );

    dist =  distance( vertPosition[0].xyz, camera_pos.xyz ) ;

    pointSize = 10;//sphereSize;// / dist;
    //pointSize = 10 / dist;

    return pointSize;

}

void main()
{
    vec2 centerOfMass;
    vec2 currentPosition;
    vec2 proteinToParticleVector;
    vec2 newPosition;
    float zPosition;
    float delta1;
    float delta2;

    centerOfMass = CenterOfMass[0].xy;
    currentPosition = vertPosition[0].xy;
    zPosition = vertPosition[0].z;
    proteinToParticleVector =  normalize( currentPosition - centerOfMass );
    delta1 = distance( centerOfMass, currentPosition );
    delta2 = Radius[0] - delta1;
    newPosition = currentPosition + (proteinToParticleVector * delta2);

    if( delta1 > 0 )
    {
        gl_PointSize = getPointSize(  );
        geomColor = vertColor[0];
        gl_Position = MVP[0] * vec4(newPosition, zPosition, 1.0);
        EmitVertex();
    }
    else
    {
        gl_PointSize = getPointSize(  );
        geomColor = vertColor[0];
        gl_Position = MVP[0] * vec4(currentPosition, zPosition, 1.0);
        EmitVertex();
    }
}

