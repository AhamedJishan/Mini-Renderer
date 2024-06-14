#include "tgaimage.h"

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);

void line(int x0, int y0, int x1, int y1, TGAImage& img, const TGAColor& color)
{
	bool steep = false;
	if (abs(x1-x0) < abs(y1-y0))				// If the line is steep we transpose the image
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	if (x0 > x1)								// Make it Left to Right
	{
		std::swap(x1, x0);
		std::swap(y1, y0);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	float derror = std::abs(dy/(float)dx);		// Slope of line or rate of increment of y over x
	float error = 0;							// This will increase by derror for every 1 x

	int y = y0;

	for (int x = 0; x <= x1; x++)
	{
		if (steep)
			img.set(y, x, color);
		else
			img.set(x, y, color);

		error += derror;
		if (error>0.5)							// checking if error (y) has accumulated enough to move up or down
		{
			y += y1 > y0 ? 1 : -1;
			error -= 1.;
		}
	}
}

int main()
{
	TGAImage image(250, 250, 3);

	line(13, 20, 80, 40, image, white);
	line(20, 13, 40, 80, image, red);
	line(80, 40, 13, 20, image, red);
	line(100, 13, 10, 250, image, blue);

	image.flip_vertically();
	image.write_tga_file("output/LineTest.tga");
}