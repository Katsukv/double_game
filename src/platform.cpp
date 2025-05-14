//
// Created by katsu on 09.04.2025.
//

#include "../hdr/Platform.h"

::Platform::Platform(float x, float y): m_x(x), m_y(y) {}

void Platform::upd_y_coordinates(float delta_y) {
    m_y += delta_y;
}

QRect Platform::GetRect() const {
    return QRect(m_x, m_y, m_width, m_height);
}