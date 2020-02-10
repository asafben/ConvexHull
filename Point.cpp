/**
 * Class that represents a point with (x,y) coordinates.
 */

// Point.cpp
#include "Point.h"

// Constructors
/**
 * A default constructor.
 */
Point::Point()
{
	_x = 0;
	_y = 0;
}

/**
 * Constructor of x,y cords.
 */
Point::Point(int x, int y)
{
	_x = x;
	_y = y;
}

/**
 * Copy constructor.
 */
Point::Point(const Point &otherPoint)
{
	_x = otherPoint.getX();
	_y = otherPoint.getY();
}

/**
 * Destructor.
 */
Point::~Point()
{
	_x = 0;
	_y = 0;
}

//Access methods
int Point::getX() const
{
	return _x;
}

int Point::getY() const
{
	return _y;
}

//Modify methods
void Point::set(const int x, const int y)
{
	_x = x;
	_y = y;
}

//Other methods
std::string Point::toString() const
{
	std::ostringstream stream;
	stream << _x << "," << _y;
	return stream.str();
}

/**
 * The Euclidian distance between points.
 */
int Point::calcSquaredDistance(const Point& other)
{
	return (int)(pow(_x - other._x, 2) + pow(_y - other._y, 2));
}


//Parameters Overloading
bool Point::operator==(const Point &other_point) const
{
	bool is_equ = false;
	if((_x == other_point._x) && (_y == other_point._y))
	{
		is_equ = true;
	}
	return is_equ;
}