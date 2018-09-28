.onAttach <- function(lib, pkg) {}
.onLoad   <- function(lib, pkg) { .xmock() }

.xmock <- function() {
  tryCatch(.JKWIDGETS$xmock <- JuniperKernel::xmock(), error=function(e){})
	init_xmock(.JKWIDGETS$xmock)
}
