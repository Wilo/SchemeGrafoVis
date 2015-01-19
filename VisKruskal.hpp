#ifndef VISKRUSKAL_HPP
#define VISKRUSKAL_HPP

// Parent class
#include <QDialog>

// Member classes
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>

class VisKruskal : public QDialog
{
    Q_OBJECT

public:
    VisKruskal(QWidget* parent = 0);
    ~VisKruskal();

    int exec();

private:
    QVBoxLayout* ui_layout;
    QLabel* ui_description;
    QDialogButtonBox* ui_buttons;
};

#endif // VISKRUSKAL_HPP
