#pragma once
#include <string>
#include <iostream>

class Interpeter
{
public:
    virtual void Initialize() = 0;
    virtual void LoadFile(std::string path) = 0;
    virtual int Run() = 0;

    Interpeter(){};
    virtual ~Interpeter(){};
};