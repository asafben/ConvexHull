CC = g++
CPPFLAGS =-g -Wextra -Wvla -pthread -Wall -std=c++11

all: PointSetBinaryOperations ConvexHull
	./PointSetBinaryOperations

Point.o:  Point.cpp Point.h
	$(CC) $(CPPFLAGS) -c Point.cpp

PointSet.o: PointSet.cpp PointSet.h Point.h
	$(CC) $(CPPFLAGS) -c PointSet.cpp

ConvexHull.o: ConvexHull.cpp PointSet.h Point.h
	$(CC) $(CPPFLAGS) -c ConvexHull.cpp

ConvexHull: ConvexHull.o PointSet.o Point.o ConvexHull.cpp
	$(CC) $(CPPFLAGS) ConvexHull.o PointSet.o Point.o -o ConvexHull

# PointSetBinaryOperations.o: PointSet.cpp PointSet.h Point.cpp Point.h
# 	$(CC) $(CPPFLAGS) PointSet.cpp PointSet.h Point.cpp Point.h PointSetBinaryOperations.cpp -o PointSetBinaryOperations

PointSetBinaryOperations: PointSet.o Point.o
	$(CC) $(CPPFLAGS) PointSet.cpp Point.cpp PointSetBinaryOperations.cpp -o PointSetBinaryOperations

clean:
	rm -rf PointSetBinaryOperations ConvexHull *.o

tar:
	tar cfv ex1.tar ConvexHull.cpp Makefile Point.cpp Point.h PointSetBinaryOperations.cpp PointSet.cpp PointSet.h README

valgrindCH: clean ConvexHull
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ConvexHull

valgrindPSBO: clean PointSetBinaryOperations
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all PointSetBinaryOperations
