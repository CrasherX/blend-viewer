#include "main.h"
#include "QApplication"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainView mainView;
    mainView.show();

//    QGraphicsView *view = new QGraphicsView();
//    view->setWindowTitle("Blend Viewer");
//    view->setBackgroundBrush(Qt::darkCyan);
//    view->resize(500, 500);
//    view->show();

//    QGraphicsScene *scene = new QGraphicsScene(0, 0, 400, 400, view);
//    scene->setBackgroundBrush(Qt::black);
//    view->setScene(scene);

//    QGraphicsRectItem *rect = scene->addRect(0, 0, 400, 400, QPen(Qt::white), QBrush(Qt::black));




    return app.exec();
}
