#version 410 core

out vec2 tc;

// gl_InstanceID - id �������� ���������
// gl_VertexID - id ������� �������

//uniform bool isClicked;
//uniform vec3 clickPoint;

void main()
{
	vec2 patchTexCoords[] = vec2[](vec2(0.0, 0.0), vec2(1.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 1.0));

	int x = gl_InstanceID % 64;
	int y = gl_InstanceID / 64;
	tc = vec2((x + patchTexCoords[gl_VertexID].x) / 64.0, (64 - y + patchTexCoords[gl_VertexID].y) / 64.0);

	gl_ClipDistance[0] = 0;
	gl_Position = vec4(tc.x - 0.5, 0.0, (1.0 - tc.y) - 0.5, 1.0);
//	if (isClicked) 
//	{
//		if (distance(gl_Position.xyz, clickPoint) < 1.0) gl_Position.y += 1;
//	}
}
