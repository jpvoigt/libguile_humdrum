#include <iostream>
#include <libguile.h>
#include "hum2ly.h"

using namespace std;

extern "C" SCM convert_HumdrumFile(hum::HumdrumFile& infile) {
	hum::HumdrumToLilypondConverter converter;
	// converter.setOptions(argc, argv);
	stringstream out;
	bool status = converter.convert(out, infile);
	if (status) {
		// cout << out.str();
		return scm_from_locale_string(out.str().c_str());
	}
	return SCM_UNSPECIFIED;
}

extern "C" SCM convert_humdrum_file(SCM scm_humfile) {
	hum::Options options;
	options.define("v|version=s:2.18.2", "lilypond version");
	// options.process(argc, argv);

	char* humfile = scm_to_locale_string(scm_humfile);
	cerr << "convert '" << humfile << "' ..." << endl;
	
	hum::HumdrumFile infile(humfile);
	
	return convert_HumdrumFile(infile);
}

extern "C" SCM convert_humdrum(SCM scm_humstr) {
	hum::Options options;
	options.define("v|version=s:2.18.2", "lilypond version");
	// options.process(argc, argv);

	char* humstr = scm_to_locale_string(scm_humstr);
	stringstream cin(humstr);
	
	cerr << "convert string ..." << endl; // << humstr << endl;
	
	hum::HumdrumFile infile;
	infile.read( cin );

	return convert_HumdrumFile(infile);
}

extern "C" void init_humdrum (void *unused)
{
	cerr << "HumDrum importer V0" << endl << endl;
	scm_c_define_gsubr ("convert-humdrum", 1, 0, 0, (SCM (*)()) convert_humdrum);
	scm_c_export ("convert-humdrum", NULL);
	scm_c_define_gsubr ("convert-humdrum-file", 1, 0, 0, (SCM (*)()) convert_humdrum_file);
	scm_c_export ("convert-humdrum-file", NULL);
}

extern "C" void scm_init_humdrum_module ()
{
  scm_c_define_module ("humdrum", init_humdrum, NULL);
}

