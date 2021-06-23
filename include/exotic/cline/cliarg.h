
/**
    \copyright MIT License Copyright (c) 2021, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 11 February 2021
    \file cliarg.h

    cliarg.h is ...
*/

#ifndef EXOTIC_CLINE_CLI_ARG_H
#define EXOTIC_CLINE_CLI_ARG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <exotic/xtd/xcommon.h>
#include <exotic/xtd/xvector.h>
#include <exotic/xtd/xcrypto.h>
#include <exotic/xtd/xhashtable.h>
#include <exotic/xtd/xstring.h>
/*#include <exotic/xtd/helpers/basic_vector_types.h>*/

/*TODO remove and move to xtd*/
#ifndef EXOTIC_CLINE_DEFINE_XTD_TYPES
#define EXOTIC_CLINE_DEFINE_XTD_TYPES
#endif

/**

*/
typedef struct cline_args_option_s {
    bool mandatory;
    bool is_prefix;
    bool case_sensitive;
    bool is_present;
    unsigned int min_value_count;
    unsigned int max_value_count;
    char **splited_option_keys;
    char **choices;
    char *description;
    char *value;
    char *help_var;
    char *prefix_delimeter
} ClineArgsOption;

/**

*/
typedef struct cline_args_group_s ClineArgsGroup;

/* tmp */
typedef char* cstr;

/**

*/
SETUP_XHASHTABLE_FOR(cstr, ClineArgsOption);

/**

*/
struct cline_args_group_s {
    char *name;
    xhashtable(cstr, ClineArgsOption) *cliopts;
};


SETUP_XHASHTABLE_FOR(cstr, ClineArgsGroup);

/**

*/
struct cline_args_s {
    char *name;
    char *description;
    char *epilog;
    char *usage;
    char *option_delimiter;
    xhashtable(cstr, ClineArgsGroup) *cli_groups;
    XAllocator allocator;
};

/**

*/
typedef struct cline_args_s ClineArgs;

/**

*/
static enum x_stat init_cline_arg(const XAllocator *xallocator, ClineArgs **out, char *name) {
    enum x_stat status;
    ClineArgs *cline_arg;
    ClineArgsGroup cli_group;
    struct xcontainer_config config;
    xhashtable(cstr, ClineArgsGroup) *cli_groups;
    xhashtable(cstr, ClineArgsOption) *cliopts;

    cline_arg = (ClineArgs *) xallocator->memory_calloc(1, sizeof(ClineArgs));
    if (!cline_arg) {
        return XTD_ALLOC_ERR;
    }
    init_xcontainer_config(&config);
    config.allocator = *xallocator;
    status = xhashtable_new_config(cstr, ClineArgsGroup)(&config, &cli_groups, xstring_cstr_equals, xcrypto_hash_string);
    if (status != XTD_OK) {
        xallocator->memory_free(cline_arg);
        return status;
    }
    status = xhashtable_new_config(cstr, ClineArgsOption)(&config, &cliopts, xstring_cstr_equals, xcrypto_hash_string);
    if (status != XTD_OK) {
        xvector_destroy(cli_groups);
        xallocator->memory_free(cline_arg);
        return status;
    }
    cli_group.name = "";
    cli_group.cliopts = cliopts;
    status = xhashtable_put(cstr, ClineArgsGroup)(cli_groups, "", cli_group);
    cline_arg->name = name;
    cline_arg->description = XTD_NULL;
    cline_arg->epilog = XTD_NULL;
    cline_arg->usage = XTD_NULL;
    cline_arg->option_delimiter = "<:>";
    cline_arg->cli_groups = cli_groups;
    cline_arg->allocator = *xallocator;
    *out = cline_arg;

    return XTD_OK;
}

