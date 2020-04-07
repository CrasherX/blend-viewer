#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "iostream"
#include "QGraphicsScene"
#include "QGraphicsRectItem"
#include "QGraphicsView"
#include "QTimer"
#include "QKeyEvent"
#include "QCoreApplication"

class MainView : public QGraphicsView
{
    Q_OBJECT
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;

public:
    explicit MainView(QWidget *p = nullptr) : QGraphicsView(p), scene(nullptr), rect(nullptr)
    {
        this->setWindowTitle("Blend Viewer");
        this->setBackgroundBrush(Qt::black);
        this->setStyleSheet("border: 0px;");

        qreal w = 854;
        qreal h = 480;
        QGraphicsScene *scene = new QGraphicsScene(0, 0, w, h, this);
        scene->setBackgroundBrush(Qt::black);
        this->setScene(scene);
        this->fitInView(scene->itemsBoundingRect(), Qt::IgnoreAspectRatio);


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
