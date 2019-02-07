//
//  main.cpp
//  assignment3
//
//  Created by Erik Poole on 1/15/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <cmath>

bool areEquivalent(double double1, double double2) {
    return abs(double1 - double2) < .0001;
}

bool areEquivalent(double double1, double double2, double double3) {
    return abs(double1 - double2) < .0001 && abs(double2 - double3) < .0001;
}

//****************************************************************************************************
//****************************************************************************************************


class Point{
private:
    int x;
    int y;
    
public:
    Point()
    :x{0}, y{0} {}
    
    Point(const int& xInput, const int& yInput)
    :x{xInput}, y{yInput} {}
    
    int getX() const {return x;}
    int getY() const {return y;}
    
    bool equals(Point inputPoint) {
        if (x == inputPoint.getX() && y == inputPoint.getY()) {
                return true;
            }
        return false;
    }
};


class Line{
private:
    int xOffset;
    int yOffset;
    Point pointArr[2];
    
public:
    Line()
    :xOffset{0}, yOffset{0} {
        pointArr[0] = {Point()};
        pointArr[1] = {Point()};
    }
    
    Line(const Point& point1, const Point& point2) {
        pointArr[0] = point1;
        pointArr[1] = point2;
        xOffset = abs(point1.getX() - point2.getX());
        yOffset = abs(point1.getY() - point2.getY());
        
    }
    
    double getLength() {
        return sqrt((double) xOffset*xOffset + (double) yOffset*yOffset);
    }
    
    double getSlope() {
        //handles 0 slope without division
        if (yOffset == 0) {
            return 0;
        }
        //handles infinite slope without division
        if(xOffset == 0) {
            return INT_MAX;
        }
        
        double slope = (double) yOffset / (double) xOffset;
        if (pointArr[0].getX() > pointArr[1].getX() && pointArr[0].getY() < pointArr[1].getY()) {
            slope *= -1;
        }
        if (pointArr[0].getX() < pointArr[1].getX() && pointArr[0].getY() > pointArr[1].getY()) {
            slope *= -1;
        }
        return slope;
    }
};

//****************************************************************************************************
//****************************************************************************************************


//adapted from Will Marrigna and https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
// Determine the orientation of three given points
int setOrientation(Point a, Point b,
                   Point c) {
    
    int val = (b.getY() - a.getY()) * (c.getX() - b.getX()) -
    (b.getX() - a.getX()) * (c.getY() - b.getY());
    
    if (val == 0)
        return 0; // points are colinear
    
    return (val > 0) ? 1 : 2; // 1 = clockwise | 2 = counter-clockwise
}

//adapted from Will Marrigna and https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
// Determines if point 'x' is on the line a-b
bool onSegment(Point a, Point x,
               Point b) {
    
    bool xSegCheck = x.getX() <= std::max(a.getX(), b.getX()) &&
    x.getX() >= std::min(a.getX(), b.getX());
    bool ySegCheck = x.getY() <= std::max(a.getY(), b.getY()) &&
    x.getY() >= std::min(a.getY(), b.getY());
    
    if (xSegCheck && ySegCheck) {
        return true;
    }
    return false;
}



//****************************************************************************************************
//****************************************************************************************************



class Shape{
private:
    Point pointArr[4];
    Line sideArr[4];
    Line diagonalArr[2];
    
public:
    Shape(const Point& inputPoint1, const Point& inputPoint2, const Point& inputPoint3) {
        //points
        pointArr[0] = Point(0, 0);
        pointArr[1] = Point(inputPoint1);
        pointArr[2] = Point(inputPoint2);
        pointArr[3] = Point(inputPoint3);
        
        //sides
        sideArr[0] = Line(pointArr[0], pointArr[1]);
        sideArr[1] = Line(pointArr[1], pointArr[2]);
        sideArr[2] = Line(pointArr[2], pointArr[3]);
        sideArr[3] = Line(pointArr[3], pointArr[0]);
        
        //diagonals
        diagonalArr[0] = Line(pointArr[0], pointArr[2]);
        diagonalArr[1] = Line(pointArr[1], pointArr[3]);
        
    }
    
    Line getSide(const int& sideNumber) const {return sideArr[sideNumber];}
    Line getDiagonal(int diagonalNumber) const {return diagonalArr[diagonalNumber];}
    
    
    //adapted from Will Marrigna and https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
    // Determines based on orientation if lines intersect
    bool doIntersect(Point a, Point b,
                     Point c, Point d) {
        
        int o1 = setOrientation(a, b, c);
        int o2 = setOrientation(a, b, d);
        int o3 = setOrientation(c, d, a);
        int o4 = setOrientation(c, d, b);
        
        if (o1 != o2 && o3 != o4)
            return true;
        
        // c-a-d are collinear and a lies on the line c-d
        if (o3 == 0 && onSegment(c, a, d))
            return true;
        
        // c-b-d are collinear and b lies on the line c-d
        if (o4 == 0 && onSegment(c, b, d))
            return true;
        
        // a-b-c are collinear and c lies on the line a-b
        if (o1 == 0 && onSegment(a, c, b))
            return true;
        
        // a-d-b are collinear and d lies on the line a-b
        if (o2 == 0 && onSegment(a, d, b))
            return true;
        
        return false;
    }
    
    //adapted from Will Marrigna and https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
    // checks for orientation of 3 points at a time and errors if lines are
    // collinear or cross each other
    void lineIntersectCheck() {
        bool case1 = doIntersect(pointArr[0], pointArr[1], pointArr[2],
                                 pointArr[3]);
        bool case2 = doIntersect(pointArr[1], pointArr[2], pointArr[3],
                                 pointArr[0]);
        
        if (case1 || case2) {
            std::cout << "error 3\n";
            exit(3);
        }
    }

