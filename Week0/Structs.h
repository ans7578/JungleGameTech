#pragma once



struct FVector
{
	float x, y, z;
	FVector(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}

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

// 1. Define the triangle vertices
struct FVertexSimple
{
	float x, y, z;    // Position
	float r, g, b, a; // Color

	void SetColor(float _r, float _g, float _b, float _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
	void SetColor(FVector color)
	{
		this->SetColor(color.x, color.y, color.z, 1.f);
	}
};
