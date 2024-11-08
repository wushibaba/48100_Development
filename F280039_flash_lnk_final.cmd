
MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to Flash" bootloader mode   */

   BEGIN           	: origin = 0x080000, length = 0x000002
   RAMM0           	: origin = 0x000128, length = 0x0002D8

   RAMLS0          	: origin = 0x008000, length = 0x000800
   RAMLS1          	: origin = 0x008800, length = 0x000800
   RAMLS2      		: origin = 0x009000, length = 0x000800
   RAMLS3      		: origin = 0x009800, length = 0x000800
   RAMLS4      		: origin = 0x00A000, length = 0x000800


   BOOTROM          : origin = 0x003F8000, length = 0x00007FC0	//10.15
   SECURE_ROM       : origin = 0x003F2000, length = 0x00006000

   RESET           	: origin = 0x3FFFC0, length = 0x000002

   /* Flash sectors */
   /* BANK 0 */
   FLASH_BANK0_SEC0  : origin = 0x080002, length = 0x000FFE	/* on-chip Flash */
   FLASH_BANK0_SEC1  : origin = 0x081000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC2  : origin = 0x082000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC3  : origin = 0x083000, length = 0x00CFF0	/* on-chip Flash 52K. leave the last 16x16 bits */
//   FLASH_BANK0_SEC4  : origin = 0x084000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC5  : origin = 0x085000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC6  : origin = 0x086000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC7  : origin = 0x087000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC8  : origin = 0x088000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC9  : origin = 0x089000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC10 : origin = 0x08A000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC11 : origin = 0x08B000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC12 : origin = 0x08C000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC13 : origin = 0x08D000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC14 : origin = 0x08E000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK0_SEC15 : origin = 0x08F000, length = 0x001000	/* on-chip Flash */

   /* BANK 1 */
   FLASH_BANK1_SEC0  : origin = 0x090000, length = 0x006000	/* on-chip Flash 24K */
   FLASH_BANK1_RAM_SEC : origin = 0x096000, length = 0x002000	/* on-chip Flash 8K */
//   FLASH_BANK1_SEC1  : origin = 0x091000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK1_SEC2  : origin = 0x092000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK1_SEC3  : origin = 0x093000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK1_SEC4  : origin = 0x094000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK1_SEC5  : origin = 0x095000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK1_SEC6  : origin = 0x096000, length = 0x001000	/* on-chip Flash */
//   FLASH_BANK1_SEC7  : origin = 0x097000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC8  : origin = 0x098000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC9  : origin = 0x099000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC10 : origin = 0x09A000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC11 : origin = 0x09B000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC12 : origin = 0x09C000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC13 : origin = 0x09D000, length = 0x002000	/* on-chip Flash */
   FLASH_BANK1_SEC14 : origin = 0x09F000, length = 0x000FF0	/* on-chip Flash. leave the last 16x16 bits */
//   FLASH_BANK1_SEC15 : origin = 0x09F000, length = 0x001000	/* on-chip Flash */

PAGE 1 :

   BOOT_RSVD       : origin = 0x000002, length = 0x00000126     /* Part of M0, BOOT rom will use this for stack */
   RAMM1           : origin = 0x000400, length = 0x00000400     /* on-chip RAM block M1 */

   RAMLS5      : origin = 0x00A800, length = 0x000800
   RAMLS6      : origin = 0x00B000, length = 0x000800
   RAMLS7      : origin = 0x00B800, length = 0x000800

   RAMGS0      : origin = 0x00C000 length = 0x001000	/* for .stack use   14K */
//   RAMGS1      : origin = 0x00E000, length = 0x001000
   RAMGS2    : origin = 0x00D000, length = 0x002000	/* for .ebss use   10K */
//   RAMGS2      : origin = 0x010000, length = 0x002000
   RAMGS3      : origin = 0x0F000, length = 0x001000


   CLA1_MSGRAMLOW   : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH  : origin = 0x001500, length = 0x000080
}

//--heap_size=0x200     /* defines a 512 heap (.sysmem section)*/

