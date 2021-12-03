
/*!
    \copyright MIT License Copyright (c) 2021, Adewale Azeez 
    \author Adewale Azeez <iamthecarisma@gmail.com>
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
#define EXOTIC_CLINE_ORPHAN_PARAM_KEY "__clinearg__orphans__internal__"

/*!

*/
#define EXOTIC_CLINE_SECTION_DESCRIPTION "__clinearg__section_description__internal__"

/*!

*/
struct cline_arg_option_s {
    bool mandatory;
    bool is_prefix;
    bool is_suffix;
    bool case_sensitive;
    bool is_present;
    bool ignored;
    size_t choices_size;
    size_t min_value_count;
    size_t max_value_count;
    size_t found_value_count;              /*!< The number of the value gotten from the augument, also equivalent to the size of cline_arg_option_s::values */
    size_t splited_option_keys_size;
    char **splited_option_keys;
    char **choices;
    char *description;
    char *epilog;
    char **values;
    char *help_var;
    char *prefix_delimeter;
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
    bool has_any_mandatory;
    bool collect_orphans;
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
    cline_arg->collect_orphans = FALSE;
    cline_arg->has_any_mandatory = TRUE;
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
                xfreep2p_wl(cline_arg->allocator, sub_entry->value->splited_option_keys, sub_entry->value->splited_option_keys_size);
            }
            if (sub_entry->value->choices != XTD_NULL) {
                xfreep2p_wl(cline_arg->allocator, sub_entry->value->choices, sub_entry->value->choices_size);
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

/*!

*/
#define cline_arg_is_collecting_orphans(cline_arg) cline_arg->collect_orphans

/*!

*/
static bool cline_arg_find_arg_option(ClineArgs *cline_arg, const char *section, const char *flag, ClineArgsOption *cli_opt, char **matching_key, bool check_starts_with, bool check_ends_with) {
    size_t index;
    enum x_stat status;
    ClineArgsGroup cli_group;
    XIterator *iterator;

    if (cline_arg == XTD_NULL || flag == XTD_NULL) {
        return FALSE;
    }
    status = xhashtable_get(cstr, ClineArgsGroup)(cline_arg->cli_groups, (section == XTD_NULL || xstring_cstr_is_empty(section) ? "" : section), &cli_group);
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
        for (index = 0; index < entry->value->splited_option_keys_size; index++) {
			/*printf("Value::%s::%s::\n", entry->key, entry->value->splited_option_keys[index]);*/
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
            if (cli_opt != XTD_NULL) {
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
static bool cline_arg_has_option(ClineArgs *cline_arg, const char *section, const char *flag) {
    ClineArgsOption cli_opt;
    return cline_arg_find_arg_option(cline_arg, section, flag, &cli_opt, XTD_NULL, FALSE, FALSE) == TRUE && cli_opt->is_present;
}

/*!

*/
static bool cline_arg_has_orphan_values(ClineArgs *cline_arg) {
    ClineArgsOption cli_opt;
    return cline_arg->collect_orphans && cline_arg_find_arg_option(cline_arg, XTD_NULL, EXOTIC_CLINE_ORPHAN_PARAM_KEY, &cli_opt, XTD_NULL, FALSE, FALSE) == TRUE && cli_opt->is_present;
}

/*!
    There is an assumption that the \cline_arg_parse_in_range does it funtion properly
*/
static size_t cline_arg_get_option_values(ClineArgs *cline_arg, const char *section, const char *flag, char ***values) {
    ClineArgsOption cli_opt;
    bool is_present = cline_arg_find_arg_option(cline_arg, section, flag, &cli_opt, XTD_NULL, FALSE, FALSE) == TRUE && cli_opt->is_present;

    if (!is_present || cli_opt->values == XTD_NULL) { return 0; }
    if (values != XTD_NULL) {
        *values = cli_opt->values;
    }
    return cli_opt->found_value_count;
}

/*!
    
*/
#define cline_arg_get_orphan_values(cline_arg, values) cline_arg_get_option_values(cline_arg, XTD_NULL, EXOTIC_CLINE_ORPHAN_PARAM_KEY, values)

/*!

*/
#define cline_arg_get_arg_option(cline_arg, section, flag, cli_opt) cline_arg_find_arg_option(cline_arg, section, flag, cli_opt, XTD_NULL, FALSE, FALSE)

/*!

*/
#define cline_arg_contains_option(cline_arg, section, option_str) cline_arg_get_arg_option(cline_arg, section, option_str, XTD_NULL)

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
                                           const char *section,  
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
    if (cline_arg_contains_option(cline_arg, section, option_str) == TRUE) {
        return XTD_DUPLICATE_ERR;
    }
    cline_arg_option = (ClineArgsOption) cline_arg->allocator.memory_calloc(1, sizeof(struct cline_arg_option_s));
    if (!cline_arg_option) {
        return XTD_ALLOC_ERR;
    }
    cline_arg_option->splited_option_keys_size = xstring_cstr_split(cline_arg->allocator, (char *) option_str, cline_arg->option_delimiter, &cline_arg_option->splited_option_keys);
    cline_arg_option->choices_size = xstring_cstr_split(cline_arg->allocator, (char *) choices_str, "|", &cline_arg_option->choices);
    cline_arg_option->description = description;
    cline_arg_option->epilog = XTD_NULL;
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
    status = xhashtable_get(cstr, ClineArgsGroup)(cline_arg->cli_groups, (section == XTD_NULL || xstring_cstr_is_empty((char *) section) ? "" : section), &cli_group);
    if (status != XTD_OK) {
        goto cline_arg_add_option_free_after_failure;
    }
    status = xhashtable_put(cstr, ClineArgsOption)(cli_group->cliopts, (char *) option_str, cline_arg_option);
    if (status != XTD_OK) {
        goto cline_arg_add_option_free_after_failure;
    }
    if (mandatory) {
        cline_arg->has_any_mandatory = TRUE;
    }

    return XTD_OK;
    cline_arg_add_option_free_after_failure:
        xfreep2p_wl(cline_arg->allocator, cline_arg_option->splited_option_keys, cline_arg_option->splited_option_keys_size);
        xfreep2p_wl(cline_arg->allocator, cline_arg_option->choices, cline_arg_option->choices_size);
        cline_arg->allocator.memory_free(cline_arg_option);
        return XTD_ERR;
}

/*!

*/
static enum x_stat cline_arg_collect_orphans(ClineArgs *cline_arg, const char *help_var, bool collect_orphans) {
    enum x_stat status;
    if (!cline_arg || collect_orphans < 0 || collect_orphans > 1) {
        return XTD_INVALID_PARAMETER;
    }
    status = cline_arg_add_cli_args_option(cline_arg, XTD_NULL, EXOTIC_CLINE_ORPHAN_PARAM_KEY, XTD_NULL, XTD_NULL, 
                                                        XTD_NULL, help_var, XTD_NULL, FALSE, FALSE, FALSE, FALSE, FALSE, 0, (sizeof(size_t)-1/2));
    if (status != XTD_OK) {
        return status;
    }
    cline_arg->collect_orphans = collect_orphans;
    return XTD_OK;
}

/*!

*/
#define cline_arg_add_property(cline_arg, section, option_str, description, help_var, mandatory) \
    cline_arg_add_cli_args_option(cline_arg, section, option_str, XTD_NULL, description, XTD_NULL, help_var, XTD_NULL, mandatory, TRUE, FALSE, FALSE, FALSE, 1, 1)

/*!

*/
#define cline_arg_add_assignment_property(cline_arg, section, option_str, description, help_var, mandatory) \
    cline_arg_add_cli_args_option(cline_arg, section, option_str, XTD_NULL, description, XTD_NULL, help_var, "=", mandatory, TRUE, FALSE, FALSE, FALSE, 1, 1)

/*!

*/
#define cline_arg_add_property_suffix(cline_arg, section, option_str, description, help_var, mandatory) \
    cline_arg_add_cli_args_option(cline_arg, section, option_str, XTD_NULL, description, XTD_NULL, help_var, XTD_NULL, mandatory, FALSE, TRUE, FALSE, FALSE, 1, 1)

/*!

*/
#define cline_arg_add_argument(cline_arg, section, option_str, description, help_var, mandatory) \
    cline_arg_add_cli_args_option(cline_arg, section, option_str, XTD_NULL, description, XTD_NULL, help_var, XTD_NULL, mandatory, FALSE, FALSE, FALSE, FALSE, 1, 1)

/*!

*/
#define cline_arg_add_option(cline_arg, section, option_str, description, mandatory) \
    cline_arg_add_cli_args_option(cline_arg, section, option_str, XTD_NULL, description, XTD_NULL, XTD_NULL, XTD_NULL, mandatory, FALSE, FALSE, FALSE, FALSE, 0, 1)

/*!

*/
#define cline_arg_add_choice(cline_arg, section, option_str, description, choice_str, mandatory) \
    cline_arg_add_cli_args_option(cline_arg, section, option_str, choice_str, description, XTD_NULL, XTD_NULL, XTD_NULL, mandatory, FALSE, FALSE, FALSE, FALSE, 1, 1)

/*!

*/
#define cline_arg_add_ignored(cline_arg, option_str, is_prefix) \
    cline_arg_add_cli_args_option(cline_arg, XTD_NULL, option_str, XTD_NULL, XTD_NULL, XTD_NULL, XTD_NULL, XTD_NULL, FALSE, is_prefix, FALSE, FALSE, TRUE, 0, 1)

/*!

*/
#define cline_arg_add_ignored_with_desc(cline_arg, option_str, description, is_prefix) \
    cline_arg_add_cli_args_option(cline_arg, XTD_NULL, option_str, XTD_NULL, description, XTD_NULL, XTD_NULL, XTD_NULL, FALSE, is_prefix, FALSE, FALSE, TRUE, 0, 1)

/*!

*/
static enum x_stat cline_arg_parse_in_range(ClineArgs *cline_arg, size_t from, size_t argc, char **argv) {
    enum x_stat status;
    bool is_true;
    bool is_orphan;
    size_t index;
    size_t sub_index;
    size_t index_cache;
    size_t argument_length;
    size_t value_count_index;
    size_t prefix_delimiter_length;
    size_t matching_value_length;
    char *matching_value;
    char **values_expander;
    ClineArgsOption cline_arg_option;
    XIterator *iterator;
    XIterator *sub_iterator;
    
    if (!cline_arg || !argv) {
        return XTD_INVALID_PARAMETER;
    }
    for (index = from; index < argc; index++) {
        is_orphan = FALSE;
        argument_length = xstring_cstr_length(argv[index]);
        is_true = cline_arg_find_arg_option(cline_arg, XTD_NULL, argv[index], &cline_arg_option, &matching_value, TRUE, TRUE);
        if (!is_true || ((!cline_arg_option->is_prefix && !xstring_cstr_equals(argv[index], matching_value)) && 
                (!cline_arg_option->is_suffix && !xstring_cstr_equals(argv[index], matching_value))))  {
            if (!cline_arg->collect_orphans) {
                return XTD_INVALID_PARAMETER_FOUND_ERR;
            }
            is_true = cline_arg_find_arg_option(cline_arg, XTD_NULL, EXOTIC_CLINE_ORPHAN_PARAM_KEY, &cline_arg_option, &matching_value, TRUE, TRUE);
            is_orphan = TRUE;
            index--;
        }
        if (cline_arg_option->ignored) {
            continue;
        }
        cline_arg_option->is_present = TRUE;
        matching_value_length = xstring_cstr_length(matching_value);
        if (cline_arg_option->min_value_count != 0 || is_orphan) {
            index_cache = index+1;
            value_count_index = cline_arg_option->found_value_count;
            for (; !cline_arg_option->is_prefix && index < argc-1 && cline_arg_option->found_value_count < cline_arg_option->max_value_count; cline_arg_option->found_value_count++) {
                char *val = argv[(index++)+1];
                if (cline_arg_contains_main_option(cline_arg, val)) {
                    index--;
                    break;
                }
                if (cline_arg_option->choices != XTD_NULL) {
                    is_true = FALSE;
                    for (sub_index = 0; sub_index < cline_arg_option->choices_size; sub_index++) {
                        if (xstring_cstr_equals(cline_arg_option->choices[sub_index], val)) {
                            is_true = TRUE;
                            break;
                        }
                    }
                    if (!is_true) {
                        return XTD_KEY_NOT_FOUND_ERR;
                    }
                }
            }
            if ((!cline_arg_option->is_prefix && !cline_arg_option->is_suffix && cline_arg_option->found_value_count < cline_arg_option->min_value_count) || 
                (cline_arg_option->is_prefix && argument_length == matching_value_length) ||
                (cline_arg_option->is_suffix && argument_length == matching_value_length)) {
                return XTD_VALUE_NOT_FOUND_ERR;
            }
            if (cline_arg_option->is_prefix || cline_arg_option->is_suffix) {
                cline_arg_option->found_value_count++;
            }
            if (cline_arg_option->values == XTD_NULL) {
                cline_arg_option->values = (char **) cline_arg->allocator.memory_malloc(cline_arg_option->found_value_count * sizeof(char *));
            } else {
                values_expander = (char **) cline_arg->allocator.memory_realloc(cline_arg_option->values, cline_arg_option->found_value_count * sizeof(char *));
                if (!values_expander) {
                    cline_arg->allocator.memory_free(cline_arg_option->values);
                    return XTD_ALLOC_ERR;
                }
                cline_arg_option->values = values_expander;
            }
            if (cline_arg_option->is_prefix || cline_arg_option->is_suffix) { /* checkback ent5ering when not suppose to */
                prefix_delimiter_length = xstring_cstr_length(cline_arg_option->prefix_delimeter);
                char *suffix_value = (char *) cline_arg->allocator.memory_calloc(argument_length-matching_value_length, sizeof(char));
                if (cline_arg_option->is_prefix) {
                    status = xstring_cstr_sub_string(argv[index], matching_value_length+prefix_delimiter_length, suffix_value);
                } else {
                    status = xstring_cstr_sub_string_in_range(argv[index], 0, argument_length-matching_value_length-prefix_delimiter_length, suffix_value);
                }
                if (status != XTD_OK) {
                    cline_arg->allocator.memory_free(cline_arg_option->values);
                    return XTD_VALUE_NOT_FOUND_ERR;
                }
                cline_arg_option->values[value_count_index++] = suffix_value;
            } else {
                for (; index_cache < index+1; index_cache++, value_count_index++) {
                    cline_arg_option->values[value_count_index] = argv[index_cache];
                }
            }
        }
    }
    if (cline_arg->has_any_mandatory) {
        iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsGroup, cline_arg->cli_groups);
        XFOREACH(const xhashtable_entry(cstr, ClineArgsGroup) *entry, iterator, {
            sub_iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsOption, entry->value->cliopts);
            XFOREACH(const xhashtable_entry(cstr, ClineArgsOption) *sub_entry, sub_iterator, {
                if (sub_entry->value->mandatory && !sub_entry->value->is_present) {
                    return XTD_MISSING_PARAM_ERR;
                }
            })
            XITERATOR_DESTROY(sub_iterator);
        })
    }
    XITERATOR_DESTROY(iterator);
    return XTD_OK;
}

/*!

*/
#define cline_arg_parse(cline_arg, argc, argv) cline_arg_parse_in_range(cline_arg, 0, argc, argv)

/*!

*/
static char *cline_arg_get_section_description(ClineArgs *cline_arg, const char *section) {
    ClineArgsOption cli_opt;
    if (section == XTD_NULL) { return cline_arg->description; }
    if (!cline_arg_find_arg_option(cline_arg, section, EXOTIC_CLINE_SECTION_DESCRIPTION, &cli_opt, XTD_NULL, FALSE, FALSE)) {
        return XTD_NULL;
    }
    return cli_opt->description;
}

/*!

*/
static enum x_stat cline_arg_set_section_description(ClineArgs *cline_arg, const char *section, const char *description) {
    ClineArgsOption cli_opt;
    if (section == XTD_NULL) {
        cline_arg->description = description;
        return XTD_OK;
    }
    if (!cline_arg_find_arg_option(cline_arg, section, EXOTIC_CLINE_SECTION_DESCRIPTION, &cli_opt, XTD_NULL, FALSE, FALSE)) {
        return cline_arg_add_ignored_with_desc(cline_arg, EXOTIC_CLINE_SECTION_DESCRIPTION, description, FALSE);
    }
    cli_opt->description = description;
    return XTD_OK;
}

/*!

*/
static char *cline_arg_get_section_epilog(ClineArgs *cline_arg, const char *section) {
    ClineArgsOption cli_opt;
    if (section == XTD_NULL) { return cline_arg->epilog; }
    if (!cline_arg_find_arg_option(cline_arg, section, EXOTIC_CLINE_SECTION_DESCRIPTION, &cli_opt, XTD_NULL, FALSE, FALSE)) {
        return XTD_NULL;
    }
    return cli_opt->description;
}

/*!

*/
static enum x_stat cline_arg_set_section_epilog(ClineArgs *cline_arg, const char *section, const char *epilog) {
    ClineArgsOption cli_opt;
    enum x_stat status;
    if (section == XTD_NULL) {
        cline_arg->epilog = epilog;
        return XTD_OK;
    }
    if (!cline_arg_find_arg_option(cline_arg, section, EXOTIC_CLINE_SECTION_DESCRIPTION, &cli_opt, XTD_NULL, FALSE, FALSE)) {
        status = cline_arg_add_ignored_with_desc(cline_arg, EXOTIC_CLINE_SECTION_DESCRIPTION, "", FALSE);
        if (status == XTD_OK && cline_arg_find_arg_option(cline_arg, section, EXOTIC_CLINE_SECTION_DESCRIPTION, &cli_opt, XTD_NULL, FALSE, FALSE) == XTD_OK) {
            goto cline_arg_set_section_epilog_return;
        }
        return status;
    }
    cline_arg_set_section_epilog_return:
        cli_opt->epilog = epilog;
        return XTD_OK;
}

/*!

*/
#define CLINE_ARG_ORPHAN_OR_OPTION__INTERNAL__(option) (xstring_cstr_equals(option->key, EXOTIC_CLINE_ORPHAN_PARAM_KEY) ? option->value->help_var : option->value->splited_option_keys[0])

/*!

*/
#define CLINE_ARG_TRANSLATE__INTERNAL__(sentence) (translate_sentence != XTD_NULL ? translate_sentence(sentence) : sentence)

/*!

*/
#define CLINE_ARG_HELP_OPTION_PRE_SPACE_SIZE 24

/*!

*//* like a milllion memory is not freed in here, CHECK later */
static enum x_stat cline_arg_section_help(ClineArgs *cline_arg, const char *section, char *(*translate_sentence)(const char *), char **out) {
    size_t index;
    size_t option_text_length = 0;
    char *text;
    char *cached_text = XTD_NULL;
    char *help_var_text = XTD_NULL;
    char *option_text = XTD_NULL;
    char *usage_text = XTD_NULL;
    char *options_text = XTD_NULL;
    char *help_text = XTD_NULL;
    XIterator *iterator;
    XIterator *sub_iterator;

    options_text = xstring_cstr_concat_cstr(cline_arg->allocator, options_text, "\n");
    if (section == XTD_NULL) {
        if (cline_arg->usage != XTD_NULL) {
            //xstring_cstr_replace(cline_arg->allocator, usage, "${name}", cline_arg->name)
            usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, cline_arg_get_usage(cline_arg));
        } else {
            usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, CLINE_ARG_TRANSLATE__INTERNAL__("usage"));
            usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, ": ");
            usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, cline_arg_get_name(cline_arg));

            iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsGroup, cline_arg->cli_groups);
            XFOREACH(const xhashtable_entry(cstr, ClineArgsGroup) *entry, iterator, {
                sub_iterator = XITERATOR_INIT2(xhashtable, cstr, ClineArgsOption, entry->value->cliopts);
                XFOREACH(const xhashtable_entry(cstr, ClineArgsOption) *sub_entry, sub_iterator, {
                    if (sub_entry->value->help_var != XTD_NULL) {
                        if (sub_entry->value->min_value_count > 0 && sub_entry->value->prefix_delimeter != XTD_NULL) {
                            help_var_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_var_text, sub_entry->value->prefix_delimeter);
                        } else if (!sub_entry->value->is_prefix && !sub_entry->value->is_suffix) {
                            help_var_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_var_text, " ");
						}
                        help_var_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_var_text, "<");
                        help_var_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_var_text, sub_entry->value->help_var);
                        help_var_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_var_text, ">");
                    }
                    usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, " ");
                    if (!sub_entry->value->mandatory) {
                        usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, "[");
                    }
                    option_text = xstring_cstr_concat_cstr(cline_arg->allocator, option_text, "  ");
                    if (help_var_text != XTD_NULL && sub_entry->value->is_suffix && !xstring_cstr_equals(sub_entry->key, EXOTIC_CLINE_ORPHAN_PARAM_KEY)) {
                        usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, help_var_text);
                        option_text = xstring_cstr_concat_cstr(cline_arg->allocator, option_text, help_var_text);
                        cline_arg->allocator.memory_free(help_var_text);
                        help_var_text = XTD_NULL;
                    }
                    usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, CLINE_ARG_ORPHAN_OR_OPTION__INTERNAL__(sub_entry));
                    option_text = xstring_cstr_concat_cstr(cline_arg->allocator, option_text, CLINE_ARG_ORPHAN_OR_OPTION__INTERNAL__(sub_entry));
                    if (xstring_cstr_equals(sub_entry->key, EXOTIC_CLINE_ORPHAN_PARAM_KEY)) {
                        cached_text = sub_entry->value->description;
                        sub_entry->value->description = XTD_NULL;
                        sub_entry->value->help_var = XTD_NULL;
                    }
                    if (help_var_text != XTD_NULL && !sub_entry->value->is_suffix && !xstring_cstr_equals(sub_entry->key, EXOTIC_CLINE_ORPHAN_PARAM_KEY)) {
                        usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, help_var_text);
                        option_text = xstring_cstr_concat_cstr(cline_arg->allocator, option_text, help_var_text);
                        cline_arg->allocator.memory_free(help_var_text);
                        help_var_text = XTD_NULL;
                    }
                    for (index = 1; index < sub_entry->value->splited_option_keys_size; index++) {
                        if (sub_entry->value->help_var != XTD_NULL) {
                            if (sub_entry->value->min_value_count > 0 && sub_entry->value->prefix_delimeter != XTD_NULL) {
                                help_var_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_var_text, sub_entry->value->prefix_delimeter);
                            } else if (!sub_entry->value->is_prefix && !sub_entry->value->is_suffix) {
                                help_var_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_var_text, " ");
							}
                            help_var_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_var_text, "<");
                            help_var_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_var_text, sub_entry->value->help_var);
                            help_var_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_var_text, ">");
                        }
                        usage_text = xstring_cstr_concat_char(cline_arg->allocator, usage_text, '|');
                        option_text = xstring_cstr_concat_cstr(cline_arg->allocator, option_text, ", ");
                        if (help_var_text != XTD_NULL && sub_entry->value->is_suffix) {
                            usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, help_var_text);
                            option_text = xstring_cstr_concat_cstr(cline_arg->allocator, option_text, help_var_text);
                            cline_arg->allocator.memory_free(help_var_text);
                            help_var_text = XTD_NULL;
                        }
                        usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, sub_entry->value->splited_option_keys[index]);
                        option_text = xstring_cstr_concat_cstr(cline_arg->allocator, option_text, sub_entry->value->splited_option_keys[index]);
                        if (help_var_text != XTD_NULL && !sub_entry->value->is_suffix) {
                            usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, help_var_text);
                            option_text = xstring_cstr_concat_cstr(cline_arg->allocator, option_text, help_var_text);
                            cline_arg->allocator.memory_free(help_var_text);
                            help_var_text = XTD_NULL;
                        }
                    }
                    if (sub_entry->value->is_prefix || sub_entry->value->is_suffix || sub_entry->value->max_value_count > 1) {
                        usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, " ...");
                        option_text = xstring_cstr_concat_cstr(cline_arg->allocator, option_text, " ...");
                    }
                    option_text_length = xstring_cstr_length(option_text);
                    do {
                        option_text = xstring_cstr_concat_char(cline_arg->allocator, option_text, ' ');
                    } while (option_text_length++ < CLINE_ARG_HELP_OPTION_PRE_SPACE_SIZE-1);
                    if (!sub_entry->value->mandatory) {
                        usage_text = xstring_cstr_concat_char(cline_arg->allocator, usage_text, ']');
                    }
                    if (sub_entry->value->description != XTD_NULL) {
                        option_text = xstring_cstr_concat_cstr(cline_arg->allocator, option_text, sub_entry->value->description);
                        option_text = xstring_cstr_concat_char(cline_arg->allocator, option_text, '\n');
                        options_text = xstring_cstr_concat_cstr(cline_arg->allocator, options_text, option_text);
                    }
                    cline_arg->allocator.memory_free(option_text);
                    option_text = XTD_NULL;
                    if (help_var_text != XTD_NULL) {
                        cline_arg->allocator.memory_free(help_var_text);
                        help_var_text = XTD_NULL;
                    }
                })
                XITERATOR_DESTROY(sub_iterator);
            })
            XITERATOR_DESTROY(iterator);
        }
        usage_text = xstring_cstr_concat_cstr(cline_arg->allocator, usage_text, "\n\n");
    }
    help_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_text, usage_text);
    cline_arg->allocator.memory_free(usage_text);
    text = CLINE_ARG_TRANSLATE__INTERNAL__(cline_arg_get_section_description(cline_arg, section));
    if (text != XTD_NULL) {
        help_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_text, text);
        help_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_text, "\n");
    }
    if (option_text_length > 0) {
        help_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_text, options_text);
        cline_arg->allocator.memory_free(options_text);
    }
    text = CLINE_ARG_TRANSLATE__INTERNAL__(cline_arg_get_section_epilog(cline_arg, section));
    if (text != XTD_NULL) {
        help_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_text, "\n");
        help_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_text, text);
        help_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_text, "\n");
    }
    *out = help_text;
            
    return XTD_OK;
}

/*!

*/
static enum x_stat cline_arg_help(ClineArgs *cline_arg, char **selected_sections, char *(*translate_sentence)(const char *), char **out) {
    int index;
    char *help_text;
    char *section_help;
    enum x_stat status;

    status = cline_arg_section_help(cline_arg, XTD_NULL, XTD_NULL, &section_help);
    if (status != XTD_OK) {
        return status;
    }
    help_text = xstring_cstr_concat_cstr(cline_arg->allocator, XTD_NULL, section_help);
    cline_arg->allocator.memory_free(section_help);
    if (selected_sections != XTD_NULL) {
        for (index = 0; selected_sections[index] != XTD_NULL; index++) {
            status = cline_arg_section_help(cline_arg, selected_sections[index], XTD_NULL, &section_help);
            if (status != XTD_OK) {
                return status;
            }
            help_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_text, section_help);
            cline_arg->allocator.memory_free(section_help);
        }
    }
    help_text = xstring_cstr_concat_cstr(cline_arg->allocator, help_text, "\n");
    *out = help_text;

    return XTD_OK;
}

#ifdef __cplusplus
}
#endif

#endif