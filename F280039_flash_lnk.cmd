/*
//###########################################################################
//
// FILE:	F280039_flash_lnk.cmd
//
// TITLE:	Linker Command File For F280039 Device
//
//###########################################################################
*/
MEMORY
{
   BEGIN           	: origin = 0x00080000, length = 0x00000002

   BOOT_RSVD		: origin = 0x00000002, length = 0x00000126

   RAMM0           	: origin = 0x00000128, length = 0x000002D8
   RAMM1            : origin = 0x00000400, length = 0x000003F8     /* on-chip RAM block M1 */
// RAMM1_RSVD       : origin = 0x000007F8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMLS0           : origin = 0x00008000, length = 0x00000800
   RAMLS1           : origin = 0x00008800, length = 0x00000800
   RAMLS2           : origin = 0x00009000, length = 0x00000800
   RAMLS3           : origin = 0x00009800, length = 0x00000800
   RAMLS4           : origin = 0x0000A000, length = 0x00000800
   RAMLS5           : origin = 0x0000A800, length = 0x00000800
   RAMLS6           : origin = 0x0000B000, length = 0x00000800
   RAMLS7           : origin = 0x0000B800, length = 0x00000800

   /* Combining all the LS RAMs */
   //RAMLS            : origin = 0x00008000, length = 0x00004000
   
   RAMGS0           : origin = 0x0000C000, length = 0x00001000
   RAMGS1_2         : origin = 0x0000D000, length = 0x00002000		//单个RAM区域不够用，将RAMGS1,RAMGS2合并
//   RAMGS2           : origin = 0x0000E000, length = 0x00001000
   RAMGS3           : origin = 0x0000F000, length = 0x00000FF8
// RAMGS3_RSVD       : origin = 0x000FFF8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   BOOTROM          : origin = 0x003F8000, length = 0x00007FC0
   SECURE_ROM       : origin = 0x003F2000, length = 0x00006000

   RESET            : origin = 0x003FFFC0, length = 0x00000002

   /* Flash sectors */
   /* BANK 0 */
   FLASH_BANK0_SEC0  : origin = 0x080002, length = 0x000FFE
   FLASH_BANK0_SEC1  : origin = 0x081000, length = 0x001000
   FLASH_BANK0_SEC2  : origin = 0x082000, length = 0x001000
   FLASH_BANK0_SEC3  : origin = 0x083000, length = 0x001000
   FLASH_BANK0_SEC4  : origin = 0x084000, length = 0x001000
   FLASH_BANK0_SEC5  : origin = 0x085000, length = 0x001000
   FLASH_BANK0_SEC6  : origin = 0x086000, length = 0x001000
   FLASH_BANK0_SEC7  : origin = 0x087000, length = 0x001000
   FLASH_BANK0_SEC8  : origin = 0x088000, length = 0x001000
   FLASH_BANK0_SEC9  : origin = 0x089000, length = 0x001000
   FLASH_BANK0_SEC10 : origin = 0x08A000, length = 0x001000
   FLASH_BANK0_SEC11 : origin = 0x08B000, length = 0x001000
   FLASH_BANK0_SEC12 : origin = 0x08C000, length = 0x001000
   FLASH_BANK0_SEC13 : origin = 0x08D000, length = 0x001000
   FLASH_BANK0_SEC14 : origin = 0x08E000, length = 0x001000
   FLASH_BANK0_SEC15 : origin = 0x08F000, length = 0x001000

   /* BANK 1 */
   FLASH_BANK1_SEC0  : origin = 0x090000, length = 0x001000
   FLASH_BANK1_SEC1  : origin = 0x091000, length = 0x001000
   FLASH_BANK1_SEC2  : origin = 0x092000, length = 0x001000
   FLASH_BANK1_SEC3  : origin = 0x093000, length = 0x001000
   FLASH_BANK1_SEC4  : origin = 0x094000, length = 0x001000
   FLASH_BANK1_SEC5  : origin = 0x095000, length = 0x001000
   FLASH_BANK1_SEC6  : origin = 0x096000, length = 0x001000
   FLASH_BANK1_SEC7  : origin = 0x097000, length = 0x001000
   FLASH_BANK1_SEC8  : origin = 0x098000, length = 0x001000
   FLASH_BANK1_SEC9  : origin = 0x099000, length = 0x001000
   FLASH_BANK1_SEC10 : origin = 0x09A000, length = 0x001000
   FLASH_BANK1_SEC11 : origin = 0x09B000, length = 0x001000
   FLASH_BANK1_SEC12 : origin = 0x09C000, length = 0x001000
   FLASH_BANK1_SEC13 : origin = 0x09D000, length = 0x001000
   FLASH_BANK1_SEC14 : origin = 0x09E000, length = 0x001000
   FLASH_BANK1_SEC15 : origin = 0x09F000, length = 0x001000

  /* BANK 2 */
   FLASH_BANK2_SEC0  : origin = 0x0A0000, length = 0x001000
   FLASH_BANK2_SEC1  : origin = 0x0A1000, length = 0x001000
   FLASH_BANK2_SEC2  : origin = 0x0A2000, length = 0x001000
   FLASH_BANK2_SEC3  : origin = 0x0A3000, length = 0x001000
   FLASH_BANK2_SEC4  : origin = 0x0A4000, length = 0x001000
   FLASH_BANK2_SEC5  : origin = 0x0A5000, length = 0x001000
   FLASH_BANK2_SEC6  : origin = 0x0A6000, length = 0x001000
   FLASH_BANK2_SEC7  : origin = 0x0A7000, length = 0x001000
   FLASH_BANK2_SEC8  : origin = 0x0A8000, length = 0x001000
   FLASH_BANK2_SEC9  : origin = 0x0A9000, length = 0x001000
   FLASH_BANK2_SEC10 : origin = 0x0AA000, length = 0x001000
   FLASH_BANK2_SEC11 : origin = 0x0AB000, length = 0x001000
   FLASH_BANK2_SEC12 : origin = 0x0AC000, length = 0x001000
   FLASH_BANK2_SEC13 : origin = 0x0AD000, length = 0x001000
   FLASH_BANK2_SEC14 : origin = 0x0AE000, length = 0x001000
   FLASH_BANK2_SEC15 : origin = 0x0AF000, length = 0x000FF0
// FLASH_BANK2_SEC15_RSVD : origin = 0x0AFFF0, length = 0x000010  /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */


}


