
#include <QToolButton>
#include <QVBoxLayout>
#include <QAction>
#include <QLabel>

#include "globalsettings.h"
#include "fileexplorer.h"
#include "xpixmaps.h"


FileExplorer::FileExplorer(QWidget *parent)
    :QWidget(parent)
    ,listview(new QListView)
    ,toolbar(new QToolBar)
{
    this->setObjectName("FILEEXPLORER");
    this->listview->setObjectName("FILESVIEW");
    this->toolbar->setObjectName("FILESEXPLORER_TOOLBAR");
    this->toolbar->setFixedHeight(24);

    this->listview->setModel(&filesModel);

    this->toolbar->addWidget(new QLabel("Files"));

    QObject::connect(this->listview, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked(QModelIndex)));

    QWidget *spacer = new QWidget;

    spacer->setObjectName("SPACER");

    spacer->setStyleSheet("QWidget {background-image: url(c:/spacerimage.ico);}");

    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacer->setVisible(true);

    this->toolbar->addWidget(spacer);

    // Add the close and hide buttons

    QToolButton *hide = new QToolButton;

    hide->setIcon(QIcon(icon_hide));

    hide->setFixedSize(18,18);

    this->toolbar->addWidget(hide);

    QToolButton *close = new QToolButton;

    close->setIcon(QIcon(icon_close));

    close->setFixedSize(18,18);

    this->toolbar->addWidget(close);


//    QGraphicsDropShadowEffect *wndShadow = new QGraphicsDropShadowEffect;

//    wndShadow->setBlurRadius(10);

//    wndShadow->setColor(QColor(120, 120, 120));

//    wndShadow->setOffset(0);

//    this->setGraphicsEffect(wndShadow);

    this->setLayout(new QVBoxLayout);
    this->layout()->setContentsMargins(0,0,0,0);
    this->layout()->addWidget(toolbar);
    this->layout()->addWidget(listview);
}

void FileExplorer::on_files(const QStringList &files)
{
    filesModel.clear();

    foreach(const QString& filename, files)
    {
        QStandardItem *item = new QStandardItem;

        item->setText(filename);
        item->setIcon(QIcon(icon_smallfile));
        item->setForeground(GlobalSettings::instance().filesViewFrontColor());
        item->setEditable(false);
        item->setSelectable(false);

        filesModel.insertRow(filesModel.rowCount(), item);
    }
}

void FileExplorer::on_clicked(const QModelIndex& index)
{
    QStandardItem *item = filesModel.item(index.row());

    emit signal_clicked(item->text());
}
