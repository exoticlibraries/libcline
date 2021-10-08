/*!gcc {0} -I. -I../../../include/ -o out -Wno-int-conversion; ./out */

#include <exotic/cester.h>
#include <exotic/xtd/xstring.h>
#include <exotic/xtd/xpriority_queue.h>
#include <exotic/cline/xtd_printers.h>

CESTER_BODY(
	typedef struct user_s {
		char *name;
		char *email;
	} User;

    typedef char* str;
    typedef User* User_ptr;
    SETUP_XPRIORITY_QUEUE_FOR(str)
    SETUP_XPRIORITY_QUEUE_FOR(int)
    SETUP_XPRIORITY_QUEUE_FOR(User_ptr)

    bool cmp_str(char *const a, char *const b) {
        return *a < *b;
    }

    bool cmp_int(int const a, int const b) {
        return a < b;
    }

    bool cmp_user(User *const a, User *const b) {
        return *(a->name) < *(b->name);
    }
)

CESTER_TEST(print_str, _, {
    xpriority_queue(str) *fruits;

    cester_assert_uint_eq(xpriority_queue_new(str)(&fruits, cmp_str), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(str)(fruits, "Apple"), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(str)(fruits, "Banana"), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(str)(fruits, "Mango"), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(str)(fruits, "Pineapple"), XTD_OK);

	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER(xpriority_queue, stdout, str, fruits, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_equal("[\"Apple\", \"Banana\", \"Mango\", \"Pineapple\"]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xpriority_queue_dequeue(str)(fruits, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XPRIORITY_QUEUE(stdout, str, fruits);
	cester_assert_stdout_stream_content_equal("[\"Pineapple\", \"Banana\", \"Mango\"]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xpriority_queue_dequeue(str)(fruits, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_dequeue(str)(fruits, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_dequeue(str)(fruits, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER(xpriority_queue, stdout, str, fruits, SUFFIX_656890909);
	cester_assert_stdout_stream_content_equal("[]");

	CESTER_RELEASE_STDOUT();
	
})

CESTER_TEST(print_int, _, {
    xpriority_queue(int) *numbers;

    cester_assert_uint_eq(xpriority_queue_new(int)(&numbers, cmp_int), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(int)(numbers, 10), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(int)(numbers, 20), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(int)(numbers, 30), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(int)(numbers, 40), XTD_OK);

	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER(xpriority_queue, stdout, int, numbers, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_equal("[10, 20, 30, 40]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xpriority_queue_dequeue(int)(numbers, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XPRIORITY_QUEUE(stdout, int, numbers);
	cester_assert_stdout_stream_content_equal("[40, 20, 30]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xpriority_queue_dequeue(int)(numbers, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_dequeue(int)(numbers, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_dequeue(int)(numbers, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER(xpriority_queue, stdout, int, numbers, SUFFIX_656890909);
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
    xpriority_queue(User_ptr) *users;

	User user1 = { .name = "thecarisma", .email = "test@user.com" };
	User user2 = { .name = "eccntriity", .email = "the_eccen@user.com" };
	User user3 = { .name = "vazrak", .email = "vazrak@user.com" };

    cester_assert_uint_eq(xpriority_queue_new(User_ptr)(&users, cmp_user), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(User_ptr)(users, &user1), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(User_ptr)(users, &user2), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(User_ptr)(users, &user3), XTD_OK);
	
	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xpriority_queue, stdout, User_ptr, users, user_to_string, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_equal("[{Name=eccntriity, Email=the_eccen@user.com}, {Name=thecarisma, Email=test@user.com}, {Name=vazrak, Email=vazrak@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xpriority_queue_dequeue(User_ptr)(users, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XPRIORITY_QUEUE_CUSTOM(stdout, User_ptr, users, user_to_string);
	cester_assert_stdout_stream_content_equal("[{Name=vazrak, Email=vazrak@user.com}, {Name=thecarisma, Email=test@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xpriority_queue_dequeue(User_ptr)(users, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_dequeue(User_ptr)(users, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER_CUSTOM(xpriority_queue, stdout, User_ptr, users, user_to_string, SUFFIX_656890909);
	cester_assert_stdout_stream_content_equal("[]");

	CESTER_RELEASE_STDOUT();
	
})

CESTER_TEST(print_pointer, _, {
    xpriority_queue(User_ptr) *users;

	User user1 = { .name = "thecarisma", .email = "test@user.com" };
	User user2 = { .name = "eccntriity", .email = "the_eccen@user.com" };
	User user3 = { .name = "vazrak", .email = "vazrak@user.com" };

    cester_assert_uint_eq(xpriority_queue_new(User_ptr)(&users, cmp_user), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(User_ptr)(users, &user1), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(User_ptr)(users, &user2), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_enqueue(User_ptr)(users, &user3), XTD_OK);
	
	CESTER_CAPTURE_STDOUT();
	CLINE_XPRINT_XTD_CONTAINER(xpriority_queue, stdout, User_ptr, users, SUFFIX_6251425454);
	cester_assert_stdout_stream_content_not_equal("[{Name=thecarisma, Email=test@user.com}, {Name=eccntriity, Email=the_eccen@user.com}, {Name=vazrak, Email=vazrak@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xpriority_queue_dequeue(User_ptr)(users, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XPRIORITY_QUEUE(stdout, User_ptr, users);
	cester_assert_stdout_stream_content_not_equal("[{Name=thecarisma, Email=test@user.com}, {Name=vazrak, Email=vazrak@user.com}]");

	CESTER_RESET_STDOUT();
    cester_assert_uint_eq(xpriority_queue_dequeue(User_ptr)(users, XTD_NULL), XTD_OK);
    cester_assert_uint_eq(xpriority_queue_dequeue(User_ptr)(users, XTD_NULL), XTD_OK);
	CLINE_XPRINT_XTD_CONTAINER(xpriority_queue, stdout, User_ptr, users, SUFFIX_656890909);
	cester_assert_stdout_stream_content_equal("[]");

	CESTER_RELEASE_STDOUT();
	
})

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(2);
)

