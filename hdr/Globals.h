//
// Created by katsu on 09.04.2025.
//

#ifndef GLOBALS_H
#define GLOBALS_H

#pragma once
extern const int SCREEN_SIZE_X;
extern const int SCREEN_SIZE_Y;
extern const int SIMULATION_SPEED;

extern const float VELOCITY_AFTER_REBOUND;
extern const float VELOCITY_AFTER_REBOUND_SPRING;
extern const float Y_ACCELERATION;

#include <string>

extern std::string path_to_LDoodle;
extern std::string path_to_RDoodle;
extern std::string path_to_standart_platform;
extern std::string path_to_moving_platform;
extern std::string path_to_fall_platform_zero_state;
extern std::string path_to_fall_platform_first_state;
extern std::string path_to_fall_platform_second_state;
extern std::string path_to_fall_platform_third_state;
extern std::string path_to_standart_spring;
extern std::string path_to_used_spring;
extern std::string path_to_background;
extern std::string path_to_menu_background;


#endif //GLOBALS_H