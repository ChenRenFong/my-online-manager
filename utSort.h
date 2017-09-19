#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

const double epsilon = 0.000001;

TEST (Sort, sortByIncreasingPerimeter) {
	vertex ori = {0, 0};
	vertex a1 = {1, 2};
	vertex a2 = {2, 1};
	vertex b1 = {5, 10};
	vertex b2 = {30, 0};
	
	Rectangle rec1(0, 0, 2, 4);
	Rectangle rec2(0, 0, 15, 20);
	Circle cir1(0, 0, 2);
	Circle cir2(0, 0, 5);
	Triangle tri1(ori, a1, a2);
	Triangle tri2(ori, b1, b2);

	std::list<Shape *> shapes;
	shapes.push_back(&rec1);
	shapes.push_back(&rec2);
	shapes.push_back(&cir1);
	shapes.push_back(&cir2);
	shapes.push_back(&tri1);
	shapes.push_back(&tri2);
	
	double ans[6] = { tri1.perimeter(), rec1.perimeter(), cir1.perimeter(), cir2.perimeter(), tri2.perimeter(), rec2.perimeter() };
	std::vector<double> youAns;
	
	Sort::sortByIncreasingPerimeter(&shapes);

	for(Shape *oneShape : shapes ) {
		youAns.push_back(oneShape->perimeter());		
	}
	
	for(int i = 0 ; i <= 6 ;i++ ) {
		ASSERT_NEAR(ans[i], youAns[i], epsilon);
	}
}

TEST (Sort, sortByDecreasingPerimeter) {
	vertex ori = {0, 0};
	vertex a1 = {1, 2};
	vertex a2 = {2, 1};
	vertex b1 = {5, 10};
	vertex b2 = {30, 0};
	
	Rectangle rec1(0, 0, 2, 4);
	Rectangle rec2(0, 0, 15, 20);
	Circle cir1(0, 0, 2);
	Circle cir2(0, 0, 5);
	Triangle tri1(ori, a1, a2);
	Triangle tri2(ori, b1, b2);

	std::list<Shape *> shapes;
	shapes.push_back(&rec1);
	shapes.push_back(&rec2);
	shapes.push_back(&cir1);
	shapes.push_back(&cir2);
	shapes.push_back(&tri1);
	shapes.push_back(&tri2);

	double ans[6] = { rec2.perimeter(), tri2.perimeter(), cir2.perimeter(), cir1.perimeter(), rec1.perimeter(), tri1.perimeter() };
	std::vector<double> youAns;

	Sort::sortByDecreasingPerimeter(&shapes);

	for(Shape *oneShape : shapes ) {
		youAns.push_back(oneShape->perimeter());		
	}
	
	for(int i = 0 ; i <= 6 ;i++ ) {
		ASSERT_NEAR(ans[i], youAns[i], epsilon);
	}
}

TEST (Sort, sortByIncreasingArea) {
	vertex ori = {0, 0};
	vertex a1 = {1, 2};
	vertex a2 = {2, 1};
	vertex b1 = {5, 10};
	vertex b2 = {30, 0};
	
	Rectangle rec1(0, 0, 2, 4);
	Rectangle rec2(0, 0, 15, 20);
	Circle cir1(0, 0, 2);
	Circle cir2(0, 0, 5);
	Triangle tri1(ori, a1, a2);
	Triangle tri2(ori, b1, b2);

	std::list<Shape *> shapes;
	shapes.push_back(&rec1);
	shapes.push_back(&rec2);
	shapes.push_back(&cir1);
	shapes.push_back(&cir2);
	shapes.push_back(&tri1);
	shapes.push_back(&tri2);

	double ans[6] = { tri1.area(), rec1.area(), cir1.area(), cir2.area(), tri2.area(), rec2.area() };
	std::vector<double> youAns;

	Sort::sortByIncreasingArea(&shapes);

	for(Shape *oneShape : shapes ) {
		youAns.push_back(oneShape->area());		
	}
	
	for(int i = 0 ; i <= 6 ;i++ ) {
		ASSERT_NEAR(ans[i], youAns[i], epsilon);
	}
}

TEST (Sort, sortByDecreasingArea) {
	vertex ori = {0, 0};
	vertex a1 = {1, 2};
	vertex a2 = {2, 1};
	vertex b1 = {5, 10};
	vertex b2 = {30, 0};
	
	Rectangle rec1(0, 0, 2, 4);
	Rectangle rec2(0, 0, 15, 20);
	Circle cir1(0, 0, 2);
	Circle cir2(0, 0, 5);
	Triangle tri1(ori, a1, a2);
	Triangle tri2(ori, b1, b2);

	std::list<Shape *> shapes;
	shapes.push_back(&rec1);
	shapes.push_back(&rec2);
	shapes.push_back(&cir1);
	shapes.push_back(&cir2);
	shapes.push_back(&tri1);
	shapes.push_back(&tri2);
	
	double ans[6] = { rec2.area(), tri2.area(), cir2.area(), cir1.area(), rec1.area(), tri1.area() };
	std::vector<double> youAns;
	
	Sort::sortByDecreasingArea(&shapes);
	
	for(Shape *oneShape : shapes ) {
		youAns.push_back(oneShape->area());		
	}
	
	for(int i = 0 ; i <= 6 ;i++ ) {
		ASSERT_NEAR(ans[i], youAns[i], epsilon);
	}
}

TEST (Sort, sortByIncreasingCompactness) {
	vertex ori = {0, 0};
	vertex a1 = {1, 2};
	vertex a2 = {2, 1};
	vertex b1 = {5, 10};
	vertex b2 = {30, 0};
	
	Rectangle rec1(0, 0, 2, 4);
	Rectangle rec2(0, 0, 15, 20);
	Circle cir1(0, 0, 2);
	Circle cir2(0, 0, 5);
	Triangle tri1(ori, a1, a2);
	Triangle tri2(ori, b1, b2);

	std::list<Shape *> shapes;
	shapes.push_back(&rec1);
	shapes.push_back(&rec2);
	shapes.push_back(&cir1);
	shapes.push_back(&cir2);
	shapes.push_back(&tri1);
	shapes.push_back(&tri2);

	double ans[6] = { ( (4*M_PI*tri2.area()) / (tri2.perimeter()*tri2.perimeter()) ),
					  ( (4*M_PI*tri1.area()) / (tri1.perimeter()*tri1.perimeter()) ),
					  ( (4*M_PI*rec1.area()) / (rec1.perimeter()*rec1.perimeter()) ),
					  ( (4*M_PI*rec2.area()) / (rec2.perimeter()*rec2.perimeter()) ),
					  ( (4*M_PI*cir1.area()) / (cir1.perimeter()*cir1.perimeter()) ),
					  ( (4*M_PI*cir2.area()) / (cir2.perimeter()*cir2.perimeter()) )};
	std::vector<double> youAns;
	
	Sort::sortByIncreasingCompactness(&shapes);
	
	for(Shape *oneShape : shapes ) {
		youAns.push_back(((4*M_PI*oneShape->area())/(oneShape->perimeter()*oneShape->perimeter())));		
	}
	
	for(int i = 0 ; i <= 6 ;i++ ) {
		ASSERT_NEAR(ans[i], youAns[i], epsilon);
	}
}

#endif
