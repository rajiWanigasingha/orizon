//
// Created by rajindawanigasingha on 2/17/26.
//

#ifndef APPLICATIONWATCH_PACMAN_H
#define APPLICATIONWATCH_PACMAN_H
#include <array>
#include <string>
#include <vector>

using namespace std;

namespace Desktop_Application{

    enum class ApplicationType {
        Application,
        Link,
        Directory
    };

    struct Desktop_Info {
        string applicationName;
        string genericApplicationName;
        string applicationDescription;
        ApplicationType applicationType;
        float applicationVersion;
        string applicationIcons;
        bool deleted;
        bool doNotDisplay;
        string onlyShowIn;
        string dontShowId;
        bool dbusActivatable;
        string tryExec;
        string executablePath;
        string path;
        bool runApplicationInTerminal;
        string actions;
        string mimeType;
        string categories;
        string keywords;
        bool startUpNotification;
        string startUpWMClass;
        bool PrefersNonDefaultGPU;
        bool SingleMainWindow;
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

        vector<string> getAllPathForDotDesktopFiles() const;

        static void filterOutApplicationInformation(const vector<string>& paths);

        static void parseDotDesktopFiles(const string& dotDesktopFile);

    public:
        Pacman();



};


#endif //APPLICATIONWATCH_PACMAN_H