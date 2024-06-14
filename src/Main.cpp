#include "tgaimage.h"

void RenderLine(int x0, int y0, int x1, int y1, TGAImage& img, TGAColor& color)
{
	for (float t = 0; t < 1; t+=0.01)
	{
		int x = x0 + (x1 - x0) * t;
		int y = y0 + (y1 - y0) * t;
		img.set(x, y, color);
	}
}

int main()
{
	TGAImage img(250, 250, 3);
	TGAColor color(255, 255, 255, 255);
	RenderLine(10, 10, 100, 80, img, color);
	img.write_tga_file("output/LineTest.tga");
}