/**

*/
static void destroy_cline_arg(ClineArgs *cline_arg) {
    XIterator *iterator;
    XIterator *sub_iterator;

    iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsGroup, cline_arg->cli_groups);
    XFOREACH(const xhashtable_entry(cstr, ClineArgsGroup) *entry, iterator, {
        sub_iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsOption, entry->value.cliopts);
        XFOREACH(const xhashtable_entry(cstr, ClineArgsOption) *sub_entry, sub_iterator, {
            if (sub_entry->value.splited_option_keys != XTD_NULL) {
                xfreep2p(sub_entry->value.splited_option_keys, cline_arg->allocator);
            }
            if (sub_entry->value.choices != XTD_NULL) {
                xfreep2p(sub_entry->value.choices, cline_arg->allocator);
            }
            /*cline_arg->allocator.memory_free(&(sub_entry->value)); cahce it then free*/
        })
        xhashtable_destroy(cstr, ClineArgsOption)(entry->value.cliopts);
        /*cline_arg->allocator.memory_free(&(entry->value)); cahce it then free*/
        XITERATOR_DESTROY(sub_iterator);
    })
    xhashtable_destroy(cstr, ClineArgsGroup)(cline_arg->cli_groups);

    XITERATOR_DESTROY(iterator);
    cline_arg->allocator.memory_free(cline_arg);
    cline_arg = XTD_NULL;
}

/**

*/
static enum x_stat cline_args_set_name(ClineArgs *cline_arg, char *name) {
    if (!cline_arg || !name) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->name = name;
    return XTD_OK;
}

/**

*/
static enum x_stat cline_args_set_description(ClineArgs *cline_arg, char *description) {
    if (!cline_arg || !description) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->description = description;
    return XTD_OK;
}

/**

*/
static enum x_stat cline_args_set_epilog(ClineArgs *cline_arg, char *epilog) {
    if (!cline_arg || !epilog) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->epilog = epilog;
    return XTD_OK;
}

/**

*/
static enum x_stat cline_args_set_usage(ClineArgs *cline_arg, char *usage) {
    if (!cline_arg || !usage) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->usage = usage;
    return XTD_OK;
}

/**

*/
static enum x_stat cline_args_set_option_delimiter(ClineArgs *cline_arg, char *option_delimiter) {
    if (!cline_arg || !option_delimiter) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->option_delimiter = option_delimiter;
    return XTD_OK;
}

/**

*/
static bool cline_args_get_args_option(ClineArgs *cline_arg, const char *parent,  const char *flag, ClineArgsOption *cli_opt) {
    size_t index;
    enum x_stat status;
    ClineArgsGroup cli_group;
    XIterator *iterator;

    if (cline_arg == XTD_NULL || flag == XTD_NULL) {
        return FALSE;
    }
    status = xhashtable_get(cstr, ClineArgsGroup)(cline_arg->cli_groups, (parent == XTD_NULL || xstring_cstr_is_empty(parent) ? "" : parent), &cli_group);
    if (status != XTD_OK) {
        return FALSE;
    }
    if (cli_opt != XTD_NULL && xhashtable_get(cstr, ClineArgsOption)(cli_group.cliopts, flag, cli_opt) == XTD_OK) {
        return TRUE;
    }
    iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsOption, cli_group.cliopts);
    XFOREACH(const xhashtable_entry(cstr, ClineArgsOption) *entry, iterator, {
        if (xstring_cstr_equals(entry->key, flag)) {
            goto cline_args_get_args_option_return;
        }
        for (index = 0; entry->value.splited_option_keys[index] != XTD_NULL; index++) {
            if (xstring_cstr_equals(entry->value.splited_option_keys[index], flag)) {
                goto cline_args_get_args_option_return;
            }
        }
        continue;
        cline_args_get_args_option_return:
            if (cli_opt) {
                *cli_opt = entry->value;
            }
            return TRUE;
    });

    XITERATOR_DESTROY(iterator);
    return FALSE;
}

/**

*/
static bool cline_args_contains_option(ClineArgs *cline_arg, const char *parent,  const char *option_str) {
    return cline_args_get_args_option(cline_arg, parent, option_str, XTD_NULL);
}

/**

*/
#define cline_args_contains_main_option(cline_arg, option_str) cline_args_contains_option(cline_arg, XTD_NULL, option_str)

