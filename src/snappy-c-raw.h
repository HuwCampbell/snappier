//
// This file is not part of snappy. It it only part of the R
// package so we can easily call the raw bindings.
//

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void snappy_raw_compress(const char* input,
                         size_t input_length,
                         char* compressed,
                         size_t *compressed_length);

int snappy_raw_uncompress(const char* compressed,
                                    size_t compressed_length,
                                    char* uncompressed);



#ifdef __cplusplus
}  // extern "C"
#endif
