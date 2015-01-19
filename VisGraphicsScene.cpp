#include "VisGraphicsScene.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QAction>
#include <QMenu>

#include <QtDebug>


///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//// Class procedures
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
VisGraphicsScene::VisGraphicsScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
    mode = EDIT;
    graph_type = UNDIRECTED;
    current_id = 0;
    line = NULL;
}

void VisGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    switch(this->mode){
    case VisGraphicsScene::EDIT:
        QGraphicsScene::mousePressEvent(event);
        break;
    case VisGraphicsScene::INSERT_EDGE:

        line = new QGraphicsLineItem(QLineF(event->scenePos(),
                                            event->scenePos()));

        addItem(line);

        break;
    case VisGraphicsScene::INSERT_ARROW:
        line = new QGraphicsLineItem(QLineF(event->scenePos(),
                                            event->scenePos()));
        addItem(line);
        break;
    case VisGraphicsScene::INSERT_VERTEX:
        emit visNodeAdded(event->scenePos().x()-VisNode::w/2,
                          event->scenePos().y()-VisNode::h/2);
        QGraphicsScene::mousePressEvent(event);
        break;
    case VisGraphicsScene::INSERT_LABEL:

        break;
    }
}

void VisGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    switch(this->mode){
    case VisGraphicsScene::EDIT:
        QGraphicsScene::mouseMoveEvent(event);
        break;
    case VisGraphicsScene::INSERT_EDGE:

        if(line == NULL)
            break;

        new_line = QLineF(line->line().p1(), event->scenePos());
        line->setLine(new_line);

        break;
    case VisGraphicsScene::INSERT_ARROW:
        if(line == NULL) break;

        new_line = QLineF(line->line().p1(), event->scenePos());
        line->setLine(new_line);

        break;
    case VisGraphicsScene::INSERT_VERTEX:
        QGraphicsScene::mouseMoveEvent(event);
        break;
    case VisGraphicsScene::INSERT_LABEL:
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void VisGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    switch(this->mode){
    case VisGraphicsScene::EDIT:
        QGraphicsScene::mouseReleaseEvent(event);
        break;
    case VisGraphicsScene::INSERT_EDGE:
        if(line == NULL) break;

        p1_selected = items(line->line().p1());
        p2_selected = items(line->line().p2());

        p1_selected.removeOne(line);
        p2_selected.removeOne(line);

        delete line;

        line  = NULL;

        // Elegir el nodo origen de p1_selected (si es que hay)
        node1 = NULL;
        foreach(QGraphicsItem* item, p1_selected){
            if(item->type() == VisNode::Type){
                node1 = qgraphicsitem_cast<VisNode*>(item);
                break;
            }
        }

        // Elegir el nodo destino de p2_selected (si es que hay)
        node2 = NULL;
        foreach(QGraphicsItem* item, p2_selected){
            if(item->type() == VisNode::Type){
                node2 = qgraphicsitem_cast<VisNode*>(item);
                break;
            }
        }

        // Agregar una arista del nodo origen al nodo destino
        if(node1 != NULL and node2 != NULL){
            emit visEdgeAdded(node1->id, node2->id);
        }

        break;
    case VisGraphicsScene::INSERT_ARROW:
        if(line == NULL) break;

        p1_selected = items(line->line().p1());
        p2_selected = items(line->line().p2());

        // Elegir el nodo origen de p1_selected (si es que hay)
        node1 = NULL;
        foreach(QGraphicsItem* item, p1_selected){
            if(item->type() == VisNode::Type){
                node1 = qgraphicsitem_cast<VisNode*>(item);
            }
        }

        // Elegir el nodo destino de p2_selected (si es que hay)
        node2 = NULL;
        foreach(QGraphicsItem* item, p2_selected){
            if(item->type() == VisNode::Type){
                node2 = qgraphicsitem_cast<VisNode*>(item);
            }
        }

        // Agregar una arista del nodo origen al nodo destino
        if(node1 != NULL and node2 != NULL){
            emit visArrowAdded(node1->id, node2->id);
        }

        //removeItem(line);
        delete line;

        line  = NULL;
        break;
    case VisGraphicsScene::INSERT_VERTEX:
        QGraphicsScene::mouseReleaseEvent(event);
        break;
    case VisGraphicsScene::INSERT_LABEL:
        QGraphicsScene::mouseReleaseEvent(event);
        break;
    }
}

