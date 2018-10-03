//
// Created by acsim on 10/2/2018.
//

#ifndef COCCOC_HANDLERDICTIONARY_H
#define COCCOC_HANDLERDICTIONARY_H

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <string>

class HandlerDictionary {
private:
    static HandlerDictionary *instance;
    char *parent;
    WIN32_FIND_DATA find_data;
    char folder[MAX_PATH];
    std::vector<std::string> listFile;

    HandlerDictionary();

public:
    ~HandlerDictionary();

    char *getParent();

    static HandlerDictionary *getInstance();

    void setParent(char *parent);

    std::vector<std::string> getListFile();

    void EnumerateFolders (const char* parent);

};


#endif //COCCOC_HANDLERDICTIONARY_H
