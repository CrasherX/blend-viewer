#include "MainView.h"
#include "QApplication"
#include "QTimer"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainView mainView;
    mainView.show();


//    QTimer::singleShot(2500, &app, &app.quit);


    return app.exec();
}

