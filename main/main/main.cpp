#include "pch.h"
#include <iomanip>
#include "Shapes.h"
#include <vector>

void init(unsigned& len, unsigned& hei, double& angle);
int treeType();
void rotate(Coordinates rect[4], double angle);
void rotate(std::vector<std::unique_ptr<Shape>>& trees, double angle);

void packCircles(Rectangle garden, std::vector<std::unique_ptr<Shape>>& trees);
void packEllipses(Rectangle garden);
void packTriangles(Rectangle garden);
void packHexagons(Rectangle garden);

void print(std::vector<std::unique_ptr<Shape>>& trees, double gardenArea);

int main()
{
	unsigned length = 0;
	unsigned height = 0;
	double angle = 0;
	init(length, height, angle);

	std::cout << "Creating garden...\n";
	Rectangle garden(length, height);
	//left bottom, right bottom, right upper, left upper
	Coordinates rectCoord[4] = { Coordinates(0, 0), Coordinates(length, 0), Coordinates(length, height), Coordinates(0, height) };
	if (angle != 0)
	{
		rotate(rectCoord, angle);
	} 

	std::vector<std::unique_ptr<Shape>> trees;
	switch (treeType())
	{
	case 1: packCircles(garden, trees);
		break;
	case 2: //Ellipse func
		break;
	case 3: //Triangle func
		break;
	case 4: //Hexagon func
		break;
	default: std::cout << "Incorrect input, no shape chosen. Terminating...";
		exit(1);
	}	

	rotate(trees, angle);
	print(trees, garden.getArea());
}

void init(unsigned& len, unsigned& hei, double& angle)
{
	std::cout << "Hello! Choose the length and the height of the garden:\n";
	std::cin >> len;
	std::cin >> hei;
	std::cout << "Now choose the angle of rotation:\n";
	std::cin >> angle;

	while (angle >= 360)
	{
		angle -= 360;
	}
	while (angle <= -360)
	{
		angle += 360;
	}
}
int treeType()
{
	std::cout << R"(
Select the shape of the trees.
1.Circle
2.Ellipse
3.Triangle
4.Hexagon
)";
	int choice = 0;
	std::cin >> choice;
	return choice;
}
void rotate(Coordinates rect[4], double angle)
{
	std::cout << "Rotating garden by: " << angle << " degrees.\nCurrent coordinates:\n";
	for (int i = 0; i < 4; i++)
	{
		std::cout << "(" << rect[i].x << "," << rect[i].y << ")" << std::right << std::setw(5);
	}
	//first point coord (0,0) => doesnt move after rotation
	//rotate counter clockwise
	//try floor/ceil
	if (angle > 0)
	{
		for (int i = 1; i < 4; i++)
		{
			double xPrime = rect[i].x;
			double yPrime = rect[i].y;

			rect[i].x = xPrime * cos(angle * PI / 180) - yPrime * sin(angle * PI / 180);
			rect[i].y = xPrime * sin(angle * PI / 180) + yPrime * cos(angle * PI / 180);
		}
	}
	else
	{
		angle = 360 + angle;
		for (int i = 1; i < 4; i++)
		{
			double xPrime = rect[i].x;
			double yPrime = rect[i].y;

			rect[i].x = xPrime * cos(angle * PI / 180) - yPrime * sin(angle * PI / 180);
			rect[i].y = xPrime * sin(angle * PI / 180) + yPrime * cos(angle * PI / 180);
		}
	}


	std::cout << "\nNew coordinates:\n";
	for (int i = 0; i < 4; i++)
	{
		std::cout << std::setprecision(2) << "(" << rect[i].x << "," << rect[i].y << ")" << std::right << std::setw(5);
	}
}

//rectangular packing
void packCircles(Rectangle garden, std::vector<std::unique_ptr<Shape>>& trees)
{
	unsigned radius = 0;
	std::cout << "Select radius:\n";
	std::cin >> radius;
	int xAxis = garden.getLength();
	int yAxis = garden.getHeight();

	for (int x = 0; x + radius * 2 <= xAxis;)
	{
		for (int y = 0; y + radius * 2 <= yAxis;)
		{
			trees.push_back(std::make_unique<Circle>(radius, radius + x, radius + y));
			y += (radius * 2);
		}
		x += (radius * 2);
	}
}

void packEllipses(Rectangle garden)
{

}
void packTriangles(Rectangle garden)
{

}


void rotate(std::vector<std::unique_ptr<Shape>>& trees, double angle)
{
	if (angle > 0)
	{
		int size = trees.size();
		for (int i = 0; i < size; i++)
		{
			Coordinates centerPrime = trees[i]->getCenterCoordinates();
			double newXcoord = centerPrime.x * cos(angle * PI / 180) - centerPrime.y * sin(angle * PI / 180);
			double newYcoord = centerPrime.x * sin(angle * PI / 180) + centerPrime.y * cos(angle * PI / 180);

			trees[i]->setCenter(newXcoord, newYcoord);
		}
	}
	else
	{
		angle = 360 + angle;
		int size = trees.size();
		for (int i = 0; i < size; i++)
		{
			Coordinates centerPrime = trees[i]->getCenterCoordinates();
			double newXcoord = centerPrime.x * cos(angle * PI / 180) - centerPrime.y * sin(angle * PI / 180);
			double newYcoord = centerPrime.x * sin(angle * PI / 180) + centerPrime.y * cos(angle * PI / 180);

			trees[i]->setCenter(newXcoord, newYcoord);
		}
	}
}
void print(std::vector<std::unique_ptr<Shape>>& trees, double gardenArea)
{
	std::cout << "Number of trees planted: " << Shape::getTreeCount() << std::endl;
	std::cout << "Coordinates of their centers:\n";
	Coordinates printer(INT_MIN, INT_MIN);
	double totalTreeArea = 0;
	for (auto& a : trees)
	{
		printer = a->getCenterCoordinates();
		std::cout << "(" << printer.x << "," << printer.y << ")\n";
		totalTreeArea += a->getArea();
	}
	// x = (totalTreeArea / gardenArea) * 100
	totalTreeArea /= gardenArea;
	std::cout << "The trees take up " << totalTreeArea * 100 << "% of the garden\n";
}

/*
Нека имаме градина с правоъгълна форма, в която искаме да засадим храстовидни растения така, че заемата от короните им площ 
да е въжможно най-голяма. Короните на храстовидните растения могат да имат кръгла, овална, триъгълна и шестоъгълна форма.

Да се напише програма, която при зададени входни данни, описани по-долу, извежда броя на растенията, координатите на геометричния 
център на короните на растенията и общата площ на короните, изразена в проценти спрямо цялата площ на градината.

Входни данни:

Размери на правоъгълната градина и ъгъл на завъртане в 2D (начало на координатната система – долен ляв ъгъл на правоъгълника);
Вид на растенията (всички растения в градината са от един вид);
Размер на растението според формата на короната (кръг, овал, правилен шестоъгълник, равностранен триъгълник).
*/