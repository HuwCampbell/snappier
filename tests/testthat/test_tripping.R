library(hedgehog)

biglist <- function( elements, from = 0, to = 10000 ) {
  gen.with(gen.element(from:to), function(num) {
    gen.map(
      function(vec) { paste(vec, collapse = "")}
    , gen.shrink( shrink.list,
        gen.impure(function(g_size) {
          sample( elements , size = num, replace = T)
        })
      )
    )
  })
}

test_that("compression and decompression are bijective", {
  forall(
      biglist(c(LETTERS, letters, 0:9))
    , function(x) { expect_equal (decompress( compress (x)), x) }
  )

  forall(
      gen.map(as.raw, gen.c(0:255))
    , function(x) { expect_equal (decompress_raw( compress_raw (x)), x) }
  )

  expect_equal("snappy compressed", decompress( compress ("snappy compressed")) )
})
