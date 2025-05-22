//pacific mode
// no war, no death, peace only
// good
// morning
// vietnam

#include <iostream>
#include <QApplication>

#include "hdr/MainWindow.h"
#include "hdr/Globals.h"

using namespace std;

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