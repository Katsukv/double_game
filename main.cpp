#include <iostream>
#include <vector>

#include <QApplication>
#include <QMainWindow>
#include <QDateTime>
#include <QMouseEvent>
#include <QPixmap>


#include "Globals.h"
#include "Platform.h"
#include "Doodle.h"

using namespace std;

const int SCREEN_SIZE_X = 640/2;
const int SCREEN_SIZE_Y = 1024/2;
const int SIMULATION_SPEED = 300;

class PainterWidget: public QWidget{
public:
    PainterWidget(QWidget* parrent, const Doodle& doodle, const vector<Platform>& platforms, const float &score):
        QWidget(parrent), m_doodle(doodle), m_platforms(platforms), m_score(score) {}

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);

        QPixmap background;
        background.load("..//sprites//Doodle Jump//doodlestein-bck@2x.png");

        painter.drawPixmap(0, 0, background);

        painter.drawPixmap(m_doodle.Get_x(), m_doodle.Get_y(), m_doodle.GetPixmap());

        painter.setBrush(Qt::black);
        for (const Platform &platform: m_platforms) {
            painter.drawRect(platform.GetRect());
        }

        painter.drawText(270, 20, QString::number((int)m_score));

        painter.end();
    }

private:
    const Doodle &m_doodle;
    const vector<Platform> &m_platforms;
    const float &m_score;
};

class MainWindow: public QMainWindow{
public:
    MainWindow(QApplication* app):QMainWindow(), m_app(app){
        m_painterWidget = new PainterWidget(this, m_doodle, m_platforms, score);

        this->setGeometry(300, 300, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        this->setCentralWidget(m_painterWidget);
    }

    void run(){
        uint64_t time = QDateTime::currentMSecsSinceEpoch();
        while(m_isRunning){
            m_app->processEvents();
            uint64_t newTime = QDateTime::currentMSecsSinceEpoch();
            float deltaTime = float(newTime - time)/SIMULATION_SPEED;

            float new_min_doodle_y_pos = min_doodle_y_pos;
            m_doodle.move(deltaTime, m_platforms, new_min_doodle_y_pos);

            score += (min_doodle_y_pos - new_min_doodle_y_pos) / 3;

            m_doodle.Upd_y_coordinates(min_doodle_y_pos - new_min_doodle_y_pos);

            for ( Platform &platform: m_platforms) {
                platform.upd_y_coordinates(min_doodle_y_pos - new_min_doodle_y_pos);
            }

            this->repaint();
            time = newTime;
        }
    }

protected:
    void closeEvent(QCloseEvent *event) override {
        m_isRunning = false;
        QMainWindow::closeEvent(event);
    }

    void mousePressEvent(QMouseEvent* event) override{

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

    void keyPressEvent(QKeyEvent* event) override {
        if(event->isAutoRepeat()) return;

        switch(event->key()) {
            case Qt::Key_Left:
                m_doodle.StartMovingLeft();
                break;
            case Qt::Key_Right:
                m_doodle.StartMovingRight();
                break;
        }
    }

    void keyReleaseEvent(QKeyEvent* event) override {
        if(event->isAutoRepeat()) return;

        switch(event->key()) {
            case Qt::Key_Left:
                m_doodle.StopMovingLeft();
                break;
            case Qt::Key_Right:
                m_doodle.StopMovingRight();
                break;
        }
    }


private:
    QApplication* m_app;
    PainterWidget* m_painterWidget;
    Doodle m_doodle = Doodle(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2,
    "..//sprites//Doodle Jump//blue-lik-right-odskok@2x.png",
            "..//sprites//Doodle Jump//blue-lik-left-odskok@2x.png");

    vector<Platform> m_platforms;
    bool m_isRunning = true;
    float min_doodle_y_pos = SCREEN_SIZE_Y / 3;
    float score = 0;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wnd(&app);
    wnd.show();
    wnd.run();
    app.exit();
}