#include <iostream>
#include <libguile.h>

using namespace std;

extern "C" void init_humdrum (void *unused)
{
	cerr << "HumDrum importer V0" << endl << endl;
/*	
	scm_c_define_gsubr ("make-jvm", 2, 0, 0, (SCM (*)()) make_jvm);
	scm_c_export ("make-jvm", NULL);
*/
}

extern "C" void scm_init_humdrum_module ()
{
  scm_c_define_module ("humdrum", init_humdrum, NULL);
}

