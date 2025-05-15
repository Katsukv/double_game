//
// Created by katsu on 09.04.2025.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#pragma once

#include <QPainter>
#include <QPixmap>

class Platform {
public:
    Platform(float x, float y);

    [[nodiscard]] QRect GetRect() const;
    [[nodiscard]] QRect GetRectStandartSpring() const;
    [[nodiscard]] QRect GetRectUsedSpring() const;

    void upd_y_coordinates(float delta_y);

    void add_x_velocity(float x);
    void add_y_velocity(float y);
    [[nodiscard]] float Get_y_velocity() const { return y_velocity; }
    [[nodiscard]] float Get_x_velocity() const { return x_velocity; }
    bool Is_moving_y() { return is_moving_y; }
    bool Is_moving_x() { return is_moving_x; }
    [[nodiscard]] float Get_up_border() const { return up_border; }

    void add_platform_to_painter(QPainter &painter) const;

    [[nodiscard]] float Get_x() const { return m_x; }
    [[nodiscard]] float Get_y() const { return m_y; }
    [[nodiscard]] float Get_height() const { return m_height; }
    [[nodiscard]] float Get_width() const { return m_width; }

    void add_spring(float x);
    void use_spring() {used_spring = true;}
    bool is_have_spring() { return is_spring; }
    [[nodiscard]] float Get_x_spring() const { return m_x + x_spring; }
    [[nodiscard]] float Get_y_spring() const { return m_y - spring_standart_height; }
    [[nodiscard]] float Get_height_spring() const { return spring_standart_height; }
    [[nodiscard]] float Get_width_spring() const { return spring_width; }

    void move(float deltaTime);

private:
    float m_x, m_y;
    float m_height = 10, m_width = 45;

    float x_velocity, y_velocity;
    float right_border, left_border;
    float up_border, down_border;
    float vertical_border = 140;
    bool is_moving_x = false;
    bool is_moving_y = false;

    bool is_spring = 0;
    float x_spring = 0;
    bool used_spring = 0;
    float spring_width = 10;
    float spring_standart_height = 7;
    float spring_used_height = 14;

    bool is_fake = 0;
    float fall_in_first_state = 0;
    float fall_in_second_state = 0;
    float fall_in_third_state = 0;

    QPixmap platform_pixmap;
    QPixmap string_pixmap;
};

#endif //PLATFORM_H