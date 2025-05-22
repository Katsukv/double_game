#include "../hdr/MenuWidget.h"
#include "../hdr/Globals.h"

MenuWidget::MenuWidget(QWidget* parent) : QWidget(parent) {
    m_platforms.push_back(Platform(35, 400));

    playButton = new CustomButton(this);
    playButton->setImages(
        "../usefullSprites/play@2x.png",
        "../usefullSprites/play-on@2x.png",
        "../usefullSprites/play-on@2x.png"
    );
    playButton->move((SCREEN_SIZE_X - playButton->width())/2, 150);
    connect(playButton, &QPushButton::clicked, this, &MenuWidget::playButtonClicked);

    highScoresButton = new CustomButton(this);
    highScoresButton->setImages(
        "../usefullSprites/scores.png",
        "../usefullSprites/scores-on@2x.png",
        "../usefullSprites/scores-on@2x.png"
    );
    highScoresButton->setFixedSize(122,40);
    highScoresButton->move(180, SCREEN_SIZE_Y - 130);
    connect(highScoresButton, &QPushButton::clicked, this, &MenuWidget::showHighScores);
}


void MenuWidget::update(double deltaTime) {
    // qDebug() << deltaTime;
    deltaTime = std::min(deltaTime, 0.1);
    float x;
    m_doodle.move(deltaTime, m_platforms, x);
}

void MenuWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPixmap background;
    if (background.load("..//sprites//Doodle Jump//Default@2x.png")) {
        painter.drawPixmap(0, 0, width(), height(), background);
    } else {
        painter.fillRect(rect(), QColor("#333333"));
    }

    for (const Platform &platform : m_platforms) {
        platform.add_platform_to_painter(painter);
    }

    painter.drawPixmap(m_doodle.Get_x(), m_doodle.Get_y(), m_doodle.GetPixmap());
}

void MenuWidget::showHighScores() {
    HighScoresDialog* dialog = new HighScoresDialog(this);
    dialog->setWindowTitle("High Scores");
    dialog->setFixedSize(320, 400);  // Фиксированный размер
    dialog->loadScores();
    dialog->exec();
    delete dialog;
}