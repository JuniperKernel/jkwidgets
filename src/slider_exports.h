#ifndef juniper_slider_exports_H
#define juniper_slider_exports_H

#include <juniper/external.h>
#include <jkwidgets/slider.h>
#include <Rcpp.h>

// [[Rcpp::export]]
SEXP make_slider(const std::string& type, double value) {
  if( type.compare("float")==0 ) {
    xw::slider<double>* s = make_slider_t<double>(value);
    s->display();
    return create_externalptr_xslider_t<double>(s, slider_finalizer_t<double>, "slider<double>*");
  }
  xw::slider<int>* s = make_slider_t<int>(static_cast<int>(value));
  s->display();
  return create_externalptr_xslider_t<int>(s, slider_finalizer_t<int>, "slider<int>*");
}

void slider_value(SEXP s, const std::string& type, SEXP value) {
  type.compare("float")==0
    ? set_slider_value<double>(s, Rcpp::as<double>(value))
    : set_slider_value<int>(s, Rcpp::as<int>(value));
}

#endif // #ifndef juniper_slider_exports_H
