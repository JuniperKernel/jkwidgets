#' 'Jupyter' Slider Widget
#' @title 'Jupyter' Slider Widget
#' @param type
#'   Either 'int' or 'float'. This argument specifies the numeric
#'   type of the slider.
#' @param value
#'   A numeric value that can be coerced to the \code{type} specified.
#' @examples
#' \dontrun{
#'    slider <- rxSlider(type='int', value=50)
#' }
#'
#' @export
rxSlider <- function(type = c('int', 'float'), value = 20) {
  type <- match.arg(type)
  stopifnot(type %in% c('int', 'float'))
  stopifnot(is(value, "numeric"))
  if( type=='int' )
    stopifnot(value == as.integer(value))
  x <- .newObj('xslider')
  attr(x, 'type') <- type
  attr(x, 'ptr') <- make_slider(type, value)

  style <- .newObj('xslider_style')
  attr(style, 'ptr') <- x
  attr(x, 'style') <- style
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
#'    slider <- rxSlider(type='int', value=50)
#'    slider
#' }
#'
#' @export
print.xslider <- function(x, ...) {
  cat("A Jupyter Slider Widget\n")
  cat("Type: ", x$type, "\n")
  cat("Value: ", x$value, "\n")
  cat("Max: ", x$max, "\n")
  cat("Min: ", x$min, "\n")
  cat("Orientation: ", x$orientation, "\n")
  cat("Description: ", x$description, "\n")
  cat("Disabled: ", x$disabled, "\n")
  cat("Step: ", x$step, "\n")
  cat("Continuous Update: ", x$continuous_update, "\n")
  cat("Readout Format: ", x$format, "\n")
  cat("Readout: ", x$readout, "\n")
  cat("Styles: ", "\n")
  print(x$style)
}

#' Get Slider Widget Value
#' @title Get Slider Widget Value
#' @param x
#'   An object of type \code{xslider}.
#' @param name
#'   The attribute of the \code{xlsider} to be fetched.
#' @examples
#' \dontrun{
#'    slider <- rxSlider(type='int', value=50)
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
#'    slider <- rxSlider(type='int', value=50)
#'    slider["value"]
#' }
#'
#' @export
`[.xslider` <- function(x, name) {
  if( name %in% c("type", "ptr", "style") ) attr(x, name)
  else slider_field(x$ptr, x$type, name)
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
#'    slider <- rxSlider(type='int', value=50)
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
#'    slider <- rxSlider(type='int', value=50)
#'    slider["value"] <- 20
#' }
#'
#' @export
`[<-.xslider` <- function(data,row,col,...,value) {
  stopifnot(missing(col))
  if( row!="style" )
    update_widget("slider", row, data$ptr, data$type, value)
  data
}


# STYLES

#' Print Method for Jupyter Slider Styles
#' @title Print Method for Jupyter Slider Styles
#' @param x
#'   Object of type \code{xslider_style}.
#' @param ...
#'   Ignored.
#' @examples
#' \dontrun{
#'    slider <- rxSlider(type='int', value=50)
#'    slider$style
#' }
#'
#' @export
print.xslider_style <- function(x, ...) {
  cat(" Description Width: ", x$description_width, "\n")
  cat(" Handle Color: ", x$handle_color, "\n")
}

#' Get Slider Widget Style
#' @title Get Slider Widget Style
#' @param x
#'   An object of type \code{xslider_style}.
#' @param name
#'   The attribute of the \code{xlsider_style} to be fetched.
#' @examples
#' \dontrun{
#'    slider <- rxSlider(type='int', value=50)
#'    slider$style$description_width
#' }
#'
#' @export
`$.xslider_style` <- function(x, name) { x[name] }

#' Get Slider Widget Style
#' @title Get Slider Widget Style
#' @param x
#'   An object of type \code{xslider_style}.
#' @param name
#'   The attribute of the \code{xslider_style} to be fetched.
#' @examples
#' \dontrun{
#'    slider <- rxSlider(type='int', value=50)
#'    slider["style"]["description_width"]
#' }
#'
#' @export
`[.xslider_style` <- function(x, name) { attr(x, 'ptr')[name] }

#' Update Slider Widget Style
#' @title Update Slider Widget Style
#' @param data
#'   An object of type \code{xslider_style}.
#' @param name
#'   The attribute of the \code{xslider_style} that should be updated.
#' @param value
#'   Update the style to this value.
#' @examples
#' \dontrun{
#'    slider <- rxSlider(type='int', value=50)
#'    slider$style$description_width <- 150
#' }
#'
#' @export
`$<-.xslider_style` <- function(data, name, value) {
  stopifnot("xslider_style" %in% class(data))
  data[name] <- value
  data
}

#' Update Slider Widget Style
#' @title Update Slider Widget Style
#' @param data
#'   An object of type \code{xslider_style}.
#' @param row
#'   The attribute of the \code{xlsider_style} that should be updated.
#' @param col
#'   Ignored.
#' @param ...
#'   Ignored.
#' @param value
#'   Update the style to this value.
#' @examples
#' \dontrun{
#'    slider <- rxSlider(type='int', value=50)
#'    slider["style"]["handle_color"] <- "blue"
#' }
#'
#' @export
`[<-.xslider_style` <- function(data, row, col, ..., value) {
  stopifnot(missing(col))
  update_widget('slider', row, data$ptr, data$type, value)
  data
}
