\encoding{utf-8}
\name{stringdistances-package}
\alias{stringdistances-package}
\alias{stringdistances}
\docType{package}
\title{
Provides various distance metrics for strings.
}
\description{
This package provides metrics to compute the distance between two strings.
}
\details{
\tabular{ll}{
Package: \tab stringdistances\cr
Type: \tab Package\cr
Version: \tab 0.1\cr
Date: \tab 2011-04-08\cr
License: \tab BSD\cr
LazyLoad: \tab yes\cr
}
The different functions in this package compute metrics for the distance between to strings.
}
\author{
Johannes Bubenzer, Emmanuel Keuleers, Kay-Michael Wuerzner
}
\references{
Damerau, F. J. (1964). A technique for computer detection and correction of spelling errors. Commun. ACM, 7:171–176.
Levenshtein, V. I. (1966). Binary codes capable of correcting deletions, insertions, and reversals. Soviet Physics Doklady, 10(1966):707–710.
}
\examples{
levenshtein_damerau(c("Test"),c("Tset"))
}
