#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <iostream>
#include <fstream>

int readTextFile(std::string nameTf);
int createTextFile(std::string nameItf, std::string nameOtf);
int addTextToFile(std::string nameTf, int a);
int countNInFile(std::string nameTf);
int foundNByNumber(std::string nameTf, int num);
bool isPrime(int num);

#endif FILE_OPERATIONS_H
