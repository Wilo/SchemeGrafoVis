#ifndef VISARROW_HPP
#define VISARROW_HPP

#include "VisBezierCurve.hpp"
#include "VisNode.hpp"

class VisArrow : public VisBezierCurve
{
public:
    enum {Type = 102};

    VisArrow(VisNode*, VisNode*, QString label_text = "", QGraphicsItem* parent = 0);

    int type() const {return Type;}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // VISARROW_HPP
