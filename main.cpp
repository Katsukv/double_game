#include <iostream>

#include "hdr/MainWindow.h"

using namespace std;

const int SCREEN_SIZE_X = 640/2;
const int SCREEN_SIZE_Y = 1024/2;
const int SIMULATION_SPEED = 300;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow wnd(&app);
    wnd.show();
    wnd.run();
    app.exit();
}