################################################################################
proc get_other_end_pin { pinobj } {
   set endpin ""
   set srcPins [find_bd_objs -relation connected_to $pinobj]
   foreach pin $srcPins {
     set pin_dir   [get_property DIR $pin]
     set pin_class [get_property CLASS $pin]
     if {("$pin_dir"  == "O" && "$pin_class" == "bd_pin") ||
         ("$pin_dir"  == "I" && "$pin_class" == "bd_port")} {
       set endpin $pin
       break;
     }
   } 
   return $endpin
}
################################################################################
proc get_pin_type { pinobj } {
    set pinType [string tolower [get_property TYPE $pinobj] ]
    if { $pinType == "undef" } {
        set pinType [string tolower [get_property CONFIG.PortType $pinobj]]
    }
    return $pinType
}
################################################################################
proc propagate { cellName dictArg } {
    set ip [get_bd_cells $cellName]
    set type [get_property CONFIG.C_BUF_TYPE $ip]
    if { $type eq "IBUFDS" } {
        set ibufds_n [get_bd_pins $ip/IBUF_DS_N]
        set ibufds_p [get_bd_pins $ip/IBUF_DS_P]
        set ibuf_out [get_bd_pins $ip/IBUF_OUT]
        set_property CONFIG.PortType "undef" $ibufds_n
        set_property CONFIG.PortType "undef" $ibufds_p
        set_property CONFIG.PortType "undef" $ibuf_out
        set srcn_pin [get_other_end_pin $ibufds_n]
        set srcp_pin [get_other_end_pin $ibufds_p]
        if { 0 == [string length $srcn_pin] && 0 == [string length $srcp_pin] } {
            #ignore when both pin are unconnected
            return
        } elseif { 0 == [string length $srcn_pin] || 0 == [string length $srcp_pin] } {
            #error when only one pin is connected.
           ::bd::send_msg -of $cellName -type ERROR -msg_id 10 -text ":Both input pins should be connected for util_ds_buf"
           return
        }
        set srcn_type "undef"
        set srcp_type "undef"
        if {0 != [string length $srcn_pin] } {
            set srcn_type [get_pin_type $srcn_pin]
        }
        if {0 != [string length $srcp_pin] } {
            set srcp_type [get_pin_type $srcp_pin]
        }
        if { $srcn_type != $srcp_type } {
           ::bd::send_msg -of $cellName -type ERROR -msg_id 10 -text ":Both input pins have different types."
           return
        }
        set_property CONFIG.PortType $srcn_type $ibufds_n
        set_property CONFIG.PortType.PROP_SRC false $ibufds_n
        set_property CONFIG.PortType $srcp_type $ibufds_p
        set_property CONFIG.PortType.PROP_SRC false $ibufds_p
        set_property CONFIG.PortType $srcn_type $ibuf_out
        if { $srcp_type == "clk" } {
            set srcn_freq [get_property CONFIG.FREQ_HZ $srcn_pin]
            set srcp_freq [get_property CONFIG.FREQ_HZ $srcp_pin]
            set srcn_phase [get_property CONFIG.PHASE $srcn_pin]
            set srcp_phase [get_property CONFIG.PHASE $srcp_pin]
            set srcn_clkdomain [get_property CONFIG.CLK_DOMAIN $srcn_pin]
            set srcp_clkdomain [get_property CONFIG.CLK_DOMAIN $srcp_pin]
            if {$srcn_freq != $srcp_freq} {
               ::bd::send_msg -of $cellName -type ERROR -msg_id 10 -text ":Both input pins do not have same clock frequency"
               return
            }
            if {$srcn_phase != $srcp_phase} {
               ::bd::send_msg -of $cellName -type ERROR -msg_id 10 -text ":Both input pins do not have same clock phase"
               return
           }

            set_property CONFIG.FREQ_HZ $srcn_freq $ibuf_out
            set_property CONFIG.PHASE $srcn_phase $ibuf_out
            set_property CONFIG.CLK_DOMAIN $srcn_clkdomain $ibuf_out
        }
    } elseif { $type eq "OBUFDS" } {
        set obuf_in   [get_bd_pins $ip/OBUF_IN]
        set obuf_ds_p [get_bd_pins $ip/OBUF_DS_P]
        set obuf_ds_n [get_bd_pins $ip/OBUF_DS_N]
        set_property CONFIG.PortType "undef" $obuf_in
        set_property CONFIG.PortType "undef" $obuf_ds_p
        set_property CONFIG.PortType "undef" $obuf_ds_n
        set srcPin [get_other_end_pin $obuf_in]
        if { 0 == [string length $srcPin] } {
            return
        }
        set pinType [get_pin_type $srcPin]
        if { 0 != [string length $pinType] && $pinType != "undef" && $pinType != "null"} {
            set_property CONFIG.PortType $pinType $obuf_in
            set_property CONFIG.PortType.PROP_SRC false $obuf_in
            set_property CONFIG.PortType $pinType $obuf_ds_p
            set_property CONFIG.PortType $pinType $obuf_ds_n
            if { $pinType == "clk"} {
                set freq [get_property CONFIG.FREQ_HZ $srcPin]
                set phase [get_property CONFIG.PHASE $srcPin]
                set clkdomain [get_property CONFIG.CLK_DOMAIN $srcPin]
                set_property CONFIG.FREQ_HZ     $freq      $obuf_ds_p
                set_property CONFIG.PHASE       $phase     $obuf_ds_p
                set_property CONFIG.CLK_DOMAIN  $clkdomain $obuf_ds_p
                set_property CONFIG.FREQ_HZ     $freq      $obuf_ds_n
                set_property CONFIG.PHASE       $phase     $obuf_ds_n
                set_property CONFIG.CLK_DOMAIN  $clkdomain $obuf_ds_n
            }
        }
    }
}
################################################################################
