#ifndef VISMinimumCostConstantFlowSP_HPP
#define VISMinimumCostConstantFlowSP_HPP

// Parent class
#include <QDialog>

// Member classes
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QDoubleSpinBox>
#include <QCheckBox>

class VisMinimumCostConstantFlowSP : public QDialog
{
    Q_OBJECT

public:
    VisMinimumCostConstantFlowSP(QList<int> ids, QWidget* parent = 0);
    ~VisMinimumCostConstantFlowSP();

    int exec();

    QList<int> getSources() { return sources; }
    QList<int> getSinks()   { return sinks; }
    double     getFlow()    { return constant; }

private:
    QVBoxLayout* ui_layout;
    QComboBox* ui_select;
    QLabel* ui_description;
    QDialogButtonBox* ui_buttons;

    QLabel* ui_sources_label;
    QLabel* ui_sinks_label;
    QLabel* ui_constant_label;

    QListWidget*    ui_sources;
    QListWidget*    ui_sinks;
    QDoubleSpinBox* ui_constant;

    QVBoxLayout* ui_sources_layout;
    QVBoxLayout* ui_sinks_layout;
    QHBoxLayout* ui_constant_layout;
    QHBoxLayout* ui_options_layout;

    QList<int> sources;
    QList<int> sinks;
    double constant;
};

#endif // VISMinimumCostConstantFlowSP_HPP
