#include "VisMainWindow.hpp"

#include <QStatusBar>
#include <QMessageBox>

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//// Auxiliary procedures
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void init_toolbar_button(QToolButton* b, QString text, bool checked = false)
{
    b->setText(text);
    b->setCheckable(true);
    b->setChecked(checked);
}

void init_toolbar_slider(QSlider* s)
{
    s->setMinimum(25);
    s->setMaximum(250);
    s->setValue(100);
}

void init_toolbar_combobox(QComboBox* cb)
{
    cb->addItem("Undirected");
    cb->addItem("Directed");
}

void init_action(QAction* a, QString sc, QMenu* m, bool e = true)
{
    a->setShortcut(QKeySequence(sc));
    m->addAction(a);
    a->setEnabled(e);
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//// Class procedures
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
VisMainWindow::VisMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("GrafoVis");

    environment = new Environment;
    setCentralWidget(environment);

    // Menus initialization
    {
        ui_menu_file = menuBar()->addMenu("file");
        ui_menu_edit = menuBar()->addMenu("edit");
        ui_menu_algorithms = menuBar()->addMenu("algorithms");
        ui_menu_about = menuBar()->addMenu("about");
    }

    // Toolbar initialization
    {
        ui_toolbar_button_edit = new QToolButton;
        init_toolbar_button(ui_toolbar_button_edit, "select", true);

        ui_toolbar_button_vertex = new QToolButton;
        init_toolbar_button(ui_toolbar_button_vertex, "vertex");

        ui_toolbar_button_edge = new QToolButton;
        init_toolbar_button(ui_toolbar_button_edge, "edge");

        ui_toolbar_button_arrow = new QToolButton;
        ui_toolbar_button_arrow->setEnabled(false);
        init_toolbar_button(ui_toolbar_button_arrow, "arrow");

        ui_toolbar_buttongroup = new QButtonGroup;
        ui_toolbar_buttongroup->addButton(ui_toolbar_button_edit,   0);
        ui_toolbar_buttongroup->addButton(ui_toolbar_button_vertex, 1);
        ui_toolbar_buttongroup->addButton(ui_toolbar_button_edge,   2);
        ui_toolbar_buttongroup->addButton(ui_toolbar_button_arrow,  3);

        ui_toolbar_label_zoom_text  = new QLabel("zoom:");
        ui_toolbar_label_zoom_value = new QLabel("100");

        ui_toolbar_slider_zoom = new QSlider(Qt::Horizontal);
        init_toolbar_slider(ui_toolbar_slider_zoom);

        ui_toolbar_combobox_graph_type = new QComboBox;
        init_toolbar_combobox(ui_toolbar_combobox_graph_type);

        ui_toolbar_button_step = new QPushButton("&step");
        ui_toolbar_button_step->setEnabled(false);

        ui_toolbar_checkbox_step = new QCheckBox;
        ui_toolbar_checkbox_step->setChecked(false);

        ui_toolbar = addToolBar("Tools");
        ui_toolbar->addWidget(ui_toolbar_button_edit);
        ui_toolbar->addWidget(ui_toolbar_button_vertex);
        ui_toolbar->addWidget(ui_toolbar_button_edge);
        ui_toolbar->addWidget(ui_toolbar_button_arrow);
        ui_toolbar->addSeparator();
        ui_toolbar->addWidget(ui_toolbar_label_zoom_text);
        ui_toolbar->addWidget(ui_toolbar_slider_zoom);
        ui_toolbar->addWidget(ui_toolbar_label_zoom_value);
        ui_toolbar->addSeparator();
        ui_toolbar->addWidget(ui_toolbar_combobox_graph_type);
        ui_toolbar->addSeparator();
        ui_toolbar->addWidget(ui_toolbar_button_step);
        ui_toolbar->addWidget(ui_toolbar_checkbox_step);
    }

    // Actions initialization
    {
        ui_action_exit = new QAction("Exit", this);
        init_action(ui_action_exit, "Ctrl+Q", ui_menu_file);

        ui_action_delete_selection = new QAction("Delete selected", this);
        init_action(ui_action_delete_selection, "DEL", ui_menu_edit);

        ui_action_clean_graph = new QAction("Clean colored graph", this);
        init_action(ui_action_clean_graph, "Ctrl+C", ui_menu_edit);

        ui_action_unlabel_graph = new QAction("Unlabel graph", this);
        init_action(ui_action_unlabel_graph, "Ctrl+U", ui_menu_edit);

        ui_action_erase_graph = new QAction("Erase graph", this);
        init_action(ui_action_erase_graph, "Ctrl+E", ui_menu_edit);

        ui_action_run_bipartiteness = new QAction("Run Bipartiteness algorithm", this);
        init_action(ui_action_run_bipartiteness, "F2", ui_menu_algorithms);

        ui_action_run_spanning_tree_bfs = new QAction("Run Spanning Tree algorithm", this);
        init_action(ui_action_run_spanning_tree_bfs, "F3", ui_menu_algorithms);

        ui_action_run_spanning_tree_dfs = new QAction("Run Spanning Tree algorithm", this);
        init_action(ui_action_run_spanning_tree_dfs, "F4", ui_menu_algorithms);

        ui_action_run_prim = new QAction("Run Prim algorithm", this);
        init_action(ui_action_run_prim, "F6", ui_menu_algorithms);

        ui_action_run_kruskal = new QAction("Run Kruskal algorithm", this);
        init_action(ui_action_run_kruskal, "F7", ui_menu_algorithms);

        ui_action_run_dijkstra = new QAction("Run Dijkstra algorithm", this);
        init_action(ui_action_run_dijkstra, "F8", ui_menu_algorithms, false);

        ui_action_run_floyd_warshall = new QAction("Run Floyd-Warshall algorithm", this);
        init_action(ui_action_run_floyd_warshall, "F9", ui_menu_algorithms, false);

        ui_action_run_ford_fulkerson = new QAction("Run Ford-Fulkerson algorithm", this);
        init_action(ui_action_run_ford_fulkerson, "F10", ui_menu_algorithms, false);

        ui_action_run_min_cost_negative_cycles = new QAction("Run Minimum Cost Constant Flow algorithm", this);
        init_action(ui_action_run_min_cost_negative_cycles, "F11", ui_menu_algorithms, false);

        ui_action_run_min_cost_shortests_paths = new QAction("Run Minimum Cost Constant Flow algorithm", this);
        init_action(ui_action_run_min_cost_shortests_paths, "F12", ui_menu_algorithms, false);

        ui_action_help = new QAction("Help", this);
        init_action(ui_action_help, "Ctrl+H", ui_menu_about);

        ui_action_info = new QAction("More info", this);
        init_action(ui_action_info, "Ctrl+?", ui_menu_about);

        ui_action_toggle_curves = new QAction("With curves", this);
        ui_action_toggle_curves->setCheckable(true);
        ui_action_toggle_curves->setChecked(false);
        init_action(ui_action_toggle_curves, "Ctrl+Alt+C", ui_menu_edit);
    }

    // Connections
    {
        connect(ui_toolbar_buttongroup, SIGNAL(buttonClicked(int)),
                environment,            SLOT(visToolSelected(int)));
        connect(ui_toolbar_slider_zoom, SIGNAL(valueChanged(int)),
                ui_toolbar_label_zoom_value, SLOT(setNum(int)));
        connect(ui_toolbar_slider_zoom, SIGNAL(valueChanged(int)),
                environment,            SLOT(visChangeZoom(int)));
        connect(ui_toolbar_combobox_graph_type, SIGNAL(activated(int)),
                this,                           SLOT(visSetGraphType(int)));
        connect(ui_toolbar_combobox_graph_type, SIGNAL(activated(int)),
                environment,                    SLOT(visSetGraphType(int)));
        connect(ui_toolbar_button_step, SIGNAL(clicked()),
                this,                   SLOT(visStepDone()));
        connect(environment, SIGNAL(visStepWait(QString)),
                this,        SLOT(visStepWait(QString)));
        connect(ui_action_exit, SIGNAL(triggered()),
                this,           SLOT(visExitApplication()));
        connect(ui_action_delete_selection, SIGNAL(triggered()),
                environment,                SLOT(visRemoveSelection()));
        connect(ui_action_clean_graph, SIGNAL(triggered()),
                environment,           SLOT(visCleanGraph()));
        connect(ui_action_erase_graph, SIGNAL(triggered()),
                environment,           SLOT(visEraseGraph()));
        connect(ui_action_unlabel_graph, SIGNAL(triggered()),
                environment,             SLOT(visUnlabelGraph()));
        connect(ui_action_run_bipartiteness, SIGNAL(triggered()),
                environment,                 SLOT(visRunBipartiteness()));
        connect(ui_action_run_spanning_tree_bfs, SIGNAL(triggered()),
                environment,                     SLOT(visRunSpanningTreeBFS()));
        connect(ui_action_run_spanning_tree_dfs, SIGNAL(triggered()),
                environment,                     SLOT(visRunSpanningTreeDFS()));
        connect(ui_action_run_prim, SIGNAL(triggered()),
                environment,        SLOT(visRunPrim()));
        connect(ui_action_run_kruskal, SIGNAL(triggered()),
                environment,           SLOT(visRunKruskal()));
        connect(ui_action_run_dijkstra, SIGNAL(triggered()),
                environment,            SLOT(visRunDijkstra()));
        connect(ui_action_run_floyd_warshall, SIGNAL(triggered()),
                environment,                  SLOT(visRunFloydWarshall()));
        connect(ui_action_run_ford_fulkerson, SIGNAL(triggered()),
                environment,                  SLOT(visRunFordFulkerson()));
        connect(ui_action_run_min_cost_negative_cycles, SIGNAL(triggered()),
                environment,                            SLOT(visRunMinimumCostConstantFlowNC()));
        connect(ui_action_run_min_cost_shortests_paths, SIGNAL(triggered()),
                environment,                            SLOT(visRunMinimumCostConstantFlowSP()));
        connect(ui_action_help, SIGNAL(triggered()),
                this,           SLOT(visShowHelp()));
        connect(ui_action_info, SIGNAL(triggered()),
                this,           SLOT(visShowInfo()));
        connect(environment, SIGNAL(visShowMessage(QString)),
                this,        SLOT(visShowMessage(QString)));

        connect(ui_action_toggle_curves, SIGNAL(toggled(bool)),
                environment,             SLOT(visCurves(bool)));
    }
}

