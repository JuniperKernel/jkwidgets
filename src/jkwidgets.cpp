
#include <juniper/xbridge.h>
#include <slider_exports.h>
#include <Rcpp.h>

// init static vars now
std::atomic<long long> JMessage::_ctr{0};
xmock* _xm;
// [[Rcpp::export]]
void init_xmock(SEXP xm) {
  _xm = reinterpret_cast<xmock*>(R_ExternalPtrAddr(xm));
}

// [[Rcpp::export]]
void update_widget(const std::string& widget_type, const std::string& field, SEXP widget, const std::string& type, SEXP value) {
//  if( widget_type.compare("slider")==0  ) { slider_update(field, widget, type, value); return; }
//  std::stringstream ss;
//  ss << "Unknown widget type: " << widget_type << std::endl;
//  throw std::runtime_error(ss.str());
}
