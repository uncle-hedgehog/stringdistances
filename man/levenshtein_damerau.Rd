\encoding{utf-8}
\name{levenshtein_damerau}
\alias{levenshtein_damerau}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Computes the Levenshtein-Damerau distance between strings.
}
\description{
Computes the Levenshtein-Damerau distance between strings.
}
\usage{
levenshtein_damerau(x, y)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
A list of words to compute the Levenshtein-Damerau distance from. Must be of type \code{character}, or convertible to type \code{character} with \code{as.character}.}
  \item{y}{
A list of words to compute the Levenshtein-Damerau distance to. Must be of type \code{character}, or convertible to type \code{character} with \code{as.character}.}
}
\details{
%%  ~~ If necessary, more details than the description above ~~
}
\value{
An integer vector containing Levenshtein-Damerau distances.
}
\author{
Johannes Bubenzer, Emmanuel Keuleers, Kay-Michael Wuerzner
}
\references{
Damerau, F. J. (1964). A technique for computer detection and correction of spelling errors. Commun. ACM, 7:171–176.
Levenshtein, V. I. (1966). Binary codes capable of correcting deletions, insertions, and reversals. Soviet Physics Doklady, 10(1966):707–710.
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\examples{
levenshtein_damerau(c("Test"),c("Tset"))
}
