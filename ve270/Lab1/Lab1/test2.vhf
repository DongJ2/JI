--------------------------------------------------------------------------------
-- Copyright (c) 1995-2008 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 10.1
--  \   \         Application : sch2vhdl
--  /   /         Filename : test2.vhf
-- /___/   /\     Timestamp : 05/23/2017 18:39:15
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: D:\Xilinx\ISE\bin\nt\unwrapped\sch2vhdl.exe -intstyle ise -family spartan3e -flat -suppress -w D:/dj/2017su/Ve270/Lab/Lab1/test2.sch test2.vhf
--Design Name: test2
--Device: spartan3e
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesis and simulted, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity test2 is
   port ( A     : in    std_logic; 
          B     : in    std_logic; 
          C     : in    std_logic; 
          carry : out   std_logic; 
          sum   : out   std_logic);
end test2;

architecture BEHAVIORAL of test2 is
   component Circuit1
      port ( A     : in    std_logic; 
             B     : in    std_logic; 
             C     : in    std_logic; 
             carry : out   std_logic; 
             sum   : out   std_logic);
   end component;
   
begin
   XLXI_1 : Circuit1
      port map (A=>A,
                B=>B,
                C=>C,
                carry=>carry,
                sum=>sum);
   
end BEHAVIORAL;


