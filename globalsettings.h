
#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QColor>
#include <QFont>

class GlobalSettings
{

private:

    GlobalSettings() {}

public:

    QFont   hexviewFont()           const { return QFont("Courier New",10); }
    QColor  hexviewColor()          const { return QColor(55,55,55); }
    QColor  hexviewOffsetColor()    const { return QColor(20, 77, 195  );}
    QColor  hexviewAsciiColor()     const { return QColor(80,80,80); }
    QColor  hexviewSelectionFront() const { return QColor(55,55,55); }
    QColor  hexviewSelectionBack()  const { return QColor(198,222,255); }
    QColor  filesViewFrontColor()   const { return QColor(40,40,40); }

public:

    static GlobalSettings& instance();
};

#endif // GLOBALSETTINGS_H
