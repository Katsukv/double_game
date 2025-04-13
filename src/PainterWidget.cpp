//
// Created by katsu on 09.04.2025.
//

#include "../hdr/PainterWidget.h"

PainterWidget::PainterWidget(QWidget *parrent, const Doodle &doodle, const std::vector<Platform> &platforms, const float &score) :
        QWidget(parrent), m_doodle(doodle), m_platforms(platforms), m_score(score) {}

void PainterWidget::paintEvent(QPaintEvent *event) {
        QPainter painter(this);

        QPixmap background;
        background.load("..//sprites//Doodle Jump//bck@2x.png");

        painter.drawPixmap(0, 0, background);

        painter.drawPixmap(m_doodle.Get_x(), m_doodle.Get_y(), m_doodle.GetPixmap());

        painter.setBrush(Qt::black);
        for (const Platform &platform: m_platforms) {
                painter.drawRect(platform.GetRect());
        }

        painter.drawText(270, 20, QString::number((int)m_score));

        painter.end();
}