#include <R.h>
#include <Rdefines.h>

#include "snappy-c.h"
#include "snappy-c-raw.h"

SEXP compress_(SEXP x) {
    // PROTECT the input variable.
    // It should already be RAWSXP,
    // but if it's not, the coercion should yield
    // an error before the protection happens,
    // and we'll exit gracefully.
    PROTECT(x = AS_RAW(x));

    // Find the length of the RAW vector using
    // R's length function.
    const size_t slen = length(x);

    // Find out the maximum length which snappy could
    // write out for this length bytestring.
    size_t dlenMax = snappy_max_compressed_length(slen);
    size_t dlen = 0;

    // Create a RAWSXP for the output. We
    // are allocating as much as we need
    // (the max length), but we don't yet
    // know how much it will actually occupy
    SEXP result = PROTECT(allocVector(RAWSXP, (R_xlen_t) dlenMax));

    // Run the snappy raw compression algorithm
    // writing directly into the RAW result buffer.
    snappy_raw_compress((const char*) RAW(x), slen, (char*) RAW(result), &dlen);

    // Set the length of the RAWSXP to the amount
    // which was actually written, rather than the
    // max it could have been.
    SETLENGTH(result, dlen);

    // UNPROTECT the input and result.
    UNPROTECT(2);
    return(result);
}

SEXP decompress_(SEXP x) {
    // PROTECT the input variable.
    // It should already be RAWSXP,
    // but if it's not, the coercion should yield
    // an error before the protection happens,
    // and we'll exit gracefully.
    PROTECT(x = AS_RAW(x));

    // Find the length of the RAW vector using
    // R's length function.
    const size_t slen = length(x);

    // Find the length of the bytestring which
    // snappy will return.
    size_t dlen = 0;
    if (SNAPPY_OK != snappy_uncompressed_length((const char*) RAW(x), slen, &dlen))
        goto fail;

    // Allocate a RAWSXP of the output size for
    // snappy to write into.
    SEXP result = PROTECT(allocVector(RAWSXP, (R_xlen_t) dlen));

    // Decompress the data into the result buffer
    // using the raw snappy bindings.
    if (SNAPPY_OK != snappy_raw_uncompress((const char*) RAW(x), slen, (char*) RAW(result)))
        goto fail2;

    // UNPROTECT the input and result and return.
    UNPROTECT(2);
    return result;

  // Error handling, protection is a stack, so
  // this is just whether we have protected
  // 1 or 2 values at the time or failure
  // before we return an R NULL value.
  fail2:
    UNPROTECT(1);

  fail:
    UNPROTECT(1);
    return R_NilValue;
}
