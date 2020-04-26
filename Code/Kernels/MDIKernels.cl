//This line helps solving a QResourse bug!
#define TWO 2.0f

float centralizeComponent(float component, float axisboundary, float shiftvalue);
float fixPBC( float component, float boundary, float shiftvalue, float delta, float maxboundary);

typedef struct GPUFloat3Components
{
    float x;
    float y;
    float z;
} GPUFloat3;

typedef struct STRUCT_VetexColor
{
    float R;
    float G;
    float B;
    float A;
} VetexColor;

typedef struct GPUProteinSpace
{
    unsigned short ProteinID ;
    float ProteinCOM[3] ;
    float ZAxis[2];
    float Radius ;
    float avgProteinCOM[3];
    float avgZAxis[2];
    float avgRadius;
} GPUProteinSpaceData ;

typedef struct GPUProteinParticle
{
    short ProteinID;
    unsigned int ParticleID;
    float Position[3];
} GPUProteinParticleData ;

typedef struct GPULipidSpace
{
    short LipidID ;
    float LipidCOM[3] ;
    float Radius ;
} GPULipidSpaceData ;

typedef struct GPULipidParticle
{
    short LipidID;
    unsigned int ParticleID;
    float Position[3];
} GPULipidParticleData ;

typedef struct GPUMoleculeParticleIdentity
    {
        unsigned int AtomIndex;
        unsigned short MoleculeType;
        unsigned short MoleculeIndex;
        unsigned short MoleculeResidueIndex;
    } GPUMoleculeParticleIdentityData;

typedef struct GPUMoleculeParticleInteraction
    {
        short MoleculeType          ;
        unsigned int ParticleID     ;
        unsigned int Interaction[ 45 ];
        short ProteinID[ 45 ];
        short InteractionCounter    ;
    } GPUMoleculeParticleInteractionData;

float centralizeComponent(float component, float axisboundary, float shiftvalue)
{
    float value;
    value = component - ( axisboundary  / TWO );
    return value ;
}

float fixPBC( float component, float boundary, float shiftvalue, float delta, float maxboundary)
{
    float newValue;

    newValue = component + shiftvalue;

    if( component > boundary )
    {
        newValue = component - boundary;
    }
    else if( (component + delta) > boundary )
    {
        newValue = maxboundary - component;
    }

    return newValue ;
}

__kernel void centralizeFrame(
__global GPUFloat3* inoutdata,
const float boxdimensionsX,
const float boxdimensionsY,
const float boxdimensionsZ,
const float minboxdimensionsX,
const float minboxdimensionsY,
const float minboxdimensionsZ,
const float maxboxdimensionsX,
const float maxboxdimensionsY,
const float maxboxdimensionsZ,
const unsigned int vertices)
{

    unsigned int vertexIndex = get_global_id(0);

    if( vertexIndex < vertices )
    {
        GPUFloat3 inFloat3;
        GPUFloat3 outFloat3;

        float maxXBoundary = 118.834;
        float maxYBoundary = 118.112;
        float maxZBoundary = 11.149;

        float avgXBoundary = 116.019;
        float avgYBoundary = 116.019;
        float avgZBoundary = 10.1359;

        float xComponent;
        float yComponent;
        float zComponent;

        //AVG       116.019, 116.019, 10.1359
        //MAX       118.834, 118.112, 11.149
        //MAX-AVG   2.815  , 2.093  , 1.0131
        //MIN       -2.486 , -2.246 , -0.39
        float xDelta = maxboxdimensionsX - boxdimensionsX;
        float yDelta = maxboxdimensionsY - boxdimensionsY;
        float zDelta = maxboxdimensionsZ - boxdimensionsZ;

        xDelta = max(xDelta, minboxdimensionsX);
        yDelta = max(yDelta, minboxdimensionsY);
        zDelta = max(zDelta, minboxdimensionsZ);

        inFloat3 = inoutdata[ vertexIndex ];

        xComponent = inFloat3.x; //fixPBC( inFloat3.x, boxdimensionsX, minboxdimensionsX, xDelta, maxboxdimensionsX);
        yComponent = inFloat3.y; //fixPBC( inFloat3.y, boxdimensionsY, minboxdimensionsY, yDelta, maxboxdimensionsY);
        zComponent = inFloat3.z; //fixPBC( inFloat3.z, boxdimensionsZ, minboxdimensionsZ, zDelta, maxboxdimensionsZ);

        outFloat3.x = centralizeComponent( xComponent, boxdimensionsX, minboxdimensionsX );
        outFloat3.y = centralizeComponent( yComponent, boxdimensionsY, minboxdimensionsY );
        outFloat3.z = centralizeComponent( zComponent, boxdimensionsZ, minboxdimensionsZ );

        inoutdata[ vertexIndex ] = outFloat3;
    }
}

