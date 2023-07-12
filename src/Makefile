OS=$(shell uname)
ifeq ($(OS), Linux)
  OPEN=xdg-open
else
  OPEN=open
endif

install:
	cmake -S . -B ../build
	cmake --build ../build
	@cp -rf ../build/PhotoLaboratory.app $(HOME)/Applications/

uninstall:
	@rm -rf $(HOME)/Applications/PhotoLaboratory.app

tests:
	@cmake -S ./Test -B ../buildtest
	@cmake --build ../buildtest
	@../buildtest/PhotoLaboratoryTest

gcov_report:
	@cmake -S ./Test -B ../buildgcov
	@cmake --build ../buildgcov
	@chmod +x *
	@../buildgcov/PhotoLaboratoryTest
	@lcov -t "gcov_report" -o gcov_report.info --no-external -c -d .
	@genhtml -o report/ gcov_report.info
	@open ./report/index.html

leaks:
	@cmake -S ./Test -B ../buildtest
	@cmake --build ../buildtest
	@CK_FORK=no leaks --atExit -- ../buildtest/PhotoLaboratoryTest

dvi:
	@$(OPEN) -n -a "Google Chrome" --args "--new-window" "https://github.com/tonitaga/PhotoLab_v1.0"

dist:
	@rm -rf PhotoLaboratory
	@mkdir PhotoLaboratory
	@cp -R ../build/PhotoLaboratory.app PhotoLaboratory
	@tar -czvf PhotoLaboratory.tar PhotoLaboratory
	@rm -rf PhotoLaboratory

bist:
	@rm -rf PhotoLaboratory.tar

clean:
	@rm -rf ../build

style:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -i Controller/*.h Model/FilterModel/*.h Model/FilterHelper/*.cc Model/FilterHelper/*.h
	@clang-format -i Model/FilterHelper/Filters/ConvolutionFilters/*.cc Model/FilterHelper/Filters/ConvolutionFilters/*.h
	@clang-format -i Model/FilterHelper/Filters/NonConvolutionFilters/*.cc Model/FilterHelper/Filters/NonConvolutionFilters/*.h
	@clang-format -i Model/FilterHelper/FilterManagers/*.h
	@clang-format -i Test/*.cc
	@clang-format -i View/*.cc View/*.h
	@clang-format -i *.cc


	@clang-format -n Controller/*.h Model/FilterModel/*.h Model/FilterHelper/*.cc Model/FilterHelper/*.h
	@clang-format -n Model/FilterHelper/Filters/ColorCorrectionFilters/*.cc Model/FilterHelper/Filters/ColorCorrectionFilters/*.h
	@clang-format -n Model/FilterHelper/Filters/ConvolutionFilters/*.cc Model/FilterHelper/Filters/ConvolutionFilters/*.h
	@clang-format -n Model/FilterHelper/Filters/NonConvolutionFilters/*.cc Model/FilterHelper/Filters/NonConvolutionFilters/*.h
	@clang-format -n Model/FilterHelper/FilterManagers/*.h
	@clang-format -n Test/*.cc
	@clang-format -n View/*.cc View/*.h
	@clang-format -n *.cc