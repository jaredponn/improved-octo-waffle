#pragma once
// -----------------------------------------
//    The Macro library of Minature Socket
// -----------------------------------------

/* Much of the functions either came from, or built upon the following website
 * http://jhnet.co.uk/articles/cpp_magic
 */

// -----------------------------------------
//    LIST OPERATIONS
// -----------------------------------------
/* LIST OPERATIONS
 */
#define FST(a, ...) a
#define SND(a, b, ...) b
#define TAIL(...) __VA_ARGS__

// returns what it is given
#define ID(id) id

// -----------------------------------------
//    Utility functions
// -----------------------------------------

/*empty*/
#define EMPTY()

/* Macro concat*/
#define MCAT(a, b) _mcat(a, b)
#define _mcat(a, b) a##b

/* stringify*/
#define STR(val) #val

/* string of file names*/
#define GET_FILE_NAME() EVAL(DEFER1(STR)(__FILE__))
#define GET_LINE_NUM() EVAL(DEFER1(STR)(__LINE__))

/* depth evaluation for macros*/
#define EVAL(...) EVAL2048(__VA_ARGS__)
#define EVAL2048(...) EVAL1024(EVAL1024(__VA_ARGS__))
#define EVAL1024(...) EVAL512(EVAL512(__VA_ARGS__))
#define EVAL512(...) EVAL256(EVAL256(__VA_ARGS__))
#define EVAL256(...) EVAL128(EVAL128(__VA_ARGS__))
#define EVAL128(...) EVAL64(EVAL64(__VA_ARGS__))
#define EVAL64(...) EVAL32(EVAL32(__VA_ARGS__))
#define EVAL32(...) EVAL16(EVAL16(__VA_ARGS__))
#define EVAL16(...) EVAL8(EVAL8(__VA_ARGS__))
#define EVAL8(...) EVAL4(EVAL4(__VA_ARGS__))
#define EVAL4(...) EVAL2(EVAL2(__VA_ARGS__))
#define EVAL2(...) EVAL1(EVAL1(__VA_ARGS__))
#define EVAL1(...) __VA_ARGS__

/* defers the expansion of a macro to the next pass*/
#define DEFER1(id) id EMPTY()
#define DEFER2(id) id EMPTY EMPTY()()
#define DEFER3(id) id EMPTY EMPTY EMPTY()()()
#define DEFER4(id) id EMPTY EMPTY EMPTY EMPTY()()()()

// -----------------------------------------
//    BOOLEAN LOGIC
// -----------------------------------------
// internals
#define IS_PROBE(...) SND(__VA_ARGS__, 0)
#define PROBE() ~, 1

/* NOT
   usage: NOT(wtf is this) -> 0
   usage: NOT(0) -> 1
 */
#define NOT(val) IS_PROBE(MCAT(_not_, val))
#define _not_0 PROBE()

/* CONVERT TO BOOL
usage: BOOL(adsf) -> 1
usage: BOOL(0) -> 0
 */
#define BOOL(val) NOT(NOT(val))

/* IMPLEMENTING IF STATEMENTS
 interface: IF_ELSE(1)(en)(nil) -> returns en
 interface: IF_ELSE(0)(en)(nil) -> returns nil
	IF_ELSE(123)(true)(false) -> true
	IF_ELSE(0)(true)(false) -> false
*/
#define IF_ELSE(condition) MCAT(_if_, BOOL(condition))
#define _if_1(...)                                                             \
	__VA_ARGS__ _if_1_else // if it is true, execute the first statement
#define _if_0(...) _if_0_else  // if it is false, execute the second statement

#define _if_1_else(...)
#define _if_0_else(...) __VA_ARGS__

// -----------------------------------------
//    Utility funcions for recursive functions
// -----------------------------------------
/* HAS_ARGS - tells us if the macro parameter list has arguemnts in it
usage: HAS_ARGS() -> 0 for false it does have args
usage: HAS_ARGS(a,b,c,) -> 1 for true it does have args
 */
#define HAS_ARGS(...) BOOL(FST(_end_of_args_ __VA_ARGS__)())
#define _end_of_args_() 0

/* ONE_ARG_LEFT tests if the variadic list has only one argeument left (BUGGY)
usage: ONE_ARG_LEFT(a,b,c) -> 0 for false it does have args
usage: ONE_ARG_LEFT(a) -> 1 for true
usage: ONE_ARG_LEFT(,) -> 1 for true
usage: ONE_ARG_LEFT() -> 1 for true BUG
 */
#define ONE_ARG_LEFT(fst, snd...) NOT(BOOL(FST(_one_arg_left_ snd)()))
#define _one_arg_left_() 0

// -----------------------------------------
//    Recursive functions
// -----------------------------------------
/* easy example*/
#define func() cool fun DEFER1(_func)(/*_func paramter */)(/*func parameter*/)
#define _func() func
// usage: EVAL(func())

/* map
usage: #define FUNCTION(a) 1234
	EVAL(MAP(FUNCTION, a, b, c)) -> 1234, 1234, 1234, 1234
*/

// clang-format off
#define MAP(f, val, ...)                                            \
        f(val) IF_ELSE(HAS_ARGS(__VA_ARGS__))                       \
                        (DEFER2(_map)()(f, __VA_ARGS__))            \
                        (/* do nothing if there are no args left */)
#define _map() MAP
// clang-format on

/* map2 -> takes two elements and applies a function that takes two arguments to
 * them
 */

// clang-format off
#define MAP2(f, a, b,...)                                            \
        f(a, b) IF_ELSE(HAS_ARGS(__VA_ARGS__))                       \
                        (DEFER2(_map2)()(f, __VA_ARGS__))            \
                        (/* do nothing if there are no args left */)
#define _map2() MAP2
// clang-format on

// clang-format off
/*MAP_INIT maps over all elements but the last
usage:
#define FUNCTINO(val) YO
EVAL(MAP_INIT(FUNCTION,a,b,c)) -> YO YO c
EVAL(MAP_INIT(FUNCTION,a,b)) -> YO b
EVAL(MAP_INIT(FUNCTION,a)) -> a
*/
#define MAP_INIT(f, val, ...)                               \
        IF_ELSE(ONE_ARG_LEFT(val, __VA_ARGS__))             \
                (val)                                       \
                (f(val) DEFER2(_map_init)()(f,__VA_ARGS__))
#define _map_init() MAP_INIT
// clang-format on

// clang-format off
/*APPLY_LAST applies a function to the last element in the variadic macro
*/
#define APPLY_LAST(f, val, ...)                            \
        IF_ELSE(ONE_ARG_LEFT(val, __VA_ARGS__))            \
                (f(val))                                   \
                (val DEFER2(_apply_last)()(f,__VA_ARGS__))
#define _apply_last() APPLY_LAST

// adds a comma past the argument
#define POSTFIX_COMMA(val) val,

// remoes trailing commas: a,b,c, -> a,b,c
#define REMOVE_EXTRA_COMMA(...) EVAL(DEFER2(MAP_INIT)(POSTFIX_COMMA, __VA_ARGS__))
// an ID function yields the same effect as REMOVE_EXTRA_COMA
#define ID_VA_ARGS(...) REMOVE_EXTRA_COMMA(__VA_ARGS__)