    bool isValid() {
        //checks intersecting points
        for (int i = 0; i < sizeof(pointArr)/sizeof(Point); i++) {
            for (int j = i+1; j < sizeof(pointArr)/sizeof(Point); j++) {
                if (pointArr[i].equals(pointArr[j])) {
                    std::cout << "error 2" << std::endl;
                    return false;
                }
            }
        }
        //checks 3 colinear points
        for (int i = 0; i < sizeof(pointArr)/sizeof(Point); i++) {
            int j = (i + 1) % 4;
            int k = i % 2;
            if (areEquivalent(sideArr[i].getSlope(), sideArr[j].getSlope(), diagonalArr[k].getSlope())) {
                std::cout << "error 4" << std::endl;
                return false;
            }
        }
        
        lineIntersectCheck();
        
        return true;
    }

};

//****************************************************************************************************
//****************************************************************************************************


bool isParallelogram(const Shape& inputShape) {
    if (areEquivalent(inputShape.getSide(0).getSlope(), inputShape.getSide(2).getSlope())) {
        if (areEquivalent(inputShape.getSide(1).getSlope(), inputShape.getSide(3).getSlope())) {
            return true;
        }
    }
    return false;
}

bool isRectangle(const Shape& inputShape) {
    if (isParallelogram(inputShape)) {
        if (areEquivalent(inputShape.getDiagonal(0).getLength(), inputShape.getDiagonal(1).getLength())) {
            return true;
        }
    }
    return false;
}

bool isRhombus(const Shape& inputShape) {
    if (!isParallelogram(inputShape)) {
        return false;
    }
    for (int i = 0; i < 3; i++) {
        if (!areEquivalent(inputShape.getSide(i).getLength(), inputShape.getSide(i+1).getLength())) {
            return false;
        }
    }
    return true;
}

bool isSquare(const Shape& inputShape) {
    return isRhombus(inputShape) && isRectangle(inputShape);
}

bool isKite(const Shape& inputShape) {
    if (areEquivalent(inputShape.getSide(0).getLength(), inputShape.getSide(1).getLength())) {
        if (areEquivalent(inputShape.getSide(2).getLength(), inputShape.getSide(3).getLength())) {
            return true;
        }
    }
    if (areEquivalent(inputShape.getSide(1).getLength(), inputShape.getSide(2).getLength())) {
        if (areEquivalent(inputShape.getSide(3).getLength(), inputShape.getSide(0).getLength())) {
            return true;
        }
    }
    return false;
}

bool isTrapezoid(const Shape& inputShape) {
    if (areEquivalent(inputShape.getSide(0).getSlope(), inputShape.getSide(2).getSlope())) {
        if (!areEquivalent(inputShape.getSide(1).getSlope(), inputShape.getSide(3).getSlope())) {
            return true;
        }
    }
    if (areEquivalent(inputShape.getSide(1).getSlope(), inputShape.getSide(3).getSlope())) {
        if (!areEquivalent(inputShape.getSide(0).getSlope(), inputShape.getSide(2).getSlope())) {
            return true;
        }
    }
    return false;
}

//****************************************************************************************************
//****************************************************************************************************

bool isValidInput(std::string inputString) {
    if (inputString.size() == 0) {
        return false;
    }
    
    if (!std::isdigit(inputString[0])) {
        return false;
    }
    int numberCount = 1;
    int spaceCount = 0;
    int valueCount = 1;
    for (int i = 1; i < inputString.length()-1; i++) {
        if (std::isdigit(inputString[i])) {
            numberCount++;
            spaceCount = 0;
        } else if (inputString[i] == ' ') {
            numberCount = 0;
            spaceCount++;
            valueCount++;
        } else {
            return false;
        }
        
        if (numberCount > 3 || spaceCount > 1) {
            return false;
        }
    }
    if (valueCount != 6) {
        return false;
    }
    
    return true;
}

//****************************************************************************************************
//****************************************************************************************************


int main(int argc, const char * argv[]) {
//    std::cout << "poop" << std::endl;
    std::string inputString;
    while(std::getline(std::cin, inputString)) {
        if (!isValidInput(inputString)) {
            std::cout << "error 1" << std::endl;
            return 0;
        }
        
        std::stringstream stringStream(inputString);
        std::string singleInput;
        int inputValueArray[6];
        int *inputValuePointer = inputValueArray;
        while (std::getline(stringStream, singleInput, ' ')){
            *inputValuePointer++ = std::stoi(singleInput);
        }
        
        for (int value : inputValueArray) {
            if (value > 100) {
                std::cout << "error 1" << std::endl;
                return 0;
            }
        }
        
        Point point1(inputValueArray[0], inputValueArray[1]);
        Point point2(inputValueArray[2], inputValueArray[3]);
        Point point3(inputValueArray[4], inputValueArray[5]);
        Shape shape(point1, point2, point3);
        
        if (!shape.isValid()) {
            return 0;
        }
        
        std::string outputString;
        if (isSquare(shape)) {
            outputString = "square";
        } else if (isRhombus(shape)) {
            outputString = "rhombus";
        } else if (isRectangle(shape)) {
            outputString = "rectangle";
        } else if (isParallelogram(shape)) {
            outputString = "parallelogram";
        } else if (isKite(shape)) {
            outputString = "kite";
        } else if (isTrapezoid(shape)) {
            outputString = "trapezoid";
        } else {
            outputString = "quadrilateral";
        }
        std::cout << outputString << std::endl;
    }
}
