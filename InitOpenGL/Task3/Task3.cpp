// Task3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "StandardIncludes.h"

static void getTrianglePoints(glm::vec3* p1, glm::vec3* p2, glm::vec3* p3)
{
    std::cout << "Enter the first point of the triangle as x y z:" << std::endl;
    std::cin >> (*p1)[0];
    std::cin >> (*p1)[1];
    std::cin >> (*p1)[2];

    std::cout << "Enter the second point of the triangle as x y z:" << std::endl;
    std::cin >> (*p2)[0];
    std::cin >> (*p2)[1];
    std::cin >> (*p2)[2];

    std::cout << "Enter the third point of the triangle as x y z:" << std::endl;
    std::cin >> (*p3)[0];
    std::cin >> (*p3)[1];
    std::cin >> (*p3)[2];
}

static glm::vec3 getLastPointInFace(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    glm::vec3 displacementVec = p1 - p2;
    return p3 + displacementVec;
}

static void getBackFace(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float depth, glm::vec3 backFace[])
{
    glm::vec3 side1;
    glm::vec3 side2;
    glm::vec3 depthVec;

    /*this would be done way better in a loop but I'm too lazy.*/
    side1 = p2 - p1;
    side2 = p3 - p2;
    depthVec = glm::cross(side1, side2); //get direction of vector perpendiuclar to two sides
    depthVec = glm::normalize(depthVec); //normalize to apply desired depth
    depthVec *= depth; //set depth of cuboid to desired depth
    backFace[0] = p2 + depthVec;

    side1 = p3 - p2;
    side2 = p4 - p3;
    depthVec = glm::cross(side1, side2); //get direction of vector perpendiuclar to two sides
    depthVec = glm::normalize(depthVec); //normalize to apply desired depth
    depthVec *= depth; //set depth of cuboid to desired depth
    backFace[1] = p3 + depthVec;

    side1 = p4 - p3;
    side2 = p1 - p4;
    depthVec = glm::cross(side1, side2); //get direction of vector perpendiuclar to two sides
    depthVec = glm::normalize(depthVec); //normalize to apply desired depth
    depthVec *= depth; //set depth of cuboid to desired depth
    backFace[2] = p4 + depthVec;

    side1 = p1 - p4;
    side2 = p2 - p1;
    depthVec = glm::cross(side1, side2); //get direction of vector perpendiuclar to two sides
    depthVec = glm::normalize(depthVec); //normalize to apply desired depth
    depthVec *= depth; //set depth of cuboid to desired depth
    backFace[3] = p1 + depthVec;
}


int main()
{
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;
    glm::vec3 p4;
    glm::vec3 backFace[4];

    float depth = 2;

    getTrianglePoints(&p1, &p2, &p3);
    p4 = getLastPointInFace(p1, p2, p3);
    getBackFace(p1, p2, p3, p4, depth, backFace);

    glm::vec3 cuboidPoints[8] = { p1, p2, p3, p4, backFace[0], backFace[1], backFace[2], backFace[3] };

    std::cout << "The points of your cuboid are:" << endl;

    for (int i = 0; i < 8; i++)
    {
        std::cout << glm::to_string(cuboidPoints[i]) << endl;
    }

    return 0;
}
