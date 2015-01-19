#ifndef VISSPANNINGTREEDFS_HPP
#define VISSPANNINGTREEDFS_HPP

// Parent class
#include <QDialog>

// Member classes
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class VisSpanningTreeDFS : public QDialog
{
    Q_OBJECT

public:
    VisSpanningTreeDFS(QList<int> ids, QWidget* parent = 0);
    ~VisSpanningTreeDFS();

    int exec();

    int getRootVertex() { return root_vertex; }

private:
    QVBoxLayout* ui_layout;
    QComboBox* ui_select;
    QLabel* ui_description;
    QDialogButtonBox* ui_buttons;

    int root_vertex;
};

#endif // VISSPANNINGTREEDFS_HPP
