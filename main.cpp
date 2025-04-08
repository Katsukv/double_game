#include <iostream>
#include <vector>

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QDateTime>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QPixmap>


using namespace std;

#define SCREEN_SIZE_X 640/2
#define SCREEN_SIZE_Y 1024/2
#define SIMULATION_SPEED 300


class Platform {
public:
    Platform(float x, float y):
        m_x(x), m_y(y) {}

    QRect getRect() const { return QRect(m_x, m_y, m_width, m_height); }
    float get_x() const { return m_x; }
    float get_y() const { return m_y; }
    float get_height() const { return m_height; }
    float get_width() const { return m_width; }

    void upd_y_coordinates(const float &delta_y) {
        m_y += delta_y;
    }

private:
    float m_x, m_y;
    float m_height = 10, m_width = 45;
};


class Doodle {
public:

    Doodle(float x, float y, QString path_to_RDoodle, QString path_to_LDoodle):
        m_x(x), m_y(y),
        y_velocity(0), y_acceleration(50),
        x_velocity(0), x_acceleration(20),
        m_path_to_RDoodle(path_to_RDoodle),
        m_path_to_LDoodle(path_to_LDoodle) {
            m_pixmap.load(m_path_to_RDoodle);
            m_height = m_pixmap.height() / 2;
            m_width = m_pixmap.width() / 2;
    }

    int get_x() const {return m_x - m_width; }
    int get_y() const {return m_y - m_height; }

    QRect getRect() const { return QRect(m_x, m_y, m_pixmap.width(), m_pixmap.width()); }
    QPixmap getPixmap() const { return m_pixmap; }

    void move(float deltaTime, vector<Platform> platforms, float &new_min_doodle_y_pos) {

        if (!m_isMoving){
            return;
        }
        float newX;
        float new_x_Velocity;

        Upd_x(newX, new_x_Velocity, deltaTime);
        Intersection_with_vertical_boundaries(newX, new_x_Velocity, deltaTime);

        float newY;
        float new_y_Velocity;

        Upd_y(newY, new_y_Velocity, deltaTime);
        Intersection_with_lower_boundaries(newY, new_y_Velocity, deltaTime);
        Intersection_with_platforms(newY, new_y_Velocity, newX, platforms, deltaTime);

        m_y = newY;
        y_velocity = new_y_Velocity;

        m_x = newX;
        x_velocity = new_x_Velocity;

        new_min_doodle_y_pos = min(new_min_doodle_y_pos, m_y);
    }

    void upd_y_coordinates(const float &delta_y) {
        m_y += delta_y;
    }

    void startMovingRight() {
        m_isMoving_right = true;
        m_pixmap.load(m_path_to_RDoodle);
    }

    void stopMovingRight() {
        m_isMoving_right = false;
        x_velocity = 0;
    }

    void startMovingLeft() {
        m_isMoving_left = true;
        m_pixmap.load(m_path_to_LDoodle);
    }

    void stopMovingLeft() {
        m_isMoving_left = false;
        x_velocity = 0;
    }

private:
    void Upd_x(float &newX, float &new_x_Velocity, const float &deltaTime) {
        newX = m_x;
        new_x_Velocity = new_x_Velocity;

        if (m_isMoving_right) {

            newX = m_x + x_velocity*deltaTime + x_acceleration*deltaTime/2;
            new_x_Velocity = x_velocity + x_acceleration*deltaTime;

            new_x_Velocity = min(new_x_Velocity, max_x_Velocity);
        }
        if (m_isMoving_left) {
            newX = m_x - x_velocity*deltaTime - x_acceleration*deltaTime/2;
            new_x_Velocity = x_velocity + x_acceleration*deltaTime;

            new_x_Velocity = min(new_x_Velocity, max_x_Velocity);
        }
    }

    void Intersection_with_vertical_boundaries(float &newX, float &new_x_Velocity, const float &deltaTime) {
        if (newX - m_width > SCREEN_SIZE_X) {
            newX = 0;
        }
        if (newX < 0) {
            newX = SCREEN_SIZE_X + m_width;
        }
    }

