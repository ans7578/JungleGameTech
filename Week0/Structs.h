#pragma once


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
