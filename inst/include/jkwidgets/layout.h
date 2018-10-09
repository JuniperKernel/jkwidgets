#ifndef jkw_layout_exports_H
#define jkw_layout_exports_H

#include <xwidgets/xlayout.hpp>
#include <Rcpp.h>

using getf = std::function<SEXP(xw::layout&)>;
using setf = std::function<void(xw::layout&, const std::string&)>;
using field_map = std::unordered_map<std::string, std::pair<getf, setf>>;

field_map& field_map() {
  static field_map m
    = {{ "align_content",
         std::make_pair([](auto layout) { return Rcpp::wrap(layout.align_content().value())},
                        [](auto layout, auto v) { layout.align_content = v; });
       },
       {"align_items",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.align_items().value())},
                       [](auto layout, auto v) { layout.align_items = v; });
       },
       {"align_self",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.align_self().value())},
                       [](auto layout, auto v) { layout.align_self = v; });
       },
       {"bottom",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"border",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.border().value())},
                       [](auto layout, auto v) { layout.border = v; });
       },
       {"display",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.display().value())},
                       [](auto layout, auto v) { layout.display = v; });
       },
       {"flex",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.flex().value())},
                       [](auto layout, auto v) { layout.flex = v; });
       },
       {"flex_flow",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.flex_flow().value())},
                       [](auto layout, auto v) { layout.flex_flow = v; });
       },
       {"height",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"justify_content",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"left",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"margin",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"max_height",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"max_width",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"min_height",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"min_width",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"overflow",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"overflow_x",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"overflow_y",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"order",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"padding",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"right",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"top",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"visibility",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       },
       {"width",
        std::make_pair([](auto layout) { return Rcpp::wrap(layout.bottom().value())},
                       [](auto layout, auto v) { layout.bottom = v; });
       }};
    return m;
}

std::vector<std::string> layout_fields() {
  std::vector<std::string> fields;
  auto fmap = field_map();
  for(auto const& it: fmap)
    fields.push_back(it.first);
  return fields;
}

SEXP get_layout_field(xw::layout& layout, const std::string& field) {
  auto fmap = field_map();
  auto f = fmap.find(field);
  if( f == fmap.end() )
    return R_NilValue;
  return f->second.first(layout);
}

void set_layout_field(xw::layout& layout, const std::string& field, const std::string& value) {
  auto fmap = field_map();
  auto f = fmap.find(field);
  if( f == fmap.end() )
    Rcpp::stop("Unkown layout field: " + field);
  f->second.second(layout, value);
}

#endif // #ifndef jkw_layout_exports_H
