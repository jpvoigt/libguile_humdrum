#ifndef __hum2ly_h__
#define __hum2ly_h__

#include "humlib.h"

namespace hum {
	
class StateVariables {
	public:
		StateVariables(void) { clear(); }
		~StateVariables() { clear(); }
		void clear();

		HumNum duration;  // duration of last note/rest
		int dots;         // augmentation dots of last note/rest
		int pitch;        // pitch of last note
};

class HumdrumToLilypondConverter {
	public:
		HumdrumToLilypondConverter(void);
		~HumdrumToLilypondConverter() {}

		bool convert          (ostream& out, HumdrumFile& infile);
		bool convert          (ostream& out, const string& input);
		bool convert          (ostream& out, istream& input);
		void setIndent        (const string& indent) { m_indent = indent; }
		void setOptions       (int argc, char** argv);

	protected:
		bool convert          (ostream& out);
		bool convertPart      (ostream& out, const string& partname,
		                       int partindex);
		void extractSegments  (void);
		bool convertSegment   (ostream& out, int partindex, int startline,
		                      int endline);
		void printHeaderComments(ostream& out);
		void printFooterComments(ostream& out);
		bool convertPartSegment(ostream& out, HTp starttoken, int endline);
		bool convertDataToken (ostream& out, HTp token);
		bool convertRest      (ostream& out, HTp token);
		bool convertChord     (ostream& out, HTp token);
		bool convertNote      (ostream& out, HTp token, int index = 0);
		int  printRelativeStartingPitch(ostream& out, int partindex,
		                       int startline, int endline);
		vector<HTp> getStartTokens(int partindex, int startline, int endline);
		int getSegmentStartingPitch(int partindex, int startline, int endline);
		int characterCount    (const string &text, char symbol);
		void convertDuration    (ostream& out, HumNum& duration, int dots);
		void convertDuration    (ostream& out, HumNum& durationnodots,
		                       HumNum& duration, int dots);
		string arabicToRomanNumeral(int arabic, int casetype = 1);
		bool convertInterpretationToken(ostream& out, HTp token);
		void addErrorMessage  (const string& message, HTp token = NULL);
		void printErrorMessages(ostream& out);
		bool convertClef      (ostream& out, HTp token);
		HTp getKeyDesignation (HTp token);
		bool convertKeySignature(ostream& out, HTp token);
		void printHeader      (ostream& tempout);
		void convertArticulations(ostream& out, const string& stok);

	private:
		vector<HTp>     m_kernstarts;
		vector<int>     m_rkern;
		vector<int>     m_segments;
		vector<string>  m_labels;
		HumdrumFile     m_infile;
		string          m_indent;
		stringstream    m_staffout;
		stringstream    m_scoreout;
		StateVariables  m_states;
		Options         m_options;
		vector<string>  m_errors;
};

} // namespace hum

#endif
