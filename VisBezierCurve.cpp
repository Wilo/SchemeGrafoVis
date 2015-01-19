#include "VisBezierCurve.hpp"

#include <QPainter>
#include <cmath>
#include <QtDebug>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QPainterPathStroker>

VisBezierCurve::VisBezierCurve(VisNode* _nodeA, VisNode* _nodeB, QString label_text, bool straight_, QGraphicsItem* parent)
    : QGraphicsItem(parent), is_highlighted(false), highlight_color(QColor(255,255,255))
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    nodeA = _nodeA;
    nodeB = _nodeB;
    nodeApos = QPointF(nodeA->pos().x()+nodeA->rect().width()/2.0,
                       nodeA->pos().y()+nodeA->rect().height()/2.0);
    nodeBpos = QPointF(nodeB->pos().x()+nodeB->rect().width()/2.0,
                       nodeB->pos().y()+nodeB->rect().height()/2.0);
    setZValue(0);

    a_id = nodeA->id;
    b_id = nodeB->id;

    label = new VisLabel(label_text);
    ctrl1 = new VisPoint(0,0);
    ctrl2 = new VisPoint(0,0);

    QPointF Abox = nodeA->rect().center();
    QPointF Bbox = nodeB->rect().center();

    QPointF A = nodeA->pos()+Abox;
    QPointF B = nodeB->pos()+Bbox;

    ctrl1->setPos(A+(1/3.0)*(B-A)-QPointF(ctrl1->w/2.0, ctrl1->h/2.0));
    ctrl2->setPos(A+(2/3.0)*(B-A)-QPointF(ctrl2->w/2.0, ctrl2->h/2.0));

    straight = straight;
}
VisBezierCurve::~VisBezierCurve()
{
    // Si elimino label, ctrl1 o ctrl2 sale un segmentation fault
    delete label;
    delete ctrl1;
    delete ctrl2;
}

void VisBezierCurve::setCtrlPoints(VisPoint* pt1, VisPoint* pt2)
{
    ctrl1 = pt1;
    ctrl2 = pt2;

    QPointF Abox = nodeA->rect().center();
    QPointF Bbox = nodeB->rect().center();

    QPointF A = nodeA->pos()+Abox;
    QPointF B = nodeB->pos()+Bbox;

    ctrl1->setPos(A+(1/3.0)*(B-A)-QPointF(ctrl1->w/2.0, ctrl1->h/2.0));
    ctrl2->setPos(A+(2/3.0)*(B-A)-QPointF(ctrl2->w/2.0, ctrl2->h/2.0));
}

void VisBezierCurve::set_highlight(int r,int g,int b,int a)
{
    highlight_color = QColor(r,g,b,a);
    is_highlighted = true;
}

void VisBezierCurve::set_unhighlighted()
{
    is_highlighted = false;
}

