
/*!
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
#include <exotic/xtd/xcrypto.h>
#include <exotic/xtd/xhashtable.h>
#include <exotic/xtd/xstring.h>
/*#include <exotic/xtd/helpers/basic_vector_types.h>*/

/*TODO remove and move to xtd*/
#ifndef EXOTIC_CLINE_DEFINE_XTD_TYPES
#define EXOTIC_CLINE_DEFINE_XTD_TYPES
#endif

/*!

*/
struct cline_arg_option_s {
    bool mandatory;
    bool is_prefix;
    bool is_suffix;
    bool case_sensitive;
    bool is_present;
    bool ignored;
    size_t min_value_count;
    size_t max_value_count;
    size_t found_value_count;              /*!< The number of the value gotten from the augument, also equivalent to the size of cline_arg_option_s::values */
    char **splited_option_keys;
    char **choices;
    char *description;
    char **values;
    char *help_var;
    char *prefix_delimeter
};

/* tmp */
typedef char* cstr;

/*!

*/
typedef struct cline_arg_option_s* ClineArgsOption;

/*!

*/
SETUP_XHASHTABLE_FOR(cstr, ClineArgsOption);

/*!

*/
struct cline_arg_group_s {
    char *name;
    xhashtable(cstr, ClineArgsOption) *cliopts;
};

/*!

*/
typedef struct cline_arg_group_s *ClineArgsGroup;


SETUP_XHASHTABLE_FOR(cstr, ClineArgsGroup);

/*!

*/
struct cline_arg_s {
    char *name;
    char *description;
    char *epilog;
    char *usage;
    char *option_delimiter;
    xhashtable(cstr, ClineArgsGroup) *cli_groups;
    XAllocator allocator;
};

/*!

*/
typedef struct cline_arg_s ClineArgs;

/*!

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
    cli_group = (ClineArgsGroup) xallocator->memory_calloc(1, sizeof(struct cline_arg_group_s));
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
        xhashtable_destroy(cstr, ClineArgsGroup)(cli_groups);
        xallocator->memory_free(cline_arg);
        return status;
    }
    cli_group->name = "";
    cli_group->cliopts = cliopts;
    status = xhashtable_put(cstr, ClineArgsGroup)(cli_groups, "", cli_group);
    if (status != XTD_OK) {
        xhashtable_destroy(cstr, ClineArgsOption)(cliopts);
        xhashtable_destroy(cstr, ClineArgsGroup)(cli_groups);
        xallocator->memory_free(cline_arg);
        return status;
    }
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

/*!
Check back for proper gabbage collection
*/
static void destroy_cline_arg(ClineArgs *cline_arg) {
    XIterator *iterator;
    XIterator *sub_iterator;

    iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsGroup, cline_arg->cli_groups);
    XFOREACH(const xhashtable_entry(cstr, ClineArgsGroup) *entry, iterator, {
        sub_iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsOption, entry->value->cliopts);
        XFOREACH(const xhashtable_entry(cstr, ClineArgsOption) *sub_entry, sub_iterator, {
            if (sub_entry->value->splited_option_keys != XTD_NULL) {
                xfreep2p(sub_entry->value->splited_option_keys, cline_arg->allocator);
            }
            if (sub_entry->value->choices != XTD_NULL) {
                xfreep2p(sub_entry->value->choices, cline_arg->allocator);
            }
            if (sub_entry->value->values != XTD_NULL) {
                cline_arg->allocator.memory_free(sub_entry->value->values);
            }
            if (sub_entry->value != XTD_NULL) {
                cline_arg->allocator.memory_free(sub_entry->value);
            }
        })
        xhashtable_destroy(cstr, ClineArgsOption)(entry->value->cliopts);
        /*cline_arg->allocator.memory_free(entry->value); free outside loop*/
        XITERATOR_DESTROY(sub_iterator);
    })
    xhashtable_destroy(cstr, ClineArgsGroup)(cline_arg->cli_groups);

    XITERATOR_DESTROY(iterator);
    cline_arg->allocator.memory_free(cline_arg);
    cline_arg = XTD_NULL;
}

/*!

*/
static enum x_stat cline_arg_set_name(ClineArgs *cline_arg, char *name) {
    if (!cline_arg || !name) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->name = name;
    return XTD_OK;
}

