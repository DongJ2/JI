VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3e"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL XLXN_1
        SIGNAL sum
        SIGNAL A
        SIGNAL B
        SIGNAL XLXN_8
        SIGNAL C
        SIGNAL XLXN_12
        SIGNAL carry
        PORT Output sum
        PORT Input A
        PORT Input B
        PORT Input C
        PORT Output carry
        BEGIN BLOCKDEF xor2
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -64 64 -64 
            LINE N 0 -128 60 -128 
            LINE N 256 -96 208 -96 
            ARC N -40 -152 72 -40 48 -48 44 -144 
            ARC N -24 -152 88 -40 64 -48 64 -144 
            LINE N 128 -144 64 -144 
            LINE N 128 -48 64 -48 
            ARC N 44 -144 220 32 208 -96 128 -144 
            ARC N 44 -224 220 -48 128 -48 208 -96 
        END BLOCKDEF
        BEGIN BLOCKDEF and2
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -64 64 -64 
            LINE N 0 -128 64 -128 
            LINE N 256 -96 192 -96 
            ARC N 96 -144 192 -48 144 -48 144 -144 
            LINE N 144 -48 64 -48 
            LINE N 64 -144 144 -144 
            LINE N 64 -48 64 -144 
        END BLOCKDEF
        BEGIN BLOCKDEF or2
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -64 64 -64 
            LINE N 0 -128 64 -128 
            LINE N 256 -96 192 -96 
            ARC N 28 -224 204 -48 112 -48 192 -96 
            ARC N -40 -152 72 -40 48 -48 48 -144 
            LINE N 112 -144 48 -144 
            ARC N 28 -144 204 32 192 -96 112 -144 
            LINE N 112 -48 48 -48 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 xor2
            PIN I0 B
            PIN I1 A
            PIN O XLXN_1
        END BLOCK
        BEGIN BLOCK XLXI_2 xor2
            PIN I0 C
            PIN I1 XLXN_1
            PIN O sum
        END BLOCK
        BEGIN BLOCK XLXI_3 and2
            PIN I0 B
            PIN I1 A
            PIN O XLXN_8
        END BLOCK
        BEGIN BLOCK XLXI_4 and2
            PIN I0 C
            PIN I1 XLXN_1
            PIN O XLXN_12
        END BLOCK
        BEGIN BLOCK XLXI_5 or2
            PIN I0 XLXN_8
            PIN I1 XLXN_12
            PIN O carry
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        INSTANCE XLXI_1 576 736 R0
        INSTANCE XLXI_2 1504 944 R0
        INSTANCE XLXI_3 560 1232 R0
        INSTANCE XLXI_4 1488 1216 R0
        INSTANCE XLXI_5 2064 1360 R0
        BEGIN BRANCH XLXN_1
            WIRE 832 640 1168 640
            WIRE 1168 640 1168 816
            WIRE 1168 816 1504 816
            WIRE 1168 816 1168 1088
            WIRE 1168 1088 1488 1088
        END BRANCH
        BEGIN BRANCH sum
            WIRE 1760 848 2784 848
        END BRANCH
        BEGIN BRANCH A
            WIRE 304 608 512 608
            WIRE 512 608 576 608
            WIRE 512 608 512 1104
            WIRE 512 1104 560 1104
        END BRANCH
        BEGIN BRANCH B
            WIRE 304 672 400 672
            WIRE 400 672 576 672
            WIRE 400 672 400 1168
            WIRE 400 1168 560 1168
        END BRANCH
        BEGIN BRANCH XLXN_8
            WIRE 816 1136 1440 1136
            WIRE 1440 1136 1440 1296
            WIRE 1440 1296 2064 1296
        END BRANCH
        BEGIN BRANCH C
            WIRE 304 1616 896 1616
            WIRE 896 1152 1488 1152
            WIRE 896 1152 896 1360
            WIRE 896 1360 896 1616
            WIRE 896 1360 1200 1360
            WIRE 1200 880 1200 1360
            WIRE 1200 880 1504 880
        END BRANCH
        BEGIN BRANCH XLXN_12
            WIRE 1744 1120 1904 1120
            WIRE 1904 1120 1904 1232
            WIRE 1904 1232 2064 1232
        END BRANCH
        BEGIN BRANCH carry
            WIRE 2320 1264 2768 1264
        END BRANCH
        IOMARKER 304 608 A R180 28
        IOMARKER 304 672 B R180 28
        IOMARKER 304 1616 C R180 28
        IOMARKER 2784 848 sum R0 28
        IOMARKER 2768 1264 carry R0 28
    END SHEET
END SCHEMATIC
