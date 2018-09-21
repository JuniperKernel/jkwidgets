#ifndef juniper_progress_exports_H
#define juniper_progress_exports_H

#include <juniper/external.h>
#include <jkwidgets/progress.h>
#include <Rcpp.h>

// [[Rcpp::export]]
SEXP make_progress(const std::string& type, double value) {
  if( type.compare("float")==0 ) {
    xw::progress<double>* s = new xw::progress<double>();
    s->display();
    return create_externalptr_xprogress_t<double>(s, progress_finalizer_t<double>, "progress<double>*");
  }
  xw::progress<int>* s = new xw::progress<int>();
  s->display();
  return create_externalptr_xprogress_t<int>(s, progress_finalizer_t<int>, "progress<int>*");
}

// [[Rcpp::export]]
void progress_update_orientation(SEXP s, const std::string& type, const std::string& value) {
  type.compare("float")==0
    ? set_progress_bar_style<double>(s,value)
    : set_progress_bar_style<int>(s, value);
}

// [[Rcpp::export]]
void progress_update_description(SEXP s, const std::string& type, const std::string& value) {
  type.compare("float")==0
    ? set_progress_description<double>(s,value)
    : set_progress_description<int>(s, value);
}

// [[Rcpp::export]]
void progress_update_description_width(SEXP s, const std::string& type, const std::string& value) {
  type.compare("float")==0
    ? set_progress_description_width<double>(s, value)
    : set_progress_description_width<int>(s, value);
}

// [[Rcpp::export]]
void progress_update_bar_color(SEXP s, const std::string& type, const std::string& value) {
  type.compare("float")==0
    ? set_progress_bar_color<double>(s, value)
    : set_progress_bar_color<int>(s, value);
}

// [[Rcpp::export]]
SEXP progress_field(SEXP s, const std::string& type, const std::string& f) {
  return type.compare("float")==0
    ? get_progress_field<double>(s, f)
    : get_progress_field<int>(s, f);
}

#endif // #ifndef juniper_progress_exports_H
