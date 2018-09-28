#ifndef juniper_juniper_slider_H
#define juniper_juniper_slider_H

#include <xwidgets/xmaterialize.hpp>
#include <xwidgets/xslider.hpp>
#include <xwidgets/xnumber.hpp>
#include <Rcpp.h>

template <class T>
SEXP create_externalptr_xslider_t(xw::slider<T>* p, finalizerT finalizer, const char* pname) {
  SEXP ptr;
  ptr = Rcpp::Shield<SEXP>(R_MakeExternalPtr(reinterpret_cast<void*>(p),Rf_install(pname),R_NilValue));
  R_RegisterCFinalizerEx(ptr, finalizer, TRUE);
  return ptr;
}

template <class T>
static void slider_finalizer_t(SEXP o) {
	xw::slider<T>* t = reinterpret_cast<xw::slider<T>*>(R_ExternalPtrAddr(o));
  if( t ) {
    delete t;
    R_ClearExternalPtr(o);
  }
}

template<typename T>
SEXP make_slider_t(T value,  const char* pname) {
  xw::slider<T>* s = new xw::slider<T>();
  s->value = value;
	s->display();
  return create_externalptr_xslider_t<T>(s, slider_finalizer_t<T>, pname);
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

#endif // #ifndef juniper_juniper_slider_H
