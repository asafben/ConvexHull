/**
 * Class that represents a mathematical set of points.
 */

#ifndef EX1_POINTSET_H
#define EX1_POINTSET_H
#include "Point.h"
#include <algorithm>

const int INIT_VEC_SIZE = 50;
const int EMPTY_VEC_SIZE = 0;
const int INC_VEC_BY = 30;

//******************************* MyVector Class *******************************
/**
 * MyVector Class
 */
class MyVector
{
public :
	//Constructors
	/**
	 * A constructor.
	 */
	MyVector();

	/**
	 * A constructor that recvies size from user.
	 */
	MyVector (int vecSize);

	/**
	 * A constructor that recives anouther vector.
	 */
	MyVector (const MyVector &otherVec);

	//Destructor
	/**
	 * A destructor.
	 */
	~MyVector();

	//Methods.
	/**
	 * Inserts new element to the vector, at the end of the vector.
	 * @Return the index in which the new element was added.
	 * Negative index means an error.
	 */
	int pushBack(Point *p);

	/**
	 * Takes out the element, at the end of the vector.
	 */
	void popBack();

	/**
	 * Removes an element from the the vector, at a given vector position.
	 * @Return A pointer to the new point at the same location of the
	 * 		   deleted point.
	 * If not found returns nullptr.
	 */
	bool erase(const Point &point);

	/**
	 * Sorts The elements currently in the array.
	 * begin states from which element in the array to begin the sorting,
	 * and end states how many from the end backwards to stop sorting.
	 */
	void vecSort(int begin, int end, bool ((*comp)(const Point*, const Point*)));

	/**
	 * @Return The number of points currently in the set.
	 */
	int size() const;

	/**
	 * Prints the set in the format: 'x1,y1' \n 'x2,y2' \n ...
	 */
	std::string toString() const;

	/**
	 * @Return True if a point is in the vector, otherwise False.
	 */
	bool find(const Point &point) const;

	/**
	 * @Return a pointer to a point in a given index of the vector.
	 */
	Point* getVecAt(int index) const;

	/**
	 * Sets new point object to a given index of the vector.
	 */
	bool setVecAt(int index, Point* newPoint) const;

	/**
	 * Operator Overloading.
	 */
	MyVector& operator=(const MyVector &otherVec);

private :
	//Variables.
	Point **_array;            //Pointer to new allocated array.
	int _cur_num_of_elements; //Grows when adding elements to the vector.
	int _init_size;           //The size in which the array was initialized.

	//Functions.
	/**
	 * Resizes array when array is too small for adding new elements.
	 */
	void _resize(int newSize);
};

//******************************* PointSet Class *******************************
/**
 * PointSet Class.
 */
class PointSet
{

public:
	/**
	 * A constructor for creating an empty PointSet of default size.
	 */
	PointSet();

	/**
	 * A copy constructor.
	 */
	PointSet(const PointSet &otherSet);

	/**
	 * A destructor.
	 */
	~PointSet();

	//Access methods
	/**
	 * @Return The number of points currently in the set.
	 */
	int size() const;

	/**
	 * @Return True if a point is in the current set, otherwise False.
	 */
	bool find(const Point &point) const;

	/**
	 * @Return the point with the smallest y and than x coordinates.
	 */
	Point* getMinPoint(int *index);

	/**
	 * @Return a pointer to a point in a given index of the set.
	 */
	Point* getSetAt(int index) const;

	//Modify methods
	/**
	 * Sets new point object to a given index of the set.
	 */
	void setSetAt(int index, Point *newPoint);

	/**
	 * Adds a new point to the current set.
	 * @return True if the point was added successfully.
	 */
	bool add(Point newPoint);

	/**
	 * Removes an existing point from the current set.
	 * @return True if the point was removed successfully.
	 */
	bool remove(const Point &point);

	//Other methods
	/**
	 * Sorts The elements currently in the set.
	 * begin states from which element in the array to begin the sorting,
	 * and end states how many from the end backwards to stop sorting.
	 */
	void setSort(int begin, int end, bool ((*comp)(const Point*, const Point*)));

	/**
	 * Prints the point in the format: (x , y).
	 */
	std::string toString() const;


	//Operator Overloading.
	/**
	 * Checks if at least one point is different between the sets.
	 */
	bool operator!=(const PointSet &other_p_set) const;
	/**
	 * Checks if all points are equal.
	 */
	bool operator==(const PointSet &other_p_set) const;

	/**
	 * Subtracts the second set from the first, and return a pointer to a new set
	 * containing these elements
	 */
	PointSet operator-(const PointSet &other_p_set) const;

	/**
	 * Intersection of two sets.
	 */
	PointSet operator&(const PointSet &other_p_set) const;

	/**
	 * Assigning all points from one set to another.
	 */
	PointSet& operator=(const PointSet &other_p_set);

private:
	MyVector pointsVec;
};

#endif //EX1_POINTSET_H
