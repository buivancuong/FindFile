// >coccoc {word} {Directory}

#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <thread>
#include <boost/algorithm/string.hpp>
#include "HandlerDictionary.h"

std::string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string( buffer ).find_last_of( "/" );
    return std::string( buffer ).substr( 0, pos);
}

void checkFiles(std::vector<std::string> vectorList, int it_begin, int it_end, std::string keyword) {
    for (int i = it_begin; i < it_end; i++) {
        std::fstream checkFile;
        checkFile.open(vectorList[i]);
        std::string line;

        while (!checkFile.eof()) {
            std::getline(checkFile, line);
//            std::cout << "Get line: " << line << std::endl;
            std::vector<std::string> wordInLine;
            boost::split(wordInLine, line, boost::is_any_of(" .,;:"));

            for (auto &iter : wordInLine) {
                if (iter == keyword) {
                    std::cout << vectorList[i] << std::endl;
                    break;
                }
            }
        }

        checkFile.close();
    }
}

int main(int argc, char *argv[]) {

    char *dictionary;
    std::string keyword = argv[1];

    if (argc == 1) {
        std::cout << "Xin hay nhap tham so" << std::endl;
        return 0;
    }
    if (argc == 3) {
        dictionary = argv[2];
    }
    if (argc == 2) {

        std::string exepath = ExePath();
        exepath.erase(exepath.end()-11, exepath.end());
        const char *temp_str = exepath.c_str();
        dictionary = new char[strlen(temp_str) + 1];
        strcpy(dictionary, temp_str);
//        exepath.erase(exepath.end()-11, exepath.end());
//        std::cout << exepath << " cc" << std::endl;
//        char *dic = const_cast<char *>(exepath.c_str());
//        std::cout << dic << " cc" << std::endl;
//        dictionary = dic;
//        std::cout << dictionary << std::endl;
    }

    HandlerDictionary *handlerDictionary = HandlerDictionary::getInstance();
    handlerDictionary->setParent(dictionary);
    handlerDictionary->EnumerateFolders(handlerDictionary->getParent());

    std::vector<std::string> fileList = handlerDictionary->getListFile();

    if (fileList.size() >= 4) {
        std::thread task1 (checkFiles, fileList, 0, fileList.size()/4, keyword);
        std::thread task2 (checkFiles, fileList, fileList.size()/4, fileList.size()/2, keyword);
        std::thread task3 (checkFiles, fileList, fileList.size()/2, fileList.size()/4*3, keyword);
        std::thread task4 (checkFiles, fileList, fileList.size()/4*3, fileList.size(), keyword);
        task1.join();
        task2.join();
        task3.join();
        task4.join();
    } else if (fileList.size() == 3) {
        std::thread task1 (checkFiles, fileList, 0, fileList.size()/3, keyword);
        std::thread task2 (checkFiles, fileList, fileList.size()/3, fileList.size()/3*2, keyword);
        std::thread task3 (checkFiles, fileList, fileList.size()/3*2, fileList.size(), keyword);
        task1.join();
        task2.join();
        task3.join();
    } else if (fileList.size() == 2) {
        std::thread task1 (checkFiles, fileList, 0, fileList.size()/2, keyword);
        std::thread task2 (checkFiles, fileList, fileList.size()/2, fileList.size(), keyword);
        task1.join();
        task2.join();
    } else {
        checkFiles(fileList, 0, static_cast<int>(fileList.size()), keyword);
    }

    std::cout << "System paused" << std::endl;
    getch();
}

