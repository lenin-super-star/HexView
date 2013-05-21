
#include <QVBoxLayout>
#include <QFileDialog>
#include <QSplitter>
#include <QFile>

#include "mainwindow.h"

#define DEFAULTSTYLE "..\\HexView\\defaultstyle.qss"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , menubar(new MainMenubar(this))
    , toolbar(new MainToolbar(this))
    , hexView(new MainView(this))
    , filesView(new FileExplorer(this))
{
    this->setMenuBar(menubar);
    this->addToolBar(toolbar);

    QFile stylesheet(DEFAULTSTYLE);

    stylesheet.open(QFile::ReadOnly);
    this->setStyleSheet(QString(QLatin1String(stylesheet.readAll())));
    stylesheet.close();

    this->resize(800, 600);

    this->setContentsMargins(0,0,0,0);

    QObject::connect(this, SIGNAL(signal_files(QStringList)), filesView, SLOT(on_files(QStringList)));
    QObject::connect(filesView, SIGNAL(signal_clicked(QString)), hexView, SLOT(on_add_view(QString)));

    // Create the views

    QSplitter *horizontalsplitter= new QSplitter;
    horizontalsplitter->setOrientation(Qt::Horizontal);

    horizontalsplitter->addWidget(filesView);
    horizontalsplitter->addWidget(hexView);

    horizontalsplitter->setStretchFactor(1,3);

    this->setCentralWidget(horizontalsplitter);
}

void MainWindow::on_openFile()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this,
                                               tr("Select file(s)"),
                                               "/home",
                                               tr("Any file (*.*)"));
    emit signal_files(filenames);
}

void MainWindow::on_find_in_current()
{
    QDialog *dialog = new QDialog;

    dialog->show();
}

MainWindow::~MainWindow()
{
    
}
