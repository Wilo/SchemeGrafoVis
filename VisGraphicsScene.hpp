#ifndef VISGRAPHICSSCENE_HPP
#define VISGRAPHICSSCENE_HPP

// Parent class
#include <QGraphicsScene>

// Member classes
#include <VisNode.hpp>
#include <VisEdge.hpp>
#include <VisArrow.hpp>
#include <VisLabel.hpp>

class VisGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum MODE  {EDIT, INSERT_VERTEX, INSERT_EDGE, INSERT_ARROW, INSERT_LABEL} mode;
    enum GRAPH {UNDIRECTED, DIRECTED} graph_type;

    VisGraphicsScene(QObject* parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    void visRemoveSelected();
    void visCleanGraph();
    void visUnlabelGraph();

    int id() { return current_id; }

    QPointF visPosNode(int id);

    QList<int> graph_node_ids() { return graph_nodes.keys(); }

    void setWithCurves(bool with_curves);

    QHash<int, VisNode*>             graph_nodes;
    QHash<QPair<int,int>, VisEdge*>  graph_edges;
    QHash<QPair<int,int>, VisArrow*> graph_arrows;
    QHash<int, VisLabel*>            graph_labels;

private:
    VisNode*              node;
    VisNode*              node1;
    VisNode*              node2;
    VisEdge*              edge;
    VisArrow*             arrow;
    VisPoint*             ctrl1;
    VisPoint*             ctrl2;
    VisLabel*             label;

    QPointF               point;
    QLineF                new_line;
    QGraphicsLineItem*    line;
    QList<QGraphicsItem*> p1_selected;
    QList<QGraphicsItem*> p2_selected;

    int current_id;

signals:
    void visNodeAdded(double x, double y);
    void visNodeRemoved(int id);
    void visEdgeAdded(int aid, int bid);
    void visEdgeRemoved(int aid, int bid);
    void visArrowAdded(int aid, int bid);
    void visArrowRemoved(int aid, int bid);

public slots:
    void visPaintNode(int id, double x, double y);
    void visUnpaintNode(int id);
    void visPaintEdge(int aid, int bid, bool with_curves);
    void visUnpaintEdge(int aid, int bid);
    void visPaintArrow(int aid, int bid, bool with_curves);
    void visUnpaintArrow(int aid, int bid);
    void visLabelNode(int id, QString);
    void visLabelEdge(int aid, int bid, QString);
    void visLabelArrow(int aid, int bid, QString);
    void visColorNode(int id, int r, int g, int b, int a);
    void visUncolorNode(int id);
    void visColorEdge(int aid, int bid, int r, int g, int b, int a);
    void visUncolorEdge(int aid, int bid);
    void visColorArrow(int aid, int bid, int r, int g, int b, int a);
    void visUncolorArrow(int aid, int bid);
    void visColorNodeLabel(int id, int r, int g, int b, int a);
    void visUncolorNodeLabel(int id);
    void visColorEdgeLabel(int aid, int bid, int r, int g, int b, int a);
    void visUncolorEdgeLabel(int aid, int bid);
    void visColorArrowLabel(int aid, int bid, int r, int g, int b, int a);
    void visUncolorArrowLabel(int aid, int bid);
    void visIncrementId();
    void visResetId();

    void visMoveNode(int id, double dx, double dy);
};

#endif // VISGRAPHICSSCENE_HPP
