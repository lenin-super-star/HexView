
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "fileexplorer.h"
#include "mainmenubar.h"
#include "maintoolbar.h"
#include "mainview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:

    void on_openFile();

    void on_find_in_current();

signals:

    void signal_files(const QStringList&);

private:

    MainMenubar     *menubar;
    MainToolbar     *toolbar;
    FileExplorer    *filesView;
    MainView        *hexView;
};

#endif // MAINWINDOW_H
