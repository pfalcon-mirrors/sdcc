// #define MICROCONTROLLER_8051
#include <mcs51reg.h>

unsigned char
_sdcc_external_startup (void)
{
  /* copied from device/examples/mcs51/simple2/hi.c */
  PCON = 0x80;  /* power control byte, set SMOD bit for serial port */
  SCON = 0x00;  /* serial control byte, mode 0, RI _NOT_ active */
  TMOD = 0x21;  /* timer control mode, byte operation */
  TCON = 0;     /* timer control register, byte operation */

  TH1  = 0xFF;  /* serial reload value, 57,600 baud at 11.0592 MHz */
  TL1  = 0xFF;  /* reload asap */
  TR1  = 1;     /* start serial timer */

  TI   = 1;     /* enable transmission of first byte */
  return 0;
}

void
_putchar (char c)
{
  while (!TI)
    ;
  TI = 0;
  SBUF = c;
}

void
_initEmu (void)
{
}

void
_exitEmu (void)
{
  while (!TI) /* wait for the last character to be transmitted */
    ;         /* before hitting the breakpoint */
  * (char idata *) 0 = * (char xdata *) 0x7654;
}
