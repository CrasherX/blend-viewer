#ifndef MAIN_H
#define MAIN_H

#include "QGraphicsScene"
#include "QGraphicsRectItem"
#include "QGraphicsView"
#include "QTimer"
#include "iostream"

class MainView : public QGraphicsView
{
    Q_OBJECT
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;

public:
    explicit MainView(QWidget *p = nullptr) : QGraphicsView(p), scene(nullptr), rect(nullptr)
    {
        this->setWindowTitle("Blend Viewer");
        this->setBackgroundBrush(Qt::darkCyan);
        this->resize(500, 500);


        QGraphicsScene *scene = new QGraphicsScene(0, 0, 400, 400, this);
        this->setScene(scene);

        scene->setBackgroundBrush(Qt::black);


        rect = scene->addRect(0, 0, 400, 400, QPen(Qt::white), QBrush(Qt::black));

        QTimer::singleShot(2500, this, &MainView::moveItem);

    }


private slots:
    void moveItem()
    {
        rect->setBrush(QBrush(Qt::white));
    }
};


#endif // MAIN_H
