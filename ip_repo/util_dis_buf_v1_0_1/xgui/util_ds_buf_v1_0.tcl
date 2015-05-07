#Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
	set Page0 [ ipgui::add_page $IPINST  -name "Page 0" -layout vertical]
	set Component_Name [ ipgui::add_param  $IPINST  -parent  $Page0  -name Component_Name ]
	set C_SIZE [ipgui::add_param $IPINST -parent $Page0 -name C_SIZE ]
	set C_BUF_TYPE [ipgui::add_param $IPINST -parent $Page0 -name C_BUF_TYPE -widget radioGroup]
}

proc update_PARAM_VALUE.C_SIZE { PARAM_VALUE.C_SIZE } {
	# Procedure called to update C_SIZE when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_SIZE { PARAM_VALUE.C_SIZE } {
	# Procedure called to validate C_SIZE
	return true
}

proc update_PARAM_VALUE.C_BUF_TYPE { PARAM_VALUE.C_BUF_TYPE } {
	# Procedure called to update C_BUF_TYPE when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_BUF_TYPE { PARAM_VALUE.C_BUF_TYPE } {
	# Procedure called to validate C_BUF_TYPE
	return true
}


proc update_MODELPARAM_VALUE.C_BUF_TYPE { MODELPARAM_VALUE.C_BUF_TYPE PARAM_VALUE.C_BUF_TYPE } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_BUF_TYPE}] ${MODELPARAM_VALUE.C_BUF_TYPE}
}

proc update_MODELPARAM_VALUE.C_SIZE { MODELPARAM_VALUE.C_SIZE PARAM_VALUE.C_SIZE } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_SIZE}] ${MODELPARAM_VALUE.C_SIZE}
}

