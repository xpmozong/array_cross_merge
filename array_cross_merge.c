/*
    +----------------------------------------------------------------------+
    | PHP Version 5                                                                                                                |
    +----------------------------------------------------------------------+
    | Copyright (c) 1997-2016 The PHP Group                                                                |
    +----------------------------------------------------------------------+
    | This source file is subject to version 3.01 of the PHP license,            |
    | that is bundled with this package in the file LICENSE, and is                |
    | available through the world-wide-web at the following url:                     |
    | http://www.php.net/license/3_01.txt                                                                    |
    | If you did not receive a copy of the PHP license and are unable to     |
    | obtain it through the world-wide-web, please send a note to                    |
    | license@php.net so we can mail you a copy immediately.                             |
    +----------------------------------------------------------------------+
    | Author:                                                                                                                            |
    +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_array_cross_merge.h"

/* If you declare any globals in php_array_cross_merge.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(array_cross_merge)
*/

/* True global resources - no need for thread safety here */
static int le_array_cross_merge;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
        STD_PHP_INI_ENTRY("array_cross_merge.global_value",            "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_array_cross_merge_globals, array_cross_merge_globals)
        STD_PHP_INI_ENTRY("array_cross_merge.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_array_cross_merge_globals, array_cross_merge_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
     so that your module can be compiled into PHP, it exists only for testing
     purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_array_cross_merge_compiled(string arg)
     Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_array_cross_merge_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "array_cross_merge", arg);
	RETURN_STRINGL(strg, len, 0);
}

PHPAPI int php_array_merge(HashTable *dest, HashTable *src, int a_index TSRMLS_DC)
{
    zval **src_entry, **dest_entry;
    char *string_key;
    uint string_key_len;
    ulong num_key;
    HashPosition pos;

    // 数组连接
    zend_hash_internal_pointer_reset_ex(src, &pos);
    while (zend_hash_get_current_data_ex(src, (void **)&src_entry, &pos) == SUCCESS) {
        switch (zend_hash_get_current_key_ex(src, &string_key, &string_key_len, &num_key, 0, &pos)) {
            case HASH_KEY_IS_STRING:
                Z_ADDREF_PP(src_entry);
                zend_hash_update(dest, string_key, string_key_len, src_entry, sizeof(zval *), NULL);
                break;
            case HASH_KEY_IS_LONG:
                Z_ADDREF_PP(src_entry);
                zend_hash_next_index_insert(dest, src_entry, sizeof(zval *), NULL);
                break;
        }
        zend_hash_move_forward_ex(src, &pos);
    }

    return 1;
}

PHPAPI int php_array_cross_merge(HashTable *dest, HashTable *src, int a_index TSRMLS_DC)
{
    zval **src_entry, **dest_entry;
    char *string_key;
    uint string_key_len;
    ulong num_key;
    HashPosition pos;

    // if (zend_hash_index_exists(src, a_index) == SUCCESS) {
    //     php_printf("%d\n", a_index);
    // }

    if (zend_hash_index_find(src, a_index, (void **)&src_entry) == SUCCESS) {
        Z_ADDREF_PP(src_entry);
        zend_hash_next_index_insert(dest, src_entry, sizeof(zval *), NULL);
    }

    return 1;
}

/**
 * 交叉合并
 */
PHP_FUNCTION(array_cross_merge)
{
    zval ***args = NULL;
    int argc, i, init_size = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "+", &args, &argc) == FAILURE) {
        return;
    }

    for (i = 0; i < argc; i++) {
        if (Z_TYPE_PP(args[i]) != IS_ARRAY) {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Argument #%d is not an array", i + 1);
            efree(args);
            RETURN_NULL();
        } else {
            int num = zend_hash_num_elements(Z_ARRVAL_PP(args[i]));
            if (num > init_size) {
                init_size = num;
            }
        }
    }

    array_init_size(return_value, init_size);

    for (int j = 0; j < init_size; j++) {
        for (i = 0; i < argc; i++) {
            php_array_cross_merge(Z_ARRVAL_P(return_value), Z_ARRVAL_PP(args[i]), j TSRMLS_CC);
        }
    }

    efree(args);
}

/**
 * 合并数组
 */
PHP_FUNCTION(my_array_merge)
{
    zval ***args = NULL;
    int argc, i, init_size = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "+", &args, &argc) == FAILURE) {
        return;
    }

    for (i = 0; i < argc; i++) {
        if (Z_TYPE_PP(args[i]) != IS_ARRAY) {
            php_error_docref(NULL TSRMLS_CC, E_WARNING, "Argument #%d is not an array", i + 1);
            efree(args);
            RETURN_NULL();
        } else {
            int num = zend_hash_num_elements(Z_ARRVAL_PP(args[i]));
            if (num > init_size) {
                init_size = num;
            }
        }
    }

    array_init_size(return_value, init_size);

    for (i = 0; i < argc; i++) {
        php_array_merge(Z_ARRVAL_P(return_value), Z_ARRVAL_PP(args[i]), i TSRMLS_CC);
    }

    efree(args);
}


/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
     unfold functions in source code. See the corresponding marks just before 
     function definition, where the functions purpose is also documented. Please 
     follow this convention for the convenience of others editing your code.
*/


/* {{{ php_array_cross_merge_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_array_cross_merge_init_globals(zend_array_cross_merge_globals *array_cross_merge_globals)
{
	array_cross_merge_globals->global_value = 0;
	array_cross_merge_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(array_cross_merge)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(array_cross_merge)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(array_cross_merge)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(array_cross_merge)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(array_cross_merge)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "array_cross_merge support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ array_cross_merge_functions[]
 *
 * Every user visible function must have an entry in array_cross_merge_functions[].
 */
const zend_function_entry array_cross_merge_functions[] = {
	PHP_FE(confirm_array_cross_merge_compiled, NULL)		/* For testing, remove later. */
    PHP_FE(array_cross_merge, NULL)
    PHP_FE(my_array_merge, NULL)
	PHP_FE_END	/* Must be the last line in array_cross_merge_functions[] */
};
/* }}} */

/* {{{ array_cross_merge_module_entry
 */
zend_module_entry array_cross_merge_module_entry = {
	STANDARD_MODULE_HEADER,
	"array_cross_merge",
	array_cross_merge_functions,
	PHP_MINIT(array_cross_merge),
	PHP_MSHUTDOWN(array_cross_merge),
	PHP_RINIT(array_cross_merge),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(array_cross_merge),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(array_cross_merge),
	PHP_ARRAY_CROSS_MERGE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ARRAY_CROSS_MERGE
ZEND_GET_MODULE(array_cross_merge)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
