#include "../hdr/MenuWidget.h"
#include <QPainter>
#include <QFontDatabase>
#include <QVBoxLayout>
#include "../hdr/Globals.h"

#include <iostream>
MenuWidget::MenuWidget(QWidget* parent) : QWidget(parent) {
    m_platforms.push_back(Platform(50, 440));

    titleLabel = new QLabel("Doodle Jump", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { color: red; font: bold 30px; }");
    titleLabel->setGeometry((SCREEN_SIZE_X - 240)/2, 30, 240, 60);

    playButton = new CustomButton(this);
    playButton->setImages(
        "../usefullSprites/play@2x.png",
        "../usefullSprites/play-on@2x.png",
        "../usefullSprites/play-on@2x.png"
    );
    playButton->move((SCREEN_SIZE_X - playButton->width())/2, 150);

    // Только одно соединение!
    connect(playButton, &QPushButton::clicked, this, &MenuWidget::playButtonClicked);
}


void MenuWidget::update(double deltaTime) {
    float x;
    m_doodle.move(deltaTime, m_platforms, x);
    // std::cout << "upd\n" << std::endl;
}

void MenuWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPixmap background;
    if (background.load("../sprites/Doodle Jump/bck@2x.png")) {
        painter.drawPixmap(0, 0, width(), height(), background);
    } else {
        painter.fillRect(rect(), QColor("#333333"));
    }

    painter.setBrush(Qt::black);
    for (const Platform &platform : m_platforms) {
        painter.drawRect(platform.GetRect());
    }

    painter.drawPixmap(m_doodle.Get_x(), m_doodle.Get_y(), m_doodle.GetPixmap());
}