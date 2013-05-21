
#ifndef HEXVIEW_H
#define HEXVIEW_H

#include <QByteArray>
#include <QTabWidget>
#include <QToolBar>
#include <QTabBar>

#include "hexviewinternal.h"

class MainView : public QTabWidget
{
    Q_OBJECT

public:

    MainView(QWidget *parent = 0);
    ~MainView();

protected slots:

    void on_find_in_current();

    void on_add_view(const QString&);

    void on_close_tab();

    void on_current_changed(int);

private:

    int currIndex;
};

#endif /* HEXVIEW_H */
