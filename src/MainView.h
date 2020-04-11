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
#include "iostream"

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

        w = 854;
        h = 480;
        scene = new QGraphicsScene(0, 0, w, h, this);
        scene->setBackgroundBrush(Qt::black);
        this->setScene(scene);

        QScreen* screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int screenW = screenGeometry.width();
        int screenH = screenGeometry.height();
        this->setGeometry((screenW / 2) - (w / 2), (screenH / 2) - (h / 2), w, h);
    }

    QGraphicsScene* getScene()
    {
        return scene;
    }

    qreal getW()
    {
        return w;
    }

    qreal getH()
    {
        return h;
    }

    void addLine(qreal x1, qreal y1, qreal x2, qreal y2, const QPen& pen = QPen())
    {
        // scale
        x1 = x1 * 100;
        x2 = x2 * 100;
        y1 = y1 * 100;
        y2 = y2 * 100;

        // normalize
        x1 = x1 + w / 2;
        x2 = x2 + w / 2;
        y1 = y1 + h / 2;
        y2 = y2 + h / 2;

        std::cout << "x1:" << x1 << " y1:" << y1 << " x2:" << x2 << " y2:" << y2 << std::endl;

        scene->addLine(x1, y1, x2, y2, pen);

        //    scene->addLine(200, 10, w - 200, h / 2 - 30, QPen(Qt::white));
        //    scene->addLine(200, h / 2 - 30, w - 200, 10, QPen(Qt::white));
        //    scene->addLine(100, h / 2, w - 100, h / 2, QPen(Qt::white));
        //    scene->addLine(100, h / 2, w / 2, h - 20, QPen(Qt::white));
        //    scene->addLine(w - 100, h / 2, w / 2, h - 20, QPen(Qt::white));
    }

protected:
    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_Q) {
            QCoreApplication::quit();
        }
    }

private:
    qreal w;
    qreal h;
};

#endif // MAIN_VIEW_H
