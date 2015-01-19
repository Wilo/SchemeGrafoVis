#include "VisNode.hpp"

#include <QBrush>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

VisNode::VisNode(int id_, double x, double y, QString label_text, QGraphicsItem* parent)
    : QGraphicsEllipseItem(parent), is_highlighted(false), highlight_color(QColor(255,255,255))
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setRect(0,0,w,h);
    setZValue(20);
    setBrush(QBrush(QColor(255,255,255)));
    id = id_;
    setPos(x, y);
    label = new VisLabel(label_text);
}

VisNode::~VisNode()
{
    delete label;
}

QPainterPath VisNode::shape() const
{
    QPainterPath path;
    path.addEllipse(QRectF(0,0,w, h));
    return path;
}

QRectF VisNode::boundingRect() const
{
    double separation = 5.0;
    return QRectF(-separation, -separation, w+2*separation, h+2*separation);
}
void VisNode::set_highlight(int r,int g,int b,int a)
{
    highlight_color = QColor(r,g,b,a);
    is_highlighted = true;
}

void VisNode::set_unhighlighted()
{
    is_highlighted = false;
}

void VisNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if(isSelected()){
        label->setSelected(true);
    }
    if(is_highlighted == true){
        QPainterPath path;
        path.addEllipse(QPointF(w/2.0, h/2.0), 2*w/3, 2*h/3);
        painter->fillPath(path, highlight_color);
    }
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->drawEllipse(rect());
    painter->drawText(boundingRect(),QString::number(id),QTextOption(Qt::AlignCenter));
    if (option->state & QStyle::State_Selected){
        painter->setPen(QPen(QColor(127,127,127), 0, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        QPainterPath path;

        path.addEllipse(QPointF(w/2.0, h/2.0), 2*w/3, 2*h/3);
        painter->drawPath(path);
        label->setSelected(true);
    }
    if(label != NULL){
        double lh = label->boundingRect().height()+6;
        double lw = label->boundingRect().width()/2.0;
        label->setPos(pos().x()-lw+w/2.0, pos().y()-lh);
    }
}

void VisNode::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
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
