//
// Created by katsu on 09.04.2025.
//

#include "../hdr/Doodle.h"
#include <cmath>


::Doodle::Doodle(float x, float y, QString path_to_RDoodle, QString path_to_LDoodle):
        m_x(x), m_y(y),
        y_velocity(0), y_acceleration(120),
        x_velocity(100),
        m_path_to_RDoodle(path_to_RDoodle),
        m_path_to_LDoodle(path_to_LDoodle) {
    m_pixmap.load(m_path_to_RDoodle);
    m_height = m_pixmap.height() / 2;
    m_width = m_pixmap.width() / 2;
}

QRect Doodle::GetRect() const {
    return QRect(m_x, m_y, m_width, m_width);
}

void Doodle::move(float deltaTime, std::vector<Platform> platforms, float &new_min_doodle_y_pos) {

    if (!m_isMoving){
        return;
    }
    float newX;

    Upd_x(newX, deltaTime);
    Intersection_with_vertical_boundaries(newX, deltaTime);

    float newY;
    float new_y_Velocity;

    Upd_y(newY, new_y_Velocity, deltaTime);
    Intersection_with_lower_boundaries(newY, new_y_Velocity, deltaTime);
    Intersection_with_platforms(newY, new_y_Velocity, newX, platforms, deltaTime);

    m_y = newY;
    y_velocity = new_y_Velocity;

    m_x = newX;

    new_min_doodle_y_pos = std::min(new_min_doodle_y_pos, m_y);
}


void Doodle::Upd_y_coordinates(const float &delta_y) {
    m_y += delta_y;
}

void Doodle::StartMovingRight() {
    m_isMoving_right = true;
    m_pixmap.load(m_path_to_RDoodle);
}

void Doodle::StopMovingRight() {
    m_isMoving_right = false;
}

void Doodle::StartMovingLeft() {
    m_isMoving_left = true;
    m_pixmap.load(m_path_to_LDoodle);
}

void Doodle::StopMovingLeft() {
    m_isMoving_left = false;
}

void Doodle::Upd_x(float &newX, const float &deltaTime) {
    newX = m_x;
    if (m_isMoving_right) {
        newX = m_x + x_velocity*deltaTime;
    }
    if (m_isMoving_left) {
        newX = m_x - x_velocity*deltaTime;
    }
}

void Doodle::Intersection_with_vertical_boundaries(float &newX, const float &deltaTime) {
    if (newX - m_width > SCREEN_SIZE_X) {
        newX = 0;
    }
    if (newX < 0) {
        newX = SCREEN_SIZE_X + m_width;
    }
}

void Doodle::Upd_y(float &newY, float &new_y_Velocity, const float &deltaTime) {
    newY = m_y + y_velocity*deltaTime + y_acceleration*deltaTime*deltaTime/2;
    new_y_Velocity = y_velocity + y_acceleration*deltaTime;
}

void Doodle::Intersection_with_lower_boundaries(float &newY, float &new_y_Velocity, const float &deltaTime) {
    if (newY > SCREEN_SIZE_Y){
        float len = SCREEN_SIZE_Y - m_y;
        float deltaTimeDown = (-y_velocity + sqrt(y_velocity*y_velocity + 2*y_acceleration*len)) / y_acceleration;
        float delatTimeUp = deltaTime - deltaTimeDown;

        newY = float(SCREEN_SIZE_Y) + velocity_after_rebound*delatTimeUp + y_acceleration*delatTimeUp*delatTimeUp/2;

        new_y_Velocity = velocity_after_rebound + y_acceleration*delatTimeUp;
    }
}

void Doodle::Intersection_with_platforms(float &newY, float &new_y_Velocity,
        float &newX, const std::vector<Platform> &platforms, const float &deltaTime) {

    for (const Platform &platform : platforms) {

        if (newX < platform.Get_x() || newX - m_width > platform.Get_x() + platform.Get_width()) continue;
        if (m_y > platform.Get_y() || newY < platform.Get_y() ) continue;

        float len = platform.Get_y() - m_y;

        float deltaTimeDown = (-y_velocity + sqrt(y_velocity*y_velocity + 2*y_acceleration*len)) / y_acceleration;
        float delatTimeUp = deltaTime - deltaTimeDown;

        newY = platform.Get_y() + velocity_after_rebound*delatTimeUp + y_acceleration*delatTimeUp*delatTimeUp/2;
        new_y_Velocity = velocity_after_rebound + y_acceleration*delatTimeUp;
    }
}