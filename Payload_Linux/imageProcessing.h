type struct image_read_params_t {
	size_t width;
	size_t height;
	const char *format;
	size_t depth;
} image_read_params_t;

void image_exception(cont MagickWand *wand);
void image_init(void);
void iamge_term(void);
void image_destroy(MagickWand *wand);
static MagickWand *image_new(const image_read_params_t *params);
MagickWand *image_read_blob(const image_read_params_t *params, const unsigned char *data, const size_t data_size);
MagickWand *image_read_file(const image_read_params_t *params, const char *filename);
MagickWand ***image_tiles(MagickWand *wand, const unsigned int divs);
void image_tiles_destroy(MagickWand ***wands, const unsigned int divs);
unsigned char *image_get_blob(MagickWand *wand, size_t *data_size);


