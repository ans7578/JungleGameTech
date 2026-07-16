#pragma once
#include <iostream>

//dx
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

/*
struct FVector
{
	float x, y, z;
	FVector(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}

	void SetVector(float scala)
	{
		x = scala;
		y = scala;
		z = scala;
	}

	void operator+(FVector& fVector)
	{
		x += fVector.x;
		y += fVector.y;
		z += fVector.z;

	}

	FVector& operator+=(FVector& fVector)
	{
		*this + fVector;

		return *this;
	}
};
*/
struct FColor
{
	float r, g, b, a; // Color

	FColor(float _r = 1, float _g = 1, float _b = 1, float _a = 1) : r(_r), g(_g), b(_b), a(_a) {}

	void SetColor(float _r, float _g, float _b, float _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
	void SetColor(FColor color)
	{
		this->SetColor(color.r, color.g, color.b, color.a);
	}
};


// 1. Define the triangle vertices
struct FVertexSimple
{
	float x, y, z;    // Position
};

// 1. Define the triangle vertices
struct FVertexUV
{
	float x, y, z;    // Position
	float u,v;
};

struct FStringToHash
{

	// 64비트 FNV-1a 규격에서 정의한 초기 오프셋 값(Offset Basis)
	static constexpr uint64_t OffsetBasis = 14695981039346656037ULL;

	// 64비트 FNV-1a 규격에서 정의한 고유한 소수(Prime)
	static constexpr uint64_t Prime = 1099511628211ULL;

	static constexpr uint64_t Hash(const wchar_t* str, uint64_t hash = OffsetBasis)
	{
		//재귀를 돌면서 각 문자에 대해 해시를 계산하고, 문자열의 끝에 도달하면 최종 해시 값을 반환
		return (*str == L'\0') ? hash : Hash(str + 1, (hash ^ static_cast<uint64_t>(*str)) * Prime);
	}
};


struct FShaderProgram
{
	
};
