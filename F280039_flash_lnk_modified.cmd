
/*
//###########################################################################
// FILE:    F280039_flash_lnk.cmd
// TITLE:   Linker Command File For F280039 Device
//###########################################################################
*/

MEMORY
{
   BOOT_RSVD         : origin = 0x00000002, length = 0x00000126

   RAMM0             : origin = 0x00000128, length = 0x000002D8
   RAMM1             : origin = 0x00000400, length = 0x000003F8     /* on-chip RAM block M1 */

   RAMLS0            : origin = 0x00008000, length = 0x00000800
   RAMLS1            : origin = 0x00008800, length = 0x00000800
   RAMLS2            : origin = 0x00009000, length = 0x00000800
   RAMLS3            : origin = 0x00009800, length = 0x00000800
   RAMLS4            : origin = 0x0000A000, length = 0x00000800
   RAMLS5            : origin = 0x0000A800, length = 0x00000800
   RAMLS6            : origin = 0x0000B000, length = 0x00000800
   RAMLS7            : origin = 0x0000B800, length = 0x00000800

   RAMGS0            : origin = 0x0000C000, length = 0x00001000
   RAMGS1            : origin = 0x0000D000, length = 0x00001000
   RAMGS2            : origin = 0x0000E000, length = 0x00001000
   RAMGS3            : origin = 0x0000F000, length = 0x00000FF8

   BOOTROM           : origin = 0x003F8000, length = 0x00007FC0
   SECURE_ROM        : origin = 0x003F2000, length = 0x00006000
   RESET             : origin = 0x003FFFC0, length = 0x00000002
}

SECTIONS
{
   codestart        : > BEGIN, ALIGN(8)
   .text            : >> FLASH_BANK0_SEC2 | FLASH_BANK0_SEC3 | FLASH_BANK0_SEC4,   ALIGN(8)
   .cinit           : > FLASH_BANK0_SEC1,  ALIGN(8)
   .switch          : > FLASH_BANK0_SEC1,  ALIGN(8)
   .reset           : > RESET,                  TYPE = DSECT /* not used, */
   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .init_array      : > FLASH_BANK0_SEC1,  ALIGN(8)
   .bss             : > RAMLS5 | RAMLS6    // Distribute .ebss across RAMLS5 and RAMLS6
   .bss:output      : > RAMLS3
   .bss:cio         : > RAMLS1             // Move .cio to RAMLS1
   .data            : > RAMLS5
   .sysmem          : > RAMLS5
   .const           : > FLASH_BANK0_SEC4,  ALIGN(8)
#else
   .pinit           : > FLASH_BANK0_SEC1,  ALIGN(8)
   .ebss            : > RAMGS0 | RAMGS1    // Adjust .ebss allocation
   .esysmem         : > RAMLS5
   .cio             : > RAMLS1             // Move .cio to RAMLS1
   .econst          : > FLASH_BANK0_SEC4,  ALIGN(8)
#endif

   ramgs0 : > RAMGS0
   ramgs1 : > RAMGS0

   IQmath           : > FLASH_BANK0_SEC1, ALIGN(8)
   IQmathTables     : > FLASH_BANK0_SEC2, ALIGN(8)

   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC1,
                      RUN = RAMLS0,
                      LOAD_START(RamfuncsLoadStart),
                      LOAD_SIZE(RamfuncsLoadSize),
                      LOAD_END(RamfuncsLoadEnd),
                      RUN_START(RamfuncsRunStart),
                      RUN_SIZE(RamfuncsRunSize),
                      RUN_END(RamfuncsRunEnd),
                      ALIGN(8)

   // CLA Program and Constants
   Cla1Prog : LOAD = FLASH_BANK0_SEC1, 
             RUN = RAMLS3, 
             LOAD_START(_Cla1ProgLoadStart),
             LOAD_END(_Cla1ProgLoadEnd),
             RUN_START(_Cla1ProgRunStart)

   Cla1Const : LOAD = FLASH_BANK0_SEC1,
               RUN = RAMLS4,
               LOAD_START(_Cla1ConstLoadStart),
               LOAD_END(_Cla1ConstLoadEnd),
               RUN_START(_Cla1ConstRunStart)
}
