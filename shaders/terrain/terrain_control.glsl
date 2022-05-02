// http://steps3d.narod.ru/tutorials/tesselation-tutorial.html
// tesselation control shader
#version 410 core

layout (vertices = 4) out; // Число вершин в патче

in vec2 tc[];
out vec2 tc_out[];

uniform int maxTessLevel;
uniform mat4 viewProject;
uniform mat4 model;

// gl_in - массив структур (gl_Position, gl_PointSize, gl_InvocationID, gl_ClipDistance[])
// gl_PatchVerticesIn - число вершин в патче
// gl_PrimitiveID - id текущего примитива
// gl_InvocationID - id вершины текущего примитива 
// gl_ClipDistance[i] - расстояние отсечения для каждой пользовательской плоскости отсечения i

// gl_out - массив структур как и gl_in
// gl_TessLevelOuter - float[4], разбиение границ примитива
// gl_TessLevelInner - float[2], разбиение внутри примитива


float calcTessLevel()
{
	const int minLevel = 4;
	const float minDepth = 0.001;
	const float maxDepth = 30.0;

	vec4 p = viewProject * model * gl_in[gl_InvocationID].gl_Position;

	float depth = clamp((abs(p.z) - minDepth)/(maxDepth - minDepth), 0.0, 1.0); // ограничить 1 значение между 2 и 3. return min(max(1,2), 3)
	float tl = mix(maxTessLevel, minLevel, depth); // линейная интерполяция между 1 и 2 с помощью 3
	return tl;
}

void main()
{
	float tessLevel = calcTessLevel();
	gl_TessLevelOuter[0] = tessLevel;
	gl_TessLevelOuter[1] = tessLevel;
	gl_TessLevelOuter[2] = tessLevel;
	gl_TessLevelOuter[3] = tessLevel;
	gl_TessLevelInner[0] = tessLevel;
	gl_TessLevelInner[1] = tessLevel;
	tc_out[gl_InvocationID] = tc[gl_InvocationID];
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	gl_out[gl_InvocationID].gl_ClipDistance[0] = gl_in[gl_InvocationID].gl_ClipDistance[0];
}
