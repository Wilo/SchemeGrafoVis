#include "Environment.hpp"

#include <VisBipartiteness.hpp>
#include <VisSpanningTreeBFS.hpp>
#include <VisSpanningTreeDFS.hpp>
#include <VisPrim.hpp>
#include <VisKruskal.hpp>
#include <VisDijkstra.hpp>
#include <VisFloydWarshall.hpp>
#include <VisFordFulkerson.hpp>
#include <VisMinimumCostConstantFlowNC.hpp>
#include <VisMinimumCostConstantFlowSP.hpp>

#include <QtDebug>

#define SCM_DEFUNC(NAME, ARGS, PROC) scm_c_define_gsubr(NAME, ARGS, 0, 0, ((scm_t_subr) PROC ))

static Environment* env = NULL;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//// Foreign language procedures
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

QString scmToString(SCM s)
{
    return QString(scm_to_locale_string(s));
}

int scmToInt(SCM i)
{
    return scm_to_int(i);
}

double scmToDouble(SCM d)
{
    return scm_to_double(d);
}

SCM scmPaintNode(SCM id, SCM x, SCM y)
{
    env->visPaintNode(scmToInt(id), scmToDouble(x), scmToDouble(y));
    env->visIncrementId();
    return SCM_UNSPECIFIED;
}

SCM scmUnpaintNode(SCM id)
{
    env->visUnpaintNode(scmToInt(id));
    return SCM_UNSPECIFIED;
}

SCM scmPaintEdge(SCM aid, SCM bid)
{
    env->visPaintEdge(scmToInt(aid), scmToInt(bid), env->with_curves);
    return SCM_UNSPECIFIED;
}

SCM scmUnpaintEdge(SCM aid, SCM bid)
{
    env->visUnpaintEdge(scmToInt(aid), scmToInt(bid));
    return SCM_UNSPECIFIED;
}

SCM scmPaintArrow(SCM aid, SCM bid)
{
    env->visPaintArrow(scmToInt(aid), scmToInt(bid), env->with_curves);
    return SCM_UNSPECIFIED;
}

SCM scmUnpaintArrow(SCM aid, SCM bid)
{
    env->visUnpaintArrow(scmToInt(aid), scmToInt(bid));
    return SCM_UNSPECIFIED;
}

SCM scmLabelNode(SCM id, SCM label)
{
    env->visLabelNode(scmToInt(id), scmToString(label));
    return SCM_UNSPECIFIED;
}

SCM scmLabelEdge(SCM aid, SCM bid, SCM label)
{
    env->visLabelEdge(scmToInt(aid), scmToInt(bid), scmToString(label));
    return SCM_UNSPECIFIED;
}

SCM scmLabelArrow(SCM aid, SCM bid, SCM label)
{
    env->visLabelArrow(scmToInt(aid), scmToInt(bid), scmToString(label));
    return SCM_UNSPECIFIED;
}

SCM scmColorNode(SCM id, SCM r, SCM g, SCM b, SCM a)
{
    env->visColorNode(scmToInt(id), scmToInt(r), scmToInt(g), scmToInt(b), scmToInt(a));
    return SCM_UNSPECIFIED;
}

SCM scmUncolorNode(SCM id)
{
    env->visUncolorNode(scmToInt(id));
    return SCM_UNSPECIFIED;
}

SCM scmColorEdge(SCM aid, SCM bid, SCM r, SCM g, SCM b, SCM a)
{
    env->visColorEdge(scmToInt(aid), scmToInt(bid), scmToInt(r), scmToInt(g), scmToInt(b), scmToInt(a));
    return SCM_UNSPECIFIED;
}

SCM scmUncolorEdge(SCM aid, SCM bid)
{
    env->visUncolorEdge(scmToInt(aid), scmToInt(bid));
    return SCM_UNSPECIFIED;
}

