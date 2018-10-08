#ifndef juniper_slider_exports_H
#define juniper_slider_exports_H

#include <juniper/external.h>
#include <jkwidgets/utils.h>
#include <xwidgets/xslider.hpp>
#include <Rcpp.h>

template<class T>
SEXP make_slider_t(T value, const char* pname) {
  xw::slider<T>* s = new xw::slider<T>();
  s->value = value;
	s->display();
  return make_xptr<xw::slider<T>>(s, pname);
}

template<class CTYPE>
using getf = std::function<SEXP(xw::slider<CTYPE>*)>;

template<class CTYPE>
using setf = std::function<void(xw::slider<CTYPE>*, SEXP)>;

template<class T>
using field_map = std::unordered_map<std::string, std::pair<getf<T>, setf<T>>>;

template<class CTYPE>
field_map<CTYPE> make_field_map() {
  field_map<CTYPE> fields;

  fields["value"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->value());},
        [](auto *slider, SEXP value) { slider->value = Rcpp::as<CTYPE>(value); });
  fields["step"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->step()); },
        [](auto *slider, SEXP value) { slider->step = Rcpp::as<int>(value); }); 
  fields["orientation"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->orientation()); },
        [](auto *slider, SEXP value) { slider->orientation = Rcpp::as<std::string>(value); });
  fields["readout"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->readout()); },
        [](auto *slider, SEXP value) { slider->readout = Rcpp::as<bool>(value); });
  fields["readout_format"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->readout_format()); },
        [](auto *slider, SEXP value) { slider->readout_format = Rcpp::as<std::string>(value); });
  fields["continuous_update"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->continuous_update()); },
        [](auto *slider, SEXP value) { slider->continuous_update = Rcpp::as<bool>(value); });
  fields["disabled"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->disabled()); },
        [](auto *slider, SEXP value) { slider->disabled = Rcpp::as<bool>(value); });

  // xnumber props
  fields["min"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->min()); },
        [](auto *slider, SEXP value) { slider->min = Rcpp::as<CTYPE>(value); });
  fields["max"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->max()); },
        [](auto *slider, SEXP value) { slider->max = Rcpp::as<CTYPE>(value); });
  fields["description"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->description()); },
        [](auto *slider, SEXP value) { slider->description = Rcpp::as<std::string>(value); });

  // xslider styles
  fields["description_width"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->style().description_width()); },
        [](auto *slider, SEXP value) { slider->style().description_width = Rcpp::as<std::string>(value); });
  fields["handle_color"]
    = std::make_pair(
        [](auto *slider) { return Rcpp::wrap(slider->style().handle_color().value()); },
        [](auto *slider, SEXP value) { slider->style().handle_color = Rcpp::as<std::string>(value); });
  return fields;
}

template<class CTYPE>
field_map<CTYPE>& get_fmap() {
  static field_map<CTYPE> fmap(make_field_map<CTYPE>());
  return fmap;
}

template<class CTYPE>
SEXP get_field(SEXP s, const std::string& field) {
  const field_map<CTYPE>& fmap = get_fmap<CTYPE>();
  xw::slider<CTYPE>* slider = xptr<xw::slider<CTYPE>>(s);
  auto f = fmap.find(field);
  if( f == fmap.end() )
    return R_NilValue;

  return f->second.first(slider);
}

template<class CTYPE>
void set_field(SEXP s, const std::string& field, SEXP value) {
  if( field=="layout" )
    Rcpp::stop("Update layout fields individually.");

  xw::slider<CTYPE>* slider = xptr<xw::slider<CTYPE>>(s);
  const field_map<CTYPE>& fmap = get_fmap<CTYPE>();
  auto f = fmap.find(field);
  if( f == fmap.end() )
    Rcpp::stop("Unkown slider field: " + field);

  f->second.second(slider, value);
}

bool assert_type(const std::string& type) {
  bool isFloat = type == "float";
  bool isInt   = type == "int";
  if( !(isFloat||isInt) )
    Rcpp::stop("Type must be 'float' or 'int'. Got: <" + type + ">");
  return isFloat;
}

// [[Rcpp::export]]
SEXP make_slider(const std::string& type, double value) {
  return assert_type(type)
		? make_slider_t<double>(value, "slider<double>*")
		: make_slider_t<int   >(static_cast<int>(value), "slider<int>*");
}

// [[Rcpp::export]]
std::vector<std::string> slider_fields() {
  std::vector<std::string> fields;
  auto fmap = get_fmap<int>();
  for(auto const& it: fmap)
    fields.push_back(it.first);
  return fields;
}

// [[Rcpp::export]]
SEXP get_slider_field(SEXP s, const std::string& type, const std::string& field) {
  return assert_type(type)
    ? get_field<double>(s, field)
    : get_field<int   >(s, field);
}

// [[Rcpp::export]]
void set_slider_field(SEXP s, const std::string& type, const std::string& field, SEXP value) {
  assert_type(type)
    ? set_field<double>(s, field, value)
    : set_field<int   >(s, field, value);
}

#endif // #ifndef juniper_slider_exports_H
