#include "VisFloydWarshall.hpp"
#include <QHBoxLayout>

VisFloydWarshall::VisFloydWarshall(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("FloydWarshall");

    ui_description = new QLabel;
    ui_description->setWordWrap(true);
    ui_description->setText("Obtain all the shortests paths of the graph using Floyd-Warshall algorithm.");

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

VisFloydWarshall::~VisFloydWarshall()
{
    delete ui_description;
    delete ui_buttons;
    delete ui_layout;
}

int VisFloydWarshall::exec()
{
    int response = QDialog::exec();

    return response;
}
