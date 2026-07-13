#pragma once
#include "../../Headers.h"

const float PI = 3.14159265f;
float totalRadian = 2.0f * PI;

#define VERTEX_COUNT 32

struct CirclePrimitive
{
	UINT vertexCount = VERTEX_COUNT;
	UINT indexCount = VERTEX_COUNT * 3;

	FVertexSimple vertices[VERTEX_COUNT + 1];
	UINT indices[VERTEX_COUNT * 3];

	UINT GetVertexStride()
	{
		return sizeof(FVertexSimple);
	}
	UINT GetVertexCount()
	{
		return vertexCount + 1;
	}

	UINT GetVerticesSize()
	{
		return sizeof(vertices);
	}
	UINT GetIndicesSize()
	{
		return sizeof(indices);

	}

	CirclePrimitive()
	{
		float angle = 0.f;

		vertices[0].x = 0.0f;
		vertices[0].y = 0.0f;
		vertices[0].z = 0.0f;


		UINT i = 0;

		for (i = 0; i < vertexCount - 1; i++)
		{
			angle = (float)i / (float)vertexCount * totalRadian;
			vertices[i + 1].x = -cos(angle);
			vertices[i + 1].y = sin(angle);
			vertices[i + 1].z = 0.0f;



			indices[i * 3] = 0;
			indices[i * 3 + 1] = i + 1;
			indices[i * 3 + 2] = i + 2;
		}
		// 2. 루프에서 제외된 '맨 마지막 피자 조각'의 정점과 인덱스는 밖에서 단 한 번만 깔끔하게 계산합니다.
		// (i가 vertexCount - 1 인 상태)
		angle = (float)i / (float)vertexCount * totalRadian;
		vertices[i + 1].x = -cos(angle);
		vertices[i + 1].y = sin(angle);
		vertices[i + 1].z = 0.0f;


		indices[i * 3] = 0;
		indices[i * 3 + 1] = i + 1;
		indices[i * 3 + 2] = 1; // 깔끔하게 1번으로 원을 닫아줌!
	}
};