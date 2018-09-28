.onAttach <- function(lib, pkg) {}
.onLoad   <- function(lib, pkg) { init_xmock(.JKWIDGETS$xmock <- JuniperKernel::xmock())  }
