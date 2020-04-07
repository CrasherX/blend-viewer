#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "iostream"
#include "QGraphicsScene"
#include "QGraphicsRectItem"
#include "QGraphicsView"
#include "QTimer"
#include "QKeyEvent"
#include "QCoreApplication"
#include "QGuiApplication"
#include "QScreen"
#include "QRect"

class MainView : public QGraphicsView
{
    Q_OBJECT
    QGraphicsScene *scene;

public:
    explicit MainView(QWidget *p = nullptr) : QGraphicsView(p), scene(nullptr)
    {
        this->setWindowTitle("Blend Viewer");
        this->setBackgroundBrush(Qt::black);
        this->setStyleSheet("border: 0px;");

        qreal w = 854;
        qreal h = 480;
        QGraphicsScene *scene = new QGraphicsScene(0, 0, w, h, this);
        scene->setBackgroundBrush(Qt::black);
        this->setScene(scene);

        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int screenW = screenGeometry.width();
        int screenH = screenGeometry.height();
        this->setGeometry((screenW / 2) - (w / 2), (screenH / 2) - (h / 2), w, h);


//        QGraphicsRectItem *rect = scene->addRect(0, 0, w, h, QPen(Qt::cyan), QBrush(Qt::red));
    }

protected:
     void keyPressEvent(QKeyEvent *event) override
     {
         if (event->key() == Qt::Key_Escape)
         {
             QCoreApplication::quit();
         }
     }
};

#endif // MAIN_VIEW_H
