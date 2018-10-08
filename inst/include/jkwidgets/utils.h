#ifndef jkw_utils_H
#define jkw_utils_H

#include <Rcpp.h>

template <class X>
static void make_finalizer(SEXP o) {
	X* t = reinterpret_cast<X*>(R_ExternalPtrAddr(o));
  if( t ) {
    delete t;
    R_ClearExternalPtr(o);
  }
}

template <class X>
SEXP make_xptr(X* p, const char* pname) {
  SEXP ptr;
  ptr = Rcpp::Shield<SEXP>(R_MakeExternalPtr(reinterpret_cast<void*>(p),Rf_install(pname),R_NilValue));
  R_RegisterCFinalizerEx(ptr, make_finalizer<X>, TRUE);
  return ptr;
}

template <class X>
X* xptr(SEXP o) {
  return reinterpret_cast<X*>(R_ExternalPtrAddr(o));
}

#endif // #ifndef jkw_utils_H
