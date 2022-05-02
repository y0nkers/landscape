// http://steps3d.narod.ru/tutorials/tesselation-tutorial.html
// tesselation evaluation shader
#version 410

layout (quads, fractional_even_spacing, ccw) in; // тип тесселяции, способ разбиения отрезков и способ упорядочивания вершин

in vec2 tc_out[];
out vec2 texCoords;
out vec3 fragPos;

uniform sampler2D heightMap;
uniform float depth;
uniform mat4 viewProject;
uniform mat4 model;
uniform vec4 clipPlane;

// gl_in как в tess control
// gl_TessCoord (u,v,w) - трехмерный вектор с координатами, идентифицирующими положение вершины в патче;

void main()
{
	vec2 tc = vec2(tc_out[0].x + (gl_TessCoord.x) / 64.0, tc_out[0].y + (1.0 - gl_TessCoord.y) / 64.0);

	vec4 tessellatedPoint = vec4(gl_in[0].gl_Position.x + gl_TessCoord.x / 64.0, 0.0, gl_in[0].gl_Position.z + gl_TessCoord.y / 64.0, 1.0);
	tessellatedPoint.y += texture(heightMap, tc).r * depth;

	gl_Position = viewProject * model * tessellatedPoint;
	fragPos = vec3(model * tessellatedPoint);

	vec4 vertexPos = vec4(fragPos, 1.0);
	gl_ClipDistance[0] = dot(vertexPos, clipPlane);
	texCoords = tc;
}
