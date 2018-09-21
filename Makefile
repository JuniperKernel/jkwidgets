#SHELL := /bin/bash
.DELETE_ON_ERROR:

# for printing variable values
# usage: make print-VARIABLE
#        > VARIABLE = value_of_variable
print-%  : ; @echo $*=$($*)

PKG_VERSION=0.0.0.1

# qstack bacon bits
# xproperty
XPROPERTY_VERSION = 0.7.0
XPROPERTY_TAR_FILE = ${XPROPERTY_VERSION}.tar.gz
XPROPERTY_URL = https://github.com/QuantStack/xproperty/archive/${XPROPERTY_TAR_FILE}

# xwidgets
XWIDGETS_VERSION = 0.13.1
XWIDGETS_TAR_FILE = ${XWIDGETS_VERSION}.tar.gz
XWIDGETS_URL = https://github.com/QuantStack/xwidgets/archive/${XWIDGETS_TAR_FILE}


R_BUILD_ARGS= --no-manual --no-build-vignettes
R_CHECK_ARGS= --no-manual --no-build-vignettes --as-cran

R_HOME=$(shell R RHOME)
R=$(R_HOME)/bin/R
RSCRIPT=$(R_HOME)/bin/Rscript

default: build/jkwidgets_$(PKG_VERSION).tar.gz

build/jkwidgets_$(PKG_VERSION).tar.gz: $(wildcard R/*R) $(wildcard src/*cpp) DESCRIPTION qstack
	@echo "building " $@ " because " $?
	@$(RSCRIPT) -e 'Rcpp::compileAttributes()'
	@$(RSCRIPT) -e 'roxygen2::roxygenize()'
	@$(R) CMD build $(R_BUILD_ARGS) .
	@[ -d build ] || mkdir build
	@mv jkwidgets_$(PKG_VERSION).tar.gz build/

qstack: ./inst/include/xproperty ./inst/include/xwidgets

./inst/include/xproperty:
	@echo "Fetching xproperty headers..."
	@[ -d ./inst/include ] || mkdir -p ./inst/include
	@curl -skLO ${XPROPERTY_URL}
	@tar -xzf ${XPROPERTY_TAR_FILE}
	@mv xproperty-${XPROPERTY_VERSION}/include/xproperty ./inst/include
	@rm -rf xproperty-${XPROPERTY_VERSION} ${XPROPERTY_TAR_FILE}

./inst/include/xwidgets:
	@echo "Fetching xwidgets headers..."
	@[ -d ./inst/include ] || mkdir -p ./inst/include
	@curl -skLO ${XWIDGETS_URL}
	@tar -xzf ${XWIDGETS_TAR_FILE}
	@mv xwidgets-${XWIDGETS_VERSION}/include/xwidgets ./inst/include
	@rm -rf xwidgets-${XWIDGETS_VERSION} ${XWIDGETS_TAR_FILE}

install: build/jkwidgets_$(PKG_VERSION).tar.gz
	@(cd build && R CMD INSTALL jkwidgets_$(PKG_VERSION).tar.gz)

check: build/jkwidgets_$(PKG_VERSION).tar.gz
	@echo "running R CMD check"
	@$(R) CMD check $(R_CHECK_ARGS) build/jkwidgets_$(PKG_VERSION).tar.gz
	@$(R) -f scripts/r_cmd_check_validate.R

.PHONY: clean
clean:
	rm -rf build
	rm -rf man
	rm -rf *Rcheck
	rm -rf R/RcppExports.R src/RcppExports.cpp
	rm -rf src/*o
	rm -rf *gz *zip
	rm -rf src/*dll
	rm -rf inst/include/x*
