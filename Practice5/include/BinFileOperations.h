#pragma once

#include <fstream>

struct Patient {
	int policyID;
	char name[20];
	int diseaseID;
	char date[10];
	int doctorID;
};

const int patientSize = sizeof(Patient);

int fillRandBinary(std::string binFileName, int cnt);

void printPatient(Patient& patient);

int overwriteFromTextToBinary(std::string binFileName, std::string textFileName);

int overwriteFromBinaryToText(std::string binFileName, std::string textFileName);

int printBinFile(std::string binFileName);

int getRecordByPosition(std::string binFileName, int recordPosition);

int replaceRecordWithLast(std::string binFileName, int key);

int deleteRecordByID(std::string binFileName, int key);

int createBinFileByDiseaseID(std::string binFileName, std::string newBinFileName, int Key);

int sizeOfFile(std::string binFileName);

int directAccessDelete(std::string binFileName, int key);

int directAcñess(std::string binFileName, int recordPosition, Patient& patient);

int testBinF();