__kernel void proteinCOM(
__global GPUProteinSpaceData* InOutProteinSpace,
__global GPUProteinParticleData* InProteinParticles,
const unsigned int proteinsNumber)
{
    const int   ZERO =0;
    const int   ONE =1;
    
    const int   X =0;
    const int   Y =1;
    const int   Z =2;
    
    const int   INT_PROTEIN_PARTICLES_NUMBER = 344;
    const float FLOAT_PROTEIN_PARTICLES_NUMBER = 344.0f;
    
    //globalID between 0 and 255 proteins number

    unsigned int globalID = get_global_id( 0 );
    
    if( globalID < proteinsNumber )
    {
        private GPUProteinSpaceData outProteinSpace;
        private float xComponent = 0.0f;
        private float yComponent = 0.0f;
        private float zComponent = 0.0f;
        
        private float xCenter = 0.0f;
        private float yCenter = 0.0f;
        private float zCenter = 0.0f;
        
        private float minX = 150.0f;
        private float maxX = -150.0f;
        private float minY = 150.0f;
        private float maxY = -150.0f;
        private float minZ = 15.0f;
        private float maxZ = -15.0f;

        private float centerToMinX = 0.0f;
        private float centerToMaxX = 0.0f;
        private float centerToMinY = 0.0f;
        private float centerToMaxY = 0.0f;

        private float maxRadius = 0;
        
        private float3 centerOfMass ;
        
        outProteinSpace = InOutProteinSpace[ globalID ];
        unsigned int lowIndex = globalID * INT_PROTEIN_PARTICLES_NUMBER;
        unsigned int hightIndex = lowIndex + INT_PROTEIN_PARTICLES_NUMBER;
        
        for( unsigned int particleIndex= lowIndex; particleIndex < hightIndex; particleIndex++)
        {
            xComponent = InProteinParticles[ particleIndex ].Position[ X ];
            yComponent = InProteinParticles[ particleIndex ].Position[ Y ];
            zComponent = InProteinParticles[ particleIndex ].Position[ Z ];
            
            //mintain the protein space
            minX = min(minX, xComponent);
            minY = min(minY, yComponent);
            minZ = min(minZ, zComponent);
            maxX = max(maxX, xComponent);
            maxY = max(maxY, yComponent);
            maxZ = max(maxZ, zComponent);

            xCenter += xComponent;
            yCenter += yComponent;
            zCenter += zComponent;
        }
        
        xCenter /= FLOAT_PROTEIN_PARTICLES_NUMBER;
        yCenter /= FLOAT_PROTEIN_PARTICLES_NUMBER;
        zCenter /= FLOAT_PROTEIN_PARTICLES_NUMBER;
        
        centerOfMass   = (float3)( xCenter, yCenter, zCenter );

        centerToMinX = distance( xCenter, minX );
        centerToMaxX = distance( xCenter, maxX );
        centerToMinY = distance( yCenter, minY );
        centerToMaxY = distance( yCenter, maxY );

        maxX = max( centerToMinX, centerToMaxX);
        maxY = max( centerToMinY, centerToMaxY);

        maxRadius = max( maxX, maxY);
            
        outProteinSpace.ProteinCOM[ X ] = xCenter;
        outProteinSpace.ProteinCOM[ Y ] = yCenter;
        outProteinSpace.ProteinCOM[ Z ] = zCenter;
        
        outProteinSpace.ZAxis[ ZERO ] = minZ;
        outProteinSpace.ZAxis[ ONE ] = maxZ;
        
        outProteinSpace.Radius = maxRadius;
        
        InOutProteinSpace[ globalID ] = outProteinSpace;
        
    }
}

