//
// Created by katsu on 09.04.2025.
//

#include "../hdr/MainWindow.h"

MainWindow::MainWindow(QApplication* app):QMainWindow(), m_app(app){

    app->setWindowIcon(QIcon("..//sprites//Doodle Jump//ach-race-legend@2x.png"));
    m_painterWidget = new PainterWidget(this, m_doodle, m_platforms, score);

    this->setGeometry(300, 300, SCREEN_SIZE_X, SCREEN_SIZE_Y);
    this->setCentralWidget(m_painterWidget);
}

void MainWindow::run() {
    uint64_t time = QDateTime::currentMSecsSinceEpoch();
    while(m_isRunning){
        m_app->processEvents();
        uint64_t newTime = QDateTime::currentMSecsSinceEpoch();
        float deltaTime = float(newTime - time)/SIMULATION_SPEED;

        float new_min_doodle_y_pos = min_doodle_y_pos;
        m_doodle.move(deltaTime, m_platforms, new_min_doodle_y_pos);

        score += (min_doodle_y_pos - new_min_doodle_y_pos) / 3;

        m_doodle.Upd_y_coordinates(min_doodle_y_pos - new_min_doodle_y_pos);

        for (Platform &platform: m_platforms) {
            platform.upd_y_coordinates(min_doodle_y_pos - new_min_doodle_y_pos);
        }

        this->repaint();
        time = newTime;
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    m_isRunning = false;
    QMainWindow::closeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent* event) {

    if (event->button() == Qt::LeftButton) {
        QPoint clickPoint = event->pos();
        m_doodle = Doodle(clickPoint.x(), clickPoint.y(), "..//sprites//Doodle Jump//blue-lik-right-odskok@2x.png",
            "..//sprites//Doodle Jump//blue-lik-left-odskok@2x.png");
    }
    else if (event->button() == Qt::RightButton) {
        QPoint clickPoint = event->pos();
        m_platforms.emplace_back(Platform(clickPoint.x(), clickPoint.y()));
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
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

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
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