VisMainWindow::~VisMainWindow()
{
    delete ui_toolbar_button_edit;
    delete ui_toolbar_button_vertex;
    delete ui_toolbar_button_edge;
    delete ui_toolbar_button_arrow;
    delete ui_toolbar_buttongroup;
    delete ui_toolbar_label_zoom_text;
    delete ui_toolbar_label_zoom_value;
    delete ui_toolbar_slider_zoom;
    delete ui_toolbar_combobox_graph_type;
    delete ui_toolbar_button_step;
    delete ui_toolbar_checkbox_step;

    delete ui_action_exit;
    delete ui_action_delete_selection;
    delete ui_action_clean_graph;
    delete ui_action_unlabel_graph;
    delete ui_action_erase_graph;
    delete ui_action_run_bipartiteness;
    delete ui_action_run_spanning_tree_bfs;
    delete ui_action_run_spanning_tree_dfs;
    delete ui_action_run_prim;
    delete ui_action_run_kruskal;
    delete ui_action_run_dijkstra;
    delete ui_action_run_floyd_warshall;
    delete ui_action_run_ford_fulkerson;
    delete ui_action_run_min_cost_negative_cycles;
    delete ui_action_run_min_cost_shortests_paths;
    delete ui_action_help;
    delete ui_action_info;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//// Class Slots
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void VisMainWindow::visSetGraphType(int type)
{
    if(type == 1){
        ui_toolbar_button_edit->setChecked(true);
        if(environment->graphType() == VisGraphicsScene::UNDIRECTED){
            ui_toolbar_button_arrow->setEnabled(true);
            ui_toolbar_button_edge->setEnabled(false);

            ui_action_run_bipartiteness->setEnabled(false);
            ui_action_run_spanning_tree_bfs->setEnabled(false);
            ui_action_run_spanning_tree_dfs->setEnabled(false);
            ui_action_run_prim->setEnabled(false);
            ui_action_run_kruskal->setEnabled(false);
            ui_action_run_dijkstra->setEnabled(true);
            ui_action_run_floyd_warshall->setEnabled(true);
            ui_action_run_ford_fulkerson->setEnabled(true);
            ui_action_run_min_cost_negative_cycles->setEnabled(true);
            ui_action_run_min_cost_shortests_paths->setEnabled(true);

        }
    }else if(type == 0){
        ui_toolbar_button_edit->setChecked(true);
        if(environment->graphType() == VisGraphicsScene::DIRECTED){
            ui_toolbar_button_arrow->setEnabled(false);
            ui_toolbar_button_edge->setEnabled(true);

            ui_action_run_bipartiteness->setEnabled(true);
            ui_action_run_spanning_tree_bfs->setEnabled(true);
            ui_action_run_spanning_tree_dfs->setEnabled(true);
            ui_action_run_prim->setEnabled(true);
            ui_action_run_kruskal->setEnabled(true);
            ui_action_run_dijkstra->setEnabled(false);
            ui_action_run_floyd_warshall->setEnabled(false);
            ui_action_run_ford_fulkerson->setEnabled(false);
            ui_action_run_min_cost_negative_cycles->setEnabled(false);
            ui_action_run_min_cost_shortests_paths->setEnabled(false);
        }
    }
}

void VisMainWindow::visExitApplication()
{
    close();
}

void VisMainWindow::visShowHelp()
{
    QMessageBox dialog(this);
    dialog.setWindowTitle("Help");
    dialog.setText("Under construction...");
    dialog.exec();
}

void VisMainWindow::visShowInfo()
{
    QMessageBox dialog(this);
    dialog.setWindowTitle("Info");
    dialog.setText("Under construction...");
    dialog.exec();
}

void VisMainWindow::visStepDone()
{
    ui_toolbar_button_step->setEnabled(false);
    environment->on_pause = false;
    statusBar()->hide();
}

void VisMainWindow::visStepWait(QString message)
{
    statusBar()->show();
    statusBar()->showMessage(message);
    if(ui_toolbar_checkbox_step->isChecked())
        ui_toolbar_button_step->setEnabled(true);
    else
        visStepDone();
}

void VisMainWindow::visShowMessage(QString message)
{
    QMessageBox* dialog = new QMessageBox;
    dialog->setWindowTitle("Message");
    dialog->setText(message);
    dialog->exec();
    visStepDone();
}
