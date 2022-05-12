#include "Hal_Spi.h"

#define SPI_BUS_NUM (1) // SPI 1

static struct spi_device * etx_spi_device;

struct spi_board_info etx_spi_device_info = 
{
  .modalias     = "spi_driver",
  .max_speed_hz = 50000,       // speed your device (slave) can handle
  .bus_num      = SPI_BUS_NUM,  // SPI 1
  .chip_select  = 0,            // Use 0 Chip select (GPIO 18)
  .mode         = SPI_MODE_0    // SPI mode 0
};

int Hal_SpiInit(void)
{
    int ret;
    struct  spi_master *master;

    master = spi_busnum_to_master( etx_spi_device_info.bus_num );
    if( master == NULL )
    {
        pr_err("SPI Master not found.\n");
        return -1;
    }

    // create a new slave device, given the master and device info
    etx_spi_device = spi_new_device( master, &etx_spi_device_info );
    if( etx_spi_device == NULL ) 
    {
        pr_err("FAILED to create slave.\n");
        return -1;
    }

    // 8-bits in a word
    etx_spi_device->bits_per_word = 8;

    // setup the SPI slave device
    ret = spi_setup( etx_spi_device );
    if( ret )
    {
        pr_err("FAILED to setup slave.\n");
        spi_unregister_device( etx_spi_device );
        return -1;
    }

    pr_info("SPI driver Registered\n");
    return 0;
}
void Hal_SpiDeInit(void)
{
    if( etx_spi_device )
    {
        spi_unregister_device( etx_spi_device ); 
    }
}
void Hal_SpiWrite(uint8_t * TxData, uint8_t * RxData, uint8_t len)
{
    if( etx_spi_device )
    {    
        struct spi_transfer package = 
        {
        .tx_buf  = TxData,
        .rx_buf = RxData,
        .len    = len,
        };

        spi_sync_transfer( etx_spi_device, &package, 1 );
        mdelay(10);
    }
}