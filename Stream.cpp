
#include "Stream.h"

Stream_Base::Stream_Base(int size) : write_pos_(0), read_pos_(0), next_(NULL)
{
	if (size > 1024 * 100)
	{
#ifdef WIN32
		throw std::exception("Stream_Base::Stream_Base(int size): size > 1024 * 100");
#else
		throw std::runtime_error("Stream_Base::Stream_Base(int size): size > 1024 * 100");
#endif
	}
	size_ = size;

	buffer_ = new OS_Buffer(size);
}

Stream_Base::~Stream_Base()
{
	delete buffer_;
    buffer_ = NULL;
}

int Stream_Base::write(const char *buffer, int size)
{
	if (size > get_space())
	{
		resize((int)(get_size() + size));
	}

	int result = buffer_->write(buffer,write_pos_,size);
	if(result != -1)
	{
		write_pos_ += size;
	}
	else
	{
#ifdef WIN32
		throw std::exception("Binary_Stream::write(const char *buffer, int size) error,result return is -1!");
#else
		throw std::runtime_error("Binary_Stream::write(const char *buffer, int size) error,result return is -1!");
#endif

	}
	return result;
}

int Stream_Base::read(char *buffer, int size)
{
	if(size > get_readable())
		return -1;
	int result = buffer_->read(buffer,read_pos_,size);
	if(result != - 1)
	{
		read_pos_ += size;
	}
	return result;
}

bool  Stream_Base::resize(int len)
{
	if (len >  1024 * 1000)
	{
#ifdef WIN32
		throw std::exception("Stream_Base::resize  len > 1024 * 1000");
#else
		throw std::runtime_error("Stream_Base::resize  len > 1024 * 1000");
#endif
	}

	if (len < (int)this->size_)
	{
		return true;
	}

	bool bCheck = Allocator_Manager::instance()->checkSize(buffer_->get_buffer(), len);
	if (bCheck == true)
	{
		size_ = len;
		buffer_->set_size(len);
	}
	else
	{
		OS_Buffer *os = new OS_Buffer(len);
		memcpy(os->get_buffer(),this->buffer_->get_buffer(),this->size_);
		delete buffer_;
		this->buffer_ = os;
		this->size(len);
	}

	return true;
}

