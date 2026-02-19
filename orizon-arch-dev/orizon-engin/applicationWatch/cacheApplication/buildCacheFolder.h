//
// Created by rajindawanigasingha on 2/19/26.
//

#ifndef APPLICATIONWATCH_BUILDCACHEFOLDER_H
#define APPLICATIONWATCH_BUILDCACHEFOLDER_H
#include <string>


class BuildCacheFolder {
    private:
        static std::string getCacheFolder();
        static void createDbFile();

    public:
        static void buildCache();
        static std::string getCacheFilePath();
};


#endif //APPLICATIONWATCH_BUILDCACHEFOLDER_H