
#include "globalsettings.h"


GlobalSettings& GlobalSettings::instance()
{
    static GlobalSettings *instance = new GlobalSettings;

    return *instance;
}
