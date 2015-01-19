#ifndef VISPRIM_HPP
#define VISPRIM_HPP

// Parent class
#include <QDialog>

// Member classes
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>

class VisPrim : public QDialog
{
    Q_OBJECT

public:
    VisPrim(QList<int> ids, QWidget* parent = 0);
    ~VisPrim();

    int exec();

    int getRootVertex() { return root_vertex; }

private:
    QVBoxLayout* ui_layout;
    QComboBox* ui_select;
    QLabel* ui_description;
    QDialogButtonBox* ui_buttons;

    QLabel* ui_select_label;
    QHBoxLayout* ui_select_layout;

    int root_vertex;
};

#endif // VISPRIM_HPP
