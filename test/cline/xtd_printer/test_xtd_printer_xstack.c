/*!gcc {0} -I. -I../../../include/ -o out -Wno-int-conversion; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>
#include <exotic/xtd/container/xstack.h>
#include <exotic/cline/xtd_printers.h>

CESTER_BODY(
	typedef struct user_s {
		char *name;
		char *email;
	} User;

    typedef char* str;
    typedef User* User_ptr;
    SETUP_XSTACK_FOR(str)
    SETUP_XSTACK_FOR(int)
    SETUP_XSTACK_FOR(User_ptr)
)

CESTER_TEST(print_str, _, {
    xstack(str) *fruits;

    cester_assert_uint_eq(xstack_new(str)(&fruits), XTD_OK);
    cester_assert_uint_eq(xstack_push(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xstack_push(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xstack_push(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xstack_push(str)(fruits, "Pineapple"), XTD_OK);

	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER(xstack, stdout, str, fruits, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_equal("[\"Apple\", \"Banana\", \"Mango\", \"Pineapple\"]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xstack_pop(str)(fruits, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XSTACK(stdout, str, fruits);
	cester_assert_stdout_stream_content_equal("[\"Apple\", \"Banana\", \"Mango\"]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xstack_pop(str)(fruits, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xstack_pop(str)(fruits, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xstack_pop(str)(fruits, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER(xstack, stdout, str, fruits, SUFFIX_656890909);
	cester_assert_stdout_stream_content_equal("[]");

	CESTER_RELEASE_STDOUT();
	
})

CESTER_TEST(print_int, _, {
    xstack(int) *numbers;

    cester_assert_uint_eq(xstack_new(int)(&numbers), XTD_OK);
    cester_assert_uint_eq(xstack_push(int)(numbers, 10), XTD_OK);
    cester_assert_uint_eq(xstack_push(int)(numbers, 20), XTD_OK);
    cester_assert_uint_eq(xstack_push(int)(numbers, 30), XTD_OK);
    cester_assert_uint_eq(xstack_push(int)(numbers, 40), XTD_OK);

	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER(xstack, stdout, int, numbers, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_equal("[10, 20, 30, 40]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xstack_pop(int)(numbers, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XSTACK(stdout, int, numbers);
	cester_assert_stdout_stream_content_equal("[10, 20, 30]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xstack_pop(int)(numbers, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xstack_pop(int)(numbers, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xstack_pop(int)(numbers, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER(xstack, stdout, int, numbers, SUFFIX_656890909);
	cester_assert_stdout_stream_content_equal("[]");

	CESTER_RELEASE_STDOUT();
	
})

CESTER_BODY(
char *user_to_string(User *user) {
	XAllocator xallocator;

	init_xallocator(&xallocator);
	char *string_value = xstring_cstr_concat_cstr(xallocator, XTD_NULL, "{Name=");
	string_value = xstring_cstr_concat_cstr_free_old(xallocator, string_value, user->name);
	string_value = xstring_cstr_concat_cstr_free_old(xallocator, string_value, ", Email=");
	string_value = xstring_cstr_concat_cstr_free_old(xallocator, string_value, user->email);
	string_value = xstring_cstr_concat_cstr_free_old(xallocator, string_value, "}");
	return string_value;
}
)

CESTER_TEST(print_struct, _, {
    xstack(User_ptr) *users;

	User user1 = { .name = "thecarisma", .email = "test@user.com" };
	User user2 = { .name = "eccntriity", .email = "the_eccen@user.com" };
	User user3 = { .name = "vazrak", .email = "vazrak@user.com" };

    cester_assert_uint_eq(xstack_new(User_ptr)(&users), XTD_OK);
    cester_assert_uint_eq(xstack_push(User_ptr)(users, &user1), XTD_OK);
    cester_assert_uint_eq(xstack_push(User_ptr)(users, &user2), XTD_OK);
    cester_assert_uint_eq(xstack_push(User_ptr)(users, &user3), XTD_OK);
	
	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xstack, stdout, User_ptr, users, user_to_string, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_equal("[{Name=thecarisma, Email=test@user.com}, {Name=eccntriity, Email=the_eccen@user.com}, {Name=vazrak, Email=vazrak@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xstack_pop(User_ptr)(users, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XSTACK_CUSTOM(stdout, User_ptr, users, user_to_string);
	cester_assert_stdout_stream_content_equal("[{Name=thecarisma, Email=test@user.com}, {Name=eccntriity, Email=the_eccen@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xstack_pop(User_ptr)(users, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xstack_pop(User_ptr)(users, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xstack, stdout, User_ptr, users, user_to_string, SUFFIX_656890909);
	cester_assert_stdout_stream_content_equal("[]");

	CESTER_RELEASE_STDOUT();
	
})

CESTER_TEST(print_pointer, _, {
    xstack(User_ptr) *users;

	User user1 = { .name = "thecarisma", .email = "test@user.com" };
	User user2 = { .name = "eccntriity", .email = "the_eccen@user.com" };
	User user3 = { .name = "vazrak", .email = "vazrak@user.com" };

    cester_assert_uint_eq(xstack_new(User_ptr)(&users), XTD_OK);
    cester_assert_uint_eq(xstack_push(User_ptr)(users, &user1), XTD_OK);
    cester_assert_uint_eq(xstack_push(User_ptr)(users, &user2), XTD_OK);
    cester_assert_uint_eq(xstack_push(User_ptr)(users, &user3), XTD_OK);
	
	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER(xstack, stdout, User_ptr, users, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_not_equal("[{Name=thecarisma, Email=test@user.com}, {Name=eccntriity, Email=the_eccen@user.com}, {Name=vazrak, Email=vazrak@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xstack_pop(User_ptr)(users, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XSTACK(stdout, User_ptr, users);
	cester_assert_stdout_stream_content_not_equal("[{Name=thecarisma, Email=test@user.com}, {Name=vazrak, Email=vazrak@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xstack_pop(User_ptr)(users, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xstack_pop(User_ptr)(users, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER(xstack, stdout, User_ptr, users, SUFFIX_656890909);
	cester_assert_stdout_stream_content_equal("[]");

	CESTER_RELEASE_STDOUT();
	
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

