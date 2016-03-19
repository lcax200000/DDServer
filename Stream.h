#ifndef STREAM_H
#define STREAM_H

#include "OS_Buffer.h"

class Stream_Base 
{
public:
	Stream_Base(int size);

	virtual ~Stream_Base(void);

	inline OS_Buffer& get_buffer()
	{
		return *buffer_;
	}

	int write(const char *buffer, int size);
			
	int read(char *buffer, int size);

	inline int get_read_pos()
	{
		return read_pos_;
	}

	inline void move_read_pos(int pos)
	{
		read_pos_ += pos;
	}

	inline int get_write_pos() const
	{
		return write_pos_;
	}
			
	inline void move_write_pos(int pos)
	{
		write_pos_ += pos;
	}

	inline void reset_all()
	{
		read_pos_ = write_pos_ = 0;
	}
			
	inline void reset_read_pos()
	{
		read_pos_ = 0;
	}

	inline void reset_wirte_pos()
	{
		write_pos_ = 0;
	}

	inline int get_readable() const
	{
		return write_pos_ - read_pos_;
	}
			
	
	inline int get_space()
	{
		return buffer_->get_size() - write_pos_;
	}

	inline char* get_read_ptr()
	{
		return (char*)buffer_->get_buffer() + read_pos_;
	}

	inline char* get_write_ptr()
	{
		return (char*)buffer_->get_buffer() + write_pos_;
	}

	inline char* rp_delta(int delta)
	{
		char* temp = get_read_ptr();
		move_read_pos(delta);
		return temp;
	}

	inline char* wp_delta(int delta)
	{
		char* temp = get_write_ptr();
		move_write_pos(delta);
		return temp;
	}

	inline char* get_base_ptr()
	{
		return buffer_->get_buffer();
	}
			
	inline void set_write_pos(int pos)
	{
		write_pos_ = pos;
	}

	inline void set_read_pos(int pos)
	{
		read_pos_ = pos;
	}

	inline size_t get_size(void) const
	{
		return size_;
	}


	virtual bool resize(int len);


	void*  operator new(size_t size)
	{
		if (size == 0)
		{
			size = 1;
		}

		void* p = Allocator_Manager::instance()->malloc(sizeof(Stream_Base));
			if (p == NULL)
			{
				throw std::bad_alloc();
			}
			else
			{
				return    p;
			}
		
	}

	void operator delete(void *p)
	{
		if (p == NULL)
		{
			return;
		}
		Allocator_Manager::instance()->free(p);
	}

	void operator delete(void *p, void *pp)
	{
		if (p == NULL)
		{
			return;
		}
		Allocator_Manager::instance()->free(p);
	}

	Stream_Base* next_;

protected:
	inline void size(size_t size)
	{
		size_ = size;
	}

	OS_Buffer* buffer_;

	int write_pos_;

	int read_pos_;

	size_t  size_;
private:
	Stream_Base& operator=(const Stream_Base&);

};



#endif



