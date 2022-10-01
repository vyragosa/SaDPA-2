#ifndef TEXT_FILE_OPERATIONS_H
#define TEXT_FILE_OPERATIONS_H

#include <iostream>
#include <fstream>

int readTextFile(std::string nameTf);
int createTextFile(std::string nametf, int size);
int addTextToFile(std::string nameTf, int a);
int countNInFile(std::string nameTf);
int findNByNumber(std::string nameTf, int num);
int createTextFilePrime(std::string nameItf, std::string nameOtf);
bool isPrime(int num);

#endif TEXT_FILE_OPERATIONS_H