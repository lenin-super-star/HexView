#ifndef TABVIEW_H
#define TABVIEW_H

#include <QToolButton>
#include <QByteArray>
#include <QTabWidget>
#include <QToolBar>
#include <QTabBar>

#include "hexviewinternal.h"

class TabView : public QTabWidget
{
    Q_OBJECT

public:

    TabView(QWidget *parent = 0);
    ~TabView();

protected slots:

    void on_find_in_current();

    void on_add_view(const QString&);

    void on_close_tab();

    void on_current_changed(int);

private:

    int currIndex;
};

#endif // TABVIEW_H
