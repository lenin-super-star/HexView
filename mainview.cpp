#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "mainview.h"

MainView::MainView(QWidget *parent)
    : QWidget(parent)
    , tabView(new TabView)
{
    this->setObjectName("MAINVIEW");

    this->setLayout(new QVBoxLayout);
    this->layout()->setContentsMargins(0,0,0,0);

//    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect;

//    wndShadow->setBlurRadius(50);

//    wndShadow->setColor(QColor(120, 120, 120));

//    wndShadow->setOffset(0);

//    this->setGraphicsEffect(wndShadow);

    this->layout()->setContentsMargins(0,0,0,0);


    this->layout()->addWidget(new QWidget);
    this->layout()->addWidget(tabView);
    this->layout()->setSpacing(0);

    QObject::connect(this, SIGNAL(signal_add_view(QString)), tabView, SLOT(on_add_view(QString)));
    QObject::connect(this, SIGNAL(signal_find_in_current()), tabView, SLOT(on_find_in_current()));
}

void MainView::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QStyleOption opt;
         opt.init(this);
         QPainter p(this);
         style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}

