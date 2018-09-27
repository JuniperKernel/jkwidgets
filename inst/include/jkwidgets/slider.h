#ifndef juniper_juniper_slider_H
#define juniper_juniper_slider_H

#include <xwidgets/xmaterialize.hpp>
#include <xwidgets/xslider.hpp>
#include <xwidgets/xnumber.hpp>
#include <Rcpp.h>

template<class B, class P...>
SEXP create_externalptr_xslider_t(xw::xmaterialize<class B, class P...>* p, finalizerT finalizer, const char* pname) {
  SEXP ptr;
  ptr = Rcpp::Shield<SEXP>(R_MakeExternalPtr(reinterpret_cast<void*>(p),Rf_install(pname),R_NilValue));
  R_RegisterCFinalizerEx(ptr, finalizer, TRUE);
  return ptr;
}

template<class B, class P...>
static void slider_finalizer_t(SEXP o) {
	xw::xmaterialize<class B, class P...>* t = reinterpret_cast<xw::xmaterialize<class B, class P...>*>(R_ExternalPtrAddr(o));
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

#endif // #ifndef juniper_juniper_slider_H
