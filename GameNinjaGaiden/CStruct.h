#pragma once


// Struct Rect thay the RECT do su dung float
struct RectEx
{
	float left;
	float right;
	float top;
	float bottom;

	RectEx(float t, float l, float b, float r)
	{
		top = t;
		left = l;
		right = r;
		bottom = b;
	}

	RectEx(RECT rect)
	{
		top = (float)rect.top;
		left = (float)rect.left;
		right = (float)rect.right;
		bottom = (float)rect.bottom;
	}

	RectEx()
	{
		left = 0.0f;
		right = 0.0f;
		top = 0.0f;
		bottom = 0.0f;
	}

	RECT GetRECT()
	{
		RECT rect;
		rect.left = (LONG)left;
		rect.right = (LONG)right;
		rect.top = (LONG)top;
		rect.bottom = (LONG)bottom;
		return rect;
	}
};