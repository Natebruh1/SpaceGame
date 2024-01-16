#version 330 core

uniform mat4 projection;
uniform mat4 model;
in VS_OUT {
    ivec3 tileId;
} gs_in[];

out vec2 texCoord;

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

void main() {
    
    float tileId = uint(gs_in[0].tileId.z);
    float tileX = float(gs_in[0].tileId.x / 16.0);
    float tileY = float(gs_in[0].tileId.y / 16.0);

    float texX= float(mod(gs_in[0].tileId.z,16.0))/16.0;
    float texY= floor(float(gs_in[0].tileId.z/16.0))/16.0;

    const float B = 1.0 / 256.0;
    float S = 1.0 / 16.0;

    gl_Position = projection * gl_in[0].gl_Position;
    texCoord = vec2(texX + B, texY + B);
    
    // texCoord = vec2(texX, texY);
    EmitVertex();

    gl_Position = projection * (gl_in[0].gl_Position + (model*vec4(16.0, 0.0, 0.0, 0.0)));
    texCoord = vec2(texX + S - B, texY + B);
    //texCoord = vec2(texX, texY);
    
    EmitVertex();

    gl_Position = projection * (gl_in[0].gl_Position + (model*vec4(0.0, 16.0, 0.0, 0.0)));
    texCoord = vec2(texX + B, texY + S - B);
    //texCoord = vec2(texX, texY);
    
    EmitVertex();

    gl_Position = projection * (gl_in[0].gl_Position + (model*vec4(16.0, 16.0, 0.0, 0.0)));
    texCoord = vec2(texX + S - B, texY + S - B);
    
    EmitVertex();

    EndPrimitive();
}  