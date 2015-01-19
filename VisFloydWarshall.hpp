#ifndef VISFloydWarshall_HPP
#define VISFloydWarshall_HPP

// Parent class
#include <QDialog>

// Member classes
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>

class VisFloydWarshall : public QDialog
{
    Q_OBJECT

public:
    VisFloydWarshall(QWidget* parent = 0);
    ~VisFloydWarshall();

    int exec();

private:
    QVBoxLayout* ui_layout;
    QLabel* ui_description;
    QDialogButtonBox* ui_buttons;
};

#endif // VISFloydWarshall_HPP