/*!

*/
static enum x_stat cline_arg_set_description(ClineArgs *cline_arg, char *description) {
    if (!cline_arg || !description) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->description = description;
    return XTD_OK;
}

/*!

*/
static enum x_stat cline_arg_set_epilog(ClineArgs *cline_arg, char *epilog) {
    if (!cline_arg || !epilog) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->epilog = epilog;
    return XTD_OK;
}

/*!

*/
static enum x_stat cline_arg_set_usage(ClineArgs *cline_arg, char *usage) {
    if (!cline_arg || !usage) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->usage = usage;
    return XTD_OK;
}

/*!

*/
static enum x_stat cline_arg_set_option_delimiter(ClineArgs *cline_arg, char *option_delimiter) {
    if (!cline_arg || !option_delimiter) {
        return XTD_INVALID_PARAMETER;
    }
    cline_arg->option_delimiter = option_delimiter;
    return XTD_OK;
}

/*!

*/
static bool cline_arg_find_arg_option(ClineArgs *cline_arg, const char *parent, const char *flag, ClineArgsOption *cli_opt, char **matching_key, bool check_starts_with, bool check_ends_with) {
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
    if (cli_opt != XTD_NULL && xhashtable_get(cstr, ClineArgsOption)(cli_group->cliopts, flag, cli_opt) == XTD_OK) {
        if (matching_key) {
            *matching_key = flag;
        }
        return TRUE;
    }
    iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsOption, cli_group->cliopts);
    XFOREACH(const xhashtable_entry(cstr, ClineArgsOption) *entry, iterator, {
        if (xstring_cstr_equals(entry->key, flag) || 
            ((entry->value->is_prefix || check_starts_with) && xstring_cstr_starts_with(flag, entry->key)) || 
            ((entry->value->is_suffix || check_ends_with) && xstring_cstr_ends_with(flag, entry->key))) {
                if (matching_key) {
                    *matching_key = entry->key;
                }
                goto cline_arg_find_arg_option_return;
        }
        for (index = 0; entry->value->splited_option_keys[index] != XTD_NULL; index++) {
            if (xstring_cstr_equals(entry->value->splited_option_keys[index], flag) || 
                ((entry->value->is_prefix || check_starts_with) && xstring_cstr_starts_with(flag, entry->value->splited_option_keys[index])) || 
                ((entry->value->is_suffix || check_ends_with) && xstring_cstr_ends_with(flag, entry->value->splited_option_keys[index]))) {
                    if (matching_key) {
                        *matching_key = entry->value->splited_option_keys[index];
                    }
                    goto cline_arg_find_arg_option_return;
            }
        }
        continue;
        cline_arg_find_arg_option_return:
            if (cli_opt) {
                *cli_opt = entry->value;
            }
            XITERATOR_DESTROY(iterator);
            return TRUE;
    });

    XITERATOR_DESTROY(iterator);
    return FALSE;
}

/*!

*/
static bool cline_arg_has_option(ClineArgs *cline_arg, const char *parent, const char *flag) {
    ClineArgsOption cli_opt;
    return cline_arg_find_arg_option(cline_arg, parent, flag, &cli_opt, XTD_NULL, FALSE, FALSE) == TRUE && cli_opt->is_present;
}

/*!
    There is an assumption that the \cline_arg_parse_in_range does it funtion properly
*/
static size_t cline_arg_get_option_values(ClineArgs *cline_arg, const char *parent, const char *flag, char ***values) {
    ClineArgsOption cli_opt;
    bool is_present = cline_arg_find_arg_option(cline_arg, parent, flag, &cli_opt, XTD_NULL, FALSE, FALSE) == TRUE && cli_opt->is_present;

    if (!is_present || cli_opt->values == XTD_NULL) { return 0; }
    if (values != XTD_NULL) {
        *values = cli_opt->values;
    }
    return cli_opt->found_value_count;
}

/*!

*/
#define cline_arg_get_arg_option(cline_arg, parent, flag, cli_opt) cline_arg_find_arg_option(cline_arg, parent, flag, cli_opt, XTD_NULL, FALSE, FALSE)

