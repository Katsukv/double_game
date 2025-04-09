//
// Created by katsu on 09.04.2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QDateTime>
#include <QMouseEvent>
#include <QApplication>

#include "PainterWidget.h"

class MainWindow: public QMainWindow{
public:

    MainWindow(QApplication* app);
    void run();

protected:
    void closeEvent(QCloseEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QApplication* m_app;
    PainterWidget* m_painterWidget;
    Doodle m_doodle = Doodle(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2,
    "..//sprites//Doodle Jump//blue-lik-right-odskok@2x.png",
            "..//sprites//Doodle Jump//blue-lik-left-odskok@2x.png");

    std::vector<Platform> m_platforms;
    bool m_isRunning = true;
    float min_doodle_y_pos = SCREEN_SIZE_Y / 3;
    float score = 0;
};

#endif //MAINWINDOW_H
