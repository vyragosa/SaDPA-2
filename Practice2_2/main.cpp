#include <iostream>
#include "binFileOperations.h"

int main() {
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

        switch (menu)
        {
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
                Patient patient;
                code = getRecordByPosition(fileName, num, patient);
                printPatient(patient);
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
