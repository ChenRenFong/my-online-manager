#include "include/Sort.h"

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

bool _sortByIncreasingPerimeter(Shape const *a,Shape const *b){
	return a->perimeter() < b->perimeter();
}

void Sort::sortByIncreasingPerimeter(std::list<Shape *> *shapeList) {
	shapeList->sort(_sortByIncreasingPerimeter);
}

bool _sortByDecreasingPerimeter(Shape const *a,Shape const *b){
	return a->perimeter() > b->perimeter();
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList) {
	shapeList->sort(_sortByDecreasingPerimeter);
}

bool _sortByIncreasingArea(Shape const *a,Shape const *b){
	return a->area() < b->area();
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList) {
	shapeList->sort(_sortByIncreasingArea);
}

bool _sortByDecreasingArea(Shape const *a,Shape const *b){
	return a->area() > b->area();
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList) {
	shapeList->sort(_sortByDecreasingArea);
}

bool _sortByIncreasingCompactness(Shape const *a,Shape const *b){
	return ((4*M_PI*a->area())/(a->perimeter()*a->perimeter())) < ((4*M_PI*b->area())/(b->perimeter()*b->perimeter()));
}

void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList) {
	shapeList->sort(_sortByIncreasingCompactness);
}