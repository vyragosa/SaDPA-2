#include "binFileOperations.h"
#include <unistd.h>

void printPatient(Patient &patient) {
	std::cout << patient.policyID << '\t'
			  << patient.name << '\t'
			  << patient.diseaseID << '\t'
			  << patient.date << '\t'
			  << patient.doctorID << std::endl;
}

int overwriteFromTextToBinary(std::string binFileName, std::string textFileName) {
	std::ifstream inTextFile(textFileName);
	std::fstream outBinFile(binFileName, std::ios::binary | std::ios::out);
	if (!inTextFile.good() && !outBinFile.good())
		return -1;
	Patient patient;

	while (inTextFile >> patient.policyID) {
		inTextFile.get();
		inTextFile.getline(patient.name, 30, '\n');
		inTextFile >> patient.diseaseID;
		inTextFile.get();
		inTextFile.getline(patient.date, 30, '\n');
		inTextFile >> patient.doctorID;
		inTextFile.get();
		outBinFile.write((char *) &patient, patientSize);
	}
	inTextFile.close();
	outBinFile.close();
	return 0;
}

int overwriteFromBinaryToText(std::string binFileName, std::string textFileName) {
	std::fstream inBinFile(binFileName, std::ios::binary | std::ios::in);
	std::ofstream outTextFile(textFileName);
	if (!inBinFile.good() && !outTextFile.good())
		return -1;
	Patient patient;

	while (inBinFile.read((char *) &patient, patientSize)) {
		outTextFile << patient.policyID << '\n'
					<< patient.name << '\n'
					<< patient.diseaseID << '\n'
					<< patient.date << '\n'
					<< patient.doctorID << '\n';
	}
	return 0;
}


int printBinFile(std::string binFileName) {
	std::fstream inBinFile(binFileName, std::ios::binary | std::ios::in);
	if (!inBinFile.good())
		return -1;
	Patient patient;

	while (inBinFile.read((char *) &patient, patientSize))
		printPatient(patient);

	inBinFile.close();
	return 0;
}


int getRecordByPosition(std::string binFileName, int recordPosition, Patient &patient) {
	std::fstream inBinFile(binFileName, std::ios::binary | std::ios::in);
	if (!inBinFile.good())
		return -1;

	int offset = (recordPosition - 1) * patientSize;
	inBinFile.seekg(offset, std::ios::beg);
	if (inBinFile.bad())
		return -1;

	inBinFile.read((char *) &patient, patientSize);
	inBinFile.close();
	return 0;
}

int replaceRecordWithLast(std::string binFileName, int key) {
	std::fstream inOutBinFile(binFileName, std::ios::binary | std::ios::in | std::ios::out);
	if (!inOutBinFile.good())
		return -1;

	inOutBinFile.seekg(-1 * patientSize, std::ios::end);
	int sizeToCut = inOutBinFile.tellg();
	inOutBinFile.seekg(std::ios::beg);

	int cnt = 0;
	Patient patient;
	while (inOutBinFile.read((char *) &patient, patientSize) && patient.policyID != key)
		cnt++;

	inOutBinFile.seekg(-1 * patientSize, std::ios::end);
	inOutBinFile.read((char *) &patient, patientSize);
	inOutBinFile.seekg(cnt * patientSize, std::ios::beg);
	inOutBinFile.write((char *) &patient, patientSize);

	truncate(binFileName.c_str(), sizeToCut);
	inOutBinFile.close();
	return 0;
}

int deleteRecordByID(std::string binFileName, int key) {
	std::fstream inOutBinFile(binFileName, std::ios::binary | std::ios::in | std::ios::out);

	inOutBinFile.seekg(-1 * patientSize, std::ios::end);
	int sizeToCut = inOutBinFile.tellg();
	inOutBinFile.seekg(std::ios::beg);

	if (!inOutBinFile.good())
		return -1;
	Patient patient;
	int cnt = 0;

	while (inOutBinFile.read((char *) &patient, patientSize) && patient.policyID != key)
		cnt++;

	while (inOutBinFile.read((char *) &patient, patientSize)) {
		inOutBinFile.seekg(-2 * patientSize, std::ios::cur);
		inOutBinFile.write((char *) &patient, patientSize);
		inOutBinFile.seekg(patientSize, std::ios::cur);
	}

	truncate(binFileName.c_str(), sizeToCut);
	inOutBinFile.close();
	return 0;
}

int createBinFileByDiseaseID(std::string binFileName, std::string newBinFileName, int Key) {
	std::fstream inBinFile(binFileName, std::ios::binary | std::ios::in);
	std::ofstream outNewBilFile(newBinFileName, std::ios::binary | std::ios::out);
	if (!inBinFile.good() && !outNewBilFile.good())
		return -1;
	Patient patient;

	while (inBinFile.read((char *) &patient, sizeof(Patient)))
		if (patient.diseaseID == Key)
			outNewBilFile.write((char *) &patient, patientSize);

	inBinFile.close();
	outNewBilFile.close();
	return 0;
}
