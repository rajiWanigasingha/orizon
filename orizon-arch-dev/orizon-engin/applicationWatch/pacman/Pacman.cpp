#include "Pacman.h"

#include <array>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <nlohmann/json.hpp>

#include "../cacheApplication/buildCacheFolder.h"

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

        parseDotDesktopFiles(dotDesktopFile ,path);
    }
}

void Pacman::parseDotDesktopFiles(const vector<string>& dotDesktopFile ,const std::string filePath){
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

            std::optional<float> number = NULL;

            try {
                number = std::stof(value);
            }
            catch (const std::invalid_argument& e) {
                number = NULL;
            }
            catch (const std::out_of_range& e) {
                number = NULL;
            }

            desktop_info.applicationVersion = number;
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
        }else if (key == "mimetype") {
            desktop_info.mimeType = value;
        }else if (key == "categories") {

            vector<string> category;

            for (const char findBreak : value) {
                if (findBreak == ';') {
                    category.push_back(value.substr(0, value.find_first_of(';')));
                    value.erase(0, value.find_first_of(';') + 1);
                }
            }

            desktop_info.categories = category;
        }else if (key == "keywords") {
            desktop_info.keywords = value;
        } else if (key == "terminal") {
            desktop_info.runApplicationInTerminal = value == "true";
        }
    }

    desktop_info.dotDesktopFilePath = filePath;

    this->applications.push_back(desktop_info);
}

Pacman::Pacman(){
    Pacman_application_handel_files pacman_application_handel_files;

    this->filePaths = pacman_application_handel_files.getApplicationPaths();

    const vector<string> paths = this->getAllPathForDotDesktopFiles();

    filterOutApplicationInformation(paths);
}

void Pacman::writeIntoCacheFile() const{


    nlohmann::json jsonObj = nlohmann::json::array();

    for (const auto & application : applications) {
        if (application.applicationType == "Application" && !application.deleted && application.applicationName != "Unknown" && !application.doNotDisplay) {
            nlohmann::json json_object;

            json_object["dotDesktopFilePath"] = application.dotDesktopFilePath;
            json_object["applicationName"] = application.applicationName;
            json_object["applicationVersion"] = application.applicationVersion;
            json_object["genericApplicationName"] = application.genericApplicationName;
            json_object["applicationDescription"] = application.applicationDescription;
            json_object["applicationIcons"] = application.applicationIcons;
            json_object["categories"] = application.categories;
            json_object["keywords"] = application.keywords;
            json_object["mimeType"] = application.mimeType;

            jsonObj.push_back(json_object);
        }
    }

    std::ofstream file(BuildCacheFolder::getCacheFilePath());

    file << jsonObj.dump(4);
}

