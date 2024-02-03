// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GameController.h"

static void AddVectors()
{
    glm::vec2 a = { 3, 5 };
    glm::vec2 b = { 2, -1 };
    glm::vec2 c = a + b;
    std::cout << glm::to_string(c) << std::endl;

    glm::vec3 d = { 3, 5, 1 };
    glm::vec3 e = { 2, -1, -1 };
    glm::vec3 f = d + e;
    std::cout << glm::to_string(f) << std::endl;
}

static void SubtractVectors()
{
    glm::vec2 a = { 3, 5 };
    glm::vec2 b = { 2, -1 };
    glm::vec2 c = b - a; //direction from a to b
    glm::vec2 d = a - b; //direction from b to a

    std::cout << glm::to_string(c) << "    Magnitude: " << glm::length(c) << std::endl;
    std::cout << glm::to_string(d) << "    Magnitude: " << glm::length(d) << std::endl;
}

static glm::vec3 pos = { 2, 2, 2 };
static void MultiplyVectors()
{
    glm::vec3 dest = { 1, 0, 0 };
    glm::vec3 dir = dest - pos;
    dir = glm::normalize(dir);
    pos += (dir * 0.1f); //0.1f per frame is our desired movement speed
    std::cout << glm::to_string(pos) << std::endl;
}

static void Distance()
{
    glm::vec3 p1 = { 1, 1, 0 };
    glm::vec3 p2 = { 2, 1, 2 };
    float distance = glm::distance(p1, p2);
    std::cout << "Distance = " << distance << std::endl;
}

static void DotProduct()
{
    glm::vec3 source = { 0, 0, 0 };
    glm::vec3 a = { 0, 2, 0 };
    glm::vec3 b = { 1, 1, 0 };
    glm::vec3 aVec = a - source; //direction and magnitude from source to a
    glm::vec3 bVec = b - source; //direction and magnitude from source to b
    aVec = glm::normalize(aVec); //normalized direction from source to a
    bVec = glm::normalize(bVec); //normalized direction from source to b
    float dot = glm::dot(aVec, bVec); //how similar the two vectors are (~0.7 result means its somewhere between the same direction and perpendicular)
    std::cout << "Dot = " << dot << std::endl;
}

static void CrossProduct()
{
    glm::vec3 source = { 0, 0, 0 };
    glm::vec3 a = { 0, 2, 0 };
    glm::vec3 b = { 1, 1, 0 };
    glm::vec3 aVec = a - source; //direction and magnitude from source to a
    glm::vec3 bVec = b - source; //direction and magnitude from source to b
    glm::vec3 cross = glm::cross(aVec, bVec);//perpendicular vector to a and b
    cross = glm::normalize(cross); //normalized direction perpendicular to a and b
    std::cout << "Cross = " << glm::to_string(cross) << std::endl;
}

int main()
{
    //AddVectors();
    //SubtractVectors();
    /*
    for (int count = 0; count < 10; count++)
        MultiplyVectors();
        */
    //Distance();
    //DotProduct();
    CrossProduct();
    

    /*
    GameController::GetInstance().Initialize();
    GameController::GetInstance().RunGame();
    */

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
