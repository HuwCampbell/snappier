#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP compress_(SEXP);
extern SEXP decompress_(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"compress_",          (DL_FUNC) &compress_,         1},
    {"decompress_",        (DL_FUNC) &decompress_,       1},
    {NULL, NULL, 0}
};

void R_init_snappier(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
