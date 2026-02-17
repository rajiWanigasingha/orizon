#include "Pacman.h"

#include <array>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

string Pacman_application_handel_files::getHomePath(){
    const string home = getenv("HOME");
    return home;
}

array<string ,3> Pacman_application_handel_files::getApplicationPaths(){

    const string home = getHomePath();
    int index = 0;
    array<string ,3> files;

    for (auto file_path : this->filePaths) {
        if (file_path.starts_with("$HOME")) {
            files[index] = file_path.replace(0 ,5 ,home);
        } else {
            files[index] = file_path;
        }
        index++;
    }

    return files;
}

vector<string> Pacman::getAllPathForDotDesktopFiles() const {
    vector<string> paths;

    for (const auto& file_path : this->filePaths) {
        if (filesystem::exists(file_path) && filesystem::is_directory(file_path)) {
            for (const auto& entry : filesystem::directory_iterator(file_path)) {
                paths.push_back(entry.path().string());
            }
        }
    }

    return paths;
}

void Pacman::filterOutApplicationInformation(const vector<string>& paths){
    for (const auto & path : paths) {
        string fullDesktopInfo;
        string desktop_content;

        ifstream MyReadFile(path);

        while (getline(MyReadFile, desktop_content)) {
            fullDesktopInfo = fullDesktopInfo + "\n" + desktop_content;
        }

        cout << fullDesktopInfo << endl;

        cout << "---------------------------------------------------------------------" << endl;
    }
}

void Pacman::parseDotDesktopFiles(const string& dotDesktopFile){

}

Pacman::Pacman(){
    Pacman_application_handel_files pacman_application_handel_files;

    this->filePaths = pacman_application_handel_files.getApplicationPaths();

    const vector<string> paths = this->getAllPathForDotDesktopFiles();

    this->filterOutApplicationInformation(paths);
}

