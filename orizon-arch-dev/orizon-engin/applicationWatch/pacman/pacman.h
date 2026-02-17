//
// Created by rajindawanigasingha on 2/17/26.
//

#ifndef APPLICATIONWATCH_PACMAN_H
#define APPLICATIONWATCH_PACMAN_H
#include <array>
#include <string>

using namespace std;

namespace Desktop_Application{
    struct Desktop_Info {
        string applicationName;
        string applicationDescription;
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

class pacman {
    private:
        array<string ,3> filePaths;


    public:
        pacman();


};


#endif //APPLICATIONWATCH_PACMAN_H