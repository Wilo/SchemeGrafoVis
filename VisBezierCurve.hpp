#ifndef VISBEZIERCURVE_HPP
#define VISBEZIERCURVE_HPP

#include <QGraphicsItem>
#include <QPainterPath>
#include <QMenu>

#include "VisNode.hpp"
#include "VisPoint.hpp"
#include "VisLabel.hpp"


class VisBezierCurve : public QGraphicsItem
{
public:

    VisBezierCurve(VisNode*, VisNode*, QString label_text="", bool staight_ = false, QGraphicsItem* parent = 0);
    ~VisBezierCurve();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *);

    void setCtrlPoints(VisPoint* pt1, VisPoint* pt2);

    VisNode*  nodeA;
    VisNode*  nodeB;
    VisPoint* ctrl1;
    VisPoint* ctrl2;

    QPointF nodeApos;
    QPointF nodeBpos;
    QPointF labelpos;

    QPointF difNodeACtrl1;
    QPointF difNodeBCtrl1;
    QPointF difNodeACtrl2;
    QPointF difNodeBCtrl2;

    VisLabel* label;

    // external id
    int a_id;
    int b_id;

    bool is_highlighted;
    QColor highlight_color;

    void set_highlight(int r,int g,int b,int a);
    void set_unhighlighted();

    bool straight;
};

#endif // VISBEZIERCURVE_HPP
