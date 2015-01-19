#ifndef VISPOINT_HPP
#define VISPOINT_HPP

#include <QGraphicsEllipseItem>

class VisPoint : public QGraphicsEllipseItem
{
public:
    enum {Type = 103};

    VisPoint(double x, double y, QGraphicsItem* parent = 0);

    QPointF vis_pos();

    const static int w = 10;
    const static int h = 10;
};

#endif // VISPOINT_HPP
