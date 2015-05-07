 -----------------------------------------------------------------------
 -- Company: 
 -- Engineer: 
 -- 
 -- Create Date:    29/07/2014 
 -- Design Name:    EVAL_UUB
 -- Module Name:    test_uub - Behavioral 
 -- Project Name: 
 -- Target Devices: 
 -- Tool versions: 
 -- Description: 
 --
 -- Dependencies: 
 --
 -- Revision: 
 --   0  29/07/14 Version initiale
 --
 -----------------------------------------------------------------------
 library ieee;
   use ieee.std_logic_1164.all;
   use ieee.std_logic_arith.all;
   use ieee.std_logic_unsigned.all;
  
 entity test_uub is
   Port ( RSTn      : in  std_logic;
          CLK       : in  std_logic;
          reg_wr0   : in  std_logic_vector(31 downto 0);
          reg_wr1   : in  std_logic_vector(31 downto 0);
          reg_wr2   : in  std_logic_vector(31 downto 0);
          reg_wr3   : in  std_logic_vector(31 downto 0);
          reg_wr4   : in  std_logic_vector(31 downto 0);
          reg_wr5   : in  std_logic_vector(31 downto 0);
          reg_wr6   : in  std_logic_vector(31 downto 0);
          reg_wr7   : in  std_logic_vector(31 downto 0);
          reg_wr8   : in  std_logic_vector(31 downto 0);
          reg_wr9   : in  std_logic_vector(31 downto 0);
          reg_wr10  : in  std_logic_vector(31 downto 0);
          reg_wr11  : in  std_logic_vector(31 downto 0);
          reg_wr12  : in  std_logic_vector(31 downto 0);
          reg_wr13  : in  std_logic_vector(31 downto 0);
          reg_wr14  : in  std_logic_vector(31 downto 0);
          reg_wr15  : in  std_logic_vector(31 downto 0);
          reg_rd0   : out std_logic_vector(31 downto 0);
          reg_rd1   : out std_logic_vector(31 downto 0);
          reg_rd2   : out std_logic_vector(31 downto 0);
          reg_rd3   : out std_logic_vector(31 downto 0);
          reg_rd4   : out std_logic_vector(31 downto 0);
          reg_rd5   : out std_logic_vector(31 downto 0);
          reg_rd6   : out std_logic_vector(31 downto 0);
          reg_rd7   : out std_logic_vector(31 downto 0);
          reg_rd8   : out std_logic_vector(31 downto 0);
          reg_rd9   : out std_logic_vector(31 downto 0);
          reg_rd10  : out std_logic_vector(31 downto 0);
          reg_rd11  : out std_logic_vector(31 downto 0);
          reg_rd12  : out std_logic_vector(31 downto 0);
          reg_rd13  : out std_logic_vector(31 downto 0);
          reg_rd14  : out std_logic_vector(31 downto 0);
          reg_rd15  : out std_logic_vector(31 downto 0);
       -- Interface ADC AD9628 (CLK)
          ADC_CK    : in  std_logic;
      -- Interface Horloge
          FPGA_CK   : in  std_logic;
       -- Interface ADC AD9628 (Datas)
          adc0      : in  std_logic_vector(25 downto 0);
          adc1      : in  std_logic_vector(25 downto 0);
          adc2      : in  std_logic_vector(25 downto 0);
          adc3      : in  std_logic_vector(25 downto 0);
          adc4      : in  std_logic_vector(25 downto 0);
          
       -- Interface switches
          sw        : in  std_logic_vector(7 downto 0);

       -- Interface Trigger
          TRIG_IN   : in  std_logic;
          TRIG_OUT  : out std_logic );

 end test_uub;
 
 architecture Behavioral of test_uub is
 
   type matrice_5x13 is array (4 downto 0) of std_logic_vector(12 downto 0);
   signal mem_data_a : matrice_5x13;
   signal out_data_a : matrice_5x13;
   signal out_data_b : matrice_5x13;
   signal out_data_a_p1 : matrice_5x13;
   signal out_data_a_p2 : matrice_5x13;
   signal out_data_b_p1 : matrice_5x13;
   signal out_data_b_p2 : matrice_5x13;
   signal TRIG_OUT_INT  : std_logic;
   
 begin
 
 --adc <= ( adc4, adc3, adc2, adc1, adc0);
             
  --******************************************************************
  -- Rseynchronisation des datas recus de l'elements Selectio_wiz_X
  --******************************************************************
 
        process(RSTn, FPGA_CK)  -- a changer par le reset SELECTIO_WIZ_X
        begin
        if RSTn = '0' then
            mem_data_a <= ( others => (others => '0'));
            out_data_a <= ( others => (others => '0'));
            out_data_b <= ( others => (others => '0'));
        elsif rising_edge(FPGA_CK) then
            mem_data_a <= ( adc4(25 downto 13),adc3(25 downto 13),adc2(25 downto 13), 
                      adc1(25 downto 13),adc0(25 downto 13));
            out_data_a <= mem_data_a;
            out_data_b <= ( adc4(12 downto 0), adc3(12 downto 0), adc2(12 downto 0), 
                      adc1(12 downto 0), adc0(12 downto 0) );
        end if;
        end process;

 --********************************************************************
 --                 Changement de domaine d horloge 
 --********************************************************************
 
  process(RSTn, CLK)
  begin
    if RSTn = '0' then
      out_data_a_p1 <= ( others => (others => '0'));
      out_data_a_p2 <= ( others => (others => '0'));
      out_data_b_p1 <= ( others => (others => '0'));
      out_data_b_p2 <= ( others => (others => '0'));
    elsif rising_edge(CLK) then
      out_data_a_p1 <= out_data_a;
      out_data_a_p2 <= out_data_a_p1;
      out_data_b_p1 <= out_data_b;
      out_data_b_p2 <= out_data_b_p1;
    end if;
  end process;
 
 --********************************************************************
 --                     Formation des registres 
 --********************************************************************
     
 --reg_rd0  <= "000" & adc0(25 downto 13) & "000" & adc0(12 downto 0);
 reg_rd0  <= "000" & out_data_b_p2(0) & "000" & out_data_a_p2(0);
 reg_rd1  <= "000" & out_data_b_p2(1) & "000" & out_data_a_p2(1);
 reg_rd2  <= "000" & out_data_b_p2(2) & "000" & out_data_a_p2(2);
 reg_rd3  <= "000" & out_data_b_p2(3) & "000" & out_data_a_p2(3);
 reg_rd4  <= "000" & out_data_b_p2(4) & "000" & out_data_a_p2(4);
 reg_rd5  <= reg_wr5(31 downto 8) & sw;
          
 reg_rd6  <= reg_wr6;           
 reg_rd7  <= reg_wr7;           
 reg_rd8  <= reg_wr8;           
 reg_rd9  <= reg_wr9;           
 reg_rd10 <= reg_wr10;           
 reg_rd11 <= reg_wr11;           
 reg_rd12 <= reg_wr12;           
 reg_rd13 <= reg_wr13;           
 reg_rd14 <= reg_wr14;           
-- reg_rd15 <= reg_wr15;           
 reg_rd15 <= x"5555AAAA";           
           
  
 
 end Behavioral;
 
