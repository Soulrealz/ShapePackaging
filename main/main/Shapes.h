#pragma once
#include <iostream>
#include "Pair.h"

#define PI 3.1415926
//1main shape - rectangle
//4sub shapes - ellipse, circle, hexagon, triangle

class Shape
{
public:
	Shape(unsigned _side, double x, double y) : side(_side), center(x, y) { treeCount++; }
	virtual ~Shape() {}

	virtual double getArea() const = 0;

	void setCenter(double x, double y)
	{
		center.x = x;
		center.y = y;	
	}
	Coordinates getCenterCoordinates() const
	{
		return center;
	}

	static int getTreeCount()
	{
		return treeCount;
	}
protected:
	unsigned side;
	Coordinates center;
	static int treeCount;

	unsigned getSide() const
	{
		return side;
	}
};
//setting to -1 because creating the initial rectangle will also increase this counter
int Shape::treeCount = -1;

class Rectangle : public Shape
{
public:
	Rectangle(unsigned _side, unsigned _height) : Shape(_side, (_side / 2.0), (_height / 2.0)), height(_height) {}

	double getArea() const override
	{
		return side * height;
	}

	unsigned getLength() const
	{
		return getSide();
	}
	unsigned getHeight() const
	{
		return height;
	}
private:
	unsigned height;
};

class Triangle : public Shape
{
public:
	Triangle(unsigned _side, double x, double y) : Shape(_side, x, y) {}

	double getArea() const override
	{
		double p = (side * 3.0) / 2.0;
		//using Heron
		return sqrt(p*((p - side) * 3));
	}
private:
};

class Hexagon : public Shape
{
public:
	Hexagon(unsigned _side, double x, double y) : Shape(_side, x, y) {}

	double getArea() const override
	{
		return (3.0 * sqrt(3.0) * pow(side, 2.0)) / 2.0;
	}
private:
};

class Circle : public Shape
{
public:
	Circle(unsigned radius, double x, double y) : Shape(radius, x, y) {}

	double getArea() const override
	{
		return PI * pow(side, 2);
	}

	unsigned getRadius() const
	{
		return side;
	}
private:
};

class Ellipse : public Shape
{
public:
	Ellipse(unsigned xRad, unsigned _yRad, double x, double y) : Shape(xRad, x, y), yRad(_yRad) {}

	double getArea() const override
	{
		return PI * side * yRad;
	}
private:
	unsigned yRad;
};