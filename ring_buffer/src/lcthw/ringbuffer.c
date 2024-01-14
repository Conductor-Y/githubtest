#undef NDEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lcthw/dbg.h>
#include <lcthw/ringbuffer.h>

RingBuffer *RingBuffer_create(int length)
{
    RingBuffer *buffer = calloc(1, sizeof(RingBuffer));
	check_mem(buffer);

    buffer->length  = length + 1;		//initialize buffer
    buffer->start = 0;
    buffer->end = 0;
    buffer->buffers = calloc(buffer->length, 1);		//sizeof(char) is 1

    return buffer;

error:
	return NULL;
}

void RingBuffer_destroy(RingBuffer *buffer)
{
	if(buffer)
	{
		if(buffer->buffers)
		{
			free(buffer->buffers);
		}
		free(buffer);
	}
}

int RingBuffer_write(RingBuffer *buffer, char *data, int length)
{
    if(RingBuffer_available_data(buffer) == 0) 
	{
		buffer->start = buffer->end = 0;
	}
    check(length <= RingBuffer_available_space(buffer),
            "Not enough space: %d request, %d available",
            RingBuffer_available_data(buffer), length);

    void *result = memcpy(RingBuffer_ends_at(buffer), data, length);
    check(result != NULL, "Failed to write data into buffer.");

    RingBuffer_commit_write(buffer, length);		//update the location of end

    return length;

error:
    return -1;
}

int RingBuffer_read(RingBuffer *buffer, char *target, int amount)
{
    check_debug(amount <= RingBuffer_available_data(buffer),
            "Not enough in the buffer: has %d, needs %d",
            RingBuffer_available_data(buffer), amount);

    void *result = memcpy(target, RingBuffer_starts_at(buffer), amount);
    check(result != NULL, "Failed to write buffer into data.");

    RingBuffer_commit_read(buffer, amount);			//update the location of start

    if(buffer->end == buffer->start)		//when buffer is empty 
	{
        buffer->start = buffer->end = 0;
    }

    return amount;

error:
    return -1;
}

bstring RingBuffer_gets(RingBuffer *buffer, int amount)
{
    check(amount > 0, "Need more than 0 for gets, you gave: %d ", amount);
    check_debug(amount <= RingBuffer_available_data(buffer),
			"Not enough in the buffer.");

    bstring result = blk2bstr(RingBuffer_starts_at(buffer), amount);		//use a stucture to receive return, the function of blk2bstr is to convert binary to string
    check(result != NULL, "Failed to create gets result.");
    check(blength(result) == amount, "Wrong result length.");

    RingBuffer_commit_read(buffer, amount);
    assert(RingBuffer_available_data(buffer) >= 0 && "Error in read commit.");

    return result;

error:
    return NULL;
}




