#ifndef BLOCK_ALLOCATOR
#define BLOCK_ALLOCATOR

//#include "stdafx.h"
#include <stdio.h>
#include "boost/lockfree/queue.hpp"
// 使用slab算法的内存池
// 一个SBlock是一页内存，SMemory_Block有该页内存的每段内存块的地址
// 一个Block_Allocator相当于一个slab
class  Block_Allocator
{
	struct SBlock
	{
		SBlock* next_;

		SBlock() : next_(NULL)
		{

		}

		SBlock(SBlock* next) : next_(next)
		{

		}
	};

	struct SMemory_Block
	{
		char* memory_block_;
		SMemory_Block* next_;

		SMemory_Block() : memory_block_(NULL), next_(NULL)
		{

		}
	};
public:
	size_t block_size_;

	size_t block_number_;

public:
	Block_Allocator(size_t block_size, size_t block_number = 32)
	{
		block_size_ = block_size > sizeof(void*) ? block_size : sizeof(void*);
		block_number_ = block_number;
		allocat_size();
	}

	~Block_Allocator(void)
	{
		while(memory_list_.next_)
		{
			SMemory_Block* block = memory_list_.next_;
			memory_list_.next_ = block->next_;
			delete []block->memory_block_;
			delete block;
		}
	}

	size_t get_allocator_size(void)
	{
		int memory_block_number = 0;
		for (SMemory_Block* block = memory_list_.next_; block != NULL; block = block->next_)
		{
			++memory_block_number;
		}

		return  memory_block_number * block_number_ * block_size_;
	}

	void* malloc()
	{
		SBlock* result = NULL;
		while (lock_free_.pop(result)==false)
		{
			if (lock_free_.empty())
			{
				
				allocat_size();
			}
		}
		if (result)
			return result;
		else
			printf("lock free pop false!!!!");
		return NULL;
	}

	void free(void *p)
	{
		if (!p)
			return;
		lock_free_.push((SBlock*)p);
	}
private:
	
	void allocat_size()
	{
		size_t total = block_size_ * block_number_;
		char* buffer = new(std::nothrow)char[total];
		if(!buffer)
			return;

		SMemory_Block* new_block = new(std::nothrow) SMemory_Block;
		if(!new_block)
		{
			delete []buffer;
			return;
		}

		new_block->next_         = memory_list_.next_;

		new_block->memory_block_ = buffer;
		memory_list_.next_       = new_block;

		SBlock* header = new(buffer)SBlock;
		header->next_  = NULL;
		buffer += block_size_;
		SBlock* block = NULL;
		for(size_t i = 1; i < block_number_ ; ++i)
		{
			block = (SBlock*)buffer;
			buffer += block_size_;
			block->next_ = header;
			header = block;
			lock_free_.push(block);
		}
	}

private:
	
	boost::lockfree::queue<SBlock*> lock_free_;


	SMemory_Block memory_list_;
};
#endif