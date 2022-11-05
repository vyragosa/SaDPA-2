#include "include/binFileOperations.h"
#include <filesystem>
#include <iostream>
#include <cstring>


Patient &generatePatient(Patient* patient, int &i) {
	patient->policyID = rand() % 1000000;
	strncpy(patient->name, ("name" + std::to_string(i % 100)).c_str(), 20);
	patient->diseaseID = rand() % 1000000;
	strncpy(patient->date, ("date" + std::to_string(i % 100)).c_str(), 10);
	patient->doctorID = rand() % 1000000;
	return *patient;
}


int fillRandBinary(std::string binFileName, int cnt) {
	Patient patient;
	std::fstream outBinFile(binFileName, std::ios::binary | std::ios::out);
	if (!outBinFile.good())
		return -1;

	for (int i = 0; i < cnt; i++) {
		outBinFile.write((char*)&generatePatient(&patient, i), patientSize);
	}
	outBinFile.close();
	return 0;
}

void printPatient(Patient& patient) {
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
		outBinFile.write((char*)&patient, patientSize);
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

	while (inBinFile.read((char*)&patient, patientSize)) {
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

	while (inBinFile.read((char*)&patient, patientSize))
		printPatient(patient);

	inBinFile.close();
	return 0;
}


int getPolicyByPosition(std::string binFileName, int recordPosition) {
	std::fstream inBinFile(binFileName, std::ios::binary | std::ios::in);
	Patient patient;
	if (!inBinFile.good())
		return -1;

	int offset = (recordPosition) * patientSize;
	inBinFile.seekg(offset, std::ios::beg);
	if (inBinFile.eof()) {
		inBinFile.close();
		return -1;
	}

	inBinFile.read((char*)&patient, patientSize);
	inBinFile.close();
	return patient.policyID;
}

int directAccess(std::string binFileName, int recordPosition, Patient& patient) {
	std::fstream inBinFile(binFileName, std::ios::binary | std::ios::in);
	if (!inBinFile.good())
		return -1;

	int offset = (recordPosition) * patientSize;
	inBinFile.seekg(offset, std::ios::beg);
	if (inBinFile.eof()) {
		inBinFile.close();
		return -1;
	}


	inBinFile.read((char*)&patient, patientSize);
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
	while (inOutBinFile.read((char*)&patient, patientSize) && patient.policyID != key)
		cnt++;

	inOutBinFile.seekg(-1 * patientSize, std::ios::end);
	inOutBinFile.read((char*)&patient, patientSize);
	inOutBinFile.seekg(cnt * patientSize, std::ios::beg);
	inOutBinFile.write((char*)&patient, patientSize);

	std::filesystem::resize_file(binFileName, sizeToCut);
	inOutBinFile.close();
	return 0;
}

int directAccessReplace(std::string binFileName, int key) {
	std::fstream inOutBinFile(binFileName, std::ios::binary | std::ios::in | std::ios::out);
	if (!inOutBinFile.good())
		return -1;

	inOutBinFile.seekg(-1 * patientSize, std::ios::end);
	int sizeToCut = inOutBinFile.tellg();
	inOutBinFile.seekg(std::ios::beg);

	Patient patient;

	inOutBinFile.seekg(-1 * patientSize, std::ios::end);
	inOutBinFile.read((char*)&patient, patientSize);
	inOutBinFile.seekg(key * patientSize, std::ios::beg);
	if (inOutBinFile.eof()) {
		inOutBinFile.close();
		return -1;
	}
	inOutBinFile.write((char*)&patient, patientSize);

	std::filesystem::resize_file(binFileName, sizeToCut);
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

	while (inOutBinFile.read((char*)&patient, patientSize) && patient.policyID != key)
		cnt++;

	while (inOutBinFile.read((char*)&patient, patientSize)) {
		inOutBinFile.seekg(-2 * patientSize, std::ios::cur);
		inOutBinFile.write((char*)&patient, patientSize);
		inOutBinFile.seekg(patientSize, std::ios::cur);
	}

	std::filesystem::resize_file(binFileName, sizeToCut);
	inOutBinFile.close();
	return 0;
}

int directAccessDelete(std::string binFileName, int key) {
	std::fstream inOutBinFile(binFileName, std::ios::binary | std::ios::in | std::ios::out);

	inOutBinFile.seekg(-1 * patientSize, std::ios::end);
	int sizeToCut = inOutBinFile.tellg();
	inOutBinFile.seekg(std::ios::beg);

	if (!inOutBinFile.good())
		return -1;
	Patient patient;
	int cnt = 0;


	inOutBinFile.seekg(patientSize * (key + 1), std::ios::beg);
	if (inOutBinFile.eof()) {
		inOutBinFile.close();
		return -1;
	}

	while (inOutBinFile.read((char*)&patient, patientSize)) {
		inOutBinFile.seekg(-2 * patientSize, std::ios::cur);
		inOutBinFile.write((char*)&patient, patientSize);
		inOutBinFile.seekg(patientSize, std::ios::cur);
	}

	std::filesystem::resize_file(binFileName, sizeToCut);
	inOutBinFile.close();
	return 0;
}


int createBinFileByDiseaseID(std::string binFileName, std::string newBinFileName, int Key) {
	std::fstream inBinFile(binFileName, std::ios::binary | std::ios::in);
	std::ofstream outNewBilFile(newBinFileName, std::ios::binary | std::ios::out);
	if (!inBinFile.good() && !outNewBilFile.good())
		return -1;
	Patient patient;

	while (inBinFile.read((char*)&patient, sizeof(Patient)))
		if (patient.diseaseID == Key)
			outNewBilFile.write((char*)&patient, patientSize);

	inBinFile.close();
	outNewBilFile.close();
	return 0;
}

int sizeOfFile(std::string binFileName) {
	std::fstream inBinFile(binFileName, std::ios::binary | std::ios::in);
	inBinFile.seekg(0, std::ios::end);
	int size = inBinFile.tellg();
	inBinFile.close();
	return size / patientSize;
}


int testBinF() {
	std::string fileName, newFileName;
	int num, code = 0, menu = 1;
	while (menu) {
		std::cout << "Press 1 to choose your interaction binary file\n"
			<< "Press 2 overwrite from text file to binary file\n"
			<< "Press 3 overwrite from binary file to text file\n"
			<< "Press 4 to print binary file\n"
			<< "Press 5 to get record by it's position\n"
			<< "Press 6 to delete (replace) record by key with last record\n"
			<< "Press 7 to generate a new binary file with patients diagnosed with a given disease ID\n"
			<< "Press 8 to delete patient information with a given key\n"
			<< "Press 0 to exit program\n";
		std::cin >> menu;

		switch (menu) {
		case 1:
			std::cout << "Enter name of your interaction file: ";
			std::cin >> fileName;
			break;
		case 2:
			std::cout << "Enter text file name: ";
			std::cin >> newFileName;
			code = overwriteFromTextToBinary(fileName, newFileName);
			break;
		case 3:
			std::cout << "Enter text file name: ";
			std::cin >> newFileName;
			code = overwriteFromBinaryToText(fileName, newFileName);
			break;
		case 4:
			code = printBinFile(fileName);
			break;
		case 5:
			std::cout << "Enter position of a record: ";
			std::cin >> num;
			code = getPolicyByPosition(fileName, num);
			break;
		case 6:
			std::cout << "Enter key: ";
			std::cin >> num;
			code = replaceRecordWithLast(fileName, num);
			break;
		case 7:
			std::cout << "Enter new binary file name and key: ";
			std::cin >> newFileName >> num;
			code = createBinFileByDiseaseID(fileName, newFileName, num);
			break;
		case 8:
			std::cout << "Enter key: ";
			std::cin >> num;
			code = deleteRecordByID(fileName, num);
			break;
		default:
			break;
		}
		if (code == -1)
			std::cout << "There are some file problems!\n";
		std::cout << std::endl;
	}
	return 0;
}
