(define-module (humdrum))
(use-modules (lily))

; on mac load libguile_humdrum.dylib (on win .dll)
(let ((libguile_humdrum.so (%search-load-path "libguile_humdrum.so")))
  (ly:message "load-extension \"~A\" ... " libguile_humdrum.so)
  (load-extension libguile_humdrum.so "scm_init_humdrum_module")
  )

(define-public convertHumdrum
  (define-void-function (sym file)(symbol? string?)
    (ly:parser-define! sym
      `((description . "To be done")
        (file . ,file)
        (lily . ,(convert-humdrum sym (ly:gulp-file file)))))
    ))
