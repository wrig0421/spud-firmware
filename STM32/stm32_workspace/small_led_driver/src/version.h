/*
 * version.h
 *
 *  Created on: Feb 19, 2023
 *      Author: spud
 */

#ifndef SRC_VERSION_H_
#define SRC_VERSION_H_

#include "config.h"

// version array
// version[0] year
// version[1] month
// version[2] day
// version[3] hour
// version[4] min
// version[5] day


#define VERSION_MAJOR   ((FIRMWARE_VERSION & 0xFF0000) >> 16)
#define VERSION_MINOR   ((FIRMWARE_VERSION & 0x00FF00) >> 8)
#define VERSION_BETA    ((FIRMWARE_VERSION & 0x0000FF))

#define BUILD_DATE_DIGIT_EXTRACT(digit) \
    ( \
        (digit == '9') ? 9 : \
        (digit == '8') ? 8 : \
        (digit == '7') ? 7 : \
        (digit == '6') ? 6 : \
        (digit == '5') ? 5 : \
        (digit == '4') ? 4 : \
        (digit == '3') ? 3 : \
        (digit == '2') ? 2 : \
        (digit == '1') ? 1 : 0 \
    )

#define BUILD_MONTH_IS_JAN ((__DATE__[0] == 'J') && (__DATE__[1] == 'A') && (__DATE__[2] == 'N'))
#define BUILD_MONTH_IS_FEB ((__DATE__[0] == 'F') && (__DATE__[1] == 'E') && (__DATE__[2] == 'B'))
#define BUILD_MONTH_IS_MAR ((__DATE__[0] == 'M') && (__DATE__[1] == 'A') && (__DATE__[2] == 'R'))
#define BUILD_MONTH_IS_APR ((__DATE__[0] == 'A') && (__DATE__[1] == 'P') && (__DATE__[2] == 'R'))
#define BUILD_MONTH_IS_MAY ((__DATE__[0] == 'M') && (__DATE__[1] == 'A') && (__DATE__[2] == 'Y'))
#define BUILD_MONTH_IS_JUN ((__DATE__[0] == 'J') && (__DATE__[1] == 'U') && (__DATE__[2] == 'N'))
#define BUILD_MONTH_IS_JUL ((__DATE__[0] == 'J') && (__DATE__[1] == 'U') && (__DATE__[2] == 'L'))
#define BUILD_MONTH_IS_AUG ((__DATE__[0] == 'A') && (__DATE__[1] == 'U') && (__DATE__[2] == 'G'))
#define BUILD_MONTH_IS_SEP ((__DATE__[0] == 'S') && (__DATE__[1] == 'E') && (__DATE__[2] == 'P'))
#define BUILD_MONTH_IS_OCT ((__DATE__[0] == 'O') && (__DATE__[1] == 'C') && (__DATE__[2] == 'T'))
#define BUILD_MONTH_IS_NOV ((__DATE__[0] == 'N') && (__DATE__[1] == 'O') && (__DATE__[2] == 'V'))
#define BUILD_MONTH_IS_DEC ((__DATE__[0] == 'D') && (__DATE__[1] == 'E') && (__DATE__[2] == 'C'))

#define BUILD_DATE_MONTH \
    ( (BUILD_MONTH_IS_JAN) ? 1 : \
      (BUILD_MONTH_IS_FEB) ? 2 : \
      (BUILD_MONTH_IS_MAR) ? 3 : \
      (BUILD_MONTH_IS_APR) ? 4 : \
      (BUILD_MONTH_IS_MAY) ? 5 : \
      (BUILD_MONTH_IS_JUN) ? 6 : \
      (BUILD_MONTH_IS_JUL) ? 7 : \
      (BUILD_MONTH_IS_AUG) ? 8 : \
      (BUILD_MONTH_IS_SEP) ? 9 : \
      (BUILD_MONTH_IS_OCT) ? 10 : \
      (BUILD_MONTH_IS_NOV) ? 11 : 0xFF)

#define BUILD_DATE_DAY      ((BUILD_DATE_DIGIT_EXTRACT(__DATE__[4]) * 10) + (BUILD_DATE_DIGIT_EXTRACT(__DATE__[5])))
#define BUILD_DATE_YEAR     ((BUILD_DATE_DIGIT_EXTRACT(__DATE__[7]) * 1000) + (BUILD_DATE_DIGIT_EXTRACT(__DATE__[8]) * 100) + (BUILD_DATE_DIGIT_EXTRACT(__DATE__[9]) * 10) + (BUILD_DATE_DIGIT_EXTRACT(__DATE__[10])))

#define BUILD_TIME_HOUR     ((BUILD_DATE_DIGIT_EXTRACT(__TIME__[0]) * 10) + (BUILD_DATE_DIGIT_EXTRACT(__TIME__[1])))
#define BUILD_TIME_MINUTE   ((BUILD_DATE_DIGIT_EXTRACT(__TIME__[3]) * 10) + (BUILD_DATE_DIGIT_EXTRACT(__TIME__[4])))
#define BUILD_TIME_SECOND   ((BUILD_DATE_DIGIT_EXTRACT(__TIME__[6]) * 10) + (BUILD_DATE_DIGIT_EXTRACT(__TIME__[7])))

typedef struct
{
    uint16_t    year;
    uint8_t     month;
    uint8_t     day;
    uint8_t     hour;
    uint8_t     minutes;
    uint8_t     seconds;
    uint8_t     fill;
} version_date_and_time_t;





#endif /* SRC_VERSION_H_ */