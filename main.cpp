#include <iostream>

#include "hdr/MainWindow.h"
#include "hdr/Globals.h"
#include <QApplication>

using namespace std;

const int SCREEN_SIZE_X = 640/2;
const int SCREEN_SIZE_Y = 1024/2;
const int SIMULATION_SPEED = 300;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    try {
        MainWindow wnd(&app);
        wnd.show();
        wnd.run();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}