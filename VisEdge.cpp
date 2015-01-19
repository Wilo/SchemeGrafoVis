#include "VisEdge.hpp"

VisEdge::VisEdge(VisNode* u, VisNode* v, QString label_text, QGraphicsItem* parent)
    : VisBezierCurve(u, v, label_text, parent)
{
}
