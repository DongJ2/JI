--------------------------------------------------------------------------------
-- Copyright (c) 1995-2008 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 10.1
--  \   \         Application : sch2vhdl
--  /   /         Filename : Circuit1.vhf
-- /___/   /\     Timestamp : 05/23/2017 12:38:56
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: D:\Xilinx\ISE\bin\nt\unwrapped\sch2vhdl.exe -intstyle ise -family spartan3e -flat -suppress -w D:/dj/2017su/Ve270/Lab/Lab1/Circuit1.sch Circuit1.vhf
--Design Name: Circuit1
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

entity Circuit1 is
   port ( A     : in    std_logic; 
          B     : in    std_logic; 
          C     : in    std_logic; 
          carry : out   std_logic; 
          sum   : out   std_logic);
end Circuit1;

architecture BEHAVIORAL of Circuit1 is
   attribute BOX_TYPE   : string ;
   signal XLXN_1  : std_logic;
   signal XLXN_8  : std_logic;
   signal XLXN_12 : std_logic;
   component XOR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR2 : component is "BLACK_BOX";
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component OR2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR2 : component is "BLACK_BOX";
   
begin
   XLXI_1 : XOR2
      port map (I0=>B,
                I1=>A,
                O=>XLXN_1);
   
   XLXI_2 : XOR2
      port map (I0=>C,
                I1=>XLXN_1,
                O=>sum);
   
   XLXI_3 : AND2
      port map (I0=>B,
                I1=>A,
                O=>XLXN_8);
   
   XLXI_4 : AND2
      port map (I0=>C,
                I1=>XLXN_1,
                O=>XLXN_12);
   
   XLXI_5 : OR2
      port map (I0=>XLXN_8,
                I1=>XLXN_12,
                O=>carry);
   
end BEHAVIORAL;


