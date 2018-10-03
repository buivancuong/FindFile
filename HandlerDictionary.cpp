//
// Created by acsim on 10/2/2018.
//

#include "HandlerDictionary.h"

HandlerDictionary *HandlerDictionary::instance = nullptr;

HandlerDictionary::HandlerDictionary() = default;

HandlerDictionary::~HandlerDictionary() = default;

HandlerDictionary *HandlerDictionary::getInstance() {
    if (!instance) {
        instance = new HandlerDictionary();
    }
    return instance;
}

char *HandlerDictionary::getParent() {
    return this->parent;
}

void HandlerDictionary::setParent(char *parent) {
    this->parent = parent;
}

std::vector<std::string> HandlerDictionary::getListFile() {
    return this->listFile;
}

void HandlerDictionary::EnumerateFolders(const char *parent) {
    sprintf(folder, "%s/*.*", parent);

    HANDLE handleFind = FindFirstFile (folder, &find_data);

    if (handleFind != INVALID_HANDLE_VALUE) {
        do {
            if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (strcmp(find_data.cFileName, ".") && strcmp(find_data.cFileName, "..")) {
//                    std::cout << "std::cout Folder: " << parent << "/" << find_data.cFileName << std::endl;
                    char child[MAX_PATH];
                    sprintf(child, "%s/%s", parent, find_data.cFileName);
                    EnumerateFolders(child);
                }
            } else {
//                std::cout << "std::cout File: " << find_data.cFileName << " with Path: " << parent << "/" << find_data.cFileName << std::endl;
                std::string filePath;
                filePath += parent;
                filePath += "/";
                filePath += find_data.cFileName;
                listFile.push_back(filePath);
            }
        } while (FindNextFile (handleFind, &find_data));
        FindClose(handleFind);
    }
}