/*!

*/
#define cline_arg_contains_option(cline_arg, parent, option_str) cline_arg_get_arg_option(cline_arg, parent, option_str, XTD_NULL)

/*!

*/
#define cline_arg_contains_main_option(cline_arg, option_str) cline_arg_contains_option(cline_arg, XTD_NULL, option_str)

/*!

*/
static size_t cline_arg_find_like_arg_options(ClineArgs *cline_arg, const char *flag, char **similar_options, size_t similar_options_count, bool (*compare_flag)(const char *, const char *)) {
    size_t index;
    enum x_stat status;
    ClineArgsGroup cli_group;
    XIterator *iterator;
    XIterator *sub_iterator;

    if (cline_arg == XTD_NULL || flag == XTD_NULL || similar_options == XTD_NULL) {
        return 0;
    }
    index = 0;
    iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsGroup, cline_arg->cli_groups);
    XFOREACH(const xhashtable_entry(cstr, ClineArgsGroup) *entry, iterator, {
        sub_iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsOption, entry->value->cliopts);
        XFOREACH(const xhashtable_entry(cstr, ClineArgsOption) *sub_entry, sub_iterator, {
            size_t key_size = xstring_cstr_length(sub_entry->key);
            size_t flag_size = xstring_cstr_length(flag);
            if (xstring_cstr_equals(sub_entry->key, flag) || xstring_cstr_contains(sub_entry->key, flag) || xstring_cstr_contains(flag, sub_entry->key) ||
                    (compare_flag != XTD_NULL && compare_flag(sub_entry->key, flag)) ||
                    xstring_cstr_starts_with(flag, sub_entry->key) ||
                        (key_size >= 3 && flag_size >= 3 && flag[0] != '-' && flag[0] == sub_entry->key[0] && flag[1] == sub_entry->key[1] && flag[2] == sub_entry->key[2]) || 
                        (key_size >= 4 && flag_size >= 4 && flag[0] == '-' && flag[1] != '-' && flag[1] == sub_entry->key[1] && flag[2] == sub_entry->key[2] && flag[3] == sub_entry->key[3]) || 
                        (key_size >= 5 && flag_size >= 5 && flag[0] == '-' && flag[1] == '-' && flag[2] == sub_entry->key[2] && flag[3] == sub_entry->key[3] && flag[4] == sub_entry->key[4])) {
                similar_options[index++] = sub_entry->key;
                if (index == similar_options_count) {
                    goto cline_arg_find_like_arg_options_return;
                }
            }
        })
        XITERATOR_DESTROY(sub_iterator);
    })

    cline_arg_find_like_arg_options_return:
        XITERATOR_DESTROY(iterator);
        return index;
}

/* TODO check for dupplicate per splited option from option_str*/
/*!

*/
static enum x_stat cline_arg_add_cli_args_option(ClineArgs *cline_arg, 
                                           const char *parent,  
                                           const char *option_str, 
                                           const char *choices_str, 
                                           const char *description,
                                           const char **default_value,
                                           const char *help_var,
                                           const char *prefix_delimeter,
                                            bool mandatory,
                                            bool is_prefix,
                                            bool is_suffix,
                                            bool case_sensitive,
                                            bool ignored,
                                            unsigned int min_value_count, 
                                            unsigned int max_value_count) {
    size_t index;
    enum x_stat status;
    ClineArgsGroup cli_group;
    ClineArgsOption cline_arg_option;

    if (cline_arg == XTD_NULL || option_str == XTD_NULL) {
        return XTD_PARAM_NULL_ERR;
    }
    if (cline_arg_contains_option(cline_arg, parent, option_str) == TRUE) {
        return XTD_DUPLICATE_ERR;
    }
    cline_arg_option = (ClineArgsOption) cline_arg->allocator.memory_calloc(1, sizeof(struct cline_arg_option_s));
    if (!cline_arg_option) {
        return XTD_ALLOC_ERR;
    }
    cline_arg_option->splited_option_keys = xstring_cstr_split(option_str, cline_arg->option_delimiter, cline_arg->allocator);
    cline_arg_option->choices = xstring_cstr_split(choices_str, "|", cline_arg->allocator);
    cline_arg_option->description = description;
    cline_arg_option->values = default_value;
    cline_arg_option->help_var = help_var;
    cline_arg_option->prefix_delimeter = prefix_delimeter;
    cline_arg_option->mandatory = mandatory;
    cline_arg_option->is_prefix = is_prefix;
    cline_arg_option->is_suffix = is_suffix;
    cline_arg_option->case_sensitive = case_sensitive;
    cline_arg_option->min_value_count = min_value_count;
    cline_arg_option->max_value_count = max_value_count;
    cline_arg_option->found_value_count = 0;
    cline_arg_option->is_present = FALSE;
    cline_arg_option->ignored = ignored;
    status = xhashtable_get(cstr, ClineArgsGroup)(cline_arg->cli_groups, (parent == XTD_NULL || xstring_cstr_is_empty(parent) ? "" : parent), &cli_group);
    if (status != XTD_OK) {
        goto cline_arg_add_option_free_after_failure;
    }
    status = xhashtable_put(cstr, ClineArgsOption)(cli_group->cliopts, option_str, cline_arg_option);
    if (status != XTD_OK) {
        goto cline_arg_add_option_free_after_failure;
    }

    return XTD_OK;
    cline_arg_add_option_free_after_failure:
        xfreep2p(cline_arg_option->splited_option_keys, cline_arg->allocator);
        cline_arg->allocator.memory_free(cline_arg_option);
        return XTD_ERR;
}

