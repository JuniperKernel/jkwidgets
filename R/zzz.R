.onAttach <- function(lib, pkg) {}
.onLoad   <- function(lib, pkg) { init_xmock(.xmock()) }

.xmock <- function() {
  tryCatch(.JKWIDGETS$xmock <- JuniperKernel::the_xmock(), error=function(e){})
}
