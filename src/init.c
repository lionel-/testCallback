#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

extern SEXP testCallbackReturn(SEXP);
extern SEXP testCallbackJump(SEXP);
extern SEXP testJumpyCallback(SEXP);
extern SEXP testNoCallbacks();

static const R_CallMethodDef CallEntries[] = {
  {"testCallbackJump", (DL_FUNC) &testCallbackJump, 1},
  {"testCallbackReturn", (DL_FUNC) &testCallbackReturn, 1},
  {"testJumpyCallback", (DL_FUNC) &testJumpyCallback, 1},
  {"testNoCallbacks", (DL_FUNC) &testNoCallbacks, 0},
  {NULL, NULL, 0}
};

void R_init_testCallback(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