__kernel void lipidCOM(
    __global GPULipidSpaceData* InOutLipidSpace,
    __global GPULipidParticleData* InLipidParticles,
    const unsigned int lipidsNumber)
{
    const int   X =0;
    const int   Y =1;
    const int   Z =2;

    const int   INT_LIPID_PARTICLES_NUMBER = 13;
    const float FLOAT_LIPID_PARTICLES_NUMBER = 13.0f;

    unsigned int globalID = get_global_id( 0 );

    if( globalID < lipidsNumber )
    {
        private GPULipidSpaceData outLipidSpace;
        private GPULipidParticleData inLipidParticle;

        private float xComponent = 0.0f;
        private float yComponent = 0.0f;
        private float zComponent = 0.0f;

        private float xCenter = 0.0f;
        private float yCenter = 0.0f;
        private float zCenter = 0.0f;

        private float2 centerPoint;
        private float2 currentPoint ;
        private float maxRadius = 0;

        private float3 centerOfMass ;

        outLipidSpace = InOutLipidSpace[ globalID ];
        inLipidParticle = InLipidParticles[ globalID ];
        unsigned int lowIndex = globalID * INT_LIPID_PARTICLES_NUMBER;
        unsigned int hightIndex = lowIndex + INT_LIPID_PARTICLES_NUMBER;

        for( unsigned int particleIndex= lowIndex; particleIndex < hightIndex; particleIndex++)
        {
            xComponent = InLipidParticles[ particleIndex ].Position[ X ];
            yComponent = InLipidParticles[ particleIndex ].Position[ Y ];
            zComponent = InLipidParticles[ particleIndex ].Position[ Z ];

            xCenter += xComponent;
            yCenter += yComponent;
            zCenter += zComponent;
        }

        xCenter /= FLOAT_LIPID_PARTICLES_NUMBER;
        yCenter /= FLOAT_LIPID_PARTICLES_NUMBER;
        zCenter /= FLOAT_LIPID_PARTICLES_NUMBER;

        centerOfMass   = (float3)( xCenter, yCenter, zCenter );

        for( unsigned int particleIndex= lowIndex; particleIndex < hightIndex; particleIndex++)
        {
            float radius ;
            xComponent = InLipidParticles[ particleIndex ].Position[ X ];
            yComponent = InLipidParticles[ particleIndex ].Position[ Y ];

            currentPoint = (float2)( xComponent, yComponent);
            radius=  distance( centerPoint, currentPoint );
            maxRadius = max(maxRadius, radius );

        }

        outLipidSpace.LipidCOM[ X ] = xCenter;
        outLipidSpace.LipidCOM[ Y ] = yCenter;
        outLipidSpace.LipidCOM[ Z ] = zCenter;

        outLipidSpace.Radius = maxRadius;

        InOutLipidSpace[ globalID ] = outLipidSpace;

    }
}

