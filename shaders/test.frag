
uniform sampler2D Sampler0;
uniform sampler2D Sampler1;

uniform sampler2D Lightmap;
uniform int LightmapPass;

varying float xpos;
varying float ypos;
varying float zpos;

void main (void)
{
    vec4 texval1 = texture2D(Sampler0, vec2(gl_TexCoord[0]));
    vec4 texval2 = texture2D(Sampler1, vec2(gl_TexCoord[0]));

    vec4 lightmap = texture2D(Lightmap, vec2(gl_TexCoord[1]));

    float gray=(lightmap.r+lightmap.g+lightmap.b)/3;
    texval1.xyz=texval1.xyz*gray+(1-gray)*lightmap.xyz/2;

    gl_FragColor = texval1;//texval2+vec4 (xpos, ypos, zpos, 1.0);
}