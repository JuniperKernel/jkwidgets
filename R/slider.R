#' 'Jupyter' Slider Widget
#' @title 'Jupyter' Slider Widget
#' @param type
#'   Either 'int' or 'float'. This argument specifies the numeric
#'   type of the slider.
#' @param value
#'   A numeric value that can be coerced to the \code{type} specified.
#' @examples
#' \dontrun{
#'    slider <- xslider(type='int', value=50)
#' }
#'
#' @export
xslider <- function(type = c('int', 'float'), value = 20) {
  type <- match.arg(type)
  stopifnot(type %in% c('int', 'float'))
  stopifnot(is(value, "numeric"))
  if( type=='int' )
    stopifnot(value == as.integer(value))
  x <- .newObj('xslider')
  attr(x, 'type') <- type
  attr(x, 'ptr') <- make_slider(type, value)

  # get field names...
  slider_fields <- get_slider_fields()
  for( f in slider_fields )
      assign(f, '', x)

  layout <- .newObj('xlayout')
  layout_fields <- get_layout_fields()
  for( f in layout_fields )
      assign(f, '', layout)
  assign('layout', layout, x)
  x
}


#' Print Method for Jupyter Slider
#' @title Print Method for Jupyter Slider
#' @param x
#'   Object of type \code{xslider}.
#' @param ...
#'   Ignored.
#' @examples
#' \dontrun{
#'    slider <- xslider(type='int', value=50)
#'    slider
#' }
#'
#' @export
print.xslider <- function(x, ...) {
  cat("A Jupyter Slider Widget\n")
  cat("type: ", x$type, "\n")
  cat("value: ", x$value, "\n")
  cat("max: ", x$max, "\n")
  cat("min: ", x$min, "\n")
  cat("orientation: ", x$orientation, "\n")
  cat("description: ", x$description, "\n")
  cat("disabled: ", x$disabled, "\n")
  cat("step: ", x$step, "\n")
  cat("continuous_update: ", x$continuous_update, "\n")
  cat("readout_format: ", x$readout_format, "\n")
  cat("readout: ", x$readout, "\n")
  cat("description_width: ", x$description_width, "\n")
  cat("handle_color: ", x$handle_color, "\n")
}

#' Get Slider Widget Value
#' @title Get Slider Widget Value
#' @param x
#'   An object of type \code{xslider}.
#' @param name
#'   The attribute of the \code{xlsider} to be fetched.
#' @examples
#' \dontrun{
#'    slider <- xslider(type='int', value=50)
#'    slider$value
#' }
#'
#' @export
`$.xslider` <- function(x, name) { x[name] }

#' Get Slider Widget Value
#' @title Get Slider Widget Value
#' @param x
#'   An object of type \code{xslider}.
#' @param name
#'   The attribute of the \code{xlsider} to be fetched.
#' @examples
#' \dontrun{
#'    slider <- xslider(type='int', value=50)
#'    slider["value"]
#' }
#'
#' @export
`[.xslider` <- function(x, name) {
  if( name %in% c("type", "ptr", "style") ) attr(x, name)
  else get_slider_field(x$ptr, x$type, name)
}

#' Update Slider Widget Value
#' @title Update Slider Widget Value
#' @param data
#'   An object of type \code{xslider}.
#' @param name
#'   The attribute of the \code{xlsider} that should be updated.
#' @param value
#'   A numeric value that can be coerced to the \code{type} specified.
#' @examples
#' \dontrun{
#'    slider <- xslider(type='int', value=50)
#'    slider$value <- 20
#' }
#'
#' @export
`$<-.xslider` <- function(data, name, value) {
  stopifnot("xslider" %in% class(data))
  data[name] <- value
  data
}

#' Update Slider Widget Value
#' @title Update Slider Widget Value
#' @param data
#'   An object of type \code{xslider}.
#' @param row
#'   The attribute of the \code{xlsider} that should be updated.
#' @param col
#'   Ignored.
#' @param ...
#'   Ignored.
#' @param value
#'   A numeric value that can be coerced to the \code{type} specified.
#' @examples
#' \dontrun{
#'    slider <- xslider(type='int', value=50)
#'    slider["value"] <- 20
#' }
#'
#' @export
`[<-.xslider` <- function(data,row,col,...,value) {
  stopifnot(missing(col))
  set_slider_field(data$ptr, data$type, row, value)
  data
}
