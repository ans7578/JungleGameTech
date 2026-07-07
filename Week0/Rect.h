

// 삼각형을 하드 코딩(삼각형 정점 3개의 포지션과 색상값을 정의해준다)
FVertexSimple rect_vertices[] =
{
	{  -1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f }, // LeftTop vertex (red)
	{  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f }, //  RightTOpvertex (green)
	{ 1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f },  // RightBottom vertex (blue)
	{ -1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f }  // LeftBottom vertex (black)

};

UINT rect_indices[] =
{
	0, 1, 2, // Triangle indices
	0, 2, 3 
};