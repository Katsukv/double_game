//
// Created by katsu on 09.04.2025.
//

#include "../hdr/Doodle.h"
#include "../hdr/Globals.h"


::Doodle::Doodle(float x, float y):
        m_x(x), m_y(y),
        y_velocity(0),
        x_velocity(100) {
    m_pixmap.load(QString::fromStdString(path_to_RDoodle));
    m_height = m_pixmap.height() / 2;
    m_width = m_pixmap.width() / 2;
}

QRect Doodle::GetRect() const {
    return QRect(m_x, m_y, m_width, m_width);
}

void Doodle::move(float deltaTime, std::vector<Platform> &platforms, float &new_min_doodle_y_pos) {

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
    m_pixmap.load(QString::fromStdString(path_to_RDoodle));
}

void Doodle::StopMovingRight() {
    m_isMoving_right = false;
}

void Doodle::StartMovingLeft() {
    m_isMoving_left = true;
    m_pixmap.load(QString::fromStdString(path_to_LDoodle));
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
    if (newX - m_width / 2 > SCREEN_SIZE_X) {
        newX = m_width / 2;
    }
    if (newX - m_width / 2 < 0) {
        newX = SCREEN_SIZE_X + m_width / 2;
    }
}

void Doodle::Upd_y(float &newY, float &new_y_Velocity, const float &deltaTime) {
    newY = m_y + y_velocity*deltaTime + Y_ACCELERATION*deltaTime*deltaTime/2;
    new_y_Velocity = y_velocity + Y_ACCELERATION*deltaTime;
}

void Doodle::Intersection_with_lower_boundaries(float &newY, float &new_y_Velocity, const float &deltaTime) {
    if (newY > SCREEN_SIZE_Y){
        lost = 1;
    }
}

void Doodle::Intersection_with_platforms(float &newY, float &new_y_Velocity,
        float &newX, std::vector<Platform> &platforms, const float &deltaTime) {

    for (Platform &platform : platforms) {

        Platform old_platform = platform;
        platform.move(deltaTime);

        if (platform.is_have_spring()) {
            if (newX >= platform.Get_x_spring() + platform.Get_width_spring() &&
                newX - m_width <= platform.Get_x_spring() &&
                m_y < old_platform.Get_y_spring() &&
                newY >= platform.Get_y_spring()) {

                float len = old_platform.Get_y_spring() - m_y;

                float deltaTimeDown = (-(y_velocity + platform.Get_y_velocity()) +
                    sqrt((y_velocity + platform.Get_y_velocity()) * (y_velocity + platform.Get_y_velocity())
                        + 2*Y_ACCELERATION*len)) / Y_ACCELERATION;

                float delatTimeUp = deltaTime - deltaTimeDown;

                newY = platform.Get_y_spring() + VELOCITY_AFTER_REBOUND_SPRING*delatTimeUp + Y_ACCELERATION*delatTimeUp*delatTimeUp/2;
                new_y_Velocity = VELOCITY_AFTER_REBOUND_SPRING + Y_ACCELERATION*delatTimeUp;

                platform.use_spring();

                continue;
            }
        }

        if (newX < platform.Get_x() || newX - m_width > platform.Get_x() + platform.Get_width()) continue;
        if (m_y > old_platform.Get_y() || newY < platform.Get_y() ) continue;

        float len = old_platform.Get_y() - m_y;

        float deltaTimeDown = (-(y_velocity + platform.Get_y_velocity()) +
            sqrt((y_velocity + platform.Get_y_velocity()) * (y_velocity + platform.Get_y_velocity())
                + 2*Y_ACCELERATION*len)) / Y_ACCELERATION;

        float delatTimeUp = deltaTime - deltaTimeDown;

        newY = platform.Get_y() + VELOCITY_AFTER_REBOUND*delatTimeUp + Y_ACCELERATION*delatTimeUp*delatTimeUp/2;
        new_y_Velocity = VELOCITY_AFTER_REBOUND + Y_ACCELERATION*delatTimeUp;
    }
}