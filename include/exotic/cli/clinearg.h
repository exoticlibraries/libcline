
/**
    \copyright MIT License Copyright (c) 2021, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 11 April 2021
    \file clinearg.h

    clinearg.h is ...
*/

#ifndef EXOTIC_CLINE_CLINE_ARG_H
#define EXOTIC_CLINE_CLINE_ARG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <exotic/xtd/xcommon.h>
#include <exotic/xtd/xvector.h>
/*#include <exotic/xtd/helpers/basic_vector_types.h>*/

/*TODO remove and move to xtd*/
#ifndef EXOTIC_CLINE_DEFINE_XTD_TYPES
#define EXOTIC_CLINE_DEFINE_XTD_TYPES
    SETUP_XVECTOR_FOR(int)
#endif

/**

*/
struct cline_args_s {
    char *name;
    char *description;
};

/**

*/
typedef struct cline_args_s ClineArgs;

/**

*/
enum x_stat init_cline_arg(ClineArgs **out, char *name)
{
    enum x_stat status;
    ClineArgs *internal;

    internal = (ClineArgs *) calloc(1, sizeof(ClineArgs));
    if (!internal) {
        return XTD_ALLOC_ERR;
    }
    internal->name = name;
    *out = internal;
    return XTD_OK;
}

/**

*/
enum x_stat cline_args_set_name(ClineArgs *cline_arg, char *name)
{
    if (!cline_arg || !name) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->name = name;
    return XTD_OK;
}

/**

*/
enum x_stat cline_args_set_description(ClineArgs *cline_arg, char *description)
{
    if (!cline_arg || !description) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->description = description;
    return XTD_OK;
}

/**

*/
enum x_stat destroy_cline_arg(ClineArgs *out)
{
    free(out);
}

/**

*/
#define cline_arg_name(cline_arg) cline_arg->name

/**

*/
#define cline_arg_description(cline_arg) cline_arg->description

#ifdef __cplusplus
}
#endif

#endif