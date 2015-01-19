#ifndef VISLABE_HPP
#define VISLABE_HPP

// Parent class
#include <QGraphicsTextItem>



class VisLabel : public QGraphicsTextItem
{
public:
    enum {Type = 104};

    VisLabel(QString text = "etiqueta", QGraphicsItem* parent = 0);

    int type() const {return Type;}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *evt);

    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);

    void setTextInteraction(bool on, bool selectAll = false);

    void set_highlight(int,int,int,int);
    void set_unhighlighted();

    bool is_highlighted;
    QColor highlight_color;
};

#endif // VISLABE_HPP
