
#include <juniper/xbridge.h>
#include <Rcpp.h>
#include <slider_exports.h>
#include <jkwidgets/layout.h>

// init static vars now
std::atomic<long long> JMessage::_ctr{0};
xmock* _xm;

// [[Rcpp::export]]
void init_xmock(SEXP xm) {
  _xm = reinterpret_cast<xmock*>(R_ExternalPtrAddr(xm));
}


// [[Rcpp::export}]
std::vector<std::string> get_layout_fields() { return layout_fields(); }