/*!

*/
#define cline_arg_add_property(cline_arg, parent, option_str, description, help_var, mandatory) \
    cline_arg_add_cli_args_option(cline_arg, parent, option_str, XTD_NULL, description, XTD_NULL, help_var, XTD_NULL, mandatory, TRUE, FALSE, FALSE, FALSE, 1, 1)

/*!

*/
#define cline_arg_add_property_suffix(cline_arg, parent, option_str, description, help_var, mandatory) \
    cline_arg_add_cli_args_option(cline_arg, parent, option_str, XTD_NULL, description, XTD_NULL, help_var, XTD_NULL, mandatory, FALSE, TRUE, FALSE, FALSE, 1, 1)

/*!

*/
#define cline_arg_add_argument(cline_arg, parent, option_str, description, help_var, mandatory) \
    cline_arg_add_cli_args_option(cline_arg, parent, option_str, XTD_NULL, description, XTD_NULL, help_var, XTD_NULL, mandatory, FALSE, FALSE, FALSE, FALSE, 1, 1)

/*!

*/
#define cline_arg_add_option(cline_arg, parent, option_str, description, mandatory) \
    cline_arg_add_cli_args_option(cline_arg, parent, option_str, XTD_NULL, description, XTD_NULL, XTD_NULL, XTD_NULL, mandatory, FALSE, FALSE, FALSE, FALSE, 0, 1)

/*!

*/
#define cline_arg_add_ignored(cline_arg, option_str, is_prefix) \
    cline_arg_add_cli_args_option(cline_arg, XTD_NULL, option_str, XTD_NULL, XTD_NULL, XTD_NULL, XTD_NULL, XTD_NULL, FALSE, is_prefix, FALSE, FALSE, TRUE, 0, 1)

