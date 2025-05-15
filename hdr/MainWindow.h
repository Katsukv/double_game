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

#include <QIcon>
#include "../hdr/Globals.h"
#include "../hdr/GameWidget.h"
#include "../hdr/MenuWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QApplication* app, QWidget* parent = nullptr);
    ~MainWindow();
    void run();

    public slots:
        void handlePlayButton();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void cleanup();

    QApplication* m_app;
    MenuWidget* m_menu = nullptr;
    GameWidget* m_game = nullptr;
    bool m_isRunning = true;

    enum class GameState { MENU, PLAYING };
    GameState m_currentState = GameState::MENU;
};

#endif //MAINWINDOW_H