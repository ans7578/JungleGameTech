#include "../../Headers.h"

#define VETEX_COUNT 4
#define	INDEX_COUNT 6

// 삼각형을 하드 코딩(삼각형 정점 3개의 포지션과 색상값을 정의해준다)
struct RectPrimitive
{
	FVertexSimple vertices[VETEX_COUNT] =
	{
		{  -1.0f,  1.0f, 0.0f }, // LeftTop vertex (red)
		{  1.0f, 1.0f, 0.0f }, //  RightTOpvertex (green)
		{ 1.0f, -1.0f, 0.0f },  // RightBottom vertex (blue)
		{ -1.0f, -1.0f, 0.0f }  // LeftBottom vertex (black)
	};

	UINT indices[INDEX_COUNT] =
	{
		0, 1, 2, // Triangle indices
		0, 2, 3
	};

	UINT vertexCount = VETEX_COUNT;
	UINT indexCount = INDEX_COUNT;

	UINT GetVertexStride()
	{
		return sizeof(FVertexSimple);
	}
	UINT GetVertexCount()
	{
		return vertexCount;
	}

	UINT GetVerticesSize()
	{
		return sizeof(vertices);
	}
	UINT GetIndicesSize()
	{
		return sizeof(indices);

	}
};