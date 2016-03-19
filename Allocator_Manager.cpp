#include "Allocator_Manager.h"
#include "Thread.h"

		
Allocator_Manager*  Allocator_Manager::instance(void)
{
	static Allocator_Manager* g_malloc = NULL;
	static DDMutex _lock;
	if (g_malloc == NULL)
	{
		GUARD_RETURN(DDMutex, obj, _lock, NULL);
		if (g_malloc == NULL)
		{
			g_malloc = new Allocator_Manager;
		}
	}
	return g_malloc;
}