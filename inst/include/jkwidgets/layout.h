#ifndef jkw_layout_exports_H
#define jkw_layout_exports_H

#include <xwidgets/xlayout.hpp>
#include <Rcpp.h>


std::vector<std::string> layout_fields() {
  return
    std::vector<std::string> {
      "align_content"  ,
      "align_items"    ,
      "align_self"     ,
      "bottom"         ,
      "border"         ,
      "display"        ,
      "flex"           ,
      "flex_flow"      ,
      "height"         ,
      "justify_content",
      "left"           ,
      "margin"         ,
      "max_height"     ,
      "max_width"      ,
      "min_height"     ,
      "min_width"      ,
      "overflow"       ,
      "overflow_x"     ,
      "overflow_y"     ,
      "order"          ,
      "padding"        ,
      "right"          ,
      "top"            ,
      "visibility"     ,
      "width"
        };
}

std::string get_layout_field(xw::layout& layout, const std::string& field) {
  if( field=="align_content"  ) return layout.align_content().value();
  if( field=="align_items"    ) return layout.align_items().value();
  if( field=="align_self"     ) return layout.align_self().value();
  if( field=="bottom"         ) return layout.bottom().value();
  if( field=="border"         ) return layout.border().value();
  if( field=="display"        ) return layout.display().value();
  if( field=="flex"           ) return layout.flex().value();
  if( field=="flex_flow"      ) return layout.flex_flow().value();
  if( field=="height"         ) return layout.height().value();
  if( field=="justify_content") return layout.justify_content().value();
  if( field=="left"           ) return layout.left().value();
  if( field=="margin"         ) return layout.margin().value();
  if( field=="max_height"     ) return layout.max_height().value();
  if( field=="max_width"      ) return layout.max_width().value();
  if( field=="min_height"     ) return layout.min_height().value();
  if( field=="min_width"      ) return layout.min_width().value();
  if( field=="overflow"       ) return layout.overflow().value();
  if( field=="overflow_x"     ) return layout.overflow_x().value();
  if( field=="overflow_y"     ) return layout.overflow_y().value();
  if( field=="order"          ) return layout.order().value();
  if( field=="padding"        ) return layout.padding().value();
  if( field=="right"          ) return layout.right().value();
  if( field=="top"            ) return layout.top().value();
  if( field=="visibility"     ) return layout.visibility().value();
  if( field=="width"          ) return layout.width().value();

  Rcpp::stop("Unkown layout field: " + field);
}

void set_layout_field(xw::layout& layout, const std::string& field, const std::string& value) {
  if( field=="align_content"  ) layout.align_content = value;
  if( field=="align_items"    ) layout.align_items = value;
  if( field=="align_self"     ) layout.align_self = value;
  if( field=="bottom"         ) layout.bottom = value;
  if( field=="border"         ) layout.border = value;
  if( field=="display"        ) layout.display = value;
  if( field=="flex"           ) layout.flex = value;
  if( field=="flex_flow"      ) layout.flex_flow = value;
  if( field=="height"         ) layout.height = value;
  if( field=="justify_content") layout.justify_content = value;
  if( field=="left"           ) layout.left = value;
  if( field=="margin"         ) layout.margin = value;
  if( field=="max_height"     ) layout.max_height = value;
  if( field=="max_width"      ) layout.max_width = value;
  if( field=="min_height"     ) layout.min_height = value;
  if( field=="min_width"      ) layout.min_width = value;
  if( field=="overflow"       ) layout.overflow = value;
  if( field=="overflow_x"     ) layout.overflow_x = value;
  if( field=="overflow_y"     ) layout.overflow_y = value;
  if( field=="order"          ) layout.order = value;
  if( field=="padding"        ) layout.padding = value;
  if( field=="right"          ) layout.right = value;
  if( field=="top"            ) layout.top = value;
  if( field=="visibility"     ) layout.visibility = value;
  if( field=="width"          ) layout.width = value;

  Rcpp::stop("Unkown layout field: " + field);
}

#endif // #ifndef juniper_slider_exports_H
