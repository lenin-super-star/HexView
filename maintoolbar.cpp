
#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include <QFileDialog>
#include <QDialog>
#include <QIcon>

#include "maintoolbar.h"
#include "xpixmaps.h"

MainToolbar::MainToolbar(QWidget *parent)
    : QToolBar(parent)
    , editFilepath(new QLineEdit)
{
    this->setIconSize(QSize(20,20));

    actionOpenFile = this->addAction(QIcon(icon_open), "Open", parent, SLOT(on_openFile()));

    actionFindInCurrent = this->addAction(QIcon(icon_find_in_current), "Find in current file", parent, SLOT(on_find_in_current()));

    this->setMovable(true);
}

void MainToolbar::on_setFilepath(const QString &path)
{
    this->editFilepath->setText(path);
}

void MainToolbar::on_find_in_current_file()
{
    QDialog *finddialog = new QDialog(this);

    finddialog->show();
}

MainToolbar::~MainToolbar()
{
    delete editFilepath;
}

#endif /* MAINTOOLBAR_H */
