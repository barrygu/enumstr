#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*====================================================================================*/
/**
 * It can't handle more than 8 elements
 */
 
#define FE_1(WHAT, X) WHAT(X) 
#define FE_2(WHAT, X, ...) WHAT(X),FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X),FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X),FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X),FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT(X),FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT(X),FE_6(WHAT, __VA_ARGS__)
#define FE_8(WHAT, X, ...) WHAT(X),FE_7(WHAT, __VA_ARGS__)

#define GET_MACRO(x,_1,_2,_3,_4,_5,_6,_7,_8,NAME,...) NAME 
#define FOR_EACH(action,...) GET_MACRO(,##__VA_ARGS__,     \
    FE_8,FE_7,FE_6,FE_5,FE_4,FE_3,FE_2,FE_1)               \
    (action,##__VA_ARGS__)

/*====================================================================================*/

/** 
 * A variadic macro which counts the number of arguments which it is
 * passed. Or, more precisely, it counts the number of commas which it is
 * passed, plus one.
 *
 * Danger: It can't count higher than 20. If it's given 0 arguments, then it
 * will evaluate to 1, rather than to 0.
 */
#define NUM_ARGS(...)                                                   \
    NUM_ARGS_COUNTER(__VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13,            \
                     12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)    

#define NUM_ARGS_COUNTER(a1,  a2,  a3,  a4,  a5,  a6,  a7,     \
                         a8,  a9,  a10, a11, a12, a13, a14,    \
                         a15, a16, a17, a18, a19, a20,         \
                         N, ...)   N

#define TO_STRING(n) #n
#define MANY_STRING(...) FOR_EACH(TO_STRING,##__VA_ARGS__)

#define NAMED_ENUM(name, ...)\
    typedef enum _enum##name\
    { __VA_ARGS__ }name;\
    static const int _enum##name##Size = NUM_ARGS(__VA_ARGS__);\
    static const char *_enum##name##Strings[] = {MANY_STRING(__VA_ARGS__)};\
    inline const char * name##ToString(const name value) \
    { return _enum##name##Strings[value]; }

#define CountOfEnum(name) _enum##name##Size

NAMED_ENUM(WeekDays, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday);
int main(int argc, char *argv[])
{
    WeekDays value;
    const char *valueName;

    printf("there are %d of elements in enum WeekDays\n", CountOfEnum(WeekDays));

    value = Tuesday;
    valueName = WeekDaysToString(value);
    printf("Value %d's name is :%s:\n", value, valueName);

    value = Friday;
    valueName = WeekDaysToString(value);
    printf("Value %d's name is :%s:\n", value, valueName);

    return 0;
}
