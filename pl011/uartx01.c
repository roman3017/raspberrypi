#include "pl011.h"
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

#define UART0_BASE   0x20201000

//------------------------------------------------------------------------
void uart_putc ( unsigned int c )
{
	pl011_putc(c, UART0_BASE);
}
//------------------------------------------------------------------------
unsigned int uart_getc ( void )
{
	return pl011_getchar(UART0_BASE);
}
//------------------------------------------------------------------------
void uart_flush ( void )
{
	pl011_flush(UART0_BASE);
}
//------------------------------------------------------------------------
void uart_init ( void )
{
	pl011_init(UART0_BASE, 3000000, 115200);
}
//------------------------------------------------------------------------
void hexstrings ( unsigned int d )
{
    //unsigned int ra;
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_putc(rc);
        if(rb==0) break;
    }
    uart_putc(0x20);//space
    uart_flush();
}
//------------------------------------------------------------------------
void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_putc(0x0D);//\r
    uart_putc(0x0A);//\n
    uart_flush();
}
//------------------------------------------------------------------------
int notmain ( unsigned int earlypc )
{
    unsigned int ra;

    uart_init();
    hexstring(0x12345678);
    hexstring(earlypc);

    for(ra=0;ra<30;ra++)
        uart_putc(0x30|(ra&7));

    for(ra=0;ra<10;ra++)
        uart_putc(0x55);//U

    //probably a better way to flush the rx fifo.  depending on if and
    //which bootloader you used you might have some stuff show up in the
    //rx fifo.
#if 0
    while(1)
    {
        if(GET32(UART0_FR)&0x10) break;
        GET32(UART0_DR);
    }
#endif
    while(1)
    {
        ra=uart_getc();
        if(ra==0x0D) uart_putc(0x0A);
        uart_putc(ra);
    }


    return(0);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//
// Copyright (c) 2012 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------
