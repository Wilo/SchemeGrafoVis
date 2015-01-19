#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T05:47:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SchemeGrafoVis
TEMPLATE = app


SOURCES += main.cpp\
        VisMainWindow.cpp \
    Environment.cpp \
    VisGraphicsScene.cpp \
    VisNode.cpp \
    VisLabel.cpp \
    VisBezierCurve.cpp \
    VisPoint.cpp \
    VisEdge.cpp \
    VisArrow.cpp \
    VisGraphicsView.cpp \
    VisBipartiteness.cpp \
    VisSpanningTreeBFS.cpp \
    VisSpanningTreeDFS.cpp \
    VisPrim.cpp \
    VisKruskal.cpp \
    VisDijkstra.cpp \
    VisFordFulkerson.cpp \
    VisFloydWarshall.cpp \
    VisMinimumCostConstantFlowNC.cpp \
    VisMinimumCostConstantFlowSP.cpp

HEADERS  += VisMainWindow.hpp \
    Environment.hpp \
    VisGraphicsScene.hpp \
    VisNode.hpp \
    VisLabel.hpp \
    VisBezierCurve.hpp \
    VisPoint.hpp \
    VisEdge.hpp \
    VisArrow.hpp \
    VisGraphicsView.hpp \
    VisBipartiteness.hpp \
    VisSpanningTreeBFS.hpp \
    VisSpanningTreeDFS.hpp \
    VisPrim.hpp \
    VisKruskal.hpp \
    VisDijkstra.hpp \
    VisFordFulkerson.hpp \
    VisFloydWarshall.hpp \
    VisMinimumCostConstantFlowNC.hpp \
    VisMinimumCostConstantFlowSP.hpp

QMAKE_CXXFLAGS += -pthread -I/usr/include/guile/2.0
QMAKE_CFLAGS += -pthread -I/usr/include/guile/2.0
QMAKE_LIBS += -lguile-2.0 -lgc
