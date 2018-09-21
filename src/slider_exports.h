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

void slider_max(SEXP s, const std::string& type, SEXP value) {
  type.compare("float")==0
    ? set_slider_max<double>(s, Rcpp::as<double>(value))
    : set_slider_max<int>(s, Rcpp::as<int>(value));
}

void slider_orientation(SEXP s, const std::string& type, const std::string& value) {
  type.compare("float")==0
    ? set_slider_orientation<double>(s,value)
    : set_slider_orientation<int>(s, value);
}

void slider_description(SEXP s, const std::string& type, const std::string& value) {
  type.compare("float")==0
    ? set_slider_description<double>(s,value)
    : set_slider_description<int>(s, value);
}

void slider_description_width(SEXP s, const std::string& type, const std::string& value) {
  type.compare("float")==0
    ? set_slider_description_width<double>(s, value)
    : set_slider_description_width<int>(s, value);
}

void slider_handle_color(SEXP s, const std::string& type, const std::string& value) {
  type.compare("float")==0
    ? set_slider_handle_color<double>(s, value)
    : set_slider_handle_color<int>(s, value);
}

void slider_disabled(SEXP s, const std::string& type, bool value) {
  type.compare("float")==0
    ? set_slider_disabled<double>(s, value)
    : set_slider_disabled<int>(s, value);
}

void slider_min(SEXP s, const std::string& type, SEXP value) {
  type.compare("float")==0
    ? set_slider_min<double>(s, Rcpp::as<double>(value))
    : set_slider_min<int>(s, Rcpp::as<int>(value));
}

void slider_step(SEXP s, const std::string& type, SEXP value) {
  type.compare("float")==0
    ? set_slider_step<double>(s, Rcpp::as<double>(value))
    : set_slider_step<int>(s, Rcpp::as<int>(value));
}

void slider_continuous_update(SEXP s, const std::string& type, bool value) {
  type.compare("float")==0
    ? set_slider_continuous_update<double>(s, value)
    : set_slider_continuous_update<int>(s, value);
}

void slider_readout_format(SEXP s, const std::string& type, const std::string& value) {
  type.compare("float")==0
    ? set_slider_readout_format<double>(s, value)
    : set_slider_readout_format<int>(s, value);
}

void slider_readout(SEXP s, const std::string& type, bool value) {
  type.compare("float")==0
    ? set_slider_readout<double>(s, value)
    : set_slider_readout<int>(s, value);
}

//[[Rcpp::export]]
SEXP slider_field(SEXP s, const std::string& type, const std::string& f) {
  return type.compare("float")==0
    ? get_slider_field<double>(s, f)
    : get_slider_field<int>(s, f);
}

void slider_update(const std::string& field, SEXP widget, const std::string& type, SEXP value) {
  if( field.compare("value")==0 )      { slider_value(widget, type, value); return; }
  if( field.compare("max")==0   )      { slider_max(widget, type, value); return;   }
  if( field.compare("orientation")==0) { slider_orientation(widget, type, Rcpp::as<std::string>(value)); return; }
  if( field.compare("description")==0) { slider_description(widget, type, Rcpp::as<std::string>(value)); return; }
  if( field.compare("description_width")==0 ) { slider_description_width(widget, type, Rcpp::as<std::string>(value)); return; }
  if( field.compare("handle_color")==0 ) { slider_handle_color(widget, type, Rcpp::as<std::string>(value)); return; }
  if( field.compare("disabled")==0 ) { slider_disabled(widget, type, Rcpp::as<bool>(value)); return; }
  if( field.compare("min")==0 ) { slider_min(widget, type, value); return; }
  if( field.compare("step")==0 ){ slider_step(widget, type, value); return; }
  if( field.compare("continuous_update")==0 ) { slider_continuous_update(widget, type, Rcpp::as<bool>(value)); return; }
  if( field.compare("format")==0 ) { slider_readout_format(widget, type, Rcpp::as<std::string>(value)); return; }
  if( field.compare("readout")==0 ) { slider_readout(widget, type, Rcpp::as<bool>(value)); return; }

  std::stringstream ss;
  ss << "Invalid field: " << field << std::endl;
  throw std::runtime_error(ss.str());
}


#endif // #ifndef juniper_slider_exports_H
