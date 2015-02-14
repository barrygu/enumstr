#include <stdio.h>
#include <stddef.h>

struct a
{
  int a;
  int b;
  int c;
};

#define STRINGIZE(arg)  STRINGIZE1(arg)
#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_1(what, x, ...) what(x)
#define FOR_EACH_2(what, x, ...) what(x); FOR_EACH_1(what,  __VA_ARGS__);
#define FOR_EACH_3(what, x, ...) what(x); FOR_EACH_2(what,  __VA_ARGS__);
#define FOR_EACH_4(what, x, ...) what(x); FOR_EACH_3(what,  __VA_ARGS__);
#define FOR_EACH_5(what, x, ...) what(x); FOR_EACH_4(what,  __VA_ARGS__);
#define FOR_EACH_6(what, x, ...) what(x); FOR_EACH_5(what,  __VA_ARGS__);
#define FOR_EACH_7(what, x, ...) what(x); FOR_EACH_6(what,  __VA_ARGS__);
#define FOR_EACH_8(what, x, ...) what(x); FOR_EACH_7(what,  __VA_ARGS__);

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__) 
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N 
#define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, x, ...) CONCATENATE(FOR_EACH_, N)(what, x, __VA_ARGS__)
#define FOR_EACH(what, x, ...) FOR_EACH_(FOR_EACH_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)

#define PRN_STRUCT_OFFSETS_(structure, field) printf(STRINGIZE(structure)":"STRINGIZE(field)" - offset = %d\n", offsetof(structure, field));
#define PRN_STRUCT_OFFSETS(field) PRN_STRUCT_OFFSETS_(struct a, field)

int main(int argc, char *argv[])
{
  FOR_EACH(PRN_STRUCT_OFFSETS, a, b, c);
  printf("\n");

  return 0;
}

/*************************************************************************************************************
 * another FOR_EACH definition
 * pay attention the end of what(x)
 * without any interpunction
 *************************************************************************************************************/
/*
#define __CONCATENATE(arg1, arg2) __CONCATENATE2(arg1, arg2)
#define __CONCATENATE1(arg1, arg2) __CONCATENATE2(arg1, arg2)
#define __CONCATENATE2(arg1, arg2) arg1##arg2
 
#define __FOREACH_MACRO_RECURSION_1(what, x, ...) what(x)
#define __FOREACH_MACRO_RECURSION_2(what, x, ...) what(x)__FOREACH_MACRO_RECURSION_1(what, __VA_ARGS__)
#define __FOREACH_MACRO_RECURSION_3(what, x, ...) what(x)__FOREACH_MACRO_RECURSION_2(what, __VA_ARGS__)
#define __FOREACH_MACRO_RECURSION_4(what, x, ...) what(x)__FOREACH_MACRO_RECURSION_3(what, __VA_ARGS__)
#define __FOREACH_MACRO_RECURSION_5(what, x, ...) what(x)__FOREACH_MACRO_RECURSION_4(what, __VA_ARGS__)
#define __FOREACH_MACRO_RECURSION_6(what, x, ...) what(x)__FOREACH_MACRO_RECURSION_5(what, __VA_ARGS__)
#define __FOREACH_MACRO_RECURSION_7(what, x, ...) what(x)__FOREACH_MACRO_RECURSION_6(what, __VA_ARGS__)
#define __FOREACH_MACRO_RECURSION_8(what, x, ...) what(x)__FOREACH_MACRO_RECURSION_7(what, __VA_ARGS__)
 
#define __FOREACH_MACRO_RECURSION_NARG(...) __FOREACH_MACRO_RECURSION_NARG_(__VA_ARGS__, __FOREACH_MACRO_RECURSION_RSEQ_N())
#define __FOREACH_MACRO_RECURSION_NARG_(...) __FOREACH_MACRO_RECURSION_ARG_N(__VA_ARGS__)
#define __FOREACH_MACRO_RECURSION_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define __FOREACH_MACRO_RECURSION_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0
 
#define __FOREACH_MACRO_RECURSION(N, what, x, ...) __CONCATENATE(__FOREACH_MACRO_RECURSION_, N)(what, x, __VA_ARGS__)
#define FOREACH_MACRO(what, x, ...) __FOREACH_MACRO_RECURSION(__FOREACH_MACRO_RECURSION_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)
 
#define copy(var) this->var = other.var;
 
FOREACH_MACRO(copy, a, b, c)

//========================================================================================================
// For just integer arguments, a better solution for any number of arguments has been proposed
#define NUMARGS(...) (int)(sizeof((int[]){0, ##__VA_ARGS__})/sizeof(int)-1)
//========================================================================================================

*/
