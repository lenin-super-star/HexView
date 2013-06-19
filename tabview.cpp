
#include <QFileInfo>

#include "xpixmaps.h"
#include "tabview.h"


TabView::TabView(QWidget *parent)
    : QTabWidget(parent)
    , currIndex(-1)
{
    this->setObjectName("TABVIEW");
    this->setContentsMargins(0,0,0,0);

    this->setGraphicsEffect(0);

    this->setTabsClosable(true);

    QObject::connect(this, SIGNAL(currentChanged(int)), this, SLOT(on_current_changed(int)));
}

void TabView::on_add_view(const QString& name)
{
    QFile           file(name);
    file.open(QFile::ReadOnly);

    QByteArray      *data = new QByteArray(file.readAll());
    HexViewInternal *hexviewinternal = new HexViewInternal(data, this);

    // Add the close button to the tab

    QToolButton *close = new QToolButton;

    close->setIcon(QIcon(icon_close_tab));

    QObject::connect(close, SIGNAL(clicked()), this, SLOT(on_close_tab()));

    int index = this->addTab(hexviewinternal, QFileInfo(name).fileName());
    this->tabBar()->setTabButton(index, QTabBar::RightSide, close);

    this->setCurrentIndex(index);
}

void TabView::on_find_in_current()
{

}

void TabView::on_close_tab()
{
    this->removeTab(this->currentIndex());
}

void TabView::on_current_changed(int index)
{
    if (-1 != currIndex && this->tabBar()->tabButton(currIndex, QTabBar::RightSide) )
        this->tabBar()->tabButton(currIndex, QTabBar::RightSide)->hide();

    if (this->tabBar()->tabButton(index, QTabBar::RightSide))
        this->tabBar()->tabButton(index, QTabBar::RightSide)->show();

    currIndex = index;
}

TabView::~TabView()
{
    // Cleanup here
}
