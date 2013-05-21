
#ifndef FILESVIEW_H
#define FILESVIEW_H

#include <QStandardItemModel>
#include <QListView>
#include <QList>

class FileExplorer : public QListView
{
    Q_OBJECT

public:

    FileExplorer(QWidget *parent = 0);

protected slots:

    void on_files(const QStringList&);

    void on_clicked(const QModelIndex& index);

signals:

    void signal_clicked(const QString&);

private:

    QStringList files;

    QStandardItemModel filesModel;
};

#endif // FILESVIEW_H
