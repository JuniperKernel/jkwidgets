::quantstack bacon bits
:: xproperty
set "XPROPERTY_VERSION=0.7.0"
set "XPROPERTY_TAR_FILE=%XPROPERTY_VERSION%.tar.gz"
set "XPROPERTY_URL=https://github.com/QuantStack/xproperty/archive/%XPROPERTY_TAR_FILE%"

:: xwidgets
set "XWIDGETS_VERSION=0.13.1"
set "XWIDGETS_TAR_FILE=%XWIDGETS_VERSION%.tar.gz"
set "XWIDGETS_URL=https://github.com/QuantStack/xwidgets/archive/%XWIDGETS_TAR_FILE%"

:: fetch headers and put them in inst\include
if not exist ".\inst\include" mkdir .\inst\include

:: fetch xtl headers
powershell -Command "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest %XPROPERTY_URL% -OutFile %XPROPERTY_TAR_FILE%"
C:\Rtools\bin\tar -xzf %XPROPERTY_TAR_FILE%
C:\Rtools\bin\mv xproperty-%XPROPERTY_VERSION%\include\xproperty .\inst\include
C:\Rtools\bin\rm -rf xproperty-%XPROPERTY_VERSION% %XPROPERTY_TAR_FILE%


:: fetch xwidgets headers
powershell -Command "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest %XWIDGETS_URL% -OutFile %XWIDGETS_TAR_FILE%"
C:\Rtools\bin\tar -xzf %XWIDGETS_TAR_FILE%
C:\Rtools\bin\mv xwidgets-%XWIDGETS_VERSION%\include\xwidgets .\inst\include
C:\Rtools\bin\rm -rf xwidgets-%XWIDGETS_VERSION% %XWIDGETS_TAR_FILE%

Rscript -e Rcpp::compileAttributes()
if %ERRORLEVEL% EQU 1 exit 1

::Rscript -e "install.packages('devtools',repo='https://cran.r-project.org')"
if %ERRORLEVEL% EQU 1 exit 1

:: install a version of roxygen2 that does not attempt to build the package...
::Rscript -e "devtools::install_version('roxygen2', version='6.0.1', repo='https://cran.r-project.org')"
if %ERRORLEVEL% EQU 1 exit 1

Rscript -e roxygen2::roxygenize()
if %ERRORLEVEL% EQU 1 exit 1

R CMD build .
if %ERRORLEVEL% EQU 1 exit 1

mkdir build
C:\Rtools\bin\mv jkwidgets*gz build
cd build
::R CMD INSTALL jkwidgets*gz
R CMD INSTALL --no-multiarch jkwidgets*gz
