#version 330 core

uniform mat4 projection;
uniform ivec2 mapSize;
uniform mat4 model;

layout (location = 0) in ivec3 aTileId; //X,Y,TILE ID

out VS_OUT {
    ivec3 tileId;
} vs_out;

void main()
{
    int i = gl_VertexID;
    float x = float(aTileId.x) * float(mapSize.x); 
    float y = float(aTileId.y) * float(mapSize.y); 
    gl_Position =model * vec4(x, -y, 0, 1);
    
    //gl_Position = vec4(0, 0, 0, 1);
    
    vs_out.tileId = aTileId;
}