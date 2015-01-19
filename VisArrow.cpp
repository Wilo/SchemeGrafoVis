#include "VisArrow.hpp"

#include <QPainter>

VisArrow::VisArrow(VisNode* u, VisNode* v, QString label_text, QGraphicsItem* parent)
    : VisBezierCurve(u, v, label_text, parent)
{
}

void VisArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    VisBezierCurve::paint(painter, option, widget);

    QRectF Abox = nodeA->rect();
    QRectF Bbox = nodeB->rect();
    double Ax = nodeA->pos().x()+Abox.width()/2.0;
    double Ay = nodeA->pos().y()+Abox.height()/2.0;
    double Bx = nodeB->pos().x()+Bbox.width()/2.0;
    double By = nodeB->pos().y()+Bbox.height()/2.0;

    QPainterPath path;

    if(straight){
        path.moveTo(Ax, Ay);
        path.cubicTo(QPointF(Ax, Ay),QPointF(Bx, By), QPointF(Bx,By));

        painter->setBrush(Qt::black);

        QPointF end = path.pointAtPercent(path.percentAtLength(path.length()-nodeB->w/2.0));
        painter->drawEllipse(end, 5, 5);
    }else{
        path.moveTo(Ax, Ay);
        path.cubicTo(ctrl1->vis_pos(),ctrl2->vis_pos(), QPointF(Bx,By));

        painter->setBrush(Qt::black);

        QPointF end = path.pointAtPercent(path.percentAtLength(path.length()-nodeB->w/2.0));
        painter->drawEllipse(end, 5, 5);
    }
}