SECTIONS
{
   codestart        : > BEGIN, ALIGN(8)
   .text            : >> FLASH_BANK0_SEC2 | FLASH_BANK0_SEC3 | FLASH_BANK0_SEC4 | FLASH_BANK0_SEC5 | FLASH_BANK0_SEC6 | FLASH_BANK0_SEC7 ,   ALIGN(8)
   .cinit           : > FLASH_BANK0_SEC1,  ALIGN(8)
   .switch          : > FLASH_BANK0_SEC1,  ALIGN(8)
   .reset           : > RESET,                  TYPE = DSECT /* not used, */

   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .init_array      : > FLASH_BANK0_SEC1,  ALIGN(8)
   .bss             : > RAMLS5
   .bss:output      : > RAMLS5	//2024.10.9修改
   .bss:cio         : > RAMLS0
   .data            : > RAMLS5
   .sysmem          : > RAMLS5
   .const           : > FLASH_BANK0_SEC4,  ALIGN(8)
#else
   .pinit           : > FLASH_BANK0_SEC1,  ALIGN(8)
   .ebss            : > RAMGS1_2 	// Adjust .ebss allocation
   .esysmem         : > RAMLS5
   .cio             : > RAMLS1	// Move .cio to RAMLS1
   .econst          : > FLASH_BANK0_SEC4,  ALIGN(8)
#endif

    ramgs0 : > RAMGS0
    ramgs1 : > RAMGS0	/* not used */

   .stack           : > RAMM1
   .bss             : > RAMLS6, ALIGN(8)
   .bss_cla         : > RAMLS2, ALIGN(8)              /* CLA未初始化变量 */
   CpuToCla1MsgRAM  : > RAMGS3, ALIGN(8)              /* CPU到CLA消息传递 */
   Cla1ToCpuMsgRAM  : > RAMLS7, ALIGN(8)              /* CLA到CPU消息传递 */

    /*  Allocate IQ math areas: */
   IQmath           : > FLASH_BANK0_SEC1, ALIGN(8)
   IQmathTables     : > FLASH_BANK0_SEC2, ALIGN(8)

   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC1,
                      RUN = RAMLS0,
                      LOAD_START(_RamfuncsLoadStart),
                      LOAD_SIZE(_RamfuncsLoadSize),
                      LOAD_END(_RamfuncsLoadEnd),
                      RUN_START(_RamfuncsRunStart),
                      RUN_SIZE(_RamfuncsRunSize),
                      RUN_END(_RamfuncsRunEnd),
                      ALIGN(8)

   /* crc/checksum section configured as COPY section to avoid including in executable */
   .TI.memcrc          : type = COPY

   // CLA Program and Constants
   Cla1Prog : LOAD = FLASH_BANK0_SEC1,
             RUN = RAMLS3, /* CLA 程序运行在 RAMLS3 */
             LOAD_START(_Cla1ProgLoadStart),
             LOAD_END(_Cla1ProgLoadEnd),
             RUN_START(_Cla1ProgRunStart),
             LOAD_SIZE(_Cla1ProgLoadSize)

   Cla1Const : LOAD = FLASH_BANK0_SEC1,
               RUN = RAMLS4,/* CLA 常量段运行在 RAMLS4 */
               LOAD_START(_Cla1ConstLoadStart),
               LOAD_END(_Cla1ConstLoadEnd),
               RUN_START(_Cla1ConstRunStart),
               LOAD_SIZE(_Cla1ConstLoadSize)

}
/*
//###########################################################################
// End of file.
//###########################################################################
*/
