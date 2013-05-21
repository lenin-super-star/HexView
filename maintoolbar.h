
#include <QLineEdit>
#include <QToolBar>

class MainToolbar : public QToolBar
{
    Q_OBJECT

public:

    MainToolbar(QWidget *parent = 0);
    ~MainToolbar();

public slots:

    void on_setFilepath(const QString& );

    void on_find_in_current_file();

private:

    QLineEdit   *editFilepath;
    QAction     *actionOpenFile;
    QAction     *actionFindInCurrent;
};
