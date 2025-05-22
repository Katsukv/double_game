//
// Created by katsu on 14.05.2025.
//
#include "../hdr/GameWidget.h"
#include "../hdr/Generator.h"
#include "../hdr/RemoveUnnecessaryPlatforms.h"

GameWidget::GameWidget(QWidget* parent)
    : QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    m_platforms.emplace_back(Platform(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 3 * 2));

    int fontId = QFontDatabase::addApplicationFont("../sprites/Doodle Jump/options/DoodleJump.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = QFont(fontFamily, 20);
    customFont.setBold(true);
}

void GameWidget::mousePressEvent(QMouseEvent* event) {

    if (event->button() == Qt::LeftButton) {
        QPoint clickPoint = event->pos();
        m_doodle = Doodle(clickPoint.x(), clickPoint.y());
    }
    else if (event->button() == Qt::RightButton) {
        QPoint clickPoint = event->pos();
        m_platforms.emplace_back(Platform(clickPoint.x(), clickPoint.y()));
        m_platforms.back().add_spring(2);
        m_platforms.back().add_y_velocity(50);
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

    if (m_doodle.IsLost()) {
        if (m_doodle.Get_y()<SCREEN_SIZE_Y*0.4) {
            emit PlayerLost((int)score);
        }
    }

    if (m_platforms.back().Get_y() > -3*SCREEN_SIZE_X) {
        Generate(m_platforms, score);
    }

    float new_min_doodle_y_pos = min_doodle_y_pos;
    m_doodle.move(deltaTime, m_platforms, new_min_doodle_y_pos);

    if (m_doodle.IsLost()) {

        RemoveUnnecessaryPlatforms(m_platforms);

        if (old_y_pos < 0) {
            old_y_pos = SCREEN_SIZE_Y - m_doodle.Get_height();
        }

        float delta = old_y_pos - m_doodle.Get_y();

        m_doodle.Upd_y_coordinates(delta*1.3);

        for (Platform &platform: m_platforms) {
            platform.upd_y_coordinates(delta*1.3);
        }
        old_y_pos = m_doodle.Get_y();
        return;

    }

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

    for (const Platform &platform: m_platforms) {
        platform.add_platform_to_painter(painter);
    }

    painter.setPen(Qt::red);
    painter.setFont(customFont);
    painter.drawText(250, 25, QString::number((int)score));

    painter.drawPixmap(m_doodle.Get_x(), m_doodle.Get_y(), m_doodle.GetPixmap());

    painter.end();
}