#ifndef juniper_juniper_progress_H
#define juniper_juniper_progress_H

#include <xwidgets/xprogress.hpp>
#include <xwidgets/xnumber.hpp>
#include <Rcpp.h>

template<typename T>
SEXP create_externalptr_xprogress_t(xw::progress<T>* p, finalizerT finalizer, const char* pname) {
  SEXP ptr;
  ptr = Rcpp::Shield<SEXP>(R_MakeExternalPtr(reinterpret_cast<void*>(p),Rf_install(pname),R_NilValue));
  R_RegisterCFinalizerEx(ptr, finalizer, TRUE);
  return ptr;
}

template<typename T>
static void progress_finalizer_t(SEXP o) {
  xw::progress<T>* t = reinterpret_cast<xw::progress<T>*>(R_ExternalPtrAddr(o));
  if( t ) {
    delete t;
    R_ClearExternalPtr(o);
  }
}

template<class CTYPE>
xw::progress<CTYPE>* get_progress(SEXP s) {
  return reinterpret_cast<xw::progress<CTYPE>*>(R_ExternalPtrAddr(s));
}

template<class CTYPE>
void set_progress_bar_style(SEXP s, const std::string& value) {
  xw::progress<CTYPE>* progress = get_progress<CTYPE>(s);
  progress->bar_style = value;
}

template<class CTYPE>
void set_progress_orientation(SEXP s, const std::string& value) {
  xw::progress<CTYPE>* progress = get_progress<CTYPE>(s);
  progress->orientation = value;
}

template<class CTYPE>
void set_progress_description(SEXP s, const std::string& value) {
  xw::progress<CTYPE>* progress = get_progress<CTYPE>(s);
  progress->description = value;
}

template<class CTYPE>
void set_progress_description_width(SEXP s, const std::string& value) {
  xw::progress<CTYPE>* progress = get_progress<CTYPE>(s);
  progress->style().description_width = value;
}

template<class CTYPE>
void set_progress_bar_color(SEXP s, const std::string& value) {
  xw::progress<CTYPE>* progress = get_progress<CTYPE>(s);
  progress->style().bar_color = value;
}

template<class CTYPE>
SEXP get_progress_field(SEXP s, const std::string& field) {
  xw::progress<CTYPE>* progress = get_progress<CTYPE>(s);
  if( field.compare("orientation")==0 )       return Rcpp::wrap(progress->orientation());
  if( field.compare("description")==0 )       return Rcpp::wrap(progress->description());
  if( field.compare("description_width")==0 ) return Rcpp::wrap(progress->style().description_width());
  if( field.compare("bar_color")==0 )         return Rcpp::wrap(progress->style().bar_color().value());
  if( field.compare("bar_style")==0 )         return Rcpp::wrap(progress->bar_style());
  return R_NilValue;
}
#endif // #ifndef juniper_juniper_progress_H
