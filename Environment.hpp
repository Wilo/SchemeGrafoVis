#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

// Parent class
#include <QWidget>

// Member classes
#include <QHBoxLayout>
#include <VisGraphicsScene.hpp>
#include <VisGraphicsView.hpp>

// Foreign language includes
#include <libguile.h>

class Environment : public QWidget
{
    Q_OBJECT
public:
    friend SCM scmPaintNode(SCM, SCM, SCM);
    friend SCM scmUnpaintNode(SCM);
    friend SCM scmPaintEdge(SCM, SCM);
    friend SCM scmUnpaintEdge(SCM, SCM);
    friend SCM scmPaintArrow(SCM, SCM);
    friend SCM scmUnpaintArrow(SCM, SCM);
    friend SCM scmLabelNode(SCM, SCM);
    friend SCM scmLabelEdge(SCM, SCM, SCM);
    friend SCM scmLabelArrow(SCM, SCM, SCM);
    friend SCM scmColorNode(SCM, SCM, SCM, SCM, SCM);
    friend SCM scmUncolorNode(SCM);
    friend SCM scmColorEdge(SCM, SCM, SCM, SCM, SCM, SCM);
    friend SCM scmUncolorEdge(SCM, SCM);
    friend SCM scmColorArrow(SCM, SCM, SCM, SCM, SCM, SCM);
    friend SCM scmUncolorArrow(SCM, SCM);
    friend SCM scmColorNodeLabel(SCM, SCM, SCM, SCM, SCM);
    friend SCM scmUncolorNodeLabel(SCM);
    friend SCM scmColorEdgeLabel(SCM, SCM, SCM, SCM, SCM, SCM);
    friend SCM scmUncolorEdgeLabel(SCM, SCM);
    friend SCM scmColorArrowLabel(SCM, SCM, SCM, SCM, SCM, SCM);
    friend SCM scmUncolorArrowLabel(SCM, SCM);
    friend SCM scmWait(SCM);
    friend SCM scmShowMessage(SCM);

    friend SCM visPosNode(SCM id);
    friend SCM visMoveNode(SCM id, SCM dx, SCM dy);

    explicit Environment(QWidget *parent = 0);
    ~Environment();

    SCM evalString(QString, bool = false);
    void evalFile(QString);
    void newGraph(VisGraphicsScene::GRAPH);
    void delGraph(VisGraphicsScene::GRAPH, bool thread);

    QString addNodeCode(int, double, double);
    QString removeNodeCode(int);
    QString addEdgeCode(int,int);
    QString removeEdgeCode(int,int);
    QString addArrowCode(int,int);
    QString removeArrowCode(int,int);

    bool on_pause;
    bool with_curves;

    VisGraphicsScene::GRAPH graphType() {return vis_scene->graph_type;}

    QPointF visPosNode(int id);


private:
    VisGraphicsScene* vis_scene;

    VisGraphicsView* vis_view;

    QHBoxLayout* ui_layout;

    void initForeign();

    void fordFulkersonParseAndLabel(VisArrow* arrow);
    void fordFulkersonParseAndLabel(VisNode* node);
    void minCostNCParseAndLabel(VisArrow* arrow);
    void minCostNCParseAndLabel(VisNode* node);
    void minCostSPParseAndLabel(VisArrow* arrow);

signals:
    // To VisMainWindow
    void visStepWait(QString);
    void visShowMessage(QString);

    // To VisGraphicsScene
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


public slots:
    // From VisMainWindow
    void visChangeZoom(int);
    void visToolSelected(int);
    void visSetGraphType(int);
    void visRemoveSelection();
    void visCleanGraph();
    void visEraseGraph();
    void visUnlabelGraph();
    void visRunBipartiteness();
    void visRunSpanningTreeBFS();
    void visRunSpanningTreeDFS();
    void visRunPrim();
    void visRunKruskal();
    void visRunDijkstra();
    void visRunFloydWarshall();
    void visRunFordFulkerson();
    void visRunMinimumCostConstantFlowNC();
    void visRunMinimumCostConstantFlowSP();
    void visCurves(bool);

private slots:
    // From VisGraphicsScene
    void visAddNode(double x, double y);
    void visRemoveNode(int id);
    void visAddEdge(int aid, int bid);
    void visRemoveEdge(int aid, int bid);
    void visAddArrow(int aid, int bid);
    void visRemoveArrow(int aid, int bid);
};

#endif // ENVIRONMENT_HPP
