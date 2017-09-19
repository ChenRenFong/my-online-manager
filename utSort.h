#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

const double epsilon = 0.000001;

TEST (Sort, sortByIncreasingPerimeter) {
	Circle cir1(0, 0, 2);
	Circle cir2(0, 0, 4);
	Circle cir3(0, 0, 6);

	std::list<Shape *> shapes;
	shapes.push_back(&cir1);
	shapes.push_back(&cir2);
	shapes.push_back(&cir3);

	double ans[3] = { 2*2*M_PI, 4*2*M_PI, 6*2*M_PI };
	std::vector<double> youAns;
	
	Sort::sortByIncreasingPerimeter(&shapes);

	for(Shape *oneShape : shapes ) {
		youAns.push_back(oneShape->perimeter());		
	}
	
	ASSERT_NEAR(ans[0], youAns[0], epsilon);
	ASSERT_NEAR(ans[1], youAns[1], epsilon);
	ASSERT_NEAR(ans[2], youAns[2], epsilon);
}

TEST (Sort, sortByDecreasingPerimeter) {
	Circle cir1(0, 0, 2);
	Circle cir2(0, 0, 4);
	Circle cir3(0, 0, 6);

	std::list<Shape *> shapes;
	shapes.push_back(&cir1);
	shapes.push_back(&cir2);
	shapes.push_back(&cir3);
	
	double ans[3] = { 6*2*M_PI, 4*2*M_PI, 2*2*M_PI };
	std::vector<double> youAns;

	Sort::sortByDecreasingPerimeter(&shapes);

	for(Shape *oneShape : shapes ) {
		youAns.push_back(oneShape->perimeter());		
	}
	
	ASSERT_NEAR(ans[0], youAns[0], epsilon);
	ASSERT_NEAR(ans[1], youAns[1], epsilon);
	ASSERT_NEAR(ans[2], youAns[2], epsilon);
}

TEST (Sort, sortByIncreasingArea) {
	Circle cir1(0, 0, 2);
	Circle cir2(0, 0, 4);
	Circle cir3(0, 0, 6);

	std::list<Shape *> shapes;
	shapes.push_back(&cir1);
	shapes.push_back(&cir2);
	shapes.push_back(&cir3);
	
	double ans[3] = { cir1.area(), cir2.area(), cir3.area() };
	std::vector<double> youAns;

	Sort::sortByIncreasingArea(&shapes);

	for(Shape *oneShape : shapes ) {
		youAns.push_back(oneShape->area());		
	}
	
	ASSERT_NEAR(ans[0], youAns[0], epsilon);
	ASSERT_NEAR(ans[1], youAns[1], epsilon);
	ASSERT_NEAR(ans[2], youAns[2], epsilon);
}

TEST (Sort, sortByDecreasingArea) {
	Circle cir1(0, 0, 2);
	Circle cir2(0, 0, 4);
	Circle cir3(0, 0, 6);

	std::list<Shape *> shapes;
	shapes.push_back(&cir1);
	shapes.push_back(&cir2);
	shapes.push_back(&cir3);
	
	double ans[3] = { cir3.area(), cir2.area(), cir1.area() };
	std::vector<double> youAns;
	
	Sort::sortByDecreasingArea(&shapes);
	
	for(Shape *oneShape : shapes ) {
		youAns.push_back(oneShape->area());		
	}
	
	ASSERT_NEAR(ans[0], youAns[0], epsilon);
	ASSERT_NEAR(ans[1], youAns[1], epsilon);
	ASSERT_NEAR(ans[2], youAns[2], epsilon);
}

TEST (Sort, sortByIncreasingCompactness) {
	Circle cir1(0, 0, 2);
	Circle cir2(0, 0, 4);
	Circle cir3(0, 0, 6);

	double ans[3] = { ((4*M_PI*cir3.area())/(cir3.perimeter()*cir3.perimeter())),
					  ((4*M_PI*cir2.area())/(cir2.perimeter()*cir2.perimeter())),
					  ((4*M_PI*cir1.area())/(cir1.perimeter()*cir1.perimeter())) };
	std::vector<double> youAns;
	
	std::list<Shape *> shapes;
	shapes.push_back(&cir1);
	shapes.push_back(&cir2);
	shapes.push_back(&cir3);
	
	for(Shape *oneShape : shapes ) {
		youAns.push_back(((4*M_PI*oneShape->area())/(oneShape->perimeter()*oneShape->perimeter())));		
	}
	
	ASSERT_NEAR(ans[0], youAns[0], epsilon);
	ASSERT_NEAR(ans[1], youAns[1], epsilon);
	ASSERT_NEAR(ans[2], youAns[2], epsilon);

	Sort::sortByIncreasingCompactness(&shapes);
}

#endif
