#ifndef VISEDGE_HPP
#define VISEDGE_HPP

#include "VisBezierCurve.hpp"

class VisEdge : public VisBezierCurve
{
public:
    enum {Type = 101};

    VisEdge(VisNode*, VisNode*, QString label_text = "", QGraphicsItem* parent = 0);

    int type() const {return Type;}
};

#endif // VISEDGE_HPP
