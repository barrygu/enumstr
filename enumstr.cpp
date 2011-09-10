
#include "days.h"             
#include "numbers.h"             
#include "fruits.h"             

/// The strings associated with the enums are gererated here
/////////////////////////////////////////////////////////////////////
#define GENERATE_ENUM_NAMES  // Start string generation

#include <strings.h>

#include "numbers.h"             
#include "days.h"             
#include "fruits.h"             

const char *GetNameByValue(ENUM_NAME_MAP_T mapEnumName[], int count, int value)
{
        int low, high, mid;
        low = 0;
        high = count - 1;

        while (low <= high) {
                mid = (high + low) / 2;
                if (mapEnumName[mid].value == value) {
                        return mapEnumName[mid].name; // found
                }
                if (mapEnumName[mid].value > value) {
                        high = mid - 1;
                } else {
                        low = mid + 1;
                }
        }
        return (const char *) NULL; // not found
}

#undef GENERATE_ENUM_NAMES
