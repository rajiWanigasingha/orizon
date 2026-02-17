#include "pacman.h"

#include <array>
#include <string>

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

pacman::pacman(){
    Pacman_application_handel_files pacman_application_handel_files;

    this->filePaths = pacman_application_handel_files.getApplicationPaths();
}

