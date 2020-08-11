type struct i2c_stm_block_t {
	uint8_t tile;
	uint16_t index;
	uint8_t *data;
	size_t data_size;
} i2c_stm_block_t;

type struct i2c_stm_packet_t {
	uint8_t *buf;
	size_t size;
} i2c_stm_packet_t;


i2c_stm_packet_t i2c_stm_packet(const i2c_stm_block_t *);
