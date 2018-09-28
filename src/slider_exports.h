#ifndef juniper_slider_exports_H
#define juniper_slider_exports_H

#include <juniper/external.h>
#include <jkwidgets/slider.h>
#include <Rcpp.h>

// [[Rcpp::export]]
SEXP make_slider(const std::string& type, double value) {
	return type.compare("float")==0
		? make_slider_t<double>(value, "slider<double>*")
		: make_slider_t<int>(static_cast<int>(value), "slider<int>*");
}

void slider_value(SEXP s, const std::string& type, SEXP value) {
  type.compare("float")==0
    ? set_slider_value<double>(s, Rcpp::as<double>(value))
    : set_slider_value<int>(s, Rcpp::as<int>(value));
}

#endif // #ifndef juniper_slider_exports_H
