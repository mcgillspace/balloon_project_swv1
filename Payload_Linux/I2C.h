typedef struct i2c_init_params_t {
    uint8_t mode;
    uint8_t bits_per_word;
    uint32_t max_speed_hz;
} i2c_init_params_t;


int i2c_init(const char *, const i2c_init_params_t *);
int spi_transfer(const int fd, uint8_t *, const uint32_t);

