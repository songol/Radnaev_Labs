#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    if (argc == 1) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    } else if (std::string(argv[1]) == "-test") {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
        return 0;
    }
}
