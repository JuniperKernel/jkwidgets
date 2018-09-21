#ifndef juniper_juniper_slider_H
#define juniper_juniper_slider_H

#include <xwidgets/xslider.hpp>
#include <xwidgets/xnumber.hpp>
#include <Rcpp.h>

template<typename T>
SEXP create_externalptr_xslider_t(xw::slider<T>* p, finalizerT finalizer, const char* pname) {
  SEXP ptr;
  ptr = Rcpp::Shield<SEXP>(R_MakeExternalPtr(reinterpret_cast<void*>(p),Rf_install(pname),R_NilValue));
  R_RegisterCFinalizerEx(ptr, finalizer, TRUE);
  return ptr;
}

template<typename T>
static void slider_finalizer_t(SEXP o) {
  xw::slider<T>* t = reinterpret_cast<xw::slider<T>*>(R_ExternalPtrAddr(o));
  if( t ) {
    delete t;
    R_ClearExternalPtr(o);
  }
}

template<typename T>
xw::slider<T>* make_slider_t(T value) {
  xw::slider<T>* s = new xw::slider<T>();
  s->value = value;
  return s;
}

template<class CTYPE>
xw::slider<CTYPE>* get_slider(SEXP s) {
  return reinterpret_cast<xw::slider<CTYPE>*>(R_ExternalPtrAddr(s));
}

template<class CTYPE>
void set_slider_value(SEXP s, CTYPE value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->value = value;
}

template<class CTYPE>
void set_slider_max(SEXP s, CTYPE value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->max = value;
}

template<class CTYPE>
void set_slider_orientation(SEXP s, const std::string& value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->orientation = value;
}

template<class CTYPE>
void set_slider_description(SEXP s, const std::string& value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->description = value;
}

template<class CTYPE>
void set_slider_description_width(SEXP s, const std::string& value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->style().description_width = value;
}

template<class CTYPE>
void set_slider_handle_color(SEXP s, const std::string& value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->style().handle_color = value;
}

template<class CTYPE>
void set_slider_disabled(SEXP s, bool value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->disabled = value;
}

template<class CTYPE>
void set_slider_min(SEXP s, CTYPE value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->min = value;
}

template<class CTYPE>
void set_slider_step(SEXP s, CTYPE value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->step = value;
}

template<class CTYPE>
void set_slider_continuous_update(SEXP s, bool value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->continuous_update = value;
}

template<class CTYPE>
void set_slider_readout_format(SEXP s, const std::string& value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->readout_format = value;
}

template<class CTYPE>
void set_slider_readout(SEXP s, bool value) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  slider->readout = value;
}

template<class CTYPE>
SEXP get_slider_field(SEXP s, const std::string& field) {
  xw::slider<CTYPE>* slider = get_slider<CTYPE>(s);
  if( field.compare("value")==0 )             return Rcpp::wrap(slider->value());
  if( field.compare("max")==0 )               return Rcpp::wrap(slider->max());
  if( field.compare("min")==0 )               return Rcpp::wrap(slider->min());
  if( field.compare("orientation")==0 )       return Rcpp::wrap(slider->orientation());
  if( field.compare("description")==0 )       return Rcpp::wrap(slider->description());
  if( field.compare("description_width")==0 ) return Rcpp::wrap(slider->style().description_width());
  if( field.compare("handle_color")==0 )      return Rcpp::wrap(slider->style().handle_color().value());
  if( field.compare("disabled")==0 )          return Rcpp::wrap(slider->disabled());
  if( field.compare("step")==0 )              return Rcpp::wrap(slider->step());
  if( field.compare("continuous_update")==0 ) return Rcpp::wrap(slider->continuous_update());
  if( field.compare("format")==0 )            return Rcpp::wrap(slider->readout_format());
  if( field.compare("readout")==0 )           return Rcpp::wrap(slider->readout());
  return R_NilValue;
}
#endif // #ifndef juniper_juniper_slider_H
