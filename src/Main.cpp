#include "tgaimage.h"

#include "model.h"
#include "vectors.h"

#include <iostream>
#include <vector>
#include <algorithm>


const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);

void line(int x0, int y0, int x1, int y1, TGAImage& img, const TGAColor& color)
{
	bool steep = false;
	if (std::abs(x0-x1) < std::abs(y0-y1))				// If the line is steep we transpose the image
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	if (x0 > x1)								// Make it Left to Right
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	

	// Original Eq for Slope of line or rate of increment of y over x
	// => derror = dy/dx			{multiply by 2 * dx both sides}
	// => 2 * dx * derror = 2 * dy	{Let 2 * dx * derror = derror2}
	// => derror2 = 2* dx			{slso means that derror = derror2 / (2*dx)}
	int derror2 = std::abs(dy) * 2;				
	int error2 = 0;								

	int y = y0;

	for (int x = x0; x <= x1; x++)
	{
		if (steep)
			img.set(y, x, color);
		else
			img.set(x, y, color);

		// Original part: error += derror
		// => error += derror2 / 2*dx			{as derror = derror2 / 2*dx}		
		// => 2 * dx * error += derror2			{Let 2 * dx * error = error2}
		// => error2 += derror2					{Also means error = error2 / (2 * dx)}
		error2 += derror2;

		// Original part: error > 0.5			{As error = error2 / (2 * dx)}
		// => error2 / (2 * dx) > 0.5
		// => error2 > 0.5 * 2 * dx
		// => error2 > dx						{Hence we can successfully replace error>0.5 with error2>dx} 
		if (error2 > dx)
		{
			y += y1 > y0 ? 1 : -1;

			// Original part: error -= 1
			// => error2 / (2 * dx) -= 1		{As error = error2 / (2 * dx)}
			// => error2 -= 1 * 2 * dx
			// => error2 -= 2 * dx
			error2 -= 2 * dx;
		}
	}
}

float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

bool triangle(Vec2i& v0, Vec2i& v1, Vec2i v2, TGAImage& img, const TGAColor& color)
{
	std::vector<Vec2i> sortedVerts = { v0, v1, v2 };

	std::sort(sortedVerts.begin(), sortedVerts.end(), [](const Vec2i& a, const Vec2i& b) { return a.y > b.y; });

	for (int y = sortedVerts[0].y - 1; y > sortedVerts[2].y; y--)
	{
		float n = (y - sortedVerts[2].y);
		float d = (sortedVerts[0].y - sortedVerts[2].y);
		float dy = n/d;
		float x1 = lerp(sortedVerts[0].x, sortedVerts[1].x, dy);
		float x2 = lerp(sortedVerts[0].x, sortedVerts[2].x, dy);
		line(x1, y, x2, y, img, color);
	}

	 line(v0.x, v0.y, v1.x, v1.y, img, blue);
	 line(v1.x, v1.y, v2.x, v2.y, img, blue);
	 line(v2.x, v2.y, v0.x, v0.y, img, blue);
	 
	return true;
}

int main()
{
	TGAImage image(500, 500, 3);

	Vec2i t1[3] = { Vec2i(100, 100), Vec2i(200, 150), Vec2i(150, 250) };
	Vec2i t2[3] = { Vec2i(300, 100), Vec2i(300, 300), Vec2i(500, 100) };
	Vec2i t3[3] = { Vec2i(50, 400), Vec2i(400, 450), Vec2i(250, 300) };

	triangle(t1[0], t1[1], t1[2], image, red);
	triangle(t2[0], t2[1], t2[2], image, white);
	triangle(t3[0], t3[1], t3[2], image, green);

	image.flip_vertically();
	image.write_tga_file("output/render.tga");
}