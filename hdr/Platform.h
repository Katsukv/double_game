//
// Created by katsu on 09.04.2025.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#pragma once

#include <QPainter>

class Platform {
public:
    Platform(float x, float y);

    [[nodiscard]] QRect GetRect() const;

    void upd_y_coordinates(float delta_y);

    [[nodiscard]] float Get_x() const { return m_x; }
    [[nodiscard]] float Get_y() const { return m_y; }
    [[nodiscard]] float Get_height() const { return m_height; }
    [[nodiscard]] float Get_width() const { return m_width; }



private:
    float m_x, m_y;
    float m_height = 10, m_width = 45;
};

#endif //PLATFORM_H