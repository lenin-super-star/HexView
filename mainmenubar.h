
#ifndef MAINMENUBAR_H
#define MAINMENUBAR_H

#include <QMenuBar>

class MainMenubar : public QMenuBar
{
    Q_OBJECT

public:

    MainMenubar(QWidget *parent = 0);

private:

    /**
     * Menu items
     */

    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuSettings;
    QMenu *menuHelp;

    /**
     * Actions
     */

    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionAbout;

    //QAction *actionSetlighttheme;
    //QAction *actionSetdarktheme;

};

#endif // MAINMENU_H
