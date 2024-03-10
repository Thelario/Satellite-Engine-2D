#pragma once

struct Color
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;

	Color(unsigned int r = 255, unsigned int g = 255, unsigned int b = 255, unsigned int a = 255)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};