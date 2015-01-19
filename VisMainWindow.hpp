#ifndef VISMAINWINDOW_HPP
#define VISMAINWINDOW_HPP

// Parent class
#include <QMainWindow>

// Member classes
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QButtonGroup>
#include <QSlider>
#include <QComboBox>
#include <QToolButton>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QCheckBox>
#include <Environment.hpp>

class VisMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    VisMainWindow(QWidget *parent = 0);
    ~VisMainWindow();

private:
    // Menubar menus
    QMenu* ui_menu_file;
    QMenu* ui_menu_edit;
    QMenu* ui_menu_algorithms;
    QMenu* ui_menu_about;

    // Toolbar
    QToolBar*     ui_toolbar;
    QToolButton*  ui_toolbar_button_edit;
    QToolButton*  ui_toolbar_button_vertex;
    QToolButton*  ui_toolbar_button_edge;
    QToolButton*  ui_toolbar_button_arrow;
    QButtonGroup* ui_toolbar_buttongroup;
    QLabel*       ui_toolbar_label_zoom_text;
    QLabel*       ui_toolbar_label_zoom_value;
    QSlider*      ui_toolbar_slider_zoom;
    QComboBox*    ui_toolbar_combobox_graph_type;
    QPushButton*  ui_toolbar_button_step;
    QCheckBox*    ui_toolbar_checkbox_step;

    // Actions
    QAction* ui_action_exit;
    QAction* ui_action_delete_selection;
    QAction* ui_action_clean_graph;
    QAction* ui_action_unlabel_graph;
    QAction* ui_action_erase_graph;
    QAction* ui_action_run_bipartiteness;
    QAction* ui_action_run_spanning_tree_bfs;
    QAction* ui_action_run_spanning_tree_dfs;
    QAction* ui_action_run_prim;
    QAction* ui_action_run_kruskal;
    QAction* ui_action_run_dijkstra;
    QAction* ui_action_run_floyd_warshall;
    QAction* ui_action_run_ford_fulkerson;
    QAction* ui_action_run_min_cost_negative_cycles;
    QAction* ui_action_run_min_cost_shortests_paths;
    QAction* ui_action_help;
    QAction* ui_action_info;

    QAction* ui_action_toggle_curves;

    // Environment
    Environment* environment;

public slots:
    void visSetGraphType(int);
    void visExitApplication();
    void visShowHelp();
    void visShowInfo();
    void visStepDone();
    void visStepWait(QString);
    void visShowMessage(QString);
};

#endif // VISMAINWINDOW_HPP
