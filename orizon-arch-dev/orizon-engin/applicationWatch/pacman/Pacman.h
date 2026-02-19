//
// Created by rajindawanigasingha on 2/17/26.
//

#ifndef APPLICATIONWATCH_PACMAN_H
#define APPLICATIONWATCH_PACMAN_H
#include <array>
#include <optional>
#include <string>
#include <vector>

using namespace std;

namespace Desktop_Application{
    struct Desktop_Info {
        std::string applicationType = "Unknown";
        std::string applicationName = "Unknown";
        std::optional<std::string> genericApplicationName;
        std::optional<std::string> applicationDescription;
        std::optional<float> applicationVersion;
        std::optional<std::string> applicationIcons;
        std::optional<bool> deleted;
        std::optional<bool> doNotDisplay;
        std::optional<bool> runApplicationInTerminal;
        std::optional<std::string> mimeType;
        std::optional<std::vector<std::string>> categories;
        std::optional<std::string> keywords;
    };

}

class Pacman_application_handel_files {
    private:
        string filePaths[3] = {
            "/usr/share/applications/",
            "/usr/local/share/applications/",
            "$HOME/.local/share/applications/"
        };

    public:
        static string getHomePath();
        array<string ,3> getApplicationPaths();
};

class Pacman {
    private:
        array<string ,3> filePaths;

        vector<Desktop_Application::Desktop_Info> applications;

        [[nodiscard]] vector<string> getAllPathForDotDesktopFiles() const;

        void filterOutApplicationInformation(const vector<string>& paths);

        void parseDotDesktopFiles(const vector<string>& dotDesktopFile);

    public:
        Pacman();

        void writeIntoCacheFile();



};


#endif //APPLICATIONWATCH_PACMAN_H