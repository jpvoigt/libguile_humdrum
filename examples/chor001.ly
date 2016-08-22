\version "2.19.47"
\include "../humdrum.ily"

\convertHumdrum mysong "chor001.krn"


#(ly:parser-include-string (assoc-get 'lily mysong))

#(ly:message "~A" (assoc-get 'lily mysong))
