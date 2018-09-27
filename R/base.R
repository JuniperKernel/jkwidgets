.newObj <- function(class) {
  stopifnot(!missing(class))
  stopifnot(is.character(class))
  structure(new.env(parent=emptyenv()), class=c(class, "rxraw"))
}
