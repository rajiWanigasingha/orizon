//
// Created by rajindawanigasingha on 2/17/26.
//
#include "pacmanTest.h"
#include  "../pacman/Pacman.h"
#include <gtest/gtest.h>

TEST(PACMANTEST ,getHomeFile){

    Pacman_application_handel_files p;

    const string home = Pacman_application_handel_files::getHomePath();

    cout << home << endl;

    EXPECT_EQ(home, "/home/rajindawanigasingha");
}

TEST(PACMANTEST ,getApplicationPath){
    Pacman_application_handel_files p;

    for (const auto& application_path : p.getApplicationPaths()) {
        cout << application_path << endl;
    }
}

TEST(PACMAN ,getFilePaths){
    Pacman pacman;
}