/**
 * Class that represents a mathematical set of points.
 */

#include "PointSet.h"
//************************************ MyVector Implementation ************************************
//Constructors
/**
 * New vector of INIT_VEC_SIZE size.
 */
MyVector::MyVector() : _array(new Point*[INIT_VEC_SIZE]), _cur_num_of_elements(EMPTY_VEC_SIZE),
					   _init_size(INIT_VEC_SIZE)
{
	std::fill_n(_array, INIT_VEC_SIZE, nullptr);
}

/**
 * New vector of requested size.
 */
MyVector::MyVector (int vecSize) : _array(new Point*[vecSize]), _cur_num_of_elements(EMPTY_VEC_SIZE)
									, _init_size(vecSize)
{
	std::fill_n(_array, vecSize, nullptr);
}

/**
 * Copy constructor.
 */
MyVector::MyVector (const MyVector &otherVec)
{
	*this = otherVec;
}

/**
 * Destructor.
 */
MyVector::~MyVector()
{
	for(int i = 0; i < _cur_num_of_elements; i++)
	{
		delete _array[i];
		_array[i] = nullptr;
	}

	delete[] _array;
	_array = nullptr;
	_cur_num_of_elements = 0;
	_init_size = 0;
}

//Methods.
/**
 * Inserts new element to the vector, at the end of the vector.
 * @Return the index in which the new element was added.
 * Negative index means an error.
 */
int MyVector::pushBack(Point *p)
{
	//No more space for new elements.
	if(_cur_num_of_elements == _init_size)
	{
		_resize(_init_size + INC_VEC_BY);
	}

	_array[_cur_num_of_elements] = p;
	_cur_num_of_elements++;

	return (_cur_num_of_elements - 1);
}

/**
 * Takes out the element, at the end of the vector.
 */
void MyVector::popBack()
{
	erase(*_array[_cur_num_of_elements - 1]);
}

/**
 * Removes an element from the the vector, at a given vector position.
 * @Return A pointer to the new point at the same location of the
 * 		   deleted point.
 * If not found returns nullptr.
 */
bool MyVector::erase(const Point &point)
{
	bool erase_success = true;
	int del_index = 0;
	for(; del_index < _cur_num_of_elements; del_index++)
	{
		if(point == *(_array[del_index]))
		{
			break;
		}
	}

	if(del_index < _cur_num_of_elements)
	{
		delete _array[del_index];
		_array[del_index] = nullptr;

		//Move all elements until the end of vector on index before
		//(Fill the "hole" of the deleted element).
		for(int i = del_index; i < (_cur_num_of_elements - 1); i++)
		{
			_array[del_index] = _array[del_index + 1];
		}
		_array[_cur_num_of_elements - 1] = nullptr;
		_cur_num_of_elements--;
	}
	else
	{
		erase_success = false;
	}
	return erase_success;
}

/**
 * Sorts The elements currently in the array.
 * begin states from which element in the array to begin the sorting,
 * and end states how many from the end backwords to stop sorting.
 */
void MyVector::vecSort(int begin, int end, bool ((*comp)(const Point*, const Point*)))
{
	std::sort(_array + begin, _array + _cur_num_of_elements - end, comp);
}

/**
 * @Return The number of points currently in the set.
 */
int MyVector::size() const
{
	return _cur_num_of_elements;
}

/**
 * Prints the set in the format: 'x1,y1' \n 'x2,y2' \n ...
 */
std::string MyVector::toString() const
{
	std::ostringstream stream;

	for(int i = 0; i < _cur_num_of_elements; i++)
	{
		stream << (*_array[i]).toString() << "\n";
	}
	return stream.str();
}
/**
 * @Return True if a point is in the vector, otherwise False.
 */
bool MyVector::find(const Point &point) const
{
	bool is_match = false;
	for(int i = 0; i < _cur_num_of_elements; i++)
	{
		if((*_array[i]) == point) //Point '==' overloaded.
		{
			is_match = true;
			break;
		}
	}
	return is_match;
}

/**
 * @Return a pointer to a point in a given index of the vector.
 */
Point* MyVector::getVecAt(int index) const
{
	if(index <= _cur_num_of_elements)
	{
		return _array[index];
	}
	else
	{
		return nullptr;
	}
}

/**
 * Sets new point object to a given index of the vector.
 */