__kernel void ProteinLipidInteracion(
    __global GPUFloat3* particlesPositionData,
    __global VetexColor* particlesColorData,
    __global GPUMoleculeParticleIdentityData* moleculeParticlesIdentity,
    __global GPUProteinSpaceData* proteinSpaces,
    __global GPUProteinParticleData* proteinParticles,
    const unsigned int moleculeParticlesNumber,
    const float interactionSpace)
{
    private const unsigned short PROTEIN = 0;
    private const unsigned short ZERO = 0;
    private const unsigned int ONE = 1;
    private const unsigned short PROTEINS_NUMBER = 256;
    private const unsigned short PROTEIN_PARTICLES_NUMBER = 344;
    private const unsigned int X = 0;
    private const unsigned int Y = 1;

    const float MIN_INTERACTION_SPACE = 0.60f; // 0.00517f;
    const float MAX_INTERACTION_SPACE = 0.80f; // 0.00689f;

    private unsigned int globalID = get_global_id(0);

    if( globalID < moleculeParticlesNumber )
    {

        private GPUMoleculeParticleIdentityData moleculeParticleIdentity;

        private GPUProteinSpaceData proteinSpace;
        private GPUProteinParticleData proteinParticle;
        private short moleculeType;
        private unsigned short proteinID;
        private unsigned short spaceProteinID;
        private float2 proteinCenterOfMass;
        private float2 proteinParticlePosition;
        private float proteinRadius;
        private unsigned int proteinParticleID;

        private GPUFloat3 particlePositionData;
        private VetexColor particleColorData;
        private float2 particlePosition;
        private float distanceToProtein;
        private float distanceToProteinParticle;

        private bool hasInteraction;

        hasInteraction = false;
        moleculeParticleIdentity = moleculeParticlesIdentity[ globalID ];
        particlePositionData = particlesPositionData[ globalID ];

        particlePosition = (float2) ( particlePositionData.x, particlePositionData.y);

        proteinID = moleculeParticleIdentity.MoleculeIndex;
        moleculeType = moleculeParticleIdentity.MoleculeType;


        for( unsigned short proteinIndex = ZERO ; proteinIndex < PROTEINS_NUMBER; proteinIndex++)
        {

            proteinSpace = proteinSpaces[ proteinIndex ];
            spaceProteinID = proteinSpace.ProteinID;
            if( spaceProteinID == proteinID && moleculeType == PROTEIN)
            {
                continue;
            }

            proteinCenterOfMass = (float2)( proteinSpace.ProteinCOM[ X ], proteinSpace.ProteinCOM[ Y ]);
            proteinRadius = proteinSpace.Radius;

            distanceToProtein = distance( proteinCenterOfMass, particlePosition );

            if( distanceToProtein <= proteinRadius )
            {
                for( unsigned short proteinParticleIndex = 0; proteinParticleIndex < PROTEIN_PARTICLES_NUMBER; proteinParticleIndex++)
                {
                    proteinParticle = proteinParticles[ spaceProteinID  * PROTEIN_PARTICLES_NUMBER + proteinParticleIndex];
                    proteinParticlePosition = (float2)( proteinParticle.Position[ X ], proteinParticle.Position[ Y ]);
                    distanceToProteinParticle = distance( particlePosition, proteinParticlePosition );

                    if( distanceToProteinParticle >= MIN_INTERACTION_SPACE && distanceToProteinParticle <= MAX_INTERACTION_SPACE )
                    {
                        hasInteraction = true;
                        continue;
                    }
                }
            }
        }

        if( hasInteraction == true )
        {
            particleColorData.R =1.0f;
            particleColorData.G =0.0f;
            particleColorData.B =0.0f;
            particleColorData.A = 1.0f;
        }
        else
        {
            particleColorData.R = 0.0f;
            particleColorData.G = 1.0f;
            particleColorData.B = 0.0f;
            particleColorData.A = 1.0f;

        }
        particlesColorData[ globalID ] = particleColorData;
    }
}

