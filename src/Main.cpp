#include "tgaimage.h"

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

int main()
{
	TGAImage image(400, 400, 3);

	//line(0, 0, 150, 100, image, white);
	//line(400, 0, 250, 100, image, white);
	//line(150, 100, 250, 100, image, green);
	//line(150, 100, 10, 250, image, blue);

	// Draw the doorway
	line(150, 100, 150, 300, image, white);  // Left vertical side
	line(250, 100, 250, 300, image, white);  // Right vertical side
	line(150, 100, 250, 100, image, white);  // Top horizontal side
	line(150, 300, 250, 300, image, white);  // Bottom horizontal side (optional)

	// Draw lines for depth
	line(150, 100, 0, 0, image, white);  // Top-left of doorway to top-left of image
	line(250, 100, 400, 0, image, white);  // Top-right of doorway to top-right of image
	line(0, 200, 150, 200, image, white);
	line(250, 200, 400, 200, image, white);


	image.flip_vertically();
	image.write_tga_file("output/LineTest.tga");
}