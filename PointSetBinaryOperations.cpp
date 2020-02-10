/**
 * Demonstration of PointSet class operator overloading.
 */

#include <iostream>
#include "PointSet.h"

using namespace std;

int main()
{
	/**
	 * Variables.
	 */
	PointSet tst_p_set1 = PointSet();
	PointSet tst_p_set2 = PointSet();
	PointSet tst_p_set3 = PointSet();

	/**
	 * Add points manually.
	 */
	tst_p_set1.add(Point(1, 1));
	tst_p_set1.add(Point(2, 2));
	tst_p_set1.add(Point(3, 3));
	tst_p_set2.add(Point(1, 1));
	tst_p_set2.add(Point(2, 2));
	tst_p_set2.add(Point(3, 3));
	tst_p_set3.add(Point(3, 3));
	tst_p_set3.add(Point(5, 5));

	/**
	 * Demonstration.
	 */
	cout << "Set3:\n" << tst_p_set3.toString() << "\nSet2:\n" << tst_p_set2.toString() << endl;
	if (tst_p_set3 != tst_p_set2)
	{
		cout << "SETS ARE NOT EQUAL\n" << endl;
	}

	cout << "Set1:\n" << tst_p_set1.toString() << "\nSet2:\n" << tst_p_set2.toString() << endl;
	if (tst_p_set1 == tst_p_set2)
	{
		cout << "SETS ARE EQUAL\n" << endl;
	}

	tst_p_set2.add(Point(4, 4));

	cout << "Set2:\n" << tst_p_set2.toString() << "\nSet1:\n" << tst_p_set1.toString() << endl;
	cout << "Less:\n" << (tst_p_set2 - tst_p_set1).toString() << endl;

	cout << "Set1:\n" << tst_p_set1.toString() << "\nSet3:\n" << tst_p_set3.toString() << endl;
	cout << "&:\n" << (tst_p_set1 & tst_p_set3).toString() << endl;

	cout << "'='" << endl;
	cout << "Before:\nSet3:\n" << tst_p_set3.toString() << "Set2:\n" << tst_p_set2.toString() <<
	endl;
	tst_p_set3 = tst_p_set2;
	cout << "After:\nSet3:\n" << tst_p_set3.toString() << "Set2:\n" << tst_p_set2.toString() <<
	endl;

	return 0;
}