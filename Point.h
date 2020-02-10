/**
 * Class that represents a point with (x,y) coordinates.
 */

// Point.h
#ifndef POINT_H
#define POINT_H
#include <string>
#include <iostream>
#include <math.h>
#include <sstream>
/**
 *  A point class. 
 *  This class represents a point with (x,y) coordinates.
 */
class Point
{
public:
	/**
     * A constructor.
     * A more elaborate description of the constructor.
     * @see initDetails()
     */
	Point();

	/**
	 * A constructor.
	 * A more elaborate description of the constructor.
	 * @see initDetails()
	 */
	Point(int x, int y);

	/**
	 * A constructor.
	 * A more elaborate description of the constructor.
	 * @see initDetails()
	 */
	Point(const Point &otherPoint);

	/**
	 * A destructor.
	 * A more elaborate description of the destructor.
	 * @see initDetails()
	 */
	~Point();

	/**
	 * Access method for the x value.
	 * @return The x value
	 */
	int getX() const;

	/**
	 * Access method for the y value.
	 * @return The y value
	 */
	int getY() const;

	/**
     * Prints the point in the format: 'x,y'.
     */
	std::string toString() const;

	/**
	 * Sets new (x , y).
	 */
	void set(const int x, const int y);

	/**
     * Calculates the Euclidean distance between two points.
     * @param other another point.
     * @return the Euclidean distance between two points.
     */
	int calcSquaredDistance(const Point& other);

	/**
	 * Parameters Overloading.
	 */
	bool operator==(const Point &other_point) const;

private:
	int _x; //X coordinate.
	int _y; //Y coordinate.
};

#endif