void VisGraphicsScene::visRemoveSelected()
{
    QGraphicsItem* item;
    p1_selected = selectedItems();
    if(p1_selected.isEmpty()){
        return;
    }else{
        item = p1_selected.first();
        if(item != NULL){
            switch(item->type()){
            case VisNode::Type:
                node = qgraphicsitem_cast<VisNode*>(item);
                node->label->setSelected(false);
                node->setSelected(false);
                emit visNodeRemoved(node->id);
                break;
            case VisEdge::Type:
                edge = qgraphicsitem_cast<VisEdge*>(item);
                edge->label->setSelected(false);
                edge->ctrl1->setSelected(false);
                edge->ctrl2->setSelected(false);
                edge->setSelected(false);
                emit visEdgeRemoved(edge->a_id, edge->b_id);
                break;
            case VisArrow::Type:
                arrow = qgraphicsitem_cast<VisArrow*>(item);
                arrow->label->setSelected(false);
                arrow->ctrl1->setSelected(false);
                arrow->ctrl2->setSelected(false);
                arrow->setSelected(false);
                emit visArrowRemoved(arrow->a_id, arrow->b_id);
                break;
            default:
                item->setSelected(false);
                break;
            }
        }
        visRemoveSelected();
    }
}

void VisGraphicsScene::visCleanGraph()
{
    QList<QGraphicsItem *> all_items = items();
    foreach( QGraphicsItem *item, all_items ) {
        switch(item->type()){
        case VisNode::Type:
            node = qgraphicsitem_cast<VisNode*>(item);
            node->set_unhighlighted();
            break;
        case VisEdge::Type:
            edge = qgraphicsitem_cast<VisEdge*>(item);
            edge->set_unhighlighted();
            break;
        case VisArrow::Type:
            arrow = qgraphicsitem_cast<VisArrow*>(item);
            arrow->set_unhighlighted();
            break;
        case VisLabel::Type:
            label = qgraphicsitem_cast<VisLabel*>(item);
            label->set_unhighlighted();
            break;
        }
        item->update();
    }
}

