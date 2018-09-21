.newObj <- function(class) {
  stopifnot(!missing(class))
  stopifnot(is.character(class))
  structure(new.env(parent=emptyenv()), class=c(class, "rxraw"))
}

#  object helpers
# `[<-.rxraw` <- function(data,row,col,...,value) .noimp(data, "[<-")
# `$<-.rxraw` <- function(data, name, value) .noimp(data, "$<-")
# `[.rxraw` <- function(data,row,col,...,value) .noimp(data, "[")
# `$.rxraw` <- function(data, name, value) .noimp(data, "$")
#
# .noimp <- function(o, m) stop(paste0("No ", m, " method for jkwidgets objects of type ", oldClass(o)[1]))
