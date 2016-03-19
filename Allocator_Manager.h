#ifndef ALLOCATOR_MANAGER
#define ALLOCATOR_MANAGER
#include "Block_Allocator.h"
#include "Thread.h"
#ifndef WIN32
#include<string.h>
#endif
class  Allocator_Manager
{
public:
	/** Method
	* - Summary:\n
	*  构造 
	* - Parameters:\n
	*初始化各个分派器
	*/
	Allocator_Manager() : Allocator16_(16),
		Allocator32_(32),
		Allocator64_(64),
		Allocator128_(128),
		Allocator256_(256),
		Allocator512_(512),
		Allocator1024_(1024),
		Allocator2048_(2048),
		Allocator4096_(4096),
		Allocator8192_(8192),
		Allocator16384_(16384),
		Allocator32768_(32768),
		Allocator65536_(65536)
	{
	}

	/** Method
	* - Summary:\n
	*  析构 
	* - Parameters:\n
	*
	*/
	~Allocator_Manager()
	{

	}

	// 判断大小是否匹配
	bool checkSize(void* p, size_t rbytes)
	{
		if (p == NULL)
			return false;

		char flag = 0;
		p = move_void_ptr(p, -1);
		memcpy(&flag, p, 1);

		switch(flag)
		{
		case 0:
			if (rbytes < 16)
			{
				return true;
			}
			break;
		case 1:
			if (rbytes < 32)
			{
				return true;
			}
			break;
		case 2:
			if (rbytes < 64)
			{
				return true;
			}
			break;
		case 3:
			if (rbytes < 128)
			{
				return true;
			}
			break;
		case 4:
			if (rbytes < 256)
			{
				return true;
			}
			break;
		case 5:
			if (rbytes < 512)
			{
				return true;
			}
			break;
		case 6:
			if (rbytes < 1024)
			{
				return true;
			}
			break;
		case 7:
			if (rbytes < 2048)
			{
				return true;
			}
			break;
		case 8:
			if (rbytes < 4096)
			{
				return true;
			}
			break;
		case 9:
			if (rbytes < 8192)
			{
				return true;
			}
			break;
		case 10:
			if (rbytes < 16384)
			{
				return true;
			}
			break;
		case 11:
			if (rbytes < 32768)
			{
				return true;
			}
			break;
		case 12:
			if (rbytes < 65536)
			{
				return true;
			}
			break;
		case 13:
			return false;
			break;
		default:
			break;
		}
		return false;
	}
	/** Method
	* - Summary:\n
	*		根据长度分派相应的分派器。有一个问题，就是如果分派器过长。
	*       那样怎么考虑。是不是直接用malloc和free
	* - Parameters:\n
	*  分派空间的长度
	* - Return:\n
	*  分派的地址
	*/
	void* malloc(size_t nbytes)
	{
		void* p = NULL;
		char flag;
		if (nbytes < 16)
		{
			p = Allocator16_.malloc();
			flag =  0;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		if (nbytes < 32)
		{
			p = Allocator32_.malloc();
			flag =  1;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		if (nbytes < 64)
		{
			p = Allocator64_.malloc();
			flag =  2;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		if (nbytes < 128)
		{
			p = Allocator128_.malloc();
			flag =  3;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		if (nbytes < 256)
		{
			p = Allocator256_.malloc();
			flag =  4;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}


		if (nbytes < 512)
		{
			p = Allocator512_.malloc();
			flag =  5;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		if(nbytes < 1024)
		{
			p = Allocator1024_.malloc();
			flag = 6;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		if(nbytes < 2048)
		{
			p = Allocator2048_.malloc();
			flag = 7;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		if (nbytes < 4096)
		{
			p = Allocator4096_.malloc();
			flag =  8;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		if(nbytes < 8192)
		{
			p = Allocator8192_.malloc();
			flag = 9;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		if (nbytes < 16384)
		{
			p = Allocator16384_.malloc();
			flag = 10;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		if(nbytes < 32768)
		{
			p = Allocator32768_.malloc();
			flag = 11;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		if (nbytes < 65536)
		{
			p = Allocator65536_.malloc();
			flag = 12;
			memcpy(p,&flag,1);
			p = move_void_ptr(p,1);
			return p;
		}

		p = ::malloc(nbytes + 1);
		if (p == NULL)
		{
			////LOGERROR("Sect_Block_Allocator::malloc  p == NULL");
		}
		flag =  13;
		memcpy(p,&flag,1);
		p = move_void_ptr(p,1);

		return p;
	}

	/** Method
	* - Summary:\n
	*		将分派的void*右移	
	*       
	* - Parameters:\n
	*  1 地址， 2 右移的字节数
	* - Return:\n
	*  右移后的地址
	*/
	inline void* move_void_ptr(void* const ptr,int i)
	{
		char* p  = (char*)ptr;
		p = p + i;
		void* np = p;
		return np;
	}

	/** Method
	* - Summary:\n
	*		释放分配的空间
	*      
	* - Parameters:\n
	*  
	* - Return:\n
	*  
	*/
	void free(void* p)
	{
		if(p == 0)
			return;
		char  flag = 0;
		p  = move_void_ptr(p,-1);
		memcpy(&flag,p,1);
		switch(flag)
		{
		case 0:
			Allocator16_.free(p);
			break;
		case 1:
			Allocator32_.free(p);
			break;
		case 2:
			Allocator64_.free(p);
			break;
		case 3:
			Allocator128_.free(p);
			break;
		case 4:
			Allocator256_.free(p);
			break;
		case 5:
			Allocator512_.free(p);
			break;
		case 6:
			Allocator1024_.free(p);
			break;
		case 7:
			Allocator2048_.free(p);
			break;
		case 8:
			Allocator4096_.free(p);
			break;
		case 9:
			Allocator8192_.free(p);
			break;
		case 10:
			Allocator16384_.free(p);
			break;
		case 11:
			Allocator32768_.free(p);
			break;
		case 12:
			Allocator65536_.free(p);
			break;
		case 13:
			::free(p);
			break;
		default:
			break;
		}

	}

	/** Method
	* - Summary:\n
	*		释放分配的空间
	*      
	* - Parameters:\n
	*  
	* - Return:\n
	*  
	*/
	void free(void* p,size_t nbytes)
	{
		if (!p)
			return;
		if (nbytes <= 16)
		{
			Allocator16_.free(p);
			return;
		}

		if (nbytes <= 32)
		{
			Allocator32_.free(p);
			return;
		}

		if (nbytes <= 64)
		{
			Allocator64_.free(p);
			return;
		}

		if (nbytes <= 128)
		{
			Allocator128_.free(p);
			return;
		}

		if (nbytes <= 256)
		{
			Allocator256_.free(p);
			return;
		}

		if (nbytes <= 512)
		{
			Allocator512_.free(p);
			return;
		}

		if (nbytes <= 1024)
		{
			Allocator1024_.free(p);
			return;
		}

		if (nbytes <= 2048)
		{
			Allocator2048_.free(p);
			return;
		}

		if (nbytes <= 4096)
		{
			Allocator4096_.free(p);
			return;
		}

		if (nbytes <= 8192)
		{
			Allocator8192_.free(p);
			return;
		}

		if (nbytes <= 16384)
		{
			Allocator16384_.free(p);
			return;
		}

		if (nbytes <= 32768)
		{
			Allocator32768_.free(p);
			return;
		}

		if (nbytes <= 65536)
		{
			Allocator65536_.free(p);
			return;
		}

		::free(p);
	}
	static  Allocator_Manager*  instance(void);


	size_t  get_total_allocator_size(void)
	{
		return Allocator16_.get_allocator_size() + Allocator32_.get_allocator_size() + Allocator64_.get_allocator_size() +Allocator128_.get_allocator_size() + Allocator256_.get_allocator_size()
			+ Allocator512_.get_allocator_size() +  Allocator1024_.get_allocator_size() + Allocator2048_.get_allocator_size() +  Allocator4096_.get_allocator_size()
			+ Allocator8192_.get_allocator_size() + Allocator16384_.get_allocator_size() + Allocator32768_.get_allocator_size() + Allocator65536_.get_allocator_size();
	}
private:
	Block_Allocator     Allocator16_;
	Block_Allocator     Allocator32_;
	Block_Allocator     Allocator64_;
	Block_Allocator     Allocator128_;
	Block_Allocator     Allocator256_;
	Block_Allocator     Allocator512_;
	Block_Allocator		Allocator1024_;
	Block_Allocator		Allocator2048_;
	Block_Allocator     Allocator4096_;
	Block_Allocator		Allocator8192_;
	Block_Allocator     Allocator16384_;
	Block_Allocator     Allocator32768_;
	Block_Allocator     Allocator65536_;
};
#endif