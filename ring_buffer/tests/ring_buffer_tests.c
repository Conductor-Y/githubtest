#include <lcthw/ring_buffer.h>
#include "minunit.h"
#include <lcthw/dbg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <lcthw/ringbuffer.h>


static ring_buffer *buffer = NULL;
char data[50] = {'\0'};

char *test_create()
{
	buffer = calloc(1, sizeof(ring_buffer));
	mu_assert(buffer != NULL, "Failed to calloc buffer.");

	ring_buffer_create(buffer, 12);

	return NULL;
}

char *test_free()
{
	check_mem(buffer);

	ring_buffer_free(buffer);		//free buffer->address

	free(buffer);
	buffer = NULL;
	mu_assert(buffer == NULL, "Failed to free buffer.");

	return NULL;

error:
	return NULL;
}

char *test_write()
{
	int status = ring_buffer_write(buffer, "my name is wahaha", sizeof("my name is wahaha"));
	mu_assert(status == 0, "Failed to write.");
	mu_assert(ring_buffer_available_data(buffer) == sizeof("my name is wahaha"), "Wrong number of available data.");
	mu_assert(ring_buffer_available_space(buffer) == buffer->length - sizeof("my name is wahaha"), "Wrong available space in buffer.");

	status = ring_buffer_read(buffer, data, sizeof("my name"));
	mu_assert(status == 0, "Failed to read.");
	mu_assert(ring_buffer_available_data(buffer) == sizeof("my name is wahaha") - sizeof("my name"), "Wrong number of available data.");
	mu_assert(ring_buffer_available_space(buffer) == buffer->length - ring_buffer_available_data(buffer), "Wrong available space in buffer.");

	ring_buffer_clear(buffer);
	mu_assert(buffer->start == 0, "Failed to clear.");
	mu_assert(buffer->end == 0, "Failed to clear.");

	return NULL;	
}


char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_write);	
	mu_run_test(test_free);
	return NULL;
}

RUN_TESTS(all_tests);
