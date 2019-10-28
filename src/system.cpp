/*
 * system.cpp
 * Copyright (C) 2019 preetham <preetham@preetham-laptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "system.hpp"

#include <string>
#include <utility>
#include <iostream>
#include <cctype>
#include <vector>


System::System() {};
System::~System() {};

void System::addMatrix(const std::string& key, int rows, int columns)
{
   Matrix mat{rows, columns};
   mat.init(); 
   
   matrices.insert(std::make_pair(key, mat)); 
}

void System::parseComputation()
{
    std::string computation;
    std::getline(std::cin, computation, '\n');
    std::vector<std::string> keys;
    for (auto& c : computation)
    {
        std::string s(1, c);
        if (std::isalpha(c))
        {
            if (matrices.count(s) > 0)
            {
                keys.push_back(s);
            }
            else
            {
                std::cout << "Matrix " << c << " does not exist!" << std::endl;
                return;
            }
        }
        else if ((std::isdigit(c)) || (s == "+") || (s == "-") || (s == "*") || (s == "/"))
        {
            keys.push_back(s);
        }
        if (keys.size() == 3)
        {
            break;
        }
    }

    if (keys[1] == "+")
    {
        if ((std::isdigit(*keys[0].data())) || (std::isdigit(*keys[2].data())))
        {
            std::cout << "Can not add matrices and scalars." << std::endl;
            return;
        }

        addMatrices(keys[0], keys[2]);
    }
    else if (keys[1] == "-")
    {
        if ((std::isdigit(*keys[0].data())) || (std::isdigit(*keys[2].data())))
        {
            std::cout << "Can not subtract matrices and scalars." << std::endl;
            return;
        }

        subtractMatrices(keys[0], keys[2]);
    }
    else if (keys[1] == "*")
    {
        if (std::isdigit(*keys[0].data()))
        {
            multiplyByScalar(keys[0], keys[2]);
        }
        else if (std::isdigit(*keys[2].data()))
        {
            multiplyByScalar(keys[2], keys[0]);
        }
        else
        {
            multiplyMatrices(keys[0], keys[2]);
        }
    }
    else if (keys[1] == "/")
    {
        if ((std::isdigit(*keys[0].data())) && (!std::isdigit(*keys[2].data())))
        {
            std::cout << "Can not divide scalar by matrix" << std::endl;
            return;
        }
        else if ((!std::isdigit(*keys[0].data())) && (!std::isdigit(*keys[2].data())))
        {
            std::cout << "Can not divide a matrix by matrix" << std::endl;
            return;
        }
        divideByScalar(keys[0], keys[2]);
    }
    else
    {
        std::cout << "Unsupported operation." << std::endl;
    }
}

void System::addMatrices(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix_1 = matrices.find(key_1)->second;
    Matrix matrix_2 = matrices.find(key_2)->second;

    if ((matrix_1.getRows() != matrix_2.getRows()) || (matrix_1.getColumns() != matrix_2.getColumns()))
    {
        std::cout << "The matrices entered do not have the same dimensions!" << std::endl;
        return;
    }

    Matrix result = matrix_1 + matrix_2;
    result.print();
}

void System::subtractMatrices(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix_1 = matrices.find(key_1)->second;
    Matrix matrix_2 = matrices.find(key_2)->second;

    if ((matrix_1.getRows() != matrix_2.getRows()) || (matrix_1.getColumns() != matrix_2.getColumns()))
    {
        std::cout << "The matrices entered do not have the same dimensions!" << std::endl;
        return;
    }

    Matrix result = matrix_1 + matrix_2;
    result.print();
}

void System::multiplyByScalar(const std::string& key_1, const std::string& key_2)
{
    int multiplier = std::stoi(key_1);
    Matrix matrix = matrices.find(key_2)->second;

    Matrix result = matrix * multiplier;
    result.print();
}

void System::multiplyMatrices(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix_1 = matrices.find(key_1)->second;
    Matrix matrix_2 = matrices.find(key_2)->second;

    Matrix result = matrix_1 * matrix_2;
    result.print();
}

void System::divideByScalar(const std::string& key_1, const std::string& key_2)
{
    Matrix matrix = matrices.find(key_1)->second;
    int divisor = std::stoi(key_2);

    Matrix result = matrix / divisor;
    result.print();
}

void System::printSystem()
{
    for (auto& elem : matrices)
    {
        std::cout << elem.first << ": " << std::endl;
        elem.second.print();
        std::cout << std::endl;
    }
}

bool System::isRunning()
{
    return running;
}

void System::setRunning(bool value)
{
    running = value;
}

