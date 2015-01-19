#include "VisFordFulkerson.hpp"
#include <QHBoxLayout>

#include <QtDebug>

VisFordFulkerson::VisFordFulkerson(QList<int> ids, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Floyd Warshall");

    ui_description = new QLabel;
    ui_description->setWordWrap(true);
    ui_description->setText("Obtain the maximum flow for the network with the Ford-Fulkerson algorithm.");

    ui_sources_label = new QLabel("Sources:");
    ui_sources = new QListWidget;
    ui_sources->setSelectionMode(QListWidget::ExtendedSelection);
    ui_sources_layout = new QVBoxLayout;
    ui_sources_layout->addWidget(ui_sources_label);
    ui_sources_layout->addWidget(ui_sources);

    ui_sinks_label = new QLabel("Sinks:");
    ui_sinks = new QListWidget;
    ui_sinks->setSelectionMode(QListWidget::ExtendedSelection);
    ui_sinks_layout = new QVBoxLayout;
    ui_sinks_layout->addWidget(ui_sinks_label);
    ui_sinks_layout->addWidget(ui_sinks);

    foreach(int id, ids){
        ui_sources->addItem(QString::number(id));
        ui_sinks->addItem(QString::number(id));
    }

    ui_options_layout = new QHBoxLayout;
    ui_options_layout->addLayout(ui_sources_layout);
    ui_options_layout->addLayout(ui_sinks_layout);

    ui_constant_label = new QLabel("fixed flow:");
    ui_constant_label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui_constant = new QDoubleSpinBox;
    ui_constant->setMinimum(0.0);
    ui_constant->setDecimals(1);
    ui_constant_enabler = new QCheckBox;
    ui_constant_enabler->setChecked(true);
    ui_constant_layout = new QHBoxLayout;
    ui_constant_layout->addWidget(ui_constant_label);
    ui_constant_layout->addWidget(ui_constant);
    ui_constant_layout->addWidget(ui_constant_enabler);
    connect(ui_constant_enabler, SIGNAL(clicked(bool)),
            ui_constant, SLOT(setEnabled(bool)));


    ui_buttons = new QDialogButtonBox(QDialogButtonBox::Ok |
                                      QDialogButtonBox::Cancel);

    connect(ui_buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui_buttons, SIGNAL(rejected()), this, SLOT(reject()));

    ui_layout = new QVBoxLayout;
    ui_layout->addWidget(ui_description);
    ui_layout->addStretch();
    ui_layout->addLayout(ui_options_layout);
    ui_layout->addLayout(ui_constant_layout);
    ui_layout->addWidget(ui_buttons);

    setLayout(ui_layout);
    ui_constant_enabler->toggle();
    ui_constant->setEnabled(false);
}

VisFordFulkerson::~VisFordFulkerson()
{
    delete ui_description;
    delete ui_buttons;
    delete ui_layout;
}

int VisFordFulkerson::exec()
{
    int response = QDialog::exec();

    foreach(QListWidgetItem* li, ui_sources->selectedItems()){
        sources.append(li->text().toInt());
    }

    foreach(QListWidgetItem* li, ui_sinks->selectedItems()){
        sinks.append(li->text().toInt());
    }

    if(ui_constant_enabler->isChecked())
        constant = ui_constant->value();
    else
        constant = -1;

    return response;
}
