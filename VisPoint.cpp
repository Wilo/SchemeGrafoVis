#include "VisPoint.hpp"

#include <QBrush>

VisPoint::VisPoint(double x, double y, QGraphicsItem* parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setRect(x,y,w,h);
    setZValue(30);
    setBrush(QBrush(QColor(0,127,0,127)));
}

QPointF VisPoint::vis_pos()
{
    return (pos()+QPointF(w/2.0, h/2.0));
}
