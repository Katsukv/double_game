//
// Created by katsu on 09.04.2025.
//

#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#pragma once

#include <QWidget>

#include "Doodle.h"

class PainterWidget: public QWidget{
public:
    PainterWidget(QWidget* parrent, const Doodle& doodle, const std::vector<Platform>& platforms, const float &score);

    void paintEvent(QPaintEvent* event);

private:
    const Doodle &m_doodle;
    const std::vector<Platform> &m_platforms;
    const float &m_score;
};

#endif //PAINTERWIDGET_H
