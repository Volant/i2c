__stack = ORIGIN(RAM) + LENGTH(RAM);

_estack = __stack;  /* STM specific definition */

MEMORY
{
       	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 0x020000
       	RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 0x020000
}

/*       	SRAM (rx)  : ORIGIN = 0x20020000, LENGTH = 0x020000 */

ENTRY(_start)

SECTIONS
{
    . = 0x0;
 
    /* the program code is stored in the .text section, which goes to Flash */
    .text :
    {
		. = ALIGN(4);
       
        *(.vectors)
        *(.isr_vector)
        *(.text)                   /* remaining code */
        *(.text.*)                   /* remaining code */
        *(.rodata)                 /* read-only data (constants) */
        *(.rodata*)
 
        . = ALIGN(4);
     	_etext = .;
     	_sidata = _etext;
    } >FLASH


    .data : AT(ADDR(.text) + SIZEOF(.text))
    {
        . = ALIGN(4);
        _sdata = . ;
       
        *(.data)
        *(.data.*)
 
        . = ALIGN(4);
	     _edata = . ;
    } >RAM
 

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
       
        *(.bss)
        *(COMMON)
       
        . = ALIGN(4);
	     _ebss = . ;
    } >RAM
}
