#pragma once



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