SCM scmColorArrow(SCM aid, SCM bid, SCM r, SCM g, SCM b, SCM a)
{
    env->visColorArrow(scmToInt(aid), scmToInt(bid), scmToInt(r), scmToInt(g), scmToInt(b), scmToInt(a));
    return SCM_UNSPECIFIED;
}

SCM scmUncolorArrow(SCM aid, SCM bid)
{
    env->visUncolorArrow(scmToInt(aid), scmToInt(bid));
    return SCM_UNSPECIFIED;
}

SCM scmColorNodeLabel(SCM id, SCM r, SCM g, SCM b, SCM a)
{
    env->visColorNodeLabel(scmToInt(id), scmToInt(r), scmToInt(g), scmToInt(b), scmToInt(a));
    return SCM_UNSPECIFIED;
}

SCM scmUncolorNodeLabel(SCM id)
{
    env->visUncolorNodeLabel(scmToInt(id));
    return SCM_UNSPECIFIED;
}

SCM scmColorEdgeLabel(SCM aid, SCM bid, SCM r, SCM g, SCM b, SCM a)
{
    env->visColorEdgeLabel(scmToInt(aid), scmToInt(bid), scmToInt(r), scmToInt(g), scmToInt(b), scmToInt(a));
    return SCM_UNSPECIFIED;
}

SCM scmUncolorEdgeLabel(SCM aid, SCM bid)
{
    env->visUncolorEdgeLabel(scmToInt(aid), scmToInt(bid));
    return SCM_UNSPECIFIED;
}

SCM scmColorArrowLabel(SCM aid, SCM bid, SCM r, SCM g, SCM b, SCM a)
{
    env->visColorArrowLabel(scmToInt(aid), scmToInt(bid), scmToInt(r), scmToInt(g), scmToInt(b), scmToInt(a));
    return SCM_UNSPECIFIED;
}

SCM scmUncolorArrowLabel(SCM aid, SCM bid)
{
    env->visUncolorArrowLabel(scmToInt(aid), scmToInt(bid));
    return SCM_UNSPECIFIED;
}

SCM scmWait(SCM message)
{
    env->on_pause = true;
    env->visStepWait(scmToString(message));
    while(env->on_pause){

    }
    return SCM_UNSPECIFIED;
}

SCM scmShowMessage(SCM message)
{
    env->visShowMessage(scmToString(message));
    return SCM_UNSPECIFIED;
}

SCM scmReload(SCM file)
{
    env->evalFile(scmToString(file));
    return SCM_UNSPECIFIED;
}

SCM scmPosNode(SCM id)
{
    QPointF pos = env->visPosNode(scmToInt(id));
    double x = pos.x();
    double y = pos.y();

    return scm_cons(scm_from_double(x), scm_from_double(y));
}

SCM scmMoveNode(SCM id, SCM dx, SCM dy)
{
    env->visMoveNode(scmToInt(id), scmToDouble(dx), scmToDouble(dy));
    return SCM_UNSPECIFIED;
}

