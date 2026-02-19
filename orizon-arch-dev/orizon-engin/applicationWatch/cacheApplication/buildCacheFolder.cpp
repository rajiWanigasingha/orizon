//
// Created by rajindawanigasingha on 2/19/26.
//

#include "buildCacheFolder.h"

#include <filesystem>
#include <fstream>
#include <iostream>

std::string BuildCacheFolder::getCacheFolder(){
    const std::string home = getenv("HOME");
    const std::string cache = home + "/.cache/applicationWatchCache/";

    if (!std::filesystem::exists(cache)) {
        std::filesystem::create_directory(cache);
    }

    return cache;
}

void BuildCacheFolder::createDbFile() {

    const std::string cacheFolder = getCacheFolder();

    if (const std::string dbFile = cacheFolder + "applicationWatchCache.json"; !std::filesystem::exists(dbFile)) {
        if (const std::ofstream file(dbFile, std::ios::out | std::ios::app); !file) {
            std::cerr << "Failed to create file: " << dbFile << "\n";
            return;
        }

        std::cout << "Created DB file at: " << dbFile << "\n";
    }
}

void BuildCacheFolder::buildCache(){
    createDbFile();
}

std::string BuildCacheFolder::getCacheFilePath(){
    return getCacheFolder() + "applicationWatchCache.json";
}
