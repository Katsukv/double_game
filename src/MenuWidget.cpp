#include "../hdr/MenuWidget.h"
#include "../hdr/Globals.h"

#include <QDebug>

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

    optionsButton = new CustomButton(this);
    optionsButton->setImages(
        "../usefullSprites/options@2x.png",
        "../usefullSprites/options-on@2x.png",
        "../usefullSprites/options-on@2x.png"
        );
    optionsButton->setFixedSize(122,40);
    optionsButton->move(180, SCREEN_SIZE_Y - 180);
    connect(optionsButton, &QPushButton::clicked, this, &MenuWidget::showOptions);
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

    painter.drawPixmap(m_doodle.GetRect(), m_doodle.GetPixmap());
}

void MenuWidget::showHighScores() {
    HighScoresDialog* dialog = new HighScoresDialog(this);
    dialog->setWindowTitle("High Scores");
    dialog->setFixedSize(320, 400);
    dialog->loadScores();
    dialog->exec();
    delete dialog;
}

void MenuWidget::showOptions() {
    OptionsDialog* dialog = new OptionsDialog(this);
    connect(dialog, &OptionsDialog::setDefaultTheme, this, []() { emit SetOptionToDefolt(); });
    connect(dialog, &OptionsDialog::setSpaceTheme, this, []() { emit SetOptionToSpace(); });
    connect(dialog, &OptionsDialog::setHalloweenTheme, this, []() { emit SetOptionToHalloween(); });

    dialog->exec();
    delete dialog;
}

void SetOptionToDefolt() {
    path_to_LDoodle = "..//sprites//Defolt//left.png";
    path_to_RDoodle = "..//sprites//Defolt//right.png";
    path_to_standart_platform = "..//sprites//Defolt//platform.png";
    path_to_horizontal_moving_platform = "..//sprites//Defolt//horizontal moving platform.png";
    path_to_vertical_moving_platform = "..//sprites//Defolt//vertical moving platform.png";
    path_to_one_touch_platform = "../sprites/Defolt/one touch platform.png";
    path_to_standart_spring = "../sprites/Defolt/standart spring.png";
    path_to_used_spring = "../sprites/Defolt/used spring.png";
    path_to_background = "..//sprites//Defolt//bck.png";
}

void SetOptionToSpace() {
    // qDebug() << "SSpace\n";
    path_to_LDoodle = "..//sprites//Space//left.png";
    path_to_RDoodle = "..//sprites//Space//right.png";
    path_to_standart_platform = "..//sprites//Space//platform.png";
    path_to_horizontal_moving_platform = "..//sprites//Space//horizontal moving platform.png";
    path_to_vertical_moving_platform = "..//sprites//Space//vertical moving platform.png";
    path_to_one_touch_platform = "../sprites/Space/one touch platform.png";
    path_to_standart_spring = "../sprites/Space/standart spring.png";
    path_to_used_spring = "../sprites/Space/used spring.png";
    path_to_background = "..//sprites//Space//bck.png";

    // qDebug() << path_to_LDoodle;
}

void SetOptionToHalloween() {
    path_to_LDoodle = "..//sprites//Halloween//left.png";
    path_to_RDoodle = "..//sprites//Halloween//right.png";
    path_to_standart_platform = "..//sprites//Halloween//platform.png";
    path_to_horizontal_moving_platform = "..//sprites//Halloween//horizontal moving platform.png";
    path_to_vertical_moving_platform = "..//sprites//Halloween//vertical moving platform.png";
    path_to_one_touch_platform = "../sprites/Halloween/one touch platform.png";
    path_to_standart_spring = "../sprites/Halloween/standart spring.png";
    path_to_used_spring = "../sprites/Halloween/used spring.png";
    path_to_background = "..//sprites//Halloween//bck.png";
}
