#' Snappy compression and decompression
#'
#' @description
#'   Snappy is a fast compression library written by google
#'   and widely used in distributed systems.
#'
#'   This package provides bindings to the standard snappy
#'   implementation.
#'
#' @details These binding contain the snappy C++ code and necessary
#'   R wrappers, so there is no need to install or link to a snappy
#'   dynamic library (so or dll file) in order to use this package.
#'
#'   Furthermore, these binding work at the level or raw bytes, not
#'   character vectors, which is more robust and should be faster.
#'   Use \code{compress_raw} and \code{decompress_raw} when working
#'   with anything other than text.
#'
#'   \code{compress} and \code{decompress} provide wrappers
#'   around \code{compress_raw} and \code{decompress_raw}
#'   which convert R character vectors into the \code{raw}
#'   type needed by the underlying engine.
#'
#' @param chars
#'   A character vector (of length 1) to compress
#'   with snappy.
#' @param raw
#'   A raw vector (RAWSXP) to compress or decompress
#'   with snappy.
#'
#' @return
#'   \code{compress} returns the raw snappy encoded bytes of
#'      the text input.
#'
#'   \code{compress_raw} returns the raw snappy encoded bytes
#'      of the raw input.
#'
#'   \code{decompress} returns the a character vector made
#'      from the decoded bytes of its input. If this coercion
#'      can't be performed (i.e., the bytes can't be represented
#'      as a string) an error will be thrown.
#'
#'   \code{decompress_raw} returns the a raw bytes decoded from
#'      its input. When passed bytes which are not snappy
#'      compressed, this function will return NULL.
#'
#' @examples
#' library(snappier)
#' # Roundtrip compression of character vector
#' decompress( compress( "this and that" ) ) # "this and that"
#'
#' compress("")                              # 00
#' compress_raw(c())                         # 00
#'
#' decompress_raw(0)                         # raw(0)
#' decompress(0)                             # ""
#'
#' @docType
#'   package
#' @name
#'   snappier
NULL

#' @rdname snappier
#' @export
compress <- function(chars) {
    compress_raw(charToRaw(chars))
}

#' @rdname snappier
#' @useDynLib snappier compress_
#' @export
compress_raw <- function(raw) {
    .Call("compress_", as.raw(raw))
}

#' @rdname snappier
#' @export
decompress <- function(raw) {
    x <- decompress_raw(raw)
    if (is.null(x))
      stop('Error decoding snappy text')
    rawToChar(x)
}

#' @rdname snappier
#' @useDynLib snappier decompress_
#' @export
decompress_raw <- function(raw) {
    .Call("decompress_", as.raw(raw))
}
