#include "Pacman.h"

#include <array>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cctype>

using namespace std;

static inline void ltrim(std::string& s){
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(std::string& s){
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void trim(std::string& s){
    rtrim(s);
    ltrim(s);
}


string Pacman_application_handel_files::getHomePath(){
    const string home = getenv("HOME");
    return home;
}

array<string, 3> Pacman_application_handel_files::getApplicationPaths(){
    const string home = getHomePath();
    int index = 0;
    array<string, 3> files;

    for (auto file_path : this->filePaths) {
        if (file_path.starts_with("$HOME")) {
            files[index] = file_path.replace(0, 5, home);
        }
        else {
            files[index] = file_path;
        }
        index++;
    }

    return files;
}

vector<string> Pacman::getAllPathForDotDesktopFiles() const{
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
    for (const auto& path : paths) {
        vector<string> dotDesktopFile;
        string desktop_content;

        ifstream MyReadFile(path);

        while (getline(MyReadFile, desktop_content)) {
            dotDesktopFile.push_back(desktop_content);
        }

        cout << "Read file " << path << endl;

        parseDotDesktopFiles(dotDesktopFile);

        cout << "---------------------------------------------------------------------" << endl;
    }
}

void Pacman::parseDotDesktopFiles(const vector<string>& dotDesktopFile){
    Desktop_Application::Desktop_Info desktop_info;

    if (dotDesktopFile.empty()) {
        cout << "Found empty file" << endl;
        return;
    }

    string confirmFirstLineIsDesktop = dotDesktopFile[0];
    trim(confirmFirstLineIsDesktop);

    if (confirmFirstLineIsDesktop.empty()) {
        cout << "Found empty line" << endl;
        return;
    }

    if (confirmFirstLineIsDesktop != "[Desktop Entry]") {
        cerr << "This path is not a desktop entry and " << confirmFirstLineIsDesktop << endl;
        return;
    }

    for (size_t i = 1; i < dotDesktopFile.size(); i++) {
        string key;
        int indexOfBreak = 0;

        for (const char findKey : dotDesktopFile[i]) {
            if (findKey != '=') {
                key += findKey;
                indexOfBreak++;
            }
            else {
                break;
            }
        }

        ranges::transform(key, key.begin(),
                          [](unsigned char c) { return std::tolower(c); });

        string value = dotDesktopFile[i].substr(indexOfBreak, dotDesktopFile[i].length() - indexOfBreak);

        value.erase(0, 1);

        if (key == "type") {
            trim(value);
            if (value == "Application") {
                desktop_info.applicationType = "Application";
            }
        }
        else if (key == "name") {
            desktop_info.applicationName = value;
        }else if (key == "version") {
            desktop_info.applicationVersion = std::stof(value);
        }else if (key == "genericname") {
            desktop_info.genericApplicationName = value;
        }else if (key == "nodisplay") {
            desktop_info.doNotDisplay = value == "true";
        }else if (key == "comment") {
            desktop_info.applicationDescription = value;
        }else if (key == "icon") {
            desktop_info.applicationIcons = value;
        }else if (key == "hidden") {
            desktop_info.deleted = value == "true";
        }else if (key == "onlyshowin") {
            desktop_info.onlyShowIn = value;
        }else if (key == "notshowin") {
            desktop_info.dontShowId = value;
        }else if (key == "dbusactivatable") {
            desktop_info.dbusActivatable = value == "true";
        }else if (key == "tryexec") {
            desktop_info.tryExec = value;
        }else if (key == "exec") {
            desktop_info.executablePath = value;
        }else if (key == "path") {
            desktop_info.path = value;
        }else if (key  == "terminal") {
            desktop_info.runApplicationInTerminal = (value == "true");
        }else if (key == "action") {
            desktop_info.actions = value;
        }else if (key == "mimetype") {
            desktop_info.mimeType = value;
        }else if (key == "categories") {
            desktop_info.categories = value;
        }else if (key == "keywords") {
            desktop_info.keywords = value;
        }else if (key == "startupnotify") {
            desktop_info.startUpNotification = value == "true";
        }else if (key == "startupwmclass") {
            desktop_info.startUpWMClass   = value;
        }else if (key == "prefersnondefaultgpu") {
            desktop_info.PrefersNonDefaultGPU = value == "true";
        }else if (key == "singlemainwindow") {
            desktop_info.SingleMainWindow = value == "true";
        }
    }

    this->applications.push_back(desktop_info);
}

Pacman::Pacman(){
    Pacman_application_handel_files pacman_application_handel_files;

    this->filePaths = pacman_application_handel_files.getApplicationPaths();

    const vector<string> paths = this->getAllPathForDotDesktopFiles();

    filterOutApplicationInformation(paths);

    for (const auto& application : this->applications) {
        std::cout << application.applicationName << std::endl;
        std::cout << application.applicationDescription.value_or("N/A") << std::endl;
        std::cout << application.applicationVersion.value_or(0.0f) << std::endl;
        std::cout << application.keywords.value_or("N/A") << std::endl;
        cout << "______________________________________" << endl;
    }
}
