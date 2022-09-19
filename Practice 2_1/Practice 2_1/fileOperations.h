#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <iostream>
#include <fstream>
int fileIsOpen(std::string nameTf);
int readTextFile(std::string nameTf);
int createTextFilePrime(std::string nameItf, std::string nameOtf);
int createTextFile(std::string nametf, int size);
int addTextToFile(std::string nameTf, int a);
int countNInFile(std::string nameTf);
int findNByNumber(std::string nameTf, int num);
bool isPrime(int num);

#endif FILE_OPERATIONS_H