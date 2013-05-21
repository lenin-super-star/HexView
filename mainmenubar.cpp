
#include "mainmenubar.h"

MainMenubar::MainMenubar(QWidget *parent)
    : QMenuBar( parent )
{
    // Initilialize the actions

    actionOpen = new QAction("Open", this);
    actionOpen->setStatusTip("Open a file");

    connect(actionOpen, SIGNAL(triggered()), parent, SLOT(on_openFile()));

    actionExit = new QAction("Exit", this);
    actionExit->setStatusTip("Exit the application");

    connect(actionExit, SIGNAL(triggered()), parent, SLOT(close()));

    actionAbout = new QAction("About", this);
    actionAbout->setStatusTip("About");

    connect(actionAbout, SIGNAL(triggered()), parent, SLOT(on_about()));

    // Initialize the menubar

    menuFile = this->addMenu("&File");
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionExit);

    menuView     = this->addMenu("&View");
    menuSettings = this->addMenu("&Settings");

    menuHelp = this->addMenu("&Help");
    menuHelp->addAction(actionAbout);

    this->setFixedHeight(30);
}