void VisBezierCurve::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if(isSelected()){
        label->setSelected(true);
    }
    QPainterPath path;

    QRectF Abox = nodeA->rect();
    QRectF Bbox = nodeB->rect();

    double Ax = nodeA->pos().x()+Abox.width()/2.0;
    double Ay = nodeA->pos().y()+Abox.height()/2.0;
    double Bx = nodeB->pos().x()+Bbox.width()/2.0;
    double By = nodeB->pos().y()+Bbox.height()/2.0;

    if(not straight){
        if(QPointF(Ax, Ay) != nodeApos){
            ctrl1->moveBy(Ax-nodeApos.x(), Ay-nodeApos.y());
            nodeApos = QPointF(Ax, Ay);
        }

        if(QPointF(Bx, By) != nodeBpos){
            ctrl2->moveBy(Bx-nodeBpos.x(), By-nodeBpos.y());
            nodeBpos = QPointF(Bx, By);
        }

        if(is_highlighted == true){
            painter->fillPath(shape(), highlight_color);
        }
        path.moveTo(Ax, Ay);
        path.cubicTo(ctrl1->vis_pos(),ctrl2->vis_pos(), QPointF(Bx,By));

        if (option->state & QStyle::State_Selected){
            if(ctrl1 != NULL and ctrl2 != NULL and !ctrl1->isVisible() and !ctrl1->isVisible()){
                ctrl1->show();
                ctrl2->show();
            }
        }else if(ctrl1 != NULL and ctrl2 != NULL and !ctrl1->isSelected() and !ctrl2->isSelected()){
            ctrl1->hide();
            ctrl2->hide();
        }
    }else{
        if(is_highlighted == true){
            painter->fillPath(shape(), highlight_color);
        }
        path.moveTo(Ax, Ay);
        path.lineTo(Bx, By);
        ctrl1->hide();
        ctrl2->hide();
    }
    painter->drawPath(path);

    if (option->state & QStyle::State_Selected){
        QPainterPath select_path = this->shape();
        painter->setPen(QPen(QColor(127,127,127), 0, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawPath(select_path);
    }

    double lh = label->boundingRect().height()+6;
    double lw = label->boundingRect().width()/2.0;
    label->setPos(path.pointAtPercent(.5).x()-lw, path.pointAtPercent(.5).y()-lh);
}

QRectF VisBezierCurve::boundingRect() const
{
    QRectF Abox = nodeA->rect();
    QRectF Bbox = nodeB->rect();

    double Ax = nodeA->pos().x()+Abox.width()/2.0;
    double Ay = nodeA->pos().y()+Abox.height()/2.0;
    double Bx = nodeB->pos().x()+Bbox.width()/2.0;
    double By = nodeB->pos().y()+Bbox.width()/2.0;

    QPainterPath path;
    if(not straight){
        path.moveTo(Ax, Ay);
        path.cubicTo(ctrl1->vis_pos(),ctrl2->vis_pos(), QPointF(Bx,By));
    }else{
        path.moveTo(Ax, Ay);
        path.lineTo(Bx, By);
        QPainterPathStroker stroker;
        stroker.setWidth(10);
        path = (stroker.createStroke(path)+path).simplified();
    }
    return path.boundingRect();
}

QPainterPath VisBezierCurve::shape() const
{
    QPainterPath select_path;

    double offset = 5.0;
    QRectF Abox = nodeA->rect();
    QRectF Bbox = nodeB->rect();

    double Ax = nodeA->pos().x()+Abox.width()/2.0;
    double Ay = nodeA->pos().y()+Abox.height()/2.0;
    double Bx = nodeB->pos().x()+Bbox.width()/2.0;
    double By = nodeB->pos().y()+Bbox.width()/2.0;

    if(not straight){
        /*
        double dxCtrl1 = ctrl1->vis_pos().x() - Ax;
        double dyCtrl1 = ctrl1->vis_pos().y() - Ay;
        double lenCtrl1 = sqrt(dxCtrl1*dxCtrl1 + dyCtrl1*dyCtrl1);
        QPointF a1(Ax+offset*dyCtrl1/lenCtrl1, Ay-offset*dxCtrl1/lenCtrl1);
        QPointF a2(Ax-offset*dyCtrl1/lenCtrl1, Ay+offset*dxCtrl1/lenCtrl1);

        double dxCtrl2 = ctrl2->vis_pos().x() - Bx;
        double dyCtrl2= ctrl2->vis_pos().y() - By;
        double lenCtrl2 = sqrt(dxCtrl2*dxCtrl2 + dyCtrl2*dyCtrl2);
        QPointF b1(Bx-offset*dyCtrl2/lenCtrl2, By+offset*dxCtrl2/lenCtrl2);
        QPointF b2(Bx+offset*dyCtrl2/lenCtrl2, By-offset*dxCtrl2/lenCtrl2);

        select_path.moveTo(a1);
        select_path.cubicTo(ctrl1->vis_pos().x()+offset*dyCtrl1/lenCtrl1, ctrl1->vis_pos().y()-offset*dxCtrl1/lenCtrl1, ctrl2->vis_pos().x()-offset*dyCtrl2/lenCtrl2, ctrl2->vis_pos().y()+offset*dxCtrl2/lenCtrl2, b1.x(), b1.y());
        select_path.lineTo(b2);
        select_path.cubicTo(ctrl2->vis_pos().x()+offset*dyCtrl2/lenCtrl2, ctrl2->vis_pos().y()-offset*dxCtrl2/lenCtrl2, ctrl1->vis_pos().x()-offset*dyCtrl1/lenCtrl1, ctrl1->vis_pos().y()+offset*dxCtrl1/lenCtrl1, a2.x(), a2.y());
        select_path.lineTo(a1);
        */
        select_path.moveTo(Ax, Ay);
        select_path.cubicTo(ctrl1->vis_pos(), ctrl2->vis_pos(), QPointF(Bx, By));
        QPainterPathStroker stroker;
        stroker.setWidth(10);
        stroker.setJoinStyle(Qt::MiterJoin);
        //select_path = (stroker.createStroke(select_path)+select_path).simplified();
        select_path = stroker.createStroke(select_path).simplified();

    }else{
        select_path.moveTo(Ax, Ay);
        select_path.lineTo(Bx, By);
        QPainterPathStroker stroker;
        stroker.setWidth(10);
        select_path = (stroker.createStroke(select_path)+select_path).simplified();

    }

    return select_path;
}

void VisBezierCurve::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction("Red");
    menu.addAction("Green");
    menu.addAction("Blue");
    menu.addAction("Yellow");
    menu.addAction("None");

    QAction* a = menu.exec(event->screenPos());

    if(a == NULL)
        return;

    QString action = a->text();

    if(action == "Red"){
        set_highlight(196,2,51,100);
    }else if(action == "Green"){
        set_highlight(0,159,107,100);
    }else if(action == "Blue"){
        set_highlight(0,135,189,100);
    }else if(action == "Yellow"){
        set_highlight(255,211,0,100);
    }else if(action == "None"){
        set_unhighlighted();
    }else{

    }
    update();
}
