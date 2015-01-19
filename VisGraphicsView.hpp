#ifndef VISGRAPHICSVIEW_HPP
#define VISGRAPHICSVIEW_HPP

// Parent class
#include <QGraphicsView>

// Member classes
#include <VisGraphicsScene.hpp>

class VisGraphicsView : public QGraphicsView
{
public:
    VisGraphicsView(VisGraphicsScene* vis_scene_, QWidget* parent = 0);

    void mousePressEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);


private:
    VisGraphicsScene* vis_scene;
};

#endif // VISGRAPHICSVIEW_HPP
