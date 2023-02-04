/*!gcc {0} -I. -I../../../include/ -o out -Wno-int-conversion; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/container/xstring.h>
#include <exotic/xtd/container/xvector.h>
#include <exotic/cline/xtd_printers.h>

CESTER_BODY(
	typedef struct user_s {
		char *name;
		char *email;
	} User;

    typedef char* str;
    typedef User* User_ptr;
    SETUP_XVECTOR_FOR(str)
    SETUP_XVECTOR_FOR(int)
    SETUP_XVECTOR_FOR(User_ptr)
)

CESTER_TEST(print_str, _, {
    xvector(str) *fruits;

    cester_assert_uint_eq(xvector_new(str)(&fruits), XTD_OK);
    cester_assert_uint_eq(xvector_add(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xvector_add(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xvector_add(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xvector_add(str)(fruits, "Pineapple"), XTD_OK);

	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER(xvector, stdout, str, fruits, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_equal("[\"Apple\", \"Banana\", \"Mango\", \"Pineapple\"]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xvector_remove_at(str)(fruits, 1, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XVECTOR(stdout, str, fruits);
	cester_assert_stdout_stream_content_equal("[\"Apple\", \"Mango\", \"Pineapple\"]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xvector_remove_at(str)(fruits, 0, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xvector_remove_at(str)(fruits, 0, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xvector_remove_at(str)(fruits, 0, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER(xvector, stdout, str, fruits, SUFFIX_656890909);
	cester_assert_stdout_stream_content_equal("[]");

	CESTER_RELEASE_STDOUT();
	
})

CESTER_TEST(print_int, _, {
    xvector(int) *numbers;

    cester_assert_uint_eq(xvector_new(int)(&numbers), XTD_OK);
    cester_assert_uint_eq(xvector_add(int)(numbers, 10), XTD_OK);
    cester_assert_uint_eq(xvector_add(int)(numbers, 20), XTD_OK);
    cester_assert_uint_eq(xvector_add(int)(numbers, 30), XTD_OK);
    cester_assert_uint_eq(xvector_add(int)(numbers, 40), XTD_OK);

	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER(xvector, stdout, int, numbers, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_equal("[10, 20, 30, 40]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xvector_remove_at(int)(numbers, 2, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XVECTOR(stdout, int, numbers);
	cester_assert_stdout_stream_content_equal("[10, 20, 40]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xvector_remove_at(int)(numbers, 0, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xvector_remove_at(int)(numbers, 0, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xvector_remove_at(int)(numbers, 0, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER(xvector, stdout, int, numbers, SUFFIX_656890909);
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
    xvector(User_ptr) *users;

	User user1 = { .name = "thecarisma", .email = "test@user.com" };
	User user2 = { .name = "eccntriity", .email = "the_eccen@user.com" };
	User user3 = { .name = "vazrak", .email = "vazrak@user.com" };

    cester_assert_uint_eq(xvector_new(User_ptr)(&users), XTD_OK);
    cester_assert_uint_eq(xvector_add(User_ptr)(users, &user1), XTD_OK);
    cester_assert_uint_eq(xvector_add(User_ptr)(users, &user2), XTD_OK);
    cester_assert_uint_eq(xvector_add(User_ptr)(users, &user3), XTD_OK);
	
	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xvector, stdout, User_ptr, users, user_to_string, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_equal("[{Name=thecarisma, Email=test@user.com}, {Name=eccntriity, Email=the_eccen@user.com}, {Name=vazrak, Email=vazrak@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xvector_remove_at(User_ptr)(users, 1, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XVECTOR_CUSTOM(stdout, User_ptr, users, user_to_string);
	cester_assert_stdout_stream_content_equal("[{Name=thecarisma, Email=test@user.com}, {Name=vazrak, Email=vazrak@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xvector_remove_at(User_ptr)(users, 0, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xvector_remove_at(User_ptr)(users, 0, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xvector, stdout, User_ptr, users, user_to_string, SUFFIX_656890909);
	cester_assert_stdout_stream_content_equal("[]");

	CESTER_RELEASE_STDOUT();
	
})

CESTER_TEST(print_pointer, _, {
    xvector(User_ptr) *users;

	User user1 = { .name = "thecarisma", .email = "test@user.com" };
	User user2 = { .name = "eccntriity", .email = "the_eccen@user.com" };
	User user3 = { .name = "vazrak", .email = "vazrak@user.com" };

    cester_assert_uint_eq(xvector_new(User_ptr)(&users), XTD_OK);
    cester_assert_uint_eq(xvector_add(User_ptr)(users, &user1), XTD_OK);
    cester_assert_uint_eq(xvector_add(User_ptr)(users, &user2), XTD_OK);
    cester_assert_uint_eq(xvector_add(User_ptr)(users, &user3), XTD_OK);
	
	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER(xvector, stdout, User_ptr, users, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_not_equal("[{Name=thecarisma, Email=test@user.com}, {Name=eccntriity, Email=the_eccen@user.com}, {Name=vazrak, Email=vazrak@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xvector_remove_at(User_ptr)(users, 1, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XVECTOR(stdout, User_ptr, users);
	cester_assert_stdout_stream_content_not_equal("[{Name=thecarisma, Email=test@user.com}, {Name=vazrak, Email=vazrak@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xvector_remove_at(User_ptr)(users, 0, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xvector_remove_at(User_ptr)(users, 0, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER(xvector, stdout, User_ptr, users, SUFFIX_656890909);
	cester_assert_stdout_stream_content_equal("[]");

	CESTER_RELEASE_STDOUT();
	
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

