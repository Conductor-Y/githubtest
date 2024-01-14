#ifndef _lcthw_Ring_Buffer_h
#define _lcthw_Ring_Buffer_h

typedef struct
{
	void *address;
	unsigned long length;
	unsigned long end;
	unsigned long start;
}ring_buffer;

void ring_buffer_create(ring_buffer *buffer, unsigned long order);
void ring_buffer_free(ring_buffer *buffer);
void *ring_buffer_end_address(ring_buffer *buffer);
void ring_buffer_end_advance(ring_buffer *buffer, unsigned long length);
void *ring_buffer_start_address(ring_buffer *buffer);
void ring_buffer_start_advance(ring_buffer *buffer, unsigned long length);
unsigned long ring_buffer_available_data(ring_buffer *buffer);
unsigned long ring_buffer_available_space(ring_buffer *buffer);
void ring_buffer_clear(ring_buffer *buffer);
int ring_buffer_write(ring_buffer *buffer, char *data, unsigned long size);
int ring_buffer_read(ring_buffer *buffer, char *data, unsigned long size);

#endif
