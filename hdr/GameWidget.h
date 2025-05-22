#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QFontDatabase>
#include <QFont>

#include "Doodle.h"
#include "Globals.h"
#include "Platform.h"

class GameWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameWidget(QWidget* parent = nullptr);
    void update(double deltaTime);
signals:
    void PlayerLost(int curr_score = 0);
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    Doodle m_doodle = Doodle(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
    std::vector<Platform> m_platforms;
    float min_doodle_y_pos = SCREEN_SIZE_Y / 3;
    float score = 0;
    float old_y_pos = -1;
    QFont customFont;
};

#endif // GAMEWIDGET_H