void Environment::initForeign()
{
    scm_init_guile();

    evalFile("init.scm");

    SCM_DEFUNC("cpp-paint-node!", 3,          scmPaintNode);
    SCM_DEFUNC("cpp-unpaint-node!", 1,        scmUnpaintNode);
    SCM_DEFUNC("cpp-paint-edge!", 2,          scmPaintEdge);
    SCM_DEFUNC("cpp-unpaint-edge!", 2,        scmUnpaintEdge);
    SCM_DEFUNC("cpp-paint-arrow!", 2,         scmPaintArrow);
    SCM_DEFUNC("cpp-unpaint-arrow!", 2,       scmUnpaintArrow);
    SCM_DEFUNC("cpp-label-node!", 2,          scmLabelNode);
    SCM_DEFUNC("cpp-label-edge!", 3,          scmLabelEdge);
    SCM_DEFUNC("cpp-label-arrow!", 3,         scmLabelArrow);
    SCM_DEFUNC("cpp-color-node!", 5,          scmColorNode);
    SCM_DEFUNC("cpp-uncolor-node!", 1,        scmUncolorNode);
    SCM_DEFUNC("cpp-color-edge!", 6,          scmColorEdge);
    SCM_DEFUNC("cpp-uncolor-edge!", 2,        scmUncolorEdge);
    SCM_DEFUNC("cpp-color-arrow!", 6,         scmColorArrow);
    SCM_DEFUNC("cpp-uncolor-arrow!", 2,       scmUncolorArrow);
    SCM_DEFUNC("cpp-color-node-label!", 5,    scmColorNodeLabel);
    SCM_DEFUNC("cpp-uncolor-node-label!", 1,  scmUncolorNodeLabel);
    SCM_DEFUNC("cpp-color-edge-label!", 6,    scmColorEdgeLabel);
    SCM_DEFUNC("cpp-uncolor-edge-label!", 2,  scmUncolorEdgeLabel);
    SCM_DEFUNC("cpp-color-arrow-label!", 6,   scmColorArrowLabel);
    SCM_DEFUNC("cpp-uncolor-arrow-label!", 2, scmUncolorArrowLabel);
    SCM_DEFUNC("cpp-wait!", 1,                scmWait);
    SCM_DEFUNC("cpp-show-message!", 1,        scmShowMessage);
    SCM_DEFUNC("cpp-reload!", 1,              scmReload);
    SCM_DEFUNC("cpp-pos-node", 1,             scmPosNode);
    SCM_DEFUNC("cpp-move-node!", 3,           scmMoveNode);

    evalFile("vis-graph.scm");

    evalFile("algorithms.scm");

    newGraph(vis_scene->graph_type);

    evalString("(spring)", true);
}

SCM Environment::evalString(QString code, bool with_thread)
{
    if(with_thread)
        code = QString("(call-with-new-thread (lambda () ") + code + QString("))");

    return scm_c_eval_string(code.toStdString().data());
}

void Environment::evalFile(QString path)
{
    scm_c_primitive_load(path.toStdString().data());
}

void Environment::newGraph(VisGraphicsScene::GRAPH type)
{
    switch(type){
    case VisGraphicsScene::UNDIRECTED:
        evalString("(define G (make <vis-undirected-graph>))");
        break;
    case VisGraphicsScene::DIRECTED:
        evalString("(define G (make <vis-directed-graph>))");
        break;
    }
}

void Environment::delGraph(VisGraphicsScene::GRAPH type, bool thread)
{
    switch(type){
    case VisGraphicsScene::UNDIRECTED:
        break;
    case VisGraphicsScene::DIRECTED:
        break;
    }
    evalString("(set! spring-movement #false)");
    evalString("(for-each (lambda (v) (remove-vertex! G v)) (vertices G))", thread);
}

QString Environment::addNodeCode(int id, double x, double y)
{
    // (add-vertex! G id x y)
    return  QString("(add-vertex! G ") + QString::number(id) + QString(" ") +
            QString::number(x) + QString(" ") + QString::number(y) + QString(")");
}

QString Environment::removeNodeCode(int id)
{
    // (remove-vertex! G id)
    return QString("(remove-vertex! G ") + QString::number(id) + ")";
}

QString Environment::addEdgeCode(int aid, int bid)
{
    // (add-edge! G '(aid bid))
    return  QString("(add-edge! G '(") + QString::number(aid) + QString(" ") +
            QString::number(bid) + QString("))");
}

QString Environment::removeEdgeCode(int aid, int bid)
{
    // (remove-edge! G '(aid bid))
    return  QString("(remove-edge! G '(") + QString::number(aid) +
            QString(" ") + QString::number(bid) + QString("))");
}

QString Environment::addArrowCode(int aid, int bid)
{
    // (add-arrow! G '(aid bid))
    return  QString("(add-arrow! G '(") + QString::number(aid) + QString(" ") +
            QString::number(bid) + QString("))");
}

