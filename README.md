Snappier
========

> R package bindings for the Snappy library.

This library provides compressions and decompression
of Snappy bytestrings in R.

Benefits
* Snappy C/C++ code is embedded in the library, so external
  dependencies are not required.
* Use or RAWSXP underneath prevents runtime errors which
  can occur with other R bindings when attempting to place
  invalid unicode into a STRSXP.
* Direct access to R's internal data structures is given to the
  Snappy library, so it's about as efficient as it can be.
* Round trip tests with hedgehog provide good assurances
  for correctness.
