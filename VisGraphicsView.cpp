#include "VisGraphicsView.hpp"

#include <QWheelEvent>
#include <QMenu>

VisGraphicsView::VisGraphicsView(VisGraphicsScene* vis_scene_, QWidget* parent)
    : QGraphicsView(parent), vis_scene(vis_scene_)
{
    setScene(vis_scene);
    setSceneRect(-2500,-2500,5000,5000);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void VisGraphicsView::mousePressEvent(QMouseEvent* event)
{
    if(vis_scene == NULL) return;

    switch(vis_scene->mode){
    case VisGraphicsScene::EDIT:
        setDragMode(QGraphicsView::ScrollHandDrag);
        break;
    case VisGraphicsScene::INSERT_VERTEX:
    case VisGraphicsScene::INSERT_EDGE:
    case VisGraphicsScene::INSERT_ARROW:
    case VisGraphicsScene::INSERT_LABEL:
        setDragMode(QGraphicsView::NoDrag);
        break;
    }
    QGraphicsView::mousePressEvent(event);
}

void VisGraphicsView::wheelEvent(QWheelEvent* event)
{
    QGraphicsView::wheelEvent(new QWheelEvent(event->posF(), event->delta()/10, event->buttons(),event->modifiers(),event->orientation()));
}
