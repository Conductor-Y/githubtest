#undef NDEBU
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <lcthw/ring_buffer.h>
#include <string.h>

void ring_buffer_create(ring_buffer *buffer, unsigned long order)
{
	char path[] = "/dev/shm/ring-buffer-XXXXXX";
	int fd;
	void *address;
	int status;

	fd = mkstemp(path);			//obtain file_descriptor
	if(fd < 0) abort();

	status = unlink(path);			//close template file
	if(status) abort();

	buffer->length = 1UL << order;		//allocate size by shifting the unsigned long number 1 to the left
	buffer->end = 0;
	buffer->start = 0;

	status = ftruncate(fd, buffer->length);		//revise the size of fd
	if(status) abort();

	buffer->address = mmap(NULL, buffer->length << 1, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if(buffer->address == MAP_FAILED) abort();

	address = mmap(buffer->address, buffer->length, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_SHARED, fd, 0);
	if(address != buffer->address) abort();

	address = mmap(buffer->address + buffer->length, buffer->length, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_SHARED, fd, 0);
	if(address != buffer->address + buffer->length) abort();

	status = close(fd);			//close file_descriptor
	if(status) abort();
}

void ring_buffer_free(ring_buffer *buffer)
{
	int status = munmap(buffer->address, buffer->length << 1);		
	if(status) abort();
}

void *ring_buffer_end_address(ring_buffer *buffer)
{
	return buffer->address + buffer->end;
}
	
void ring_buffer_end_advance(ring_buffer *buffer, unsigned long length)
{
	buffer->end += length;
}

void *ring_buffer_start_address(ring_buffer *buffer)
{
	return buffer->address + buffer->start;
}

void ring_buffer_start_advance(ring_buffer *buffer, unsigned long length)
{
	buffer->start += length;

	if(buffer->start >= buffer->length)		//If the read pointer exceeds the cache length, put the read and write pointer back in the range [0, buffer->length] 
	{
		buffer->start -= buffer->length;
		buffer->end -= buffer->length;
	}
}

unsigned long ring_buffer_available_data(ring_buffer *buffer)
{
	return buffer->end - buffer->start;
}

unsigned long ring_buffer_available_space(ring_buffer *buffer)
{
	return buffer->length - ring_buffer_available_data(buffer);
}

void ring_buffer_clear(ring_buffer *buffer)
{
	buffer->end = 0;
	buffer->start = 0;
}


int ring_buffer_write(ring_buffer *buffer, char *data, unsigned long size) 
{
    void *write_ptr = ring_buffer_end_address(buffer);
	int status = 1;

    if (write_ptr != NULL) 
	{
        if (size <= ring_buffer_available_space(buffer)) 
		{
            memcpy(write_ptr, data, size);
            ring_buffer_end_advance(buffer, size);
			status = 0;
        } 
    }

	return status;
}

int ring_buffer_read(ring_buffer *buffer, char *data, unsigned long size)
{
	void *read_ptr = ring_buffer_start_address(buffer);
	int status = 1;

	if(read_ptr != NULL)
	{
		if(size <= ring_buffer_available_data(buffer))
		{
			memcpy(data, read_ptr, size);
			ring_buffer_start_advance(buffer, size);
			status = 0;
		}
	}

	return status; 
}
