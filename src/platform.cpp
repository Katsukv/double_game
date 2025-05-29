//
// Created by katsu on 09.04.2025.
//

#include "../hdr/Platform.h"
#include "../hdr/Globals.h"

::Platform::Platform(float x, float y): m_x(x), m_y(y),
                                        x_velocity(0), y_velocity(0),
                                        left_border(x - 1), right_border(x + m_width + 1),
                                        up_border(y - 1), down_border(y + m_height + 1) {
    platform_pixmap.load(QString::fromStdString(path_to_standart_platform));
    m_width = platform_pixmap.width() / 2;
    m_height = platform_pixmap.height() / 2;
    spring_pixmap.load(QString::fromStdString(path_to_standart_spring));
    spring_width = spring_pixmap.width() / 2;
    spring_standart_height = spring_pixmap.height() / 2;
    right_border = x + m_width + 1;
    down_border = y + m_height + 1;
}


void Platform::add_platform_to_painter(QPainter &painter) const {

    if (is_OneTouch && is_Touch) return;

    painter.drawPixmap(static_cast<int>(m_x),
                      static_cast<int>(m_y),
                      static_cast<int>(m_width),
                      static_cast<int>(m_height),
                      platform_pixmap);

    if (is_spring) {
        if (used_spring) {
            painter.drawPixmap(m_x + x_spring, m_y - spring_used_height,spring_width, spring_used_height, spring_pixmap);
        } else {
            painter.drawPixmap(m_x + x_spring, m_y - spring_standart_height,spring_width, spring_standart_height, spring_pixmap);
        }
    }
}

void Platform::upd_y_coordinates(float delta_y) {
    m_y += delta_y;
    down_border += delta_y;
    up_border += delta_y;
}

void Platform::add_spring(float x) {
    is_spring = true;
    x_spring = x;
}

void Platform::add_x_velocity(float x) {
    platform_pixmap.load(QString::fromStdString(path_to_horizontal_moving_platform));
    is_moving_x = true;
    x_velocity = x;
    right_border = SCREEN_SIZE_X;
    left_border = 0;
}

void Platform::add_y_velocity(float y) {
    platform_pixmap.load(QString::fromStdString(path_to_vertical_moving_platform));
    is_moving_y = true;
    y_velocity = y;
    // up_border = m_y - half_vertical_border;
    down_border = m_y + vertical_border;
    left_border = 0;
}

void Platform::DoOneTouch() {
    platform_pixmap.load(QString::fromStdString(path_to_one_touch_platform));
    is_OneTouch = true;
}

void Platform::move(float deltaTime) {
    float newX, newY;
    newX = m_x + x_velocity * deltaTime;

    if (newX + m_width > right_border) {
        newX = right_border - m_width - (newX + m_width- right_border);
        x_velocity *= -1;
    }
    if (newX < left_border) {
        newX = left_border + (left_border - newX);
        x_velocity *= -1;
    }

    newY = m_y + y_velocity * deltaTime;

    if (newY < up_border) {
        newY = up_border + (up_border - newY);
        y_velocity *= -1;
    }
    if (newY + m_height > down_border) {
        newY = down_border - m_height - (newY + m_height- down_border);
        y_velocity *= -1;
    }

    m_x = newX;
    m_y = newY;


}


QRect Platform::GetRect() const {
    return QRect(m_x, m_y, m_width, m_height);
}

QRect Platform::GetRectStandartSpring() const {
    return QRect(m_x + x_spring, m_y - spring_standart_height, spring_width, spring_standart_height);
}

QRect Platform::GetRectUsedSpring() const {
    return QRect(m_x + x_spring, m_y - spring_used_height, spring_width, spring_used_height);
}

void Platform::use_spring() {
    used_spring = true;
    spring_pixmap.load(QString::fromStdString(path_to_used_spring));
    spring_used_height = spring_pixmap.height() / 2;
}

