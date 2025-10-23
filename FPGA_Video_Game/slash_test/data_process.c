#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer.h"
#include "altera_avalon_timer_regs.h"
#include "altera_up_avalon_accelerometer_spi.h"
#include "sys/alt_irq.h"
#include "system.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "altera_avalon_uart_regs.h"
#include "altera_avalon_uart.h"
#include "altera_avalon_jtag_uart_regs.h"
#include "altera_avalon_jtag_uart.h"

#define NUM_TAPS 5
#define Q 16
#define EXPONENT (1 << Q)
#define CHARLIM 256 // Maximum character length for user input
#define OFFSET -32
#define PWM_PERIOD 16


void
send_xyz_data (alt_32 x, alt_32 y, alt_32 z)
{
  char buffer[100];
  int length = snprintf(buffer, sizeof(buffer), "X: %ld, Y: %ld, Z: %ld\n", (long)x, (long)y, (long)z);

  for (int i = 0; i < length; i++)
    {
      while (!(IORD_ALTERA_AVALON_JTAG_UART_CONTROL(JTAG_UART_BASE) & ALTERA_AVALON_JTAG_UART_CONTROL_WSPACE_MSK))
        {
          // Wait for JTAG UART to be ready to transmit
        }
      IOWR_ALTERA_AVALON_JTAG_UART_DATA(JTAG_UART_BASE, buffer[i]);
    }
}

int
main ()
{
  alt_32 x_read, y_read, z_read;
  alt_up_accelerometer_spi_dev *acc_dev;

  acc_dev = alt_up_accelerometer_spi_open_dev ("/dev/accelerometer_spi");
  if (acc_dev == NULL)
    {
      printf ("Error: Could not open accelerometer device.\n");
      return 1;
    }

  while (1)
    {
      alt_up_accelerometer_spi_read_x_axis (acc_dev, &x_read);
      alt_up_accelerometer_spi_read_y_axis (acc_dev, &y_read);
      alt_up_accelerometer_spi_read_z_axis (acc_dev, &z_read);

      send_xyz_data (x_read, y_read, z_read);
    }

  return 0;
}