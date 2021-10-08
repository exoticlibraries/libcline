
/*!
    \copyright MIT License Copyright (c) 2021, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 07 October 2021
    \file xtd_printers.h

    xtd_printers.h is ...
*/

#ifndef EXOTIC_CLINE_FONT_EFFECT_H
#define EXOTIC_CLINE_FONT_EFFECT_H

#ifdef __cplusplus
extern "C" {
#endif

/*!

*/
#include "cline_common.h"
#include <exotic/metaref.h>

/*!

*/
#define CLINE_XTD_PRINTER_SELECT_QUOTE(value) _Generic(value,\
		char *: "\"",\
		default: ""\
	)


/*!

*/
#define CLINE_XPRINT_XTD_CONTAINER(container_type, stream, type, container, var_suffix) XIterator *iterator##var_suffix = XITERATOR_INIT(container_type, type, container);\
	fprintf(stream, "["); size_t size##var_suffix = container_type##_size(container);\
	XFOREACH_INDEX(size_t index##var_suffix, type value##var_suffix, iterator##var_suffix, {\
		fprintf(stream, CLINE_XTD_PRINTER_SELECT_QUOTE(value##var_suffix));\
		fprintf(stream, METAREF_GENERIC_FORMAT_SPECIFIER(value##var_suffix), value##var_suffix);\
		fprintf(stream, CLINE_XTD_PRINTER_SELECT_QUOTE(value##var_suffix)); if (index##var_suffix < size##var_suffix-1) fprintf(stream, ", ");\
	}); fprintf(stream, "]"); XITERATOR_DESTROY(iterator##var_suffix);

/*!

*/
#define CLINE_XPRINT_XDEQUE(stream, type, container) CLINE_XPRINT_XTD_CONTAINER(xdeque, stream, type, container, __LINE__)

/*!

*/
#define CLINE_XPRINT_XLIST(stream, type, container) CLINE_XPRINT_XTD_CONTAINER(xlist, stream, type, container, __LINE__)

/*!

*/
#define CLINE_XPRINT_XSLIST(stream, type, container) CLINE_XPRINT_XTD_CONTAINER(xslist, stream, type, container, __LINE__)

/*!

*/
#define CLINE_XPRINT_XQUEUE(stream, type, container) CLINE_XPRINT_XTD_CONTAINER(xqueue, stream, type, container, __LINE__)

/*!

*/
#define CLINE_XPRINT_XSTACK(stream, type, container) CLINE_XPRINT_XTD_CONTAINER(xstack, stream, type, container, __LINE__)

/*!

*/
#define CLINE_XPRINT_XPRIORITY_QUEUE(stream, type, container) CLINE_XPRINT_XTD_CONTAINER(xpriority_queue, stream, type, container, __LINE__)

/*!

*/
#define CLINE_XPRINT_XVECTOR(stream, type, container) CLINE_XPRINT_XTD_CONTAINER(xvector, stream, type, container, __LINE__)

/*!

*/
#define CLINE_XPRINT_XSET(stream, type, container) CLINE_XPRINT_XTD_CONTAINER(xset, stream, type, container, __LINE__)

/*!

*/
#define CLINE_XPRINT_XUNORDERED_SET(stream, type, container) CLINE_XPRINT_XTD_CONTAINER(xunordered_set, stream, type, container, __LINE__)

/*!

*/
#define CLINE_XPRINT_XTD_CONTAINER_CUSTOM(container_type, stream, type, container, value_formatter, var_suffix) XIterator *iterator##var_suffix = XITERATOR_INIT(container_type, type, container);\
	fprintf(stream, "["); size_t size##var_suffix = container_type##_size(container);\
	XFOREACH_INDEX(size_t index##var_suffix, type value##var_suffix, iterator##var_suffix, {\
		fprintf(stream, value_formatter(value##var_suffix));\
		if (index##var_suffix < size##var_suffix-1) fprintf(stream, ", ");\
	}); fprintf(stream, "]"); XITERATOR_DESTROY(iterator##var_suffix);


/*!

*/
#define CLINE_XPRINT_XDEQUE_CUSTOM(stream, type, container, value_formatter) CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xdeque, stream, type, container, value_formatter, __LINE__)

/*!

*/
#define CLINE_XPRINT_XLIST_CUSTOM(stream, type, container, value_formatter) CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xlist, stream, type, container, value_formatter, __LINE__)

/*!

*/
#define CLINE_XPRINT_XSLIST_CUSTOM(stream, type, container, value_formatter) CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xslist, stream, type, container, value_formatter, __LINE__)

/*!

*/
#define CLINE_XPRINT_XQUEUE_CUSTOM(stream, type, container, value_formatter) CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xqueue, stream, type, container, value_formatter, __LINE__)

/*!

*/
#define CLINE_XPRINT_XSTACK_CUSTOM(stream, type, container, value_formatter) CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xstack, stream, type, container, value_formatter, __LINE__)

/*!

*/
#define CLINE_XPRINT_XPRIORITY_QUEUE_CUSTOM(stream, type, container, value_formatter) CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xpriority_queue, stream, type, container, value_formatter, __LINE__)

/*!

*/
#define CLINE_XPRINT_XVECTOR_CUSTOM(stream, type, container, value_formatter) CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xvector, stream, type, container, value_formatter, __LINE__)

/*!

*/
#define CLINE_XPRINT_XSET_CUSTOM(stream, type, container, value_formatter) CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xset, stream, type, container, value_formatter, __LINE__)

/*!

*/
#define CLINE_XPRINT_XUNORDERED_SET_CUSTOM(stream, type, container, value_formatter) CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xunorderes_set, stream, type, container, value_formatter, __LINE__)


#ifdef __cplusplus
}
#endif

#endif