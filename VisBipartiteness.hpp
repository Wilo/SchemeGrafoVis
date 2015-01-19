#ifndef VISBIPARTITENESS_HPP
#define VISBIPARTITENESS_HPP

// Parent class
#include <QDialog>

// Member classes
#include <QLabel>
#include <QVBoxLayout>
#include <QDialogButtonBox>

class VisBipartiteness : public QDialog
{
    Q_OBJECT

public:
    VisBipartiteness(QWidget* parent = 0);
    ~VisBipartiteness();

private:
    QVBoxLayout* ui_layout;
    QDialogButtonBox* ui_buttons;
    QLabel* ui_description;
};

#endif // VISBIPARTITENESS_HPP