    void Upd_y(float &newY, float &new_y_Velocity, const float &deltaTime) {
        newY = m_y + y_velocity*deltaTime + y_acceleration*deltaTime*deltaTime/2;
        new_y_Velocity = y_velocity + y_acceleration*deltaTime;
    }

    void Intersection_with_lower_boundaries(float &newY, float &new_y_Velocity, const float &deltaTime) {
        if (newY > SCREEN_SIZE_Y){
            float len = SCREEN_SIZE_Y - m_y;
            float deltaTimeDown = (-y_velocity + sqrt(y_velocity*y_velocity + 2*y_acceleration*len)) / y_acceleration;
            float delatTimeUp = deltaTime - deltaTimeDown;

            newY = float(SCREEN_SIZE_Y) + velocity_after_rebound*delatTimeUp + y_acceleration*delatTimeUp*delatTimeUp/2;

            new_y_Velocity = velocity_after_rebound + y_acceleration*delatTimeUp;
        }
    }

    void Intersection_with_platforms(float &newY, float &new_y_Velocity,
        float &newX, const vector<Platform> &platforms, const float &deltaTime) {

        for (const Platform &platform : platforms) {

            if (newX < platform.get_x() || newX - m_width > platform.get_x() + platform.get_width()) continue;
            if (m_y > platform.get_y() || newY < platform.get_y() ) continue;

            float len = platform.get_y() - m_y;

            float deltaTimeDown = (-y_velocity + sqrt(y_velocity*y_velocity + 2*y_acceleration*len)) / y_acceleration;
            float delatTimeUp = deltaTime - deltaTimeDown;

            newY = platform.get_y() + velocity_after_rebound*delatTimeUp + y_acceleration*delatTimeUp*delatTimeUp/2;
            new_y_Velocity = velocity_after_rebound + y_acceleration*delatTimeUp;
        }
    }

    float m_x, m_y, m_r;
    float m_height, m_width;
    float y_velocity, y_acceleration;
    float x_velocity, x_acceleration;
    float max_x_Velocity = 800;
    float velocity_after_rebound = -150;

    bool m_isMoving = 1;
    bool m_isMoving_right = 0;
    bool m_isMoving_left = 0;

    QString m_path_to_RDoodle;
    QString m_path_to_LDoodle;
    QPixmap m_pixmap;
};

class PainterWidget: public QWidget{
public:
    PainterWidget(QWidget* parrent, const Doodle& doodle, const vector<Platform>& platforms):
        QWidget(parrent), m_doodle(doodle), m_platforms(platforms) {}

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);

        QPixmap background;
        background.load("..//sprites//Doodle Jump//doodlestein-bck@2x.png");

        painter.drawPixmap(0, 0, background);

        painter.drawPixmap(m_doodle.get_x(), m_doodle.get_y(), m_doodle.getPixmap());

        painter.setBrush(Qt::black);
        for (const Platform &platform: m_platforms) {
            painter.drawRect(platform.getRect());
        }

        painter.end();
    }

private:
    const Doodle &m_doodle;
    const vector<Platform> &m_platforms;
};

class MainWindow: public QMainWindow{
public:
    MainWindow(QApplication* app):QMainWindow(), m_app(app){
        m_painterWidget = new PainterWidget(this, m_doodle, m_platforms);

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

            m_doodle.upd_y_coordinates(min_doodle_y_pos - new_min_doodle_y_pos);

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
                m_doodle.startMovingLeft();
                break;
            case Qt::Key_Right:
                m_doodle.startMovingRight();
                break;
        }
    }

    void keyReleaseEvent(QKeyEvent* event) override {
        if(event->isAutoRepeat()) return;

        switch(event->key()) {
            case Qt::Key_Left:
                m_doodle.stopMovingLeft();
                break;
            case Qt::Key_Right:
                m_doodle.stopMovingRight();
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
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wnd(&app);
    wnd.show();
    wnd.run();
    app.exit();
}