bool MyVector::setVecAt(int index, Point* newPoint) const
{
	if(index <= _cur_num_of_elements)
	{
		_array[index] = newPoint;
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Resizes array when array is too small for adding new elements.
 */
void MyVector::_resize(int newSize)
{
	if(newSize > _init_size)
	{
		Point **new_array(new Point*[newSize]);
		for(int i = 0; i < _cur_num_of_elements; i++)
		{
			new_array[i] = new Point(*_array[i]);
		}

		//Memory free.
		for(int i = 0; i < _cur_num_of_elements; i++)
		{
			delete _array[i];
			_array[i] = nullptr;
		}

		delete[] _array;
		_array = new_array;
		//new_array = nullptr; new array dies after scope.
		_init_size = newSize;
	}
}

/**
 * Operator Overloading.
 */
MyVector& MyVector::operator=(const MyVector &otherVec)
{
	for(int i = 0; i < _cur_num_of_elements; i++)
	{
		delete _array[i];
		_array[i] = nullptr;
	}
	delete[] _array;
	_cur_num_of_elements = 0;
	_init_size = INIT_VEC_SIZE;

	_array = new Point*[otherVec._init_size];
	for(int i = 0; i < otherVec.size(); i++)
	{
		pushBack(new Point((*otherVec.getVecAt(i)).getX(), (*otherVec.getVecAt(i)).getY()));
	}

	_init_size = otherVec._init_size;
	_cur_num_of_elements = otherVec._cur_num_of_elements;
	return *this;
}

//************************************ PointSet Implementation ************************************
//Constructors
PointSet::PointSet() : pointsVec() {}
PointSet::PointSet(const PointSet &otherSet)
{
	*this = otherSet;
}

//Destructor
PointSet::~PointSet()
{
	pointsVec.~MyVector();
}

//Access methods
/**
 * @Return The number of points currently in the set.
 */
int PointSet::size() const
{
	return pointsVec.size();
}

/**
 * @Return True if a point is in the current set, otherwise False.
 */
bool PointSet::find(const Point &point) const
{
	return pointsVec.find(point);
}

/**
 * @Return a pointer to a point in a given index of the set.
 */
Point* PointSet::getSetAt(int index) const
{
	return pointsVec.getVecAt(index);
}

/**
 * @Return the point with the smallest y and than x coordinates.
 */
Point* PointSet::getMinPoint(int *index)
{
	Point *tmpPoint = nullptr;
	*index = -1;

	if(size() > 0)
	{
		//Get the first point in the set.
		tmpPoint = new Point((*getSetAt(0)).getX(), (*getSetAt(0)).getY());
		*index = 0;

		//For every other point in the set.
		//Find the lowest point, and in case of a tie, the point that is more
		//to the left.
		for(int i = 1; i < size(); i++)
		{
			int curY = (*getSetAt(i)).getY(), curX = (*getSetAt(i)).getX();
			if((curY < (*tmpPoint).getY()) ||
			   ((curY == (*tmpPoint).getY()) && (curX < (*tmpPoint).getX())))
			{
				(*tmpPoint).set(curX, curY);
				*index = i;
			}
		}
	}
	return tmpPoint;
}

//Modify methods
/**
 * Sets new point object to a given index of the set.
 */
void PointSet::setSetAt(int index, Point *newPoint)
{
	pointsVec.setVecAt(index, newPoint);
}

/**
 * Adds a new point to the current set.
 * @return True if the point was added successfully.
 */
bool PointSet::add(Point newPoint)
{
	bool success = true;
	//Point *tempPoint = new Point(newPoint);

	//If found don't add the point, then check if add succeeded.
	if(!find(newPoint) && (pointsVec.pushBack(new Point(newPoint)) < 0))
	{
		success = false;
		//delete tempPoint;
	}
	return success;
}

/**
 * Removes an existing point from the current set.
 * @return True if the point was removed successfully.
 */
bool PointSet::remove(const Point &point)
{
	bool remove_success = true;

	if(pointsVec.erase(point))
	{
		remove_success = false;
	}
	return remove_success;
}

//Other methods
/**
 * Sorts The elements currently in the set.
 * begin states from which element in the array to begin the sorting,
 * and end states how many from the end backwards to stop sorting.
 */
void  PointSet::setSort(int begin, int end, bool ((*comp)(const Point*, const Point*)))
{
	pointsVec.vecSort(begin, end, comp);
}

std::string PointSet::toString() const
{
	return pointsVec.toString();
}

//Operator Overloading
/**
 * Checks if at least one point is different between the sets.
 */
bool PointSet::operator!=(const PointSet &other_p_set) const
{
	return !(*this == other_p_set);
}

/**
 * Checks if all points are equal.
 */
bool PointSet::operator==(const PointSet &other_p_set) const
{
	int equ_counter = 0;
	bool equ_size = true;

	if(size() != other_p_set.size())
	{
		equ_size = false;
	}

	//Until reaching the end of the first set, when their size is equal.
	for(int i = 0; equ_size && i < size(); i++)
	{
		if(other_p_set.find((*getSetAt(i))))
		{
			equ_counter++;
		}
		else
		{
			break;
		}
	}
	return (equ_counter == size());
}

/**
 * Subtracts the second set from the first, and return a pointer to a new set
 * containing these eelements
 */
PointSet PointSet::operator-(const PointSet &other_p_set) const
{
	PointSet new_set;
	for(int i = 0; i < size(); i++)
	{
		if(!other_p_set.find((*getSetAt(i))))
		{
			new_set.add(Point((*getSetAt(i)).getX(), (*getSetAt(i)).getY()));
		}
	}
	return new_set;
}

/**
 * Intersection of two sets.
 */
PointSet PointSet::operator&(const PointSet &other_p_set) const
{
	PointSet new_set;
	int i;

	//Until reaching the end of the first set.
	for(i = 0; i < size(); i++)
	{
		if(other_p_set.find((*getSetAt(i))))
		{
			new_set.add(Point((*getSetAt(i)).getX(), (*getSetAt(i)).getY()));
		}
	}
	return new_set;
}

/**
 * Assigning all points from one set to another.
 */
PointSet& PointSet::operator=(const PointSet &other_p_set)
{
	(*this).pointsVec = other_p_set.pointsVec;
	return *this;
}