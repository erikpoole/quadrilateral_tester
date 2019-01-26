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

class Point{
private:
    float x;
    float y;
    
public:
    Point() {
    }
    
    Point(const float& xInput, const float& yInput) {
        x = xInput;
        y = yInput;
    }
    
    float getX() const {return x;}
    float getY() const {return y;}
};


class Line{
private:
    int xOffset;
    int yOffset;
    Point pointArr[2];
    
public:
    Line() {
    }
    
    Line(const Point& point1, const Point& point2) {
        pointArr[0] = point1;
        pointArr[1] = point2;
        xOffset = abs(point1.getX() - point2.getX());
        yOffset = abs(point1.getY() - point2.getY());
        
    }
    
    Point getPoint(const int& pointNumber) const {return pointArr[pointNumber];}
    int getXOffset() const {return xOffset;}
    int getYOffset() const {return yOffset;}
    
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
    
    Point getPoint(const int& pointNumber) const {return pointArr[pointNumber];}
    Line getSide(const int& sideNumber) const {return sideArr[sideNumber];}
    Line getDiagonal(int diagonalNumber) const {return diagonalArr[diagonalNumber];}
    
};

//****************************************************************************************************
//****************************************************************************************************


bool areEquivalent(double double1, double double2) {
    return abs(double1 - double2) < .0001;
}

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
        if (!areEquivalent(inputShape.getSide(0).getLength(), inputShape.getSide(3).getLength())) {
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


int main(int argc, const char * argv[]) {
    std::string inputString;
    while(std::getline(std::cin, inputString)) {
        std::stringstream stringStream(inputString);
        
        std::string singleInput;
        int inputValueArray[6];
        int *inputValuePointer = inputValueArray;
        while (std::getline(stringStream, singleInput, ' ')){
            *inputValuePointer++ = std::stoi(singleInput);
        }
        
        Point point1(inputValueArray[0], inputValueArray[1]);
        Point point2(inputValueArray[2], inputValueArray[3]);
        Point point3(inputValueArray[4], inputValueArray[5]);
        Shape shape(point1, point2, point3);
        
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
