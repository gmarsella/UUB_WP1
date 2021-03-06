# 
# Synthesis run script generated by Vivado
# 

  set_param gui.test TreeTableDev
set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
create_project -in_memory -part xc7z020clg484-1
set_property target_language VHDL [current_project]
set_property board_part em.avnet.com:zed:part0:1.0 [current_project]
set_param project.compositeFile.enableAutoGeneration 0
set_property default_lib xil_defaultlib [current_project]
set_property ip_repo_paths {
  C:/Xilinx/Vivado/2014.2/progetti/ip_repo
  C:/xilinx/vivado/2014.2/progetti/ip_repo/adc_interface
  C:/xilinx/vivado/2014.2/progetti/ip_repo/delay_input
  C:/xilinx/vivado/2014.2/progetti/ip_repo/adc_interface
  C:/xilinx/vivado/2014.2/progetti/ip_repo/adc_interface
  C:/xilinx/vivado/2014.2/progetti/ip_repo/adc_interface
  C:/xilinx/vivado/2014.2/progetti/ip_repo/adc_interface
  c:/xilinx/vivado/2014.2/progetti/ip_repo/adc_interface
} [current_fileset]

add_files C:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/WP1_system.bd
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_processing_system7_0_0/WP1_system_processing_system7_0_0.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_axi_gpio_0_0/WP1_system_axi_gpio_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_axi_gpio_0_0/WP1_system_axi_gpio_0_0.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_axi_gpio_0_0/WP1_system_axi_gpio_0_0_board.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_rst_processing_system7_0_100M_0/WP1_system_rst_processing_system7_0_100M_0.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_rst_processing_system7_0_100M_0/WP1_system_rst_processing_system7_0_100M_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_rst_processing_system7_0_100M_0/WP1_system_rst_processing_system7_0_100M_0_board.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_xbar_0/WP1_system_xbar_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_selectio_wiz_0_0/WP1_system_selectio_wiz_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_selectio_wiz_0_0/WP1_system_selectio_wiz_0_0.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_selectio_wiz_1_0/WP1_system_selectio_wiz_1_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_selectio_wiz_1_0/WP1_system_selectio_wiz_1_0.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_blk_mem_gen_0_2/WP1_system_blk_mem_gen_0_2_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_axi_bram_ctrl_0_1/WP1_system_axi_bram_ctrl_0_1_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_axi_bram_ctrl_1_0/WP1_system_axi_bram_ctrl_1_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_blk_mem_gen_1_0/WP1_system_blk_mem_gen_1_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_s00_data_fifo_0/WP1_system_s00_data_fifo_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_auto_pc_0/WP1_system_auto_pc_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_auto_pc_1_0/WP1_system_auto_pc_1_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/ip/WP1_system_auto_pc_2/WP1_system_auto_pc_2_ooc.xdc]
set_property used_in_implementation false [get_files -all C:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/WP1_system_ooc.xdc]
set_msg_config -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property is_locked true [get_files C:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/sources_1/bd/WP1_system/WP1_system.bd]

read_xdc C:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/constrs_1/imports/WP1/roberto_constraints.xdc
set_property used_in_implementation false [get_files C:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.srcs/constrs_1/imports/WP1/roberto_constraints.xdc]

read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir C:/Xilinx/Vivado/2014.2/progetti/WP1/WP1/WP1.cache/wt [current_project]
set_property parent.project_dir C:/Xilinx/Vivado/2014.2/progetti/WP1/WP1 [current_project]
catch { write_hwdef -file WP1_system.hwdef }
synth_design -top WP1_system -part xc7z020clg484-1
write_checkpoint WP1_system.dcp
report_utilization -file WP1_system_utilization_synth.rpt -pb WP1_system_utilization_synth.pb
