#version 410 core

out vec2 tc;

// gl_InstanceID - id текущего примитива
// gl_VertexID - id текущей вершины

void main()
{
	vec2 patchTexCoords[] = vec2[](vec2(0.0, 0.0), vec2(1.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 1.0));

	int x = gl_InstanceID % 512;
	int y = gl_InstanceID / 512;
	tc = vec2((x + patchTexCoords[gl_VertexID].x) / 512.0, (512 - y + patchTexCoords[gl_VertexID].y) / 512.0);

	gl_ClipDistance[0] = 0;
	gl_Position = vec4(tc.x - 0.5, 0.0, (1.0 - tc.y) - 0.5, 1.0); // (x: [-0.5, 0.5]; y: 0;	z: [0.5, -0.5]; w: 1.0)
}
