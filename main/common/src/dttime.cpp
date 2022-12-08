#include "dttime.h"


QString DTTime::getCurrentTimeStamp()
{
    int nTimeStamp =  QDateTime::currentDateTime().toTime_t();
    return QString::number(nTimeStamp);
}