QString Environment::removeArrowCode(int aid,int bid)
{
    // (remove-arrow! G '(aid bid))
    return  QString("(remove-arrow! G '(") + QString::number(aid) +
            QString(" ") + QString::number(bid) + QString("))");
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//// Class procedures
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
Environment::Environment(QWidget *parent) :
    QWidget(parent)
{
    vis_scene = new VisGraphicsScene;

    vis_view = new VisGraphicsView(vis_scene);

    ui_layout = new QHBoxLayout;
    ui_layout->addWidget(vis_view, 0, 0);

    setLayout(ui_layout);

    // Conections
    {
        connect(vis_scene, SIGNAL(visNodeAdded(double,double)),
                this,      SLOT(visAddNode(double,double)));
        connect(vis_scene, SIGNAL(visNodeRemoved(int)),
                this,      SLOT(visRemoveNode(int)));
        connect(vis_scene, SIGNAL(visEdgeAdded(int,int)),
                this,      SLOT(visAddEdge(int,int)));
        connect(vis_scene, SIGNAL(visEdgeRemoved(int,int)),
                this,      SLOT(visRemoveEdge(int,int)));
        connect(vis_scene, SIGNAL(visArrowAdded(int,int)),
                this,      SLOT(visAddArrow(int,int)));
        connect(vis_scene, SIGNAL(visArrowRemoved(int,int)),
                this,      SLOT(visRemoveArrow(int,int)));

        connect(this,      SIGNAL(visPaintNode(int,double,double)),
                vis_scene, SLOT(visPaintNode(int,double,double)));
        connect(this,      SIGNAL(visUnpaintNode(int)),
                vis_scene, SLOT(visUnpaintNode(int)));
        connect(this,      SIGNAL(visPaintEdge(int,int, bool)),
                vis_scene, SLOT(visPaintEdge(int,int, bool)));
        connect(this,      SIGNAL(visUnpaintEdge(int,int)),
                vis_scene, SLOT(visUnpaintEdge(int,int)));
        connect(this,      SIGNAL(visPaintArrow(int,int, bool)),
                vis_scene, SLOT(visPaintArrow(int,int, bool)));
        connect(this,      SIGNAL(visUnpaintArrow(int,int)),
                vis_scene, SLOT(visUnpaintArrow(int,int)));

        connect(this,      SIGNAL(visLabelNode(int,QString)),
                vis_scene, SLOT(visLabelNode(int,QString)));
        connect(this,      SIGNAL(visLabelEdge(int,int,QString)),
                vis_scene, SLOT(visLabelEdge(int,int,QString)));
        connect(this,      SIGNAL(visLabelArrow(int,int,QString)),
                vis_scene, SLOT(visLabelArrow(int,int,QString)));

        connect(this,      SIGNAL(visColorNode(int,int,int,int,int)),
                vis_scene, SLOT(visColorNode(int,int,int,int,int)));
        connect(this,      SIGNAL(visUncolorNode(int)),
                vis_scene, SLOT(visUncolorNode(int)));
        connect(this,      SIGNAL(visColorEdge(int,int,int,int,int,int)),
                vis_scene, SLOT(visColorEdge(int,int,int,int,int,int)));
        connect(this,      SIGNAL(visUncolorEdge(int,int)),
                vis_scene, SLOT(visUncolorEdge(int,int)));
        connect(this,      SIGNAL(visColorArrow(int,int,int,int,int,int)),
                vis_scene, SLOT(visColorArrow(int,int,int,int,int,int)));
        connect(this,      SIGNAL(visUncolorArrow(int,int)),
                vis_scene, SLOT(visUncolorArrow(int,int)));
        connect(this,      SIGNAL(visColorNodeLabel(int,int,int,int,int)),
                vis_scene, SLOT(visColorNodeLabel(int,int,int,int,int)));
        connect(this,      SIGNAL(visUncolorNodeLabel(int)),
                vis_scene, SLOT(visUncolorNodeLabel(int)));
        connect(this,      SIGNAL(visColorEdgeLabel(int,int,int,int,int,int)),
                vis_scene, SLOT(visColorEdgeLabel(int,int,int,int,int,int)));
        connect(this,      SIGNAL(visUncolorEdgeLabel(int,int)),
                vis_scene, SLOT(visUncolorEdgeLabel(int,int)));
        connect(this,      SIGNAL(visColorArrowLabel(int,int,int,int,int,int)),
                vis_scene, SLOT(visColorArrowLabel(int,int,int,int,int,int)));
        connect(this,      SIGNAL(visUncolorArrowLabel(int,int)),
                vis_scene, SLOT(visUncolorArrowLabel(int,int)));

        connect(this,      SIGNAL(visIncrementId()),
                vis_scene, SLOT(visIncrementId()));
        connect(this,      SIGNAL(visResetId()),
                vis_scene, SLOT(visResetId()));

        connect(this,      SIGNAL(visMoveNode(int,double,double)),
                vis_scene, SLOT(visMoveNode(int,double,double)));
    }

    env = this;
    on_pause = false;
    with_curves = false;

    initForeign();
}

Environment::~Environment()
{
    delete vis_scene;
    delete vis_view;
    delete ui_layout;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//// Class Public Slots
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void Environment::visChangeZoom(int percent)
{
    double zoom = percent/100.0;

    QMatrix old_matrix = vis_view->matrix();
    vis_view->resetMatrix();
    vis_view->translate(old_matrix.dx(),old_matrix.dy());
    vis_view->scale(zoom, zoom);
    vis_view->repaint();
}

void Environment::visToolSelected(int tool)
{
    vis_scene->mode = VisGraphicsScene::MODE(tool);
}

void Environment::visSetGraphType(int type)
{
    if(type == 1 and graphType() == VisGraphicsScene::UNDIRECTED){
        delGraph(graphType(), false);
        emit visResetId();
        vis_scene->graph_type = VisGraphicsScene::DIRECTED;
        newGraph(VisGraphicsScene::DIRECTED);
    }else if(type == 0 and graphType() == VisGraphicsScene::DIRECTED){
        delGraph(graphType(), false);
        emit visResetId();
        vis_scene->graph_type = VisGraphicsScene::UNDIRECTED;
        newGraph(VisGraphicsScene::UNDIRECTED);
    }
}

void Environment::visRemoveSelection()
{
    vis_scene->visRemoveSelected();
}

void Environment::visCleanGraph()
{
    vis_scene->visCleanGraph();
}

void Environment::visUnlabelGraph()
{
    vis_scene->visUnlabelGraph();
}

void Environment::visEraseGraph()
{
    delGraph(graphType(), true);
    emit visResetId();
}

void Environment::visRunBipartiteness()
{
    VisBipartiteness dialog(this);
    int response = dialog.exec();

    if(response == 1){ // OK Button clicked
        evalString("(run-bipartiteness G)", true);
    }
}

void Environment::visRunSpanningTreeBFS()
{
    VisSpanningTreeBFS dialog(vis_scene->graph_node_ids(), this);
    int response = dialog.exec();

    if(response == 1){
        int root_vertex = dialog.getRootVertex();
        evalString(QString("(run-spanning-tree-bfs G ")+QString::number(root_vertex)+QString(")"), true);
    }
}

void Environment::visRunSpanningTreeDFS()
{
    VisSpanningTreeDFS dialog(vis_scene->graph_node_ids(), this);
    int response = dialog.exec();

    if(response == 1){
        int root_vertex = dialog.getRootVertex();
        evalString(QString("(run-spanning-tree-dfs G ")+QString::number(root_vertex)+QString(")"), true);
    }
}

void Environment::visRunPrim()
{
    VisPrim dialog(vis_scene->graph_node_ids(), this);
    int response = dialog.exec();

    if(response == 1){
        int root_vertex = dialog.getRootVertex();
        foreach(VisEdge* edge, vis_scene->graph_edges.values()){
            int aid = edge->a_id;
            int bid = edge->b_id;
            evalString(QString("(add-atribute! G '(" + QString::number(aid) + QString(" ") + QString::number(bid)
                               + QString(") #:weight " + edge->label->toPlainText() + QString(")"))));
        }
        evalString(QString("(run-prim G ") + QString::number(root_vertex) + QString(")"), true);
    }
}

void Environment::visRunKruskal()
{
    VisKruskal dialog(this);
    int response = dialog.exec();

    if(response == 1){
        foreach(VisEdge* edge, vis_scene->graph_edges.values()){
            int aid = edge->a_id;
            int bid = edge->b_id;
            evalString(QString("(add-atribute! G '(" + QString::number(aid) + QString(" ") + QString::number(bid)
                               + QString(") #:weight " + edge->label->toPlainText() + QString(")"))));
        }
        evalString(QString("(run-kruskal G)"), true);
    }
}

void Environment::visRunDijkstra()
{
    VisDijkstra dialog(vis_scene->graph_node_ids(), this);
    int response = dialog.exec();

    if(response == 1){
        int starting_vertex = dialog.getStartingVertex();
        int ending_vertex = dialog.getEndingVertex();
        foreach(VisArrow* arrow, vis_scene->graph_arrows.values()){
            int aid = arrow->a_id;
            int bid = arrow->b_id;
            evalString(QString("(add-atribute! G '(" + QString::number(aid) + QString(" ") + QString::number(bid)
                               + QString(") #:distance " + arrow->label->toPlainText() + QString(")"))));
        }
        evalString(QString("(run-dijkstra G ")+QString::number(starting_vertex)+QString(" ")+QString::number(ending_vertex)+QString(")"), true);
    }
}

void Environment::visRunFloydWarshall()
{
    VisFloydWarshall dialog(this);
    int response = dialog.exec();

    if(response == 1){
        foreach(VisArrow* arrow, vis_scene->graph_arrows.values()){
            int aid = arrow->a_id;
            int bid = arrow->b_id;
            evalString(QString("(add-atribute! G '(" + QString::number(aid) + QString(" ") + QString::number(bid)
                               + QString(") #:distance " +arrow->label->toPlainText() + QString(")"))));
        }
        evalString("(run-floyd-warshall G)", true);
    }
}

void Environment::fordFulkersonParseAndLabel(VisArrow* arrow)
{
    // La etiqueta puede tener uno o dos valores separados por coma representando la capacidad o la restricción minima y capacidad ejemplo "1,2", "3", "1,5"
    QString label = arrow->label->toPlainText();
    QStringList lst = label.split(",", QString::SkipEmptyParts);
    int size = lst.size();

    if(size == 0){
        evalString(QString("(add-atribute! G '("+QString::number(arrow->a_id)+QString(" ")+QString::number(arrow->b_id)+QString(") #:q-max 0)")));
    }else if(size == 1){
        QString q = lst[0];
        double q2 = q.toDouble();
        evalString(QString("(add-atribute! G '("+QString::number(arrow->a_id)+QString(" ")+QString::number(arrow->b_id)+QString(") #:q-max ")+QString::number(q2)+QString(")")));
    }else{
        QString r = lst[0];
        double r2 = r.toDouble();
        QString q = lst[1];
        double q2 = q.toDouble();
        evalString(QString("(add-atribute! G '("+QString::number(arrow->a_id)+QString(" ")+QString::number(arrow->b_id)+QString(") #:q-max ")+QString::number(q2)+QString(")")));
        evalString(QString("(add-atribute! G '("+QString::number(arrow->a_id)+QString(" ")+QString::number(arrow->b_id)+QString(") #:q-min ")+QString::number(r2)+QString(")")));
    }
}

void Environment::fordFulkersonParseAndLabel(VisNode* node)
{
    // La etiqueta puede tener uno o dos valores separados por coma representando la capacidad o la restricción minima y capacidad ejemplo "1,2", "3", "1,5"
    QString label = node->label->toPlainText();
    QStringList lst = label.split(",", QString::SkipEmptyParts);
    int size = lst.size();

    if(size == 0){

    }else if(size == 1){
        QString q = lst[0];
        double q2 = q.toDouble();
        evalString(QString("(add-atribute! G "+QString::number(node->id)+QString(" ")+QString(" #:q-max ")+QString::number(q2)+QString(")")));
    }else{
        QString r = lst[0];
        double r2 = r.toDouble();
        QString q = lst[1];
        double q2 = q.toDouble();
        evalString(QString("(add-atribute! G "+QString::number(node->id)+QString(" #:q-max ")+QString::number(q2)+QString(")")));
        evalString(QString("(add-atribute! G "+QString::number(node->id)+QString(" #:q-min ")+QString::number(r2)+QString(")")));
    }
}

QString listToString(QList<int> lst)
{
    QString str = "'( ";
    foreach(int x, lst){
        str+=QString::number(x);
        str+=" ";
    }

    str += ")";
    return str;
}

void Environment::visRunFordFulkerson()
{
    VisFordFulkerson dialog(vis_scene->graph_node_ids(), this);
    int response = dialog.exec();

    QList<int> sources = dialog.getSources();
    QList<int> sinks   = dialog.getSinks();
    double     flow    = dialog.getFlow();

    if(response == 1){
        foreach(VisArrow* arrow, vis_scene->graph_arrows.values()){
            fordFulkersonParseAndLabel(arrow);
        }
        foreach(VisNode* node, vis_scene->graph_nodes.values()){
            fordFulkersonParseAndLabel(node);
        }

        if(flow == -1){  // El algoritmo deberá maximizar flujo
            evalString(QString("(run-ford-fulkerson G ")+listToString(sources)+QString(" ")+listToString(sinks)+QString(")"), true);
        }else{           // El algoritmo deberá obtener el flujo dado
            evalString(QString("(run-ford-fulkerson G ")+listToString(sources)+QString(" ")+listToString(sinks)+QString(" ")+QString::number(flow)+QString(")"), true);
        }

    }
}

void Environment::minCostNCParseAndLabel(VisArrow* arrow)
{
    int i = 0;
    // La etiqueta puede tener tres valores "r,q,$" o dos valores "q,$"
    QString label = arrow->label->toPlainText();
    QStringList lst = label.split(",", QString::SkipEmptyParts);


    if(lst.size() >= 3){
        i=1;
        evalString(QString("(add-atribute! G '(")+QString::number(arrow->a_id)+QString(" ")+QString::number(arrow->b_id)+
                   QString(") #:q-min ")+QString::number(lst[0].toDouble())+QString(")"));
    }

    evalString(QString("(add-atribute! G '(")+QString::number(arrow->a_id)+QString(" ")+QString::number(arrow->b_id)+
               QString(") #:q-max ")+QString::number(lst[0+i].toDouble())+QString(")"));

    evalString(QString("(add-atribute! G '(")+QString::number(arrow->a_id)+QString(" ")+QString::number(arrow->b_id)+
               QString(") #:cost ")+QString::number((lst[1+i].remove(0,1)).toDouble())+QString(")"));
}

void Environment::minCostNCParseAndLabel(VisNode* node)
{
    // La etiqueta puede tener uno o dos valores separados por coma representando la capacidad o la restricción minima y capacidad ejemplo "1,2", "3", "1,5"
    QString label = node->label->toPlainText();
    QStringList lst = label.split(",", QString::SkipEmptyParts);
    int size = lst.size();

    if(size == 0){

    }else if(size == 1){
        QString q = lst[0];
        double q2 = q.toDouble();
        evalString(QString("(add-atribute! G "+QString::number(node->id)+QString(" ")+QString(" #:q-max ")+QString::number(q2)+QString(")")));
    }else{
        QString r = lst[0];
        double r2 = r.toDouble();
        QString q = lst[1];
        double q2 = q.toDouble();
        evalString(QString("(add-atribute! G "+QString::number(node->id)+QString(" #:q-max ")+QString::number(q2)+QString(")")));
        evalString(QString("(add-atribute! G "+QString::number(node->id)+QString(" #:q-min ")+QString::number(r2)+QString(")")));
    }
}

void Environment::visRunMinimumCostConstantFlowNC()
{
    VisMinimumCostConstantFlowNC dialog(vis_scene->graph_node_ids(), this);
    int response = dialog.exec();

    QList<int> sources = dialog.getSources();
    QList<int> sinks   = dialog.getSinks();
    double     flow    = dialog.getFlow();

    if(response == 1){
        foreach(VisArrow* arrow, vis_scene->graph_arrows.values()){
            minCostNCParseAndLabel(arrow);
        }
        foreach(VisNode* node, vis_scene->graph_nodes.values()){
            minCostNCParseAndLabel(node);
        }

        evalString(QString("(run-minimum-cost-constant-flow-nc G ")+listToString(sources)+QString(" ")+listToString(sinks)+QString(" ")+QString::number(flow)+QString(")"), true);
    }
}

void Environment::minCostSPParseAndLabel(VisArrow* arrow)
{
    // La etiqueta debe tener dos valores separados por coma representando la capacidad y el costo ejemplo "1,2", "3", "1,5"
    QString label = arrow->label->toPlainText();
    QStringList lst = label.split(",", QString::SkipEmptyParts);

    evalString(QString("(add-atribute! G '(")+QString::number(arrow->a_id)+QString(" ")+QString::number(arrow->b_id)+
               QString(") #:q-max ")+QString::number(lst[0].toDouble())+QString(")"));

    evalString(QString("(add-atribute! G '(")+QString::number(arrow->a_id)+QString(" ")+QString::number(arrow->b_id)+
               QString(") #:cost ")+QString::number((lst[1].remove(0,1)).toDouble())+QString(")"));
}

void Environment::visRunMinimumCostConstantFlowSP()
{
    VisMinimumCostConstantFlowSP dialog(vis_scene->graph_node_ids(), this);
    int response = dialog.exec();

    QList<int> sources = dialog.getSources();
    QList<int> sinks   = dialog.getSinks();
    double     flow    = dialog.getFlow();

    if(response == 1){
        foreach(VisArrow* arrow, vis_scene->graph_arrows.values()){
            minCostSPParseAndLabel(arrow);
        }

        evalString(QString("(run-minimum-cost-constant-flow-sp G ")+listToString(sources)+QString(" ")+listToString(sinks)+QString(" ")+QString::number(flow)+QString(")"), true);
    }
}

void Environment::visCurves(bool with_curves)
{
    this->with_curves = with_curves;
    vis_scene->setWithCurves(with_curves);
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//// Class Private Slots
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void Environment::visAddNode(double x, double y)
{
    int id = vis_scene->id();
    QString code = addNodeCode(id, x, y);
    evalString(code);
}

void Environment::visRemoveNode(int id)
{
    QString code = removeNodeCode(id);
    evalString(code);
}

void Environment::visAddEdge(int aid, int bid)
{
    QString code = addEdgeCode(aid, bid);
    evalString(code);
}

void Environment::visRemoveEdge(int aid, int bid)
{
    QString code = removeEdgeCode(aid, bid);
    evalString(code);
}

void Environment::visAddArrow(int aid, int bid)
{
    QString code = addArrowCode(aid, bid);
    evalString(code);
}

void Environment::visRemoveArrow(int aid, int bid)
{
    QString code = removeArrowCode(aid, bid);
    evalString(code);
}

QPointF Environment::visPosNode(int id)
{
    return vis_scene->visPosNode(id);
}
