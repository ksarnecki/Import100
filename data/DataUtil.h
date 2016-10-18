#ifndef _DATA_UTIL_H_
#define _DATA_UTIL_H_
#include "AnsiString.h"
#include "DynSet.h"
#include "Data.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


class DataUtil {
  public:
    static void printInfoCSV(Info&);
    static void printInfosCSV(Infos&);
};

#endif