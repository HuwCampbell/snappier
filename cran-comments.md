## Test environments
* local OS X install, R 3.3.1
* Centos
* Travis

## R CMD check results

0 errors | 0 warnings | 0 note

* This is a new release.

* It provides bindings to Google's Snappy compression
  algorithm, but inlines its source code such that one
  doesn't need to `brew install` or the like.

* There are no required dependencies.

## Reverse dependencies

This is a new release, so there are no reverse dependencies.

---

* I have run R CMD check and found no issues with the package.

* I have unit and property tests for the package using hedgehog
  and testthat.

* My property tests are written in hedgehog, which is my R port
  of the Haskell library (https://github.com/hedgehogqa/r-hedgehog).
  I haven't released it yet, as I'm trying to thrash on the API
  before a solid CRAN release.

* The only significant c code I have written is in
  *src/r-snappy-binding.c*, I'm not sure about the level in which
  CRAN volunteers like to review the code of packages, but if
  you're keen to, that's the place.
