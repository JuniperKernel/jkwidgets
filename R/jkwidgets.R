#' jkwidgets: Widgets for JuniperKernel
#'
#' @docType package
#' @name jkwidgets
NULL

# global package environment
.JKWIDGETS <- new.env(parent=emptyenv())

.xmock <- function() {
  tryCatch(.JKWIDGETS$xmock <- JuniperKernel::the_xmock(), error=function(e){})
}

.init <- function() {
  init_xmock(.xmock())
}