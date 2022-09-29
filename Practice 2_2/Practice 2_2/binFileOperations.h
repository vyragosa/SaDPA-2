#ifndef BIN_FILE_OPERATIONS_H
#define BIN_FILE_OPERATIONS_H

#include <iostream>
#include <fstream>

struct Patient {
	int policyID;
	char name[20];
	int diseaseID;
	char date[10];
	int doctorID;
};

const int patientSize = sizeof(Patient);

void printPatient(Patient& patient);
int overwriteFromTextToBinary(std::string binFileName, std::string textFileName);
int overwriteFromBinaryToText(std::string binFileName, std::string textFileName);
int printBinFile(std::string binFileName);
int getRecordByPosition(std::string binFileName, int recordPosition, Patient& patient);
int replaceRecordWithLast(std::string binFileName, int key);
int deleteRecordByID(std::string binFileName, int key);
int createBinFileByDiseaseID(std::string binFileName, std::string newBinFileName, int Key);

#endif FILE_OPERATIONS_H