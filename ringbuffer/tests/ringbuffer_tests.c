#include "minunit.h"
#include <lcthw/dbg.h>
#include <lcthw/ringbuffer.h>

static RingBuffer *buffer = NULL;
char data[50] = {'\0'};

char *test_create()
{
	buffer = RingBuffer_create(50);
	mu_assert(buffer != NULL, "Failed to create ring buffer.");

	return NULL;
}

char *test_destroy()
{
	check_mem(buffer);	
	
	RingBuffer_destroy(buffer);
	buffer = NULL;
	mu_assert(buffer == NULL, "Failed to destroy ring buffer.");

	return NULL;

error:
	return NULL;
}

char *test_write()
{
	mu_assert(RingBuffer_empty(buffer), "Should be empty.");
    mu_assert(!RingBuffer_full(buffer), "Should NOT be full.");

	int length = RingBuffer_write(buffer, data, sizeof("my name is wahaha"));
	mu_assert(length == sizeof("my name is wahaha"), "Failed to wirte correctly.");
	mu_assert(RingBuffer_available_data(buffer) == 18, "Should have 18 data.");
    mu_assert(RingBuffer_available_space(buffer) == 50 - 18, "Should have 2 space left.");

	int rc = RingBuffer_read(buffer, data, 18);
	mu_assert(rc == 18, "Failed to read buffer.");
	mu_assert(RingBuffer_available_data(buffer) == 0, "Should have 0 data.");
	mu_assert(RingBuffer_available_space(buffer) == 50, "Should have 32 space left.");

	bstring data = bfromcstr("hello");
	rc = RingBuffer_puts(buffer, data);
	mu_assert(rc != -1, "Failed to write a bstring.");
    mu_assert(!RingBuffer_empty(buffer), "Should not be empty.");
	bdestroy(data);

	data = RingBuffer_gets(buffer, 2);
    mu_assert(data, "Didn't get any bstring from gets.");
    mu_assert(bisstemeqblk(data, "he", 2), "Wrong gets result.");
    bdestroy(data);

	data = RingBuffer_get_all(buffer);
	mu_assert(data, "Didn't get any bstring from get_all.");
	mu_assert(bisstemeqblk(data, "llo", 3), "Wrong gets all result.");
	bdestroy(data);

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_write);
	mu_run_test(test_destroy);

	return NULL;
}

RUN_TESTS(all_tests);
