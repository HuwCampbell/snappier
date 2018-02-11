Snappier
========

[![Build Status](https://travis-ci.org/HuwCampbell/snappier.svg?branch=master)](https://travis-ci.org/HuwCampbell/snappier)
[![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/snappier)](https://cran.r-project.org/package=snappier)

> R package bindings for the Snappy library.

This library provides compressions and decompression
of Snappy bytestrings in R.

### Benefits
* Snappy C/C++ code is embedded in the library, so external
  dependencies are not required.
* Use or RAWSXP underneath prevents runtime errors
* Direct access to R's internal data structures is given to the
  Snappy library, so it's about as efficient as it can be.
* Round trip tests with hedgehog provide good assurances
  for correctness.

### Basic Usage
```r
# Compress a character vector
comp <- compress("this text will be compressed")
decompress(comp)
```

```
## [1] "this text will be compressed"
```
