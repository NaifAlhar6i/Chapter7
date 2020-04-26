#version 410

layout(location = 0) in vec3 attributePosition;
layout(location = 1) in vec4 attributeColor;

uniform mat4 uniMVP;

out vec4 vertColor;

float getPointSize(  )
{

    float pointSize;
    float dist;
    vec4 camera_pos = vec4( 0.0f, 0.3f, -0.7f, 1.0 );

    dist =  distance( attributePosition.xyz, camera_pos.xyz ) ;

    pointSize = 13;//sphereSize;// / dist;
    //pointSize = 10 / dist;

    return pointSize;

}

void main()
{

    gl_PointSize = getPointSize(  );
    gl_Position = uniMVP * vec4( attributePosition, 1.0f);
    vertColor= attributeColor;


}
