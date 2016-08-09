#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <libguile.h>

#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif

extern "C" void init_humdrum (void *unused)
{
	puts("HumDrum importer V0");
}

extern "C" void scm_init_humdrum_module ()
{
  scm_c_define_module ("humdrum", init_humdrum, NULL);
}