__kernel void PLCOMOnTheFlyInteracion(
                                        __global GPUFloat3* particlesPositionData,
                                        __global GPUFloat3* particlesColorData,
                                       __global GPUProteinSpaceData* proteinSpaces,
                                       __global short* referenceProtein,
                                       __global short* interactionCount,
                                       const unsigned int moleculeParticlesNumber,
                                       const float interactionSpace)
{
    private const short ZERO = 0;
    private const unsigned int ONE = 1;
    private const unsigned int X = 0;
    private const unsigned int Y = 1;
    private const short PROTEINS_NUMBER = 256;
    private unsigned int globalID = get_global_id(0);

    if( globalID < moleculeParticlesNumber )
    {

        private GPUProteinSpaceData proteinSpace;
        private short spaceProteinID;
        private float2 proteinCenterOfMass;
        private float proteinRadius;

        private short particleInteractionCounter;
        private GPUFloat3 particlePositionData;
        private float2 particlePosition;
        private float distanceToProtein;
        private GPUFloat3 particleColor;

        particlePositionData = particlesPositionData[ globalID ];
        particlePosition = (float2) ( particlePositionData.x, particlePositionData.y);

        particleColor.x = 0.0f;
        particleColor.y = 1.0f;
        particleColor.z = 0.0f;

        particleInteractionCounter = ZERO;

        referenceProtein[ globalID ] = -1;
        for( short proteinIndex = ZERO ; proteinIndex < PROTEINS_NUMBER; proteinIndex++)
        {

            proteinSpace = proteinSpaces[ proteinIndex ];
            spaceProteinID = proteinSpace.ProteinID;
            if( spaceProteinID == (globalID + ONE))
            {
                referenceProtein[ globalID ] = -1;
                continue;
            }

            proteinCenterOfMass = (float2)( proteinSpace.ProteinCOM[ X ], proteinSpace.ProteinCOM[ Y ]);
            proteinRadius = proteinSpace.Radius;

            distanceToProtein = distance( proteinCenterOfMass, particlePosition );

            if( distanceToProtein <= proteinRadius )
            {
                if( particleInteractionCounter == ZERO )
                {     
                    particleColor.x = 1.0f;
                    particleColor.y = 0.0f;
                    particleColor.z = 0.0f;
                    referenceProtein[ globalID ] = spaceProteinID;
                }
                particleInteractionCounter++;
            }
        }

        particlesColorData[ globalID ] = particleColor;
        interactionCount[ globalID ] = particleInteractionCounter;
    }
}

__kernel void PLCOMInteracion(
                                       __global GPUFloat3* particlesPositionData,
                                       __global GPUProteinSpaceData* proteinSpaces,
                                       __global short* referenceProtein,
                                       __global short* interactionCount,
                                       const unsigned int moleculeParticlesNumber,
                                       const float interactionSpace)
{
    private const short ZERO = 0;
    private const unsigned int ONE = 1;
    private const unsigned int X = 0;
    private const unsigned int Y = 1;
    private const short PROTEINS_NUMBER = 256;

    private unsigned int globalID = get_global_id(0);

    if( globalID < moleculeParticlesNumber )
    {

        private GPUProteinSpaceData proteinSpace;
        private short spaceProteinID;
        private float2 proteinCenterOfMass;
        private float proteinRadius;

        private short particleInteractionCounter;
        private GPUFloat3 particlePositionData;
        private float2 particlePosition;
        private float distanceToProtein;

        particlePositionData = particlesPositionData[ globalID ];
        particlePosition = (float2) ( particlePositionData.x, particlePositionData.y);

        particleInteractionCounter = ZERO;

        for( short proteinIndex = ZERO ; proteinIndex < PROTEINS_NUMBER; proteinIndex++)
        {

            proteinSpace = proteinSpaces[ proteinIndex ];
            spaceProteinID = proteinSpace.ProteinID;
            if( spaceProteinID == (globalID + ONE) )
            {
                referenceProtein[ globalID ] = -1;
                continue;
            }

            proteinCenterOfMass = (float2)( proteinSpace.ProteinCOM[ X ], proteinSpace.ProteinCOM[ Y ]);
            proteinRadius = proteinSpace.Radius;

            distanceToProtein = distance( proteinCenterOfMass, particlePosition );

            if( distanceToProtein <= proteinRadius )
            {
                if( particleInteractionCounter == ZERO )
                {
                    referenceProtein[ globalID ] = spaceProteinID;
                }
                particleInteractionCounter++;
            }
        }

        interactionCount[ globalID ] = particleInteractionCounter;
    }
}
