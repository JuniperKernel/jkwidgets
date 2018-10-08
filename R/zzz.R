.onAttach <- function(lib, pkg) {}
.onLoad   <- function(lib, pkg) {
  xm <- tryCatch(
    JuniperKernel::xmock(),
    error = function(e) {
      if( e$message == "no xmock available." )
        NULL
      else
        stop(e$message)
     })
  if( !is.null(xm) )
    init_xmock(.JKWIDGETS$xmock <- xm)
}
