#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "QCoreApplication"
#include "QGraphicsRectItem"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QGuiApplication"
#include "QKeyEvent"
#include "QRect"
#include "QScreen"
#include "QTimer"

class MainView : public QGraphicsView {
    Q_OBJECT
    QGraphicsScene* scene;

public:
    explicit MainView(QWidget* p = nullptr)
        : QGraphicsView(p)
        , scene(nullptr)
    {
        this->setWindowTitle("Blend Viewer");
        this->setBackgroundBrush(Qt::black);
        this->setStyleSheet("border: 0px;");

        qreal w = 854;
        qreal h = 480;
        QGraphicsScene* scene = new QGraphicsScene(0, 0, w, h, this);
        scene->setBackgroundBrush(Qt::black);
        this->setScene(scene);

        QScreen* screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int screenW = screenGeometry.width();
        int screenH = screenGeometry.height();
        this->setGeometry((screenW / 2) - (w / 2), (screenH / 2) - (h / 2), w, h);

        scene->addLine(200, 10, w - 200, h / 2 - 30, QPen(Qt::white));
        scene->addLine(200, h / 2 - 30, w - 200, 10, QPen(Qt::white));
        scene->addLine(100, h / 2, w - 100, h / 2, QPen(Qt::white));
        scene->addLine(100, h / 2, w / 2, h - 20, QPen(Qt::white));
        scene->addLine(w - 100, h / 2, w / 2, h - 20, QPen(Qt::white));
    }

protected:
    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_Q) {
            QCoreApplication::quit();
        }
    }
};

#endif // MAIN_VIEW_H
