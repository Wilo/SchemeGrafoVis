#include "VisDijkstra.hpp"
#include <QHBoxLayout>

VisDijkstra::VisDijkstra(QList<int> ids, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Dijkstra");

    ui_description = new QLabel;
    ui_description->setWordWrap(true);
    ui_description->setText("Obtain the shortest path from a starting vertex to an ending vertex using Dijkstra's algorithm");

    ui_select_starting = new QComboBox;
    foreach(int id, ids){
        ui_select_starting->addItem(QString::number(id));
    }
    ui_select_starting_label = new QLabel("Start vertex:");
    ui_select_starting_label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui_select_starting_layout = new QHBoxLayout;
    ui_select_starting_layout->addWidget(ui_select_starting_label);
    ui_select_starting_layout->addWidget(ui_select_starting);

    ui_select_ending = new QComboBox;
    foreach(int id, ids){
        ui_select_ending->addItem(QString::number(id));
    }
    ui_select_ending_label = new QLabel("End vertex:");
    ui_select_ending_label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui_select_ending_layout = new QHBoxLayout;
    ui_select_ending_layout->addWidget(ui_select_ending_label);
    ui_select_ending_layout->addWidget(ui_select_ending);


    ui_buttons = new QDialogButtonBox(QDialogButtonBox::Ok |
                                      QDialogButtonBox::Cancel);

    connect(ui_buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui_buttons, SIGNAL(rejected()), this, SLOT(reject()));

    ui_layout = new QVBoxLayout;
    ui_layout->addWidget(ui_description);
    ui_layout->addStretch();
    ui_layout->addLayout(ui_select_starting_layout);
    ui_layout->addLayout(ui_select_ending_layout);
    ui_layout->addWidget(ui_buttons);

    setLayout(ui_layout);

    starting_vertex = -1;
    ending_vertex = -1;
}

VisDijkstra::~VisDijkstra()
{
    delete ui_select_ending;
    delete ui_select_ending_label;
    delete ui_select_ending_layout;

    delete ui_select_starting;
    delete ui_select_starting_label;
    delete ui_select_starting_layout;

    delete ui_description;
    delete ui_buttons;
    delete ui_layout;
}

int VisDijkstra::exec()
{
    int response = QDialog::exec();
    starting_vertex = ui_select_starting->currentText().toInt();
    ending_vertex = ui_select_ending->currentText().toInt();

    return response;
}
