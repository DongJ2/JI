VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3e"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL C
        SIGNAL sum
        SIGNAL carry
        SIGNAL A
        SIGNAL B
        PORT Input C
        PORT Output sum
        PORT Output carry
        PORT Input A
        PORT Input B
        BEGIN BLOCKDEF Circuit1
            TIMESTAMP 2017 5 23 10 31 55
            RECTANGLE N 64 -192 192 -64 
            LINE N 96 -192 96 -256 
            LINE N 160 -192 160 -256 
            LINE N 192 -160 256 -160 
            LINE N 64 -160 0 -160 
            LINE N 96 -64 96 0 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 Circuit1
            PIN A A
            PIN B B
            PIN C C
            PIN carry carry
            PIN sum sum
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        BEGIN BRANCH C
            WIRE 1616 1232 1904 1232
            WIRE 1904 1232 1920 1232
        END BRANCH
        BEGIN BRANCH sum
            WIRE 1456 1392 1456 1728
            WIRE 1456 1728 1456 1744
        END BRANCH
        IOMARKER 1456 1744 sum R90 28
        IOMARKER 1040 1232 carry R180 28
        BEGIN BRANCH carry
            WIRE 1040 1232 1056 1232
            WIRE 1056 1232 1360 1232
        END BRANCH
        BEGIN INSTANCE XLXI_1 1360 1392 R0
        END INSTANCE
        BEGIN BRANCH A
            WIRE 1456 752 1456 1136
        END BRANCH
        BEGIN BRANCH B
            WIRE 1520 816 1520 1136
        END BRANCH
        IOMARKER 1456 752 A R270 28
        IOMARKER 1520 816 B R270 28
        IOMARKER 1920 1232 C R0 28
    END SHEET
END SCHEMATIC
