// http://steps3d.narod.ru/tutorials/tesselation-tutorial.html
// tesselation control shader
#version 410 core

layout (vertices = 4) out; // ����� ������ � �����

in vec2 tc[];
out vec2 tc_out[];

uniform int tesselationLevel;
uniform mat4 viewProject;
uniform mat4 model;

// gl_in - ������ �������� (gl_Position, gl_PointSize, gl_InvocationID, gl_ClipDistance[])
// gl_PatchVerticesIn - ����� ������ � �����
// gl_PrimitiveID - id �������� ���������
// gl_InvocationID - id ������� �������� ��������� 
// gl_ClipDistance[i] - ���������� ��������� ��� ������ ���������������� ��������� ��������� i

// gl_out - ������ �������� ��� � gl_in
// gl_TessLevelOuter - float[4], ��������� ������ ���������
// gl_TessLevelInner - float[2], ��������� ������ ���������


float calcTessLevel()
{
	const int minTess = 4;
	const float minDepth = 0.001;
	const float maxDepth = 30.0;

	vec4 p = viewProject * model * gl_in[gl_InvocationID].gl_Position;

	float depth = clamp((abs(p.z) - minDepth)/(maxDepth - minDepth), 0.0, 1.0); // ���������� 1 �������� ����� 2 � 3. return min(max(1,2), 3)
	float tl = mix(tesselationLevel, minTess, depth); // �������� ������������ ����� 1 � 2 � ������� 3
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