void VisGraphicsScene::visUnlabelGraph()
{
    QList<QGraphicsItem *> all_items = items();
    foreach( QGraphicsItem *item, all_items ) {
        switch(item->type()){
        case VisNode::Type:
            node = qgraphicsitem_cast<VisNode*>(item);
            node->label->setPlainText("");
            break;
        case VisEdge::Type:
            edge = qgraphicsitem_cast<VisEdge*>(item);
            edge->label->setPlainText("");
            break;
        case VisArrow::Type:
            arrow = qgraphicsitem_cast<VisArrow*>(item);
            arrow->label->setPlainText("");
            break;
        }
        item->update();
    }
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//// Class Slots
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void VisGraphicsScene::visPaintNode(int id, double x, double y)
{
    node = new VisNode(id, x, y);
    graph_nodes[id] = node;
    addItem(node);
    addItem(node->label);
    update(sceneRect());
}

void VisGraphicsScene::visUnpaintNode(int id)
{
    node = graph_nodes[id];
    graph_nodes.remove(id);
    node->label->setSelected(false);
    node->setSelected(false);
    delete node;
    node = NULL;
    update(sceneRect());
}

void VisGraphicsScene::visPaintEdge(int aid, int bid, bool with_curves)
{
    node1 = graph_nodes[aid];
    node2 = graph_nodes[bid];
    edge = new VisEdge(node1, node2);
    edge->straight = !with_curves;
    graph_edges[QPair<int,int>(aid,bid)] = edge;
    graph_edges[QPair<int,int>(bid,aid)] = edge;
    addItem(edge->label);
    addItem(edge->ctrl1);
    addItem(edge->ctrl2);
    addItem(edge);
    edge->update();
    update(sceneRect());
}

void VisGraphicsScene::visUnpaintEdge(int aid, int bid)
{
    node1 = graph_nodes[aid];
    node2 = graph_nodes[bid];
    edge = graph_edges[QPair<int,int>(aid,bid)];
    graph_edges.remove(QPair<int,int>(aid,bid));
    graph_edges.remove(QPair<int,int>(bid,aid));
    edge->label->setSelected(false);
    edge->ctrl1->setSelected(false);
    edge->ctrl2->setSelected(false);
    edge->setSelected(false);
    delete edge;
    edge = NULL;
    update(sceneRect());
}

void VisGraphicsScene::visPaintArrow(int aid, int bid, bool with_curves)
{
    node1 = graph_nodes[aid];
    node2 = graph_nodes[bid];
    arrow = new VisArrow(node1, node2);
    arrow->straight = !with_curves;
    graph_arrows[QPair<int,int>(aid,bid)] = arrow;
    addItem(arrow->label);
    addItem(arrow->ctrl1);
    addItem(arrow->ctrl2);
    addItem(arrow);
    arrow->update();
    update(sceneRect());
}

void VisGraphicsScene::visUnpaintArrow(int aid, int bid)
{
    node1 = graph_nodes[aid];
    node2 = graph_nodes[bid];
    arrow = graph_arrows[QPair<int,int>(aid,bid)];
    graph_arrows.remove(QPair<int,int>(aid,bid));
    delete arrow;
    arrow = NULL;
    update(sceneRect());
}

void VisGraphicsScene::visLabelNode(int id, QString label)
{
    node = graph_nodes[id];
    node->label->setPlainText(label);
}

void VisGraphicsScene::visLabelEdge(int aid, int bid, QString label)
{
    edge = graph_edges[QPair<int,int>(aid,bid)];
    edge->label->setPlainText(label);
}

void VisGraphicsScene::visLabelArrow(int aid, int bid, QString label)
{
    arrow = graph_arrows[QPair<int,int>(aid,bid)];
    arrow->label->setPlainText(label);
}

void VisGraphicsScene::visColorNode(int id, int r, int g, int b, int a)
{
    node = graph_nodes[id];
    node->set_highlight(r,g,b,a);
    node->update();
}

void VisGraphicsScene::visUncolorNode(int id)
{
    node = graph_nodes[id];
    node->set_unhighlighted();
    node->update();
}

void VisGraphicsScene::visColorEdge(int aid, int bid, int r, int g, int b, int a)
{
    edge = graph_edges[QPair<int,int>(aid, bid)];
    edge->set_highlight(r,g,b,a);
    edge->update();
}

void VisGraphicsScene::visUncolorEdge(int aid, int bid)
{
    edge = graph_edges[QPair<int,int>(aid, bid)];
    edge->set_unhighlighted();
    edge->update();
}

void VisGraphicsScene::visColorArrow(int aid, int bid, int r, int g, int b, int a)
{
    arrow = graph_arrows[QPair<int,int>(aid, bid)];
    arrow->set_highlight(r,g,b,a);
    arrow->update();
}

void VisGraphicsScene::visUncolorArrow(int aid, int bid)
{
    arrow = graph_arrows[QPair<int,int>(aid, bid)];
    arrow->set_unhighlighted();
    arrow->update();
}

void VisGraphicsScene::visColorNodeLabel(int id, int r, int g, int b, int a)
{
    node = graph_nodes[id];
    node->label->set_highlight(r,g,b,a);
    node->label->update();
}

void VisGraphicsScene::visUncolorNodeLabel(int id)
{
    node = graph_nodes[id];
    node->label->set_unhighlighted();
    node->label->update();
}

void VisGraphicsScene::visColorEdgeLabel(int aid, int bid, int r, int g, int b, int a)
{
    edge = graph_edges[QPair<int,int>(aid, bid)];
    edge->label->set_highlight(r,g,b,a);
    edge->label->update();
}

void VisGraphicsScene::visUncolorEdgeLabel(int aid, int bid)
{
    edge = graph_edges[QPair<int,int>(aid, bid)];
    edge->label->set_unhighlighted();
    edge->label->update();
}

void VisGraphicsScene::visColorArrowLabel(int aid, int bid, int r, int g, int b, int a)
{
    arrow = graph_arrows[QPair<int,int>(aid, bid)];
    arrow->label->set_highlight(r,g,b,a);
    arrow->label->update();
}

void VisGraphicsScene::visUncolorArrowLabel(int aid, int bid)
{
    arrow = graph_arrows[QPair<int,int>(aid, bid)];
    arrow->label->set_unhighlighted();
    arrow->label->update();
}

void VisGraphicsScene::visIncrementId()
{
    current_id++;
}

void VisGraphicsScene::visResetId()
{
    current_id = 0;
}

QPointF VisGraphicsScene::visPosNode(int id)
{
    node = graph_nodes[id];
    return node->pos();
}

void VisGraphicsScene::visMoveNode(int id, double dx, double dy)
{
    node = graph_nodes[id];
    double newx = node->pos().x()+dx;
    double newy = node->pos().y()+dy;
    if((newx > -2450 or newx < 2450) and
       (newy > -2450 or newy < 2450)){
        qDebug() << newx << " " << newy;
        node->moveBy(dx,dy);
        node->update();
    }
}

void VisGraphicsScene::setWithCurves(bool with_curves)
{
    foreach(VisEdge* edge, graph_edges.values()){
        edge->straight = !with_curves;
        edge->setCtrlPoints(edge->ctrl1, edge->ctrl2);
        edge->update();
    }
    foreach(VisArrow* arrow, graph_arrows.values()){
        arrow->straight = !with_curves;
        arrow->setCtrlPoints(arrow->ctrl1, arrow->ctrl2);
        arrow->update();
    }
}
