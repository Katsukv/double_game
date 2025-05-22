//
// Created by katsu on 09.04.2025.
//

#include "../hdr/MainWindow.h"
#include "../hdr/Globals.h"


MainWindow::MainWindow(QApplication* app, QWidget* parent)
    : QMainWindow(parent), m_app(app)
{
    m_app->setWindowIcon(QIcon("..//sprites//Doodle Jump//ach-race-legend@2x.png"));
    this->setGeometry(300, 300, SCREEN_SIZE_X, SCREEN_SIZE_Y);

    QFile file("scores.csv");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() >= 3) {
                    m_high_score = std::max(m_high_score, parts[1].toInt());
            }
        }
        file.close();
    }
    StartMenu();
}

void MainWindow::cleanup() {
    QWidget* current = takeCentralWidget();
    if (current) {
        current->deleteLater();
    }

    m_game = nullptr;
    m_menu = nullptr;
}

void MainWindow::handlePlayButton() {
    cleanup();

    m_game = new GameWidget(this);
    setCentralWidget(m_game);
    connect(m_game, &GameWidget::PlayerLost, this, &MainWindow::PlayerLost);
    m_currentState = GameState::PLAYING;
    m_game->setFocus();
}

void MainWindow::StartMenu() {

    cleanup();

    m_menu = new MenuWidget(this);
    setCentralWidget(m_menu);

    connect(m_menu, &MenuWidget::playButtonClicked, this, &MainWindow::handlePlayButton);

    m_currentState = GameState::MENU;
    m_menu->setFocus();
}

void MainWindow::PlayerLost(int score) {

    cleanup();

    m_high_score = std::max(m_high_score, score);
    m_end_game = new EndGameWidget( score, m_high_score, this);
    setCentralWidget(m_end_game);



    connect(m_end_game, &EndGameWidget::playAgainButtonClicked, this, &MainWindow::handlePlayButton);
    connect(m_end_game, &EndGameWidget::menuButtonClicked, this, &MainWindow::StartMenu);



    m_currentState = GameState::ENDGAME;
    m_end_game->setFocus();
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
            case GameState::ENDGAME:
                if (m_end_game) m_end_game->update(deltaTime);
            break;
        }

        update();
    }

    cleanup();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    m_isRunning = false;

    cleanup();
    close();
}

MainWindow::~MainWindow() {
    cleanup();
}