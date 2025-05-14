//
// Created by katsu on 14.05.2025.
//
#include "../hdr/GameWidget.h"

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
}

void GameWidget::mousePressEvent(QMouseEvent* event) {

    if (event->button() == Qt::LeftButton) {
        QPoint clickPoint = event->pos();
        m_doodle = Doodle(clickPoint.x(), clickPoint.y(), "..//sprites//Doodle Jump//blue-lik-right-odskok@2x.png",
            "..//sprites//Doodle Jump//blue-lik-left-odskok@2x.png");
    }
    else if (event->button() == Qt::RightButton) {
        QPoint clickPoint = event->pos();
        m_platforms.emplace_back(Platform(clickPoint.x(), clickPoint.y()));
    }
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    if(event->isAutoRepeat()) return;

    switch(event->key()) {
        case Qt::Key_Left:
            m_doodle.StartMovingLeft();
        break;
        case Qt::Key_Right:
            m_doodle.StartMovingRight();
        break;
        default:
            break;
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent* event) {
    if(event->isAutoRepeat()) return;

    switch(event->key()) {
        case Qt::Key_Left:
            m_doodle.StopMovingLeft();
        break;
        case Qt::Key_Right:
            m_doodle.StopMovingRight();
        break;
        default:
            break;
    }
}

void GameWidget::update(double deltaTime) {
    float new_min_doodle_y_pos = min_doodle_y_pos;
    m_doodle.move(deltaTime, m_platforms, new_min_doodle_y_pos);

    score += (min_doodle_y_pos - new_min_doodle_y_pos) / 3;

    m_doodle.Upd_y_coordinates(min_doodle_y_pos - new_min_doodle_y_pos);

    for (Platform &platform: m_platforms) {
        platform.upd_y_coordinates(min_doodle_y_pos - new_min_doodle_y_pos);
    }
}

void GameWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QPixmap background;
    background.load("..//sprites//Doodle Jump//bck@2x.png");

    painter.drawPixmap(0, 0, background);

    painter.setBrush(Qt::black);
    for (const Platform &platform: m_platforms) {
        painter.drawRect(platform.GetRect());
    }

    painter.drawText(270, 20, QString::number((int)score));

    painter.drawPixmap(m_doodle.Get_x(), m_doodle.Get_y(), m_doodle.GetPixmap());

    painter.end();
}

