.First.lib <- function(lib,pkg)
{
   library.dynam("stringdistances",pkg,lib)
   cat("stringdistances library\n")
}
