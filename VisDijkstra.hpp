#ifndef VISDIJKSTRA_HPP
#define VISDIJKSTRA_HPP

// Parent class
#include <QDialog>

// Member classes
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class VisDijkstra : public QDialog
{
    Q_OBJECT

public:
    VisDijkstra(QList<int> ids, QWidget* parent = 0);
    ~VisDijkstra();

    int exec();

    int getStartingVertex() { return starting_vertex; }
    int getEndingVertex() { return ending_vertex; }

private:
    QVBoxLayout* ui_layout;
    QLabel* ui_description;

    QComboBox*   ui_select_starting;
    QLabel*      ui_select_starting_label;
    QHBoxLayout* ui_select_starting_layout;

    QComboBox*   ui_select_ending;
    QLabel*      ui_select_ending_label;
    QHBoxLayout* ui_select_ending_layout;

    QDialogButtonBox* ui_buttons;

    int starting_vertex;
    int ending_vertex;
};

#endif // VISDIJKSTRA_HPP
