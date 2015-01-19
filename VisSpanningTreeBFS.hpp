#ifndef VISSPANNINGTREEBFS_HPP
#define VISSPANNINGTREEBFS_HPP

// Parent class
#include <QDialog>

// Member classes
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class VisSpanningTreeBFS : public QDialog
{
    Q_OBJECT

public:
    VisSpanningTreeBFS(QList<int> ids, QWidget* parent = 0);
    ~VisSpanningTreeBFS();

    int exec();

    int getRootVertex() { return root_vertex; }

private:
    QVBoxLayout* ui_layout;
    QComboBox* ui_select;
    QLabel* ui_description;
    QDialogButtonBox* ui_buttons;

    int root_vertex;
};

#endif // VISSPANNINGTREEBFS_HPP
