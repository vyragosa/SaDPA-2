#include <iostream>
#include <fstream>

struct book {
    int isbn;
    char namebook[20];
    char author[30];
    unsigned int year_of_publication;
};

int createBinFile(std::string nametf, std::string namebf) {
    std::ifstream itf(nametf);
    if (!itf)
        return -1;
    book b;
    std::fstream obf(namebf, std::ios::binary | std::ios::out);
    while (!itf.eof()) {
        itf >> b.isbn;
        itf.get();
        itf.getline(b.namebook, 30, '\n');
        itf.getline(b.author, 30, '\n');
        itf >> b.year_of_publication;
        obf.write((char*)&b, sizeof(book));
    }
    itf.close();
    obf.close();
    return 0;
}

int outBinFile(std::string namebf) {
    std::fstream ibf(namebf, std::ios::binary | std::ios::in);
    if (!ibf)
        return 1;
    book b;
    int len = sizeof(book);
    ibf.read((char*)&b, len);
    while (!ibf.eof()) {
        std::cout << b.isbn << ' ' << b.namebook
                  << ' ' << b.author << ' ' << b.year_of_publication <<std::endl;
        ibf.read((char*)&b, len);

    }
    ibf.close();
    return 0;
}

int searchKeyInBinFile(std::string namebf, int key) {
    std::fstream ibf(namebf, std::ios::binary | std::ios::in);
    if (!ibf)
        return 1;
    book b;
    int i = 0;
    int len = sizeof(book);
    ibf.read((char*)&b, len);
    while (!ibf.eof()) {
        i++;
        if (key == b.isbn) {
            ibf.close();
            return i;
        }

        ibf.read((char*)&b, len);

    }
    ibf.close();
    return -1;
}

int directAccessToTheRecordBinFile(std::string namebf, int numRecord, book& r) {
    int code;
    std::fstream bf(namebf, std::ios::binary | std::ios::in);
    if (!bf) {
        return 2;
    }

    int offset = (numRecord - 1) * sizeof(r);
    bf.seekg(offset, std::ios::beg);
    if (!bf.bad()) {
        bf.read((char*)&r, sizeof(book));
        code = 0;
    }
    else
        code = 1;
    bf.close();
    return code;
}

int main() {
    createBinFile("TextFile1.txt", "BinFile.bin");
    outBinFile("BinFile.bin");
    std::cout << searchKeyInBinFile("BinFile.bin", 222) << std::endl;
    book b;
    directAccessToTheRecordBinFile("BinFile.bin", 3, b);
    std::cout << b.isbn << std::endl;
}
