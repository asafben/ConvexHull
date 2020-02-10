/**
 * Convex Hull algorithm logic.
 */

//Includes.
#include <iostream>
#include <regex>
#include "PointSet.h"

//Globals.
Point *p0;

//Functions.
/**
 * Findes the direction of the three points.
 * @ Return:  0 If all three points on the same line,
 *            1 ClockWise,
 *           -1 CounterClockWise.
 */
int tripletDirection(const Point *p0, const Point *p1, const Point *p2)
{
	int retVal = 0;
	int result = ((*p1).getY() - (*p0).getY()) * ((*p2).getX() - (*p1).getX());
	    result -= ((*p1).getX() - (*p0).getX()) * ((*p2).getY() - (*p1).getY());

	if(result > 0)
	{
		retVal = 1;
	}
	else if(0 > result)
	{
		retVal = -1;
	}
	return retVal;
}

/**
 * Comparator by X cord from small to big, and then Y cord from small to
 * big.
 * Used for printing ConvexHull results.
 */
bool printCompare(const Point *point1, const Point *point2)
{
	//No identical points in the set.
	return ((*point1).getX() < (*point2).getX()) || (((*point1).getX() == (*point2).getX()) &&
			                                         ((*point1).getY() < (*point2).getY()));
}

/**
 * Comparator by X cord from small to big, and then Y cord from small to
 * big.
 * Used for printing ConvexHull results.
 */
bool angleDistanceCompare(const Point *point1, const Point *point2)
{
	int retVal;

	//P0 found in main and is global.
	int direction = tripletDirection(p0, point1, point2);

	//Pre calculate square distance between p0 and the other two points.
	int p0p1Dist = p0 -> calcSquaredDistance(*point1);
	int p0p2Dist = p0 -> calcSquaredDistance(*point2);

	//Compare shortest distance.
	if ((direction == 0) && (p0p2Dist >= p0p1Dist))
	{
		retVal = -1;
	}
	else if((direction == 0) && (p0p2Dist < p0p1Dist))
	{
		retVal = 1;
	}
	else
	{
		retVal = direction;
	}
	return retVal == -1; //False if: retVal == 1, True if: retVal == -1.
}

/**
 * Algorithm description as requested in the exercise:
 * (a) How does the algorithm works?
 *     Finds the point with the smallest y and then x coordinates, we'll call it p0.
 *     Swaps p0 and the first point in the set.
 *     If there are only 2 or less points, print them as is, else preform the algorithm.
 *     Sorts all elements except p0 (that is in the first place), by its angle relative to p0.
 *     Removes all points in-between points on the same line.
 *     Push p0 and the first two of the sorted points to a stack.
 *     Finds the direction of the next point relative to the last two points entered to the stack.
 *     If the direction isn't CounterClockWise discards the top element of the stack.
 *     In any case, pushed the next point to top of the stack.
 *
 * (b) The algorithm complexity:
 *     I won't elaborate about all of the O(1) operations.
 * 	   Entering all points to the data-structure:                O(n).
 *     Removing all points in-between points on the same line:   O(n).
 *     Finds the direction of the next point relative to the-
 *     -last two points entered to the stack:                    O(n).
 *     Sorting for the algorithm and for printing:            O(nlogn).
 *     In total:                                              O(nlogn).
 *
 * (c) Algorithm source:
 *     'Wikipedia' and 'geeksforgeeks'.
 */
int main()
{
	//Data types.
	PointSet conHullSet;
	MyVector tempVector;
	int p0Index = 0;

	//Two capturing groups for numbers as a string (x,y), positive or negative.
	std::regex cordsRegex("(-?\\d+)\\s*,\\s*(-?\\d+)");
	std::string nextPointCords;
	std::smatch match;

	//Reads string until the next separator (space, newline, tab).
	while(std::cin >> nextPointCords)   //Ends with reading EOF.
    {
		if(regex_match(nextPointCords, match, cordsRegex))
		{
			conHullSet.add(Point(std::stoi(match[1].str().c_str()), \
									 std::stoi(match[2].str().c_str())));
		}
		else
		{
			exit(1); //Reaching a bad format parameter.
		}
    }

	//Finds the point with the smallest y and then x coordinates.
	p0 = conHullSet.getMinPoint(&p0Index);

	//Swap p0 and the first point in the set.
	Point *tmpPoint = conHullSet.getSetAt(0);

	if(tmpPoint != nullptr)
	{
		conHullSet.setSetAt(0, p0);
		conHullSet.setSetAt(p0Index, tmpPoint);

		//In a new Stack, save p0.
		tempVector.pushBack(p0);
	}

	//If there are only 2 or less points, print them as is.
	//Else preform the algorithm.
	int setSize = conHullSet.size();
	if(setSize == 2) //P0 && P1
	{
		tempVector.pushBack(conHullSet.getSetAt(1));
	}

	//Preform the algorithm if (more points than P0 or None).
	else if(setSize > 1)
	{
		int conHullSetNewSize = 1;

		//Sort all elements except p0.
		conHullSet.setSort(1, 0, angleDistanceCompare);

		//Remove all points in-between points on the same line.
		for(int i = 1; i < setSize; i++)
		{
			while((i < (setSize - 1)) &&
				  (tripletDirection(p0, conHullSet.getSetAt(i), conHullSet.getSetAt(i + 1)) == 0))
			{
				i++;
			}

			if(i != conHullSetNewSize) //No place changing for the same index.
			{
				delete conHullSet.getSetAt(conHullSetNewSize); //Free object we are going to run over.
				conHullSet.setSetAt(conHullSetNewSize, conHullSet.getSetAt(i)); //Replace
				//delete conHullSet.getSetAt(i); //Delete duplicate.
				conHullSet.setSetAt(i, nullptr);
			}
			conHullSetNewSize++;
		}

		//If result is less or equal than 3 elements, convex hull isn't
		//possible, yet we'll return the resulting points (school solution).
		if(conHullSetNewSize <= 3)
		{
			for(int i = 1; i < conHullSetNewSize; i++)
			{
				tempVector.pushBack(new Point(*conHullSet.getSetAt(i)));
			}
		}
		else
		{
			//Push the next two points after sorting.
			tempVector.pushBack(conHullSet.getSetAt(1));
			tempVector.pushBack(conHullSet.getSetAt(2));

			//Run the algorithm on the remaining points.
			for(int i = 3; i < conHullSetNewSize; i++)
			{
				while(tripletDirection(
					  //One before the last element in vector.
					  tempVector.getVecAt(tempVector.size() - 2),
					  //Last element in vector.
					  tempVector.getVecAt(tempVector.size() - 1),
					  //The next point from the sorted set.
					  conHullSet.getSetAt(i)) != -1) //==1
				{
					tempVector.popBack();
				}
				tempVector.pushBack(conHullSet.getSetAt(i));
			}
		}
	}

	//Print the results.
	tempVector.vecSort(0, 0, printCompare);
	std::cout << "result\n" << tempVector.toString() << std::flush;

	//Memory Free.
	//Constructors will be called.
    return 0;
}