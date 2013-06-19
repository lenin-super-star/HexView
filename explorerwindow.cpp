#include <QVBoxLayout>

#include "explorerwindow.h"

ExplorerWindow::ExplorerWindow(QWidget *parent)
    :QWidget(parent)
    ,toolbar(new QToolBar)
{
    this->setObjectName("EXPLORERWINDOW");
    this->toolbar->setObjectName("EXPLORERWINDOW_TOOLBAR");
    this->toolbar->setFixedHeight(20);

    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(toolbar);
    this->layout()->addWidget(fileexplorer);
}
