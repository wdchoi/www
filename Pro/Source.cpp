#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include "math.h"
#include <stdbool.h>
#include <iostream>
const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i1 > i0) {
		if (j1 >= j0) {
			for (int i = i0; i <= i1; i++)
			{
				const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

				drawPixel(i, j, red, green, blue);
			}
		}
		else {
			for (int i = i0; i <= i1; i++)
			{
				const int j = j0 - (j0 - j1)*(i - i0) / (i1 - i0);

				drawPixel(i, j, red, green, blue);
			}
		}
	}
	else if (i1 < i0) {
		if (j1 >= j0) {
			for (int i = i1; i <= i0; i++)
			{
				const int j = j1 - (j1 - j0)*(i - i1) / (i0 - i1);
				drawPixel(i, j, red, green, blue);
			}
		}
		else {
			for (int i = i1; i <= i0; i++)
			{
				const int j = j1 + (j0 - j1)*(i - i1) / (i0 - i1);

				drawPixel(i, j, red, green, blue);
			}
		}
	}
	else {
		for (int j = j0; j <= j1; j++) {
			drawPixel(i0, j, 1.0f, 0.0f, 0.0f);
		}
	}
}

void drawThickerLine(const int& i0, const int& j0, const int& i1, const int& j1)
{
	drawLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);
	drawLine(i0 - 1, j0, i1, j1 + 1, 1.0f, 0.0f, 0.0f);
	drawLine(i0, j0 - 1, i1, j1 - 1, 1.0f, 0.0f, 0.0f);
}

void drawSquare(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		drawPixel(i, j0, red, green, blue);
		drawPixel(i, j1, red, green, blue);
	}
	for (int j = j0; j <= j1; j++)
	{
		drawPixel(i0, j, red, green, blue);
		drawPixel(i1, j, red, green, blue);
	}
}


bool isInsideCircle(const int i0, const int j0, const int i, const int j, const int r)
{
	const int f = (i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r;
	if (f > 50 || f < -50) return false;
	else return true;
}

void drawcircle(const int x, const int y, const int r, const float& red, const float& green, const float& blue)
{
	int x_c = x;
	int y_c = y;


	for (int a = 0; a <= 2 * r; a++)
	{
		for (int b = 0; b <= 2 * r; b++)
		{
			int f = (r - b)*(r - b) + (r - a)*(r - a) - r*r;
			if (f < 0 && -200 < f)
			{
				drawPixel(x - r + b, y - r + a, 255, 0, 0);
			}
		}
	}
}
void drawCircle(const int& i0, const int& j0, const int& r, const int& x_pos, const int& y_pos)
{
	float red, green, blue;
	double dLength = sqrt((x_pos - i0)*(x_pos - i0) + (y_pos - j0)*(y_pos - j0));
	if (dLength <= r) {
		red = 0.0f;
		green = 0.0f;
		blue = 1.0f;
	}
	else {
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}
	for (int j = j0 - r; j <= j0 + r; j++)
	{
		for (int i = i0 - r; i <= i0 + r; i++)
		{
			if (isInsideCircle(i0, j0, i, j, r) == true) {
				drawPixel(i, j, red, green, blue);
				drawPixel(i - 1, j, red, green, blue);
				drawPixel(i + 1, j, red, green, blue);
				drawPixel(i, j - 1, red, green, blue);
				drawPixel(i, j + 1, red, green, blue);

			}
		}
	}

}



void drawOnPixelBuffer()
{
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background
	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		//get mouse position
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		//draw line and circle
		drawThickerLine(50, 350, 100, 400);
		drawCircle(75, 375, 50, xpos, 480 - ypos);

		

		//draw square and circle
		drawSquare(300, 350, 350, 400, 1.0f, 0.0f, 0.0f);
		drawCircle(325, 375, 50, xpos, 480 - ypos);

		

		//draw ¡é and circle
		drawLine(575, 350, 575, 400, 1.0f, 0.0f, 0.0f);
		drawLine(575, 350, 590, 365, 1.0f, 0.0f, 0.0f);
		drawLine(575, 350, 560, 365, 1.0f, 0.0f, 0.0f);
		drawCircle(575, 375, 50, xpos, 480 - ypos);


		

		//draw A and circle
		drawThickerLine(200, 175, 175, 125);
		drawThickerLine(200, 175, 225, 125);
		drawThickerLine(187.5, 150, 212.5, 150);
		drawCircle(200, 150, 50, xpos, 480 - ypos);

		

		//draw ¡ç and circle
		drawLine(425, 150, 475, 150, 1.0f, 0.0f, 0.0f);
		drawLine(425, 150, 440, 165, 1.0f, 0.0f, 0.0f);
		drawLine(425, 150, 440, 135, 1.0f, 0.0f, 0.0f);
		drawCircle(450, 150, 50, xpos, 480 - ypos);

		//draw ¡è and circle
		drawLine(575, 125, 575, 175, 1.0f, 0.0f, 0.0f);
		drawLine(590, 160, 575, 175, 1.0f, 0.0f, 0.0f);
		drawLine(560, 160, 575, 175, 1.0f, 0.0f, 0.0f);
		drawCircle(575, 150, 50, xpos, 480 - ypos);


		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::cout << xpos << "   " << 480 - ypos << std::endl;
	}


	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}