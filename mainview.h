#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "tabview.h"

#include <QPlainTextEdit>

class MainView : public QWidget
{
    Q_OBJECT

public:

    MainView(QWidget *parent = 0);

signals:

    void signal_find_in_current();

    void signal_add_view(const QString&);

protected:

    void MainView::paintEvent(QPaintEvent *e);

private:

    TabView     *tabView;
};

#endif /* MAINVIEW_H */
