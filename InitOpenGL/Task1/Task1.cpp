// Task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "StandardIncludes.h"

static void Task1()
{
    glm::vec3 v1;
    glm::vec3 v2;
    float speed = 0;

    std::cout << "Enter the person's source position as x y z:" << std::endl;
    std::cin >> v1[0];
    std::cin >> v1[1];
    std::cin >> v1[2];

    std::cout << "Enter the desired destination position as x y z:" << std::endl;
    std::cin >> v2[0];
    std::cin >> v2[1];
    std::cin >> v2[2];

    std::cout << "What is the person's speed per step (as a scalar)?" << std::endl;
    std::cin >> speed;

    float dist = glm::distance(v1, v2);
    int steps = std::ceil(dist / speed);

    std::cout << "\nRequired number of steps to reach destination: " << steps << std::endl;
}

int main()
{
    Task1();
    return 0;
}