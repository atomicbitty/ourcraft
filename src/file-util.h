#ifndef __file_util_h__
#define __file_util_h__

#include <stdio.h>

//NOTE: the memory allocated by these functions MUST BE FREED!
extern char *get_filename_text(const char *filename);
extern char *get_file_text(FILE *filename);

#endif // __file_util_h__