SECTIONS
{
   codestart        : > BEGIN,     PAGE = 0, ALIGN(4)
   .text            : >>FLASH_BANK0_SEC0 | FLASH_BANK0_SEC1 | FLASH_BANK0_SEC2 | FLASH_BANK0_SEC3 | FLASH_BANK1_SEC0,   PAGE = 0, ALIGN(4)
   .cinit           : > FLASH_BANK1_SEC13,     PAGE = 0, ALIGN(4)
   .switch          : > FLASH_BANK1_SEC13,     PAGE = 0, ALIGN(4)
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */
   .stack           : > RAMGS0,    PAGE = 1	/* RAMGS0 | RAMGS1 */

#if defined(__TI_EABI__)
   .init_array      : > FLASH_BANK1_SEC13,      PAGE = 0, ALIGN(4)
   .bss             : > RAMGS2,     PAGE = 1
   .bss:output      : > RAMGS2,     PAGE = 1
   .bss:cio         : > RAMGS2,     PAGE = 1
   .data            : > RAMGS2,     PAGE = 1
   .sysmem          : > RAMM1,      PAGE = 1
   .const           : > FLASH_BANK1_SEC13,    PAGE = 0, ALIGN(4)
#else
   .pinit           : > FLASH_BANK1_SEC12,     PAGE = 0, ALIGN(4)

   .ebss            : > RAMGS2,    PAGE = 1
   .esysmem         : > RAMM1,     PAGE = 1
   .econst          : > FLASH_BANK1_SEC12 | FLASH_BANK1_SEC13,    PAGE = 0, ALIGN(4)
#endif

   ramgs0           : > RAMGS3,    PAGE = 1
   ramgs1           : > RAMGS3,    PAGE = 1	/* not used */


#if defined(__TI_EABI__)
    .TI.ramfunc : {} LOAD = FLASH_BANK1_RAM_SEC,
                         RUN = RAMLS0,
                         LOAD_START(RamfuncsLoadStart),
                         LOAD_SIZE(RamfuncsLoadSize),
                         LOAD_END(RamfuncsLoadEnd),
                         RUN_START(RamfuncsRunStart),
                         RUN_SIZE(RamfuncsRunSize),
                         RUN_END(RamfuncsRunEnd),
                         PAGE = 0, ALIGN(4)
#else
    .TI.ramfunc : {} LOAD = FLASH_BANK1_RAM_SEC,
                         RUN = RAMLS0,
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_SIZE(_RamfuncsLoadSize),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         RUN_SIZE(_RamfuncsRunSize),
                         RUN_END(_RamfuncsRunEnd),
                         PAGE = 0, ALIGN(4)
#endif


#if defined(__TI_EABI__)
    /* CLA specific sections */
    Cla1Prog        : LOAD = FLASH_BANK1_SEC9,
                      RUN = RAMLS1,
                      LOAD_START(Cla1ProgLoadStart),
                      RUN_START(Cla1ProgRunStart),
                      LOAD_SIZE(Cla1ProgLoadSize),
                      PAGE = 0, ALIGN(4)
#else
    /* CLA specific sections */
    Cla1Prog        : LOAD = FLASH_BANK1_SEC9,
                      RUN = RAMLS1,
                      LOAD_START(_Cla1ProgLoadStart),
                      RUN_START(_Cla1ProgRunStart),
                      LOAD_SIZE(_Cla1ProgLoadSize),
                      PAGE = 0, ALIGN(4)
#endif


    Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW,   PAGE = 1
    CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH,  PAGE = 1

   .scratchpad      : > RAMLS2,           PAGE = 0
   .bss_cla         : > RAMLS2,           PAGE = 0

   Cla1DataRam      : > RAMLS4,           PAGE = 0
   cla_shared       : > RAMLS2,           PAGE = 0

#if defined(__TI_EABI__)
   .const_cla      : LOAD = FLASH_BANK1_SEC10,
                      RUN = RAMLS3,
                      RUN_START(Cla1ConstRunStart),
                      LOAD_START(Cla1ConstLoadStart),
                      LOAD_SIZE(Cla1ConstLoadSize),
                      PAGE = 0, ALIGN(4)
#else
   .const_cla      : LOAD = FLASH_BANK1_SEC10,
                      RUN = RAMLS3,
                      RUN_START(_Cla1ConstRunStart),
                      LOAD_START(_Cla1ConstLoadStart),
                      LOAD_SIZE(_Cla1ConstLoadSize),
                      PAGE = 0, ALIGN(4)
#endif
}


/*
//===========================================================================
// End of file.
//===========================================================================
*/
