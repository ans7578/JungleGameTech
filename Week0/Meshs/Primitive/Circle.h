#pragma once
#include "../../Headers.h"

const float PI = 3.14159265f;
float totalRadian = 2.0f * PI;

#define VERTEX_COUNT 32

struct CirclePrimitive
{
	CirclePrimitive()
	{
		float angle = 0.f;

		// 1. 중심점 세팅
		vertices[0].x = 0.0f;
		vertices[0].y = 0.0f;
		vertices[0].z = 0.0f;
		vertices[0].u = 0.5f; // 텍스처의 정중앙
		vertices[0].v = 0.5f;

		UINT i = 0;

		// 2. 외곽 정점 루프 연산
		for (i = 0; i < vertexCount - 1; i++)
		{
			angle = (float)i / (float)vertexCount * totalRadian;

			// 포지션 계산
			vertices[i + 1].x = -cos(angle);
			vertices[i + 1].y = sin(angle);
			vertices[i + 1].z = 0.0f;

			// UV 좌표 보정 연산
			// 포지션 좌표의 범위 [-1, 1]을 반지름 0.5 크기로 축소하고 중심을 0.5만큼 이동하여 [0, 1]로 맞춘다.
			// DirectX의 V축은 아래 방향이 양수이므로 포지션 Y축(sin)과 반대 방향으로 매핑하기 위해 부호를 반전
			vertices[i + 1].u = (-cos(angle)) * 0.5f + 0.5f;
			vertices[i + 1].v = (-sin(angle)) * 0.5f + 0.5f;

			indices[i * 3] = 0;
			indices[i * 3 + 1] = i + 1;
			indices[i * 3 + 2] = i + 2;
		}

		// 3. 맨 마지막 피자 조각의 정점 연산
		angle = (float)i / (float)vertexCount * totalRadian;
		vertices[i + 1].x = -cos(angle);
		vertices[i + 1].y = sin(angle);
		vertices[i + 1].z = 0.0f;

		// 마지막 정점 역시 동일한 UV 보정 공식을 적용
		vertices[i + 1].u = (-cos(angle)) * 0.5f + 0.5f;
		vertices[i + 1].v = (-sin(angle)) * 0.5f + 0.5f;

		indices[i * 3] = 0;
		indices[i * 3 + 1] = i + 1;
		indices[i * 3 + 2] = 1; // 1번으로 원을 닫음
	}

	UINT vertexCount = VERTEX_COUNT;
	UINT indexCount = VERTEX_COUNT * 3;

	FVertexUV vertices[VERTEX_COUNT + 1];
	UINT indices[VERTEX_COUNT * 3];

	UINT GetVertexStride()
	{
		return sizeof(FVertexUV);
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
};