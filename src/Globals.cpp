//
// Created by katsu on 15.05.2025.
//
#include "../hdr/Globals.h"

const int SCREEN_SIZE_X = 640/2;
const int SCREEN_SIZE_Y = 1024/2;
const int SIMULATION_SPEED = 300;

std::string path_to_LDoodle = "..//sprites//Defolt//left.png";
std::string path_to_RDoodle = "..//sprites//Defolt//right.png";
std::string path_to_standart_platform = "..//sprites//Defolt//platform.png";
std::string path_to_horizontal_moving_platform = "..//sprites//Defolt//horizontal moving platform.png";
std::string path_to_vertical_moving_platform = "..//sprites//Defolt//vertical moving platform.png";
std::string path_to_one_touch_platform = "../sprites/Defolt/one touch platform.png";
std::string path_to_fall_platform_zero_state = "";
std::string path_to_fall_platform_first_state = "";
 std::string path_to_fall_platform_second_state = "";
std::string path_to_fall_platform_third_state = "";
std::string path_to_standart_spring = "../sprites/Defolt/standart spring.png";
std::string path_to_used_spring = "../sprites/Defolt/used spring.png";
std::string path_to_background = "..//sprites//Defolt//bck.png";
std::string path_to_menu_background = "..//sprites//Doodle Jump//Default@2x.png";

const float VELOCITY_AFTER_REBOUND = -210;
const float VELOCITY_AFTER_REBOUND_SPRING = -370;
const float Y_ACCELERATION = 120;
