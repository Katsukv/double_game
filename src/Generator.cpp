//
// Created by katsu on 15.05.2025.
//

#include "../hdr/Generator.h"
#include "../hdr/RemoveUnnecessaryPlatforms.h"

using std::cout;
using std::endl;

std::mt19937_64 gen(std::chrono::system_clock().now().time_since_epoch().count());

void Generate(vector<Platform> &platforms, float score) {

    RemoveUnnecessaryPlatforms(platforms);

    float dop = 0;

    std::uniform_real_distribution<float> unif(0, 1);

    // cout << "Gen\n";
    // cout << score << endl;

    while (dop < SCREEN_SIZE_Y * 3) {
        float y = platforms.back().Get_y();

        float max_h = VELOCITY_AFTER_REBOUND*VELOCITY_AFTER_REBOUND/2/Y_ACCELERATION;

        if (platforms.back().is_have_spring()) {
            max_h = VELOCITY_AFTER_REBOUND_SPRING*VELOCITY_AFTER_REBOUND_SPRING/2/Y_ACCELERATION;
        }
        else if (platforms.back().Is_moving_y()) {
            max_h *= 0.9;
        }

        max_h *= 0.95;

        // cout << y << ' ' << max_h << ' ' << std::min(0.98, score / 10000.0) << endl;

        float base_h = max_h * std::min(0.98, score / 10000.0);
        float h = base_h + unif(gen) * (max_h - base_h);

        // cout << "h = " << h << endl;

        float w = platforms.back().Get_width();
        float w_s = platforms.back().Get_width_spring();

        platforms.emplace_back(Platform(unif(gen) * (SCREEN_SIZE_X - w), y - h));

        // cout << (std::max(0.1, 1 - score / 10000.0)) << endl;
        if ((unif(gen) / (std::max(0.1, 1 - score / 10000.0))) > 0.9) {
            platforms.back().add_spring(unif(gen) * (w - w_s));
        }

        if ((unif(gen) / (std::max(0.1, 1 - score / 10000.0))) > 0.9) {

            // cout << "add_velocity: " << std::max(0.1, (1.0 - score / 10000.0)) << endl;
            if (unif(gen) > 0.5) {
                platforms.back().add_y_velocity(15 + std::min(30.0, 30 * unif(gen) / std::max(0.1, 1 - score / 10000.0)) );
            } else {
                platforms.back().add_x_velocity(15 + std::min(30.0, 30 * unif(gen) / std::max(0.1, 1 - score / 10000.0)) );
            }
        }

        dop += h;
    }
}