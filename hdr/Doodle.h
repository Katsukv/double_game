//
// Created by katsu on 09.04.2025.
//

#ifndef DOODLE_H
#define DOODLE_H

#pragma once

#include "Globals.h"
#include "Platform.h"

class Doodle {
public:

    Doodle(float x, float y);

    float Get_x() const {return m_x - m_width; }
    float Get_y() const {return m_y - m_height; }

    QRect GetRect() const;
    QPixmap GetPixmap() const { return m_pixmap; }

    void move(float deltaTime, std::vector<Platform> &platforms, float &new_min_doodle_y_pos);

    void Upd_y_coordinates(const float &delta_y);

    void StartMovingRight();
    void StopMovingRight();
    void StartMovingLeft();
    void StopMovingLeft();

private:
    void Upd_x(float &newX, const float &deltaTime);
    void Intersection_with_vertical_boundaries(float &newX, const float &deltaTime);
    void Upd_y(float &newY, float &new_y_Velocity, const float &deltaTime);
    void Intersection_with_lower_boundaries(float &newY, float &new_y_Velocity, const float &deltaTime);
    void Intersection_with_platforms(float &newY, float &new_y_Velocity,
        float &newX, std::vector<Platform> &platforms, const float &deltaTime);

    float m_x, m_y;
    float m_height, m_width;
    float y_velocity;
    float x_velocity;
    bool m_isMoving = true;
    bool m_isMoving_right = false;
    bool m_isMoving_left = false;

    QPixmap m_pixmap;
};

#endif //DOODLE_H