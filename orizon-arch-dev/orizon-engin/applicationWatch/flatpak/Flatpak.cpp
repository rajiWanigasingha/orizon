//
// Created by rajindawanigasingha on 2/19/26.
//

#include "Flatpak.h"

#include <string>

void Flatpak::getFlatpakInfo(){

    std::string flatpakCMD = R"(flatpak list --app --columns=name,application,version,branch,origin,description \
        | jq -R -s '
        split("\n")[:-1] |
        map(split("\t")) |
        map({
          name: .[0],
          application: .[1],
          version: .[2],
          branch: .[3],
          origin: .[4],
          description: .[5]
        })
        ')";



}
