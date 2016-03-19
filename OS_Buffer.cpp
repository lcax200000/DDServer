
#include "OS_Buffer.h"

OS_Buffer::OS_Buffer(int buffer_size)
{
	buffer_size_ = buffer_size;
	buffer_ = (char*)Allocator_Manager::instance()->malloc(buffer_size);
}

OS_Buffer::~OS_Buffer(void)
{
	Allocator_Manager::instance()->free(buffer_);
}

char* OS_Buffer::get_buffer()
{
	return buffer_;
}

int OS_Buffer::get_size()
{
	return buffer_size_;
}

void OS_Buffer::set_size(int size)
{
	buffer_size_ = size;
}

int OS_Buffer::write(const char* source, int begin, int size)
{
	if(begin + size > buffer_size_)
		return -1;

	memcpy(buffer_ + begin, source, size);
	return size;
}

int OS_Buffer::read(char *target, int begin, int size)
{
	if(begin + size > buffer_size_)
		return -1;
	memcpy(target, buffer_ + begin, size);
	return size;
}


