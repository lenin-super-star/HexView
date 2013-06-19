#ifndef EXPLORERWINDOW_H
#define EXPLORERWINDOW_H

#include <QToolBar>

#include "fileexplorer.h"

class ExplorerWindow : public QWidget
{
    Q_OBJECT
public:
    ExplorerWindow(QWidget *parent = 0);

private:

    QToolBar        *toolbar;
    FileExplorer    *fileexplorer;
};

#endif // EXPLORERWINDOW_H
