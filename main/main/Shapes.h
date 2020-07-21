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
	virtual void setCenter(double x, double y) = 0;

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
//setting to -1 because creating a rectangle would also increase this counter
int Shape::treeCount = -1;

class Rectangle : public Shape
{
public:
	Rectangle(unsigned _side, unsigned _height) : Shape(_side, (_side / 2.0), (_height / 2.0)), height(_height) {}

	double getArea() const override
	{
		return side * height;
	}
	void setCenter(double x, double y) override
	{
		center.x = x;
		center.y = y;
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
	//C = [(x1 + x2 + x3)/ 3, (y1 + y2 + y3)/ 3)
	Triangle(unsigned _side, double x, double y) : Shape(_side, x, y) {}

	double getArea() const override
	{
		double p = (side * 3.0) / 2.0;
		//using Heron
		return sqrt(p*((p - side) * 3));
	}
	void setCenter(double x, double y) override
	{

	}
private:
};

class Hexagon : public Shape
{
public:
	Hexagon(unsigned _side) : Shape(_side, 1, 1) {}

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
	void setCenter(double x, double y) override
	{
		center.x = x;
		center.y = y;
	}

	unsigned getRadius() const
	{
		return getSide();
	}
private:
};

class Ellipse : public Shape
{
public:
	Ellipse(unsigned bigRadius, unsigned _smallRadius) : Shape(bigRadius, 1, 1), smallRadius(_smallRadius) {}

	double getArea() const override
	{
		return PI * side * smallRadius;
	}
	void setCenter(double x, double y) override
	{

	}
private:
	unsigned smallRadius;
};