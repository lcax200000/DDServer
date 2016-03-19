#pragma once

#include "Allocator_Manager.h"


class OS_Buffer
{
public:

	OS_Buffer(int buffer_size);

public:

	~OS_Buffer(void);


	int write(const char* source, int begin, int size);

	int read(char* target, int begin, int size);

	char* get_buffer(void);

	int get_size(void);
	void set_size(int size);

	
private:

	char* buffer_;
			
	int  buffer_size_;

private:
	OS_Buffer(const OS_Buffer&);
	OS_Buffer& operator = (const OS_Buffer&);
};



