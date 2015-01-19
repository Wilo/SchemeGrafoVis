#include "VisKruskal.hpp"
#include <QHBoxLayout>

VisKruskal::VisKruskal(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Kruskal");

    ui_description = new QLabel;
    ui_description->setWordWrap(true);
    ui_description->setText("Obtain a Minimum Spanning Forest using Kruskal algorithm.");

    ui_buttons = new QDialogButtonBox(QDialogButtonBox::Ok |
                                      QDialogButtonBox::Cancel);

    connect(ui_buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui_buttons, SIGNAL(rejected()), this, SLOT(reject()));

    ui_layout = new QVBoxLayout;
    ui_layout->addWidget(ui_description);
    ui_layout->addStretch();
    ui_layout->addWidget(ui_buttons);

    setLayout(ui_layout);
}

VisKruskal::~VisKruskal()
{
    delete ui_description;
    delete ui_buttons;
    delete ui_layout;
}

int VisKruskal::exec()
{
    int response = QDialog::exec();

    return response;
}
