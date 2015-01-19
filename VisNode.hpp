#ifndef VISNODE_HPP
#define VISNODE_HPP

// Parent class
#include <QGraphicsEllipseItem>

// Member
#include "VisLabel.hpp"

class VisNode : public QGraphicsEllipseItem
{
public:
    enum {Type = 100};

    VisNode(int, double x = 0, double y = 0, QString label_text = "", QGraphicsItem* parent = 0);
    ~VisNode();

    int type() const {return Type;}

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *);

    const static int w = 30;
    const static int h = 30;

    VisLabel* label;

    void set_highlight(int,int,int,int);
    void set_unhighlighted();

    // external id
    int id;
    bool is_highlighted;
    QColor highlight_color;
};

#endif // VISNODE_HPP
