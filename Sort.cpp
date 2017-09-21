#include "include/Sort.h"

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

bool doSortByIncreasingPerimeter(Shape const *a,Shape const *b){
	return a->perimeter() < b->perimeter();
}

void Sort::sortByIncreasingPerimeter(std::list<Shape *> *shapeList) {
	shapeList->sort(doSortByIncreasingPerimeter);
}

bool doSortByDecreasingPerimeter(Shape const *a,Shape const *b){
	return a->perimeter() > b->perimeter();
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList) {
	shapeList->sort(doSortByDecreasingPerimeter);
}

bool doSortByIncreasingArea(Shape const *a,Shape const *b){
	return a->area() < b->area();
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList) {
	shapeList->sort(doSortByIncreasingArea);
}

bool doSortByDecreasingArea(Shape const *a,Shape const *b){
	return a->area() > b->area();
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList) {
	shapeList->sort(doSortByDecreasingArea);
}

bool doSortByIncreasingCompactness(Shape const *a,Shape const *b){
	return ( (a->area()) / (a->perimeter()) ) < ( (b->area()) / (b->perimeter()) );
}

void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList) {
	shapeList->sort(doSortByIncreasingCompactness);
}