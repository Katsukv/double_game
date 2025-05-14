//
// Created by katsu on 09.04.2025.
//

#include "../hdr/MainWindow.h"

#include "iostream"
#include "../hdr/Globals.h"


MainWindow::MainWindow(QApplication* app, QWidget* parent)
    : QMainWindow(parent), m_app(app)
{
    m_app->setWindowIcon(QIcon("..//sprites//Doodle Jump//ach-race-legend@2x.png"));
    this->setGeometry(300, 300, SCREEN_SIZE_X, SCREEN_SIZE_Y);

    m_menu = new MenuWidget(this);
    setCentralWidget(m_menu);

    connect(m_menu, &MenuWidget::playButtonClicked, this, &MainWindow::handlePlayButton);
}

void MainWindow::cleanup() {
    // Удаляем текущий центральный виджет
    if (centralWidget()) {
        takeCentralWidget(); // Убираем виджет из иерархии без удаления
    }

    // Явное удаление виджетов в правильном порядке
    if (m_game) {
        delete m_game;
        m_game = nullptr;
    }

    if (m_menu) {
        delete m_menu;
        m_menu = nullptr;
    }
}

void MainWindow::handlePlayButton() {
    cleanup(); // Очищаем перед созданием нового виджета

    m_game = new GameWidget(this);
    setCentralWidget(m_game);
    m_currentState = GameState::PLAYING;
    m_game->setFocus();
}

void MainWindow::run() {
    uint64_t lastTime = QDateTime::currentMSecsSinceEpoch();

    while (m_isRunning) {
        m_app->processEvents();

        uint64_t currentTime = QDateTime::currentMSecsSinceEpoch();
        float deltaTime = float(currentTime - lastTime) / SIMULATION_SPEED;
        lastTime = currentTime;

        switch (m_currentState) {
            case GameState::MENU:
                if (m_menu) m_menu->update(deltaTime);
                break;
            case GameState::PLAYING:
                if (m_game) m_game->update(deltaTime);
                break;
        }

        update();
    }

    cleanup(); // Дополнительная очистка при выходе из run()
}

void MainWindow::closeEvent(QCloseEvent* event) {
    m_isRunning = false;

    // Даем время на завершение цикла

    cleanup();
    close();
}

MainWindow::~MainWindow() {
    cleanup();
}