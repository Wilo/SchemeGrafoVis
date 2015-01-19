#include "VisSpanningTreeDFS.hpp"
#include <QHBoxLayout>

VisSpanningTreeDFS::VisSpanningTreeDFS(QList<int> ids, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Spanning Tree DFS");

    ui_description = new QLabel;
    ui_description->setWordWrap(true);
    ui_description->setText("Obtain a Spanning Tree using a Depth First Search.");

    ui_select = new QComboBox;
    foreach(int id, ids){
        ui_select->addItem(QString::number(id));
    }

    QLabel* ui_select_label = new QLabel("Root vertex:");
    ui_select_label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    QHBoxLayout* ui_select_layout = new QHBoxLayout;
    ui_select_layout->addWidget(ui_select_label);
    ui_select_layout->addWidget(ui_select);


    ui_buttons = new QDialogButtonBox(QDialogButtonBox::Ok |
                                      QDialogButtonBox::Cancel);

    connect(ui_buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui_buttons, SIGNAL(rejected()), this, SLOT(reject()));

    ui_layout = new QVBoxLayout;
    ui_layout->addWidget(ui_description);
    ui_layout->addStretch();
    ui_layout->addLayout(ui_select_layout);
    ui_layout->addWidget(ui_buttons);

    setLayout(ui_layout);
}

VisSpanningTreeDFS::~VisSpanningTreeDFS()
{
    delete ui_description;
    delete ui_buttons;
    delete ui_layout;
}

int VisSpanningTreeDFS::exec()
{
    int response = QDialog::exec();
    root_vertex = ui_select->currentText().toInt();

    return response;
}