/* TODO check for dupplicate per splited option from option_str*/
/**

*/
static enum x_stat cline_args_add_cli_args_option(ClineArgs *cline_arg, 
                                            const char *parent,  
                                            const char *option_str, 
                                            const char *choices_str, 
                                            const char *description,
                                            const char *default_value,
                                            const char *help_var,
                                            const char *prefix_delimeter,
                                            bool mandatory,
                                            bool is_prefix,
                                            bool case_sensitive,
                                            unsigned int min_value_count, 
                                            unsigned int max_value_count) {
    size_t index;
    enum x_stat status;
    ClineArgsGroup cli_group;
    ClineArgsOption *cline_args_option;

    if (cline_arg == XTD_NULL || option_str == XTD_NULL) {
        return XTD_PARAM_NULL_ERR;
    }
    if (cline_args_contains_option(cline_arg, parent, option_str) == TRUE) {
        return XTD_DUPLICATE_ERR;
    }
    cline_args_option = (ClineArgsOption *) cline_arg->allocator.memory_calloc(1, sizeof(ClineArgsOption));
    if (!cline_args_option) {
        return XTD_ALLOC_ERR;
    }
    cline_args_option->splited_option_keys = xstring_cstr_split(option_str, cline_arg->option_delimiter, cline_arg->allocator);
    cline_args_option->choices = xstring_cstr_split(choices_str, "|", cline_arg->allocator);
    cline_args_option->description = description;
    cline_args_option->value = default_value;
    cline_args_option->help_var = help_var;
    cline_args_option->prefix_delimeter = prefix_delimeter;
    cline_args_option->mandatory = mandatory;
    cline_args_option->is_prefix = is_prefix;
    cline_args_option->case_sensitive = case_sensitive;
    cline_args_option->min_value_count = min_value_count;
    cline_args_option->max_value_count = max_value_count;
    cline_args_option->is_present = FALSE;
    status = xhashtable_get(cstr, ClineArgsGroup)(cline_arg->cli_groups, (parent == XTD_NULL || xstring_cstr_is_empty(parent) ? "" : parent), &cli_group);
    if (status != XTD_OK) {
        goto cline_args_add_option_free_after_failure;
    }
    status = xhashtable_put(cstr, ClineArgsOption)(cli_group.cliopts, option_str, *cline_args_option);
    if (status != XTD_OK) {
        goto cline_args_add_option_free_after_failure;
    }

    return XTD_OK;
    cline_args_add_option_free_after_failure:
        xfreep2p(cline_args_option->splited_option_keys, cline_arg->allocator);
        cline_arg->allocator.memory_free(cline_args_option);
        return XTD_ERR;
}

/**

*/
#define cline_args_add_property(cline_arg, parent, option_str, description, help_var, mandatory) \
    cline_args_add_cli_args_option(cline_arg, parent, option_str, XTD_NULL, description, XTD_NULL, help_var, XTD_NULL, mandatory, TRUE, FALSE, 0, 1)

/**

*/
#define cline_args_add_argument(cline_arg, parent, option_str, description, help_var, mandatory) \
    cline_args_add_cli_args_option(cline_arg, parent, option_str, XTD_NULL, description, XTD_NULL, help_var, XTD_NULL, mandatory, FALSE, FALSE, 0, 1)

/**

*/
#define cline_args_add_option(cline_arg, parent, option_str, description, mandatory) \
    cline_args_add_cli_args_option(cline_arg, parent, option_str, XTD_NULL, description, XTD_NULL, XTD_NULL, XTD_NULL, mandatory, FALSE, FALSE, 0, 1)

/**

*/
#define cline_arg_get_name(cline_arg) cline_arg->name

/**

*/
#define cline_arg_get_description(cline_arg) cline_arg->description

/**

*/
#define cline_arg_get_epilog(cline_arg) cline_arg->epilog

/**

*/
#define cline_arg_get_usage(cline_arg) cline_arg->usage

/**

*/
#define cline_arg_get_option_delimiter(cline_arg) cline_arg->option_delimiter

#ifdef __cplusplus
}
#endif

#endif