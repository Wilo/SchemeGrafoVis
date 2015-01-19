#include "VisBipartiteness.hpp"

VisBipartiteness::VisBipartiteness(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Bipartiteness");

    ui_description = new QLabel;
    ui_description->setWordWrap(true);
    ui_description->setText("Chek if the graph is bipartite.");

    ui_buttons = new QDialogButtonBox(QDialogButtonBox::Ok |
                                      QDialogButtonBox::Cancel);

    connect(ui_buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui_buttons, SIGNAL(rejected()), this, SLOT(reject()));

    ui_layout = new QVBoxLayout;
    ui_layout->addWidget(ui_description);
    ui_layout->addWidget(ui_buttons);

    setLayout(ui_layout);
}

VisBipartiteness::~VisBipartiteness()
{
    delete ui_description;
    delete ui_buttons;
    delete ui_layout;
}
