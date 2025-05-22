//
// Created by katsu on 22.05.2025.
//

#include "../hdr/RemoveUnnecessaryPlatforms.h"
#include "../hdr/Globals.h"

void RemoveUnnecessaryPlatforms(std::vector<Platform> &platforms) {
    std::vector<Platform> new_platforms;

    for (Platform &p : platforms) {
        if (p.Get_y() > SCREEN_SIZE_Y) continue;

        new_platforms.push_back(p);
    }

    platforms = new_platforms;
}