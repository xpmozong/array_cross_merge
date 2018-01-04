dnl $Id$
dnl config.m4 for extension array_cross_merge

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(array_cross_merge, for array_cross_merge support,
dnl Make sure that the comment is aligned:
dnl [  --with-array_cross_merge             Include array_cross_merge support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(array_cross_merge, whether to enable array_cross_merge support,
Make sure that the comment is aligned:
[  --enable-array_cross_merge           Enable array_cross_merge support])

if test "$PHP_ARRAY_CROSS_MERGE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-array_cross_merge -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/array_cross_merge.h"  # you most likely want to change this
  dnl if test -r $PHP_ARRAY_CROSS_MERGE/$SEARCH_FOR; then # path given as parameter
  dnl   ARRAY_CROSS_MERGE_DIR=$PHP_ARRAY_CROSS_MERGE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for array_cross_merge files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ARRAY_CROSS_MERGE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ARRAY_CROSS_MERGE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the array_cross_merge distribution])
  dnl fi

  dnl # --with-array_cross_merge -> add include path
  dnl PHP_ADD_INCLUDE($ARRAY_CROSS_MERGE_DIR/include)

  dnl # --with-array_cross_merge -> check for lib and symbol presence
  dnl LIBNAME=array_cross_merge # you may want to change this
  dnl LIBSYMBOL=array_cross_merge # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ARRAY_CROSS_MERGE_DIR/$PHP_LIBDIR, ARRAY_CROSS_MERGE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ARRAY_CROSS_MERGELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong array_cross_merge lib version or lib not found])
  dnl ],[
  dnl   -L$ARRAY_CROSS_MERGE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ARRAY_CROSS_MERGE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(array_cross_merge, array_cross_merge.c, $ext_shared)
fi
