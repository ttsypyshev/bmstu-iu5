#set(FIND_MYLIB_PATHS ~/data/education/programming/labs-inf-1-2-semester/2 term/practice/practice_01/MyLib)
set(FIND_MYLIB_PATHS ~/data/other/MyLib)

find_path(MYLIB_INCLUDE_DIR myLib.h
        PATH_SUFFIXES include
        PATHS ${FIND_MYLIB_PATHS})

find_library(MYLIB_LIBRARY
        NAMES myLib
        PATH_SUFFIXES lib
        PATHS ${FIND_MYLIB_PATHS})