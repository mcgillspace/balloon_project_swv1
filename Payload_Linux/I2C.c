
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>



int i2c_init(const char *device, const i2c_init_params_t *params)
{
    int fd;

    /* Open I2C device */
    fd = open(device, O_RDWR);
    //If it fails to open the device
    if (fd == -1) {
        return -1;
    }

    /* Set mode */
    if (ioctl(fd, I2C_IOC_WR_MODE, &params->mode) == -1) {
        return -1;
    }

    /* Set bits per word */
    if (ioctl(fd, I2C_IOC_WR_BITS_PER_WORD, &params->bits_per_word) == -1) {
        return -1;
    }

    /* Set maximum speed in Hz  */
    if (ioctl(fd, I2C_IOC_WR_MAX_SPEED_HZ, &params->max_speed_hz) == -1) {
        perror("Unable to set SPI maximum speed");
        return -1;
    }

    return fd;
}


int i2c_transfer(const int fd, uint8_t *buf, const uint32_t buf_siz)
{
    struct ioc_transfer transfer;

    memset(&transfer, 0, sizeof(transfer));

    transfer.tx_buf = (__u64) buf;
    transfer.rx_buf = (__u64) buf;
    transfer.len = buf_siz;

    if (ioctl(fd, i2c_IOC_MESSAGE(1), &transfer) == -1) {
        return -1;
    }

    return 0;
}

