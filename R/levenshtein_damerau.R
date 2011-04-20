levenshtein_damerau <-
function ( x, y )
{
lx <- length ( x )
ly <- length ( y )
lz <- max ( lx, ly )
z <- integer ( lz )
distances <- .C ( "levenshtein_damerau_R", as.character ( x ), as.character ( y ), lx, ly, z, PACKAGE="stringdistances" )[[5]]
return ( distances )
}