/*!

*/
static enum x_stat cline_arg_parse_in_range(ClineArgs *cline_arg, size_t from, size_t argc, char **argv) {
    enum x_stat status;
    size_t index;
    size_t sub_index;
    size_t index_cache;
    size_t argument_length;
    size_t value_count_index;
    size_t matching_value_length;
    char *matching_value;
    char **values_expander;
    ClineArgsOption cline_arg_option;
    if (!cline_arg || !argv) {
        return XTD_INVALID_PARAMETER;
    }
    for (index = from; index < argc; index++) {
        printf("OK to next %d\n", index);
        argument_length = xstring_cstr_length(argv[index]);
        if (cline_arg_find_arg_option(cline_arg, XTD_NULL, argv[index], &cline_arg_option, &matching_value, TRUE, TRUE) == FALSE || 
                ((!cline_arg_option->is_prefix && !xstring_cstr_equals(argv[index], matching_value)) && 
                (!cline_arg_option->is_suffix && !xstring_cstr_equals(argv[index], matching_value)))) {
            printf("Invalid param %s\n\n", argv[index], matching_value);
            return XTD_INVALID_PARAMETER_FOUND_ERR;
        }
        if (cline_arg_option->ignored) {
            continue;
        }
        cline_arg_option->is_present = TRUE;
        matching_value_length = xstring_cstr_length(matching_value);
        printf("Matching value %s\n", matching_value);
        printf("FINDING: %s-%d", argv[index], cline_arg_option->min_value_count);
        if (cline_arg_option->min_value_count != 0) {
            index_cache = index+1;
            value_count_index = cline_arg_option->found_value_count;
            printf(" ::VALUES => \n");
            for (; !cline_arg_option->is_prefix && index < argc-1 && cline_arg_option->found_value_count < cline_arg_option->max_value_count; cline_arg_option->found_value_count++) {
                char *val = argv[(index++)+1];
                if (cline_arg_contains_main_option(cline_arg, val)) {
                    index--;
                    break;
                }
                printf("  FOUND:%s\n", val);
            }
            printf(" VALUES AGGR: %d \n", cline_arg_option->found_value_count);
            if ((!cline_arg_option->is_prefix && !cline_arg_option->is_suffix && cline_arg_option->found_value_count < cline_arg_option->min_value_count) || 
                (cline_arg_option->is_prefix && argument_length == matching_value_length) ||
                (cline_arg_option->is_suffix && argument_length == matching_value_length)) {
                printf("TERMINATE ::%d ::%d ::%d\n\n", cline_arg_option->is_prefix, argument_length, matching_value_length);
                return XTD_VALUE_NOT_FOUND_ERR;
            }
            if (cline_arg_option->is_prefix || cline_arg_option->is_suffix) {
                cline_arg_option->found_value_count++;
            }
            printf("The FVC::%d\n", cline_arg_option->found_value_count);
            if (cline_arg_option->values == XTD_NULL) {
                cline_arg_option->values = (char **) cline_arg->allocator.memory_calloc(cline_arg_option->found_value_count, sizeof(char *));
            } else {
                values_expander = (char **) cline_arg->allocator.memory_realloc(cline_arg_option->values, cline_arg_option->found_value_count * sizeof(char *));
                if (!values_expander) {
                    cline_arg->allocator.memory_free(cline_arg_option->values);
                    return XTD_ALLOC_ERR;
                }
                cline_arg_option->values = values_expander;
            }
            if (cline_arg_option->is_prefix || cline_arg_option->is_suffix) {
                char *suffix_value = (char *) cline_arg->allocator.memory_calloc(argument_length-matching_value_length, sizeof(char));
                if (cline_arg_option->is_prefix) {
                    status = xstring_cstr_sub_string(argv[index], matching_value_length, suffix_value);
                } else {
                    status = xstring_cstr_sub_string_in_range(argv[index], 0, argument_length-matching_value_length, suffix_value);
                }
                if (status != XTD_OK) {
                    cline_arg->allocator.memory_free(cline_arg_option->values);
                    return XTD_VALUE_NOT_FOUND_ERR;
                }
                printf("  STORING FOUND:%d:%d:%d:%s\n", matching_value_length, argument_length, argument_length-matching_value_length, suffix_value);
                cline_arg_option->values[value_count_index++] = suffix_value;
            } else {
                for (; index_cache < index+1; index_cache++, value_count_index++) {
                    printf("  STORING FOUND:%d:%d:%d:%s\n", cline_arg_option->found_value_count, value_count_index, index_cache, argv[index_cache]);
                    cline_arg_option->values[value_count_index] = argv[index_cache];
                }
            }
        }
        printf("\n\n");
    }
    return XTD_OK;
}

/*!

*/
#define cline_arg_parse(cline_arg, argc, argv) cline_arg_parse_in_range(cline_arg, 0, argc, argv)

/*!

*/
#define cline_arg_get_name(cline_arg) cline_arg->name

/*!

*/
#define cline_arg_get_description(cline_arg) cline_arg->description

/*!

*/
#define cline_arg_get_epilog(cline_arg) cline_arg->epilog

/*!

*/
#define cline_arg_get_usage(cline_arg) cline_arg->usage

/*!

*/
#define cline_arg_get_option_delimiter(cline_arg) cline_arg->option_delimiter

#ifdef __cplusplus
}
#endif

#endif