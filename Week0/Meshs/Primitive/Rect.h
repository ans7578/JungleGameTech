#include "../../Headers.h"

#define VETEX_COUNT 4
#define	INDEX_COUNT 6

// 삼각형을 하드 코딩(삼각형 정점 3개의 포지션과 색상값을 정의해준다)
struct RectPrimitive
{
	FVertexUV vertices[VETEX_COUNT] =
	{
		{  -1.0f,  1.0f, 0.0f, 0.f, 0.f }, // LeftTop vertex (red)
		{  1.0f, 1.0f, 0.0f, 1.f, 0.f	}, //  RightTOpvertex (green)
		{ 1.0f, -1.0f, 0.0f, 1.f, 1.f 	 },  // RightBottom vertex (blue)
		{ -1.0f, -1.0f, 0.0f, 0.f, 1.f 	 }  // LeftBottom vertex (black)
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
		return sizeof(vertices[0]);
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