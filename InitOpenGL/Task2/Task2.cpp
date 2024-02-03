// Task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "StandardIncludes.h"

static float getTrianglePerimeter(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    return glm::distance(p1, p2) + glm::distance(p2, p3) + glm::distance(p3, p1);
}

static float getTriangleArea(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float perimeter)
{
    // Heron's formula
    float s = perimeter / 2;
    float area = std::sqrt( s * (s - glm::distance(p1, p2)) * (s - glm::distance(p2, p3)) * (s - glm::distance(p3, p1)) );
    return area;
}

static void task2()
{
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 v3;

    std::cout << "Enter the position of object 1 as x y z:" << std::endl;
    std::cin >> v1[0];
    std::cin >> v1[1];
    std::cin >> v1[2];

    std::cout << "Enter the position of object 1 as x y z:" << std::endl;
    std::cin >> v2[0];
    std::cin >> v2[1];
    std::cin >> v2[2];

    std::cout << "Enter the position of object 3 as x y z:" << std::endl;
    std::cin >> v3[0];
    std::cin >> v3[1];
    std::cin >> v3[2];

    float perimeter = getTrianglePerimeter(v1, v2, v3);
    float area = getTriangleArea(v1, v2, v3, perimeter);

    std::cout << "\nPerimeter of the triangle: " << perimeter << std::endl;
    std::cout << "Area of the triangle: " << area << std::endl;
}


int main()
{
    task2();
    return 0;
}