
#include "globalsettings.h"
#include "fileexplorer.h"
#include "xpixmaps.h"

FileExplorer::FileExplorer(QWidget *parent)
    :QListView(parent)
{
    this->setObjectName("FILESVIEW");

    this->setModel(&filesModel);

    QObject::connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked(QModelIndex)));
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
