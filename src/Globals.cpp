//
// Created by katsu on 15.05.2025.
//
#include "../hdr/Globals.h"

const int SCREEN_SIZE_X = 640/2;
const int SCREEN_SIZE_Y = 1024/2;
const int SIMULATION_SPEED = 300;

std::string path_to_LDoodle = "..//sprites//Doodle Jump//blue-lik-left-odskok@2x.png";
std::string path_to_RDoodle = "..//sprites//Doodle Jump//blue-lik-right-odskok@2x.png";
std::string path_to_standart_platform = "..//sprites//Doodle Jump//platform.png";
std::string path_to_moving_platform = "..//sprites//Doodle Jump//platform-moving.png";
std::string path_to_fall_platform_zero_state = "";
std::string path_to_fall_platform_first_state = "";
 std::string path_to_fall_platform_second_state = "";
std::string path_to_fall_platform_third_state = "";
std::string path_to_standart_spring = "";
std::string path_to_used_spring = "";
std::string path_to_background = "..//sprites//Doodle Jump//bck@2x.png";
std::string path_to_menu_background = "..//sprites//Doodle Jump//Default@2x.png";

const float VELOCITY_AFTER_REBOUND = -210;
const float VELOCITY_AFTER_REBOUND_SPRING = -370;
const float Y_ACCELERATION = 120;
