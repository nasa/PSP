#include "common_types.h"
#include "osapi.h"

// TODO: set blocksize of cds memory in reserved memory map
init32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS)
{
	int32 return_code;

	if (SizeOfCDS == NULL)
	{
		return OS_ERROR;
	}

	/* set blocksize of cds memory in reserved memory map */
	return OS_SUCCESS;
}
