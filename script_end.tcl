
add_files AF_classifier.hpp
add_files -tb AF_classifier_test.cpp
add_files -tb data.hpp
add_files -tb label.hpp
add_files -tb s_data.hpp
add_files -tb s_label.hpp
open_solution "solution1"
set_part {xc7z020clg400-1} -tool vivado
create_clock -period 10 -name default
config_export -format ip_catalog -rtl verilog
#source "./demo51/solution1/directives.tcl"
csim_design
csynth_design
#cosim_design
#export_design -rtl verilog -format ip_catalog
close_project