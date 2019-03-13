#ifndef _JPEG_H
#define _JPEG_H

#define ROUND_UP(val, round) ((val+(round)-1)/(round)*(round))

#define BLOCK_WIDTH 8
#define BLOCK_HEIGHT 8
#define WIDTH 48
#define HEIGHT 48
#define BLOCK_SIZE (BLOCK_WIDTH*BLOCK_HEIGHT)

#define MAX_WIDTH ROUND_UP(WIDTH, BLOCK_WIDTH)
#define MAX_HEIGHT ROUND_UP(HEIGHT, BLOCK_HEIGHT)

#define BLOCKS_W (MAX_WIDTH/BLOCK_WIDTH)
#define BLOCKS_H (MAX_HEIGHT/BLOCK_HEIGHT)

#define NBLOCKS (BLOCKS_H*BLOCKS_W)

/*
 * JPEG format parsing markers
 */
#define SOI_MK	0xFFD8		/* start of image	*/
#define APP_MK	0xFFE0		/* custom, up to FFEF */
#define COM_MK	0xFFFE		/* commment segment	*/
#define SOF_MK	0xFFC0		/* start of frame	*/
#define SOS_MK	0xFFDA		/* start of scan	*/
#define DHT_MK	0xFFC4		/* Huffman table	*/
#define DQT_MK	0xFFDB		/* Quant. table		*/
#define DRI_MK	0xFFDD		/* restart interval	*/
#define EOI_MK	0xFFD9		/* end of image		*/
#define MK_MSK	0xFFF0
/* is x a restart interval ? */
#define RST_MK(x)	( (0xFFF8&(x)) == 0xFFD0 )


#define DATA_MAGIC 0xda1a0000

int bloc[6][64] = {{
  1, 2, 3, 4, 5, 6, 7, 8,
  1, 2, 3, 4, 5, 6, 7, 8,
  1, 2, 3, 4, 5, 6, 7, 8,
  1, 2, 3, 4, 5, 6, 7, 8,
  1, 2, 3, 4, 5, 6, 7, 8,
  1, 2, 3, 4, 5, 6, 7, 8,
  1, 2, 3, 4, 5, 6, 7, 8,
  1, 2, 3, 4, 5, 6, 7, 8
},{
  11, 12, 13, 14, 15, 16, 17, 18,
  11, 12, 13, 14, 15, 16, 17, 18,
  11, 12, 13, 14, 15, 16, 17, 18,
  11, 12, 13, 14, 15, 16, 17, 18,
  11, 12, 13, 14, 15, 16, 17, 18,
  11, 12, 13, 14, 15, 16, 17, 18,
  11, 12, 13, 14, 15, 16, 17, 18,
  11, 12, 13, 14, 15, 16, 17, 18
},{
  21, 22, 23, 24, 25, 226, 27, 28,
  21, 22, 23, 24, 25, 226, 27, 28,
  21, 22, 23, 24, 25, 226, 27, 28,
  21, 22, 23, 24, 25, 226, 27, 28,
  21, 22, 23, 24, 25, 226, 27, 28,
  21, 22, 23, 24, 25, 226, 27, 28,
  21, 22, 23, 24, 25, 226, 27, 28,
  21, 22, 23, 24, 25, 226, 27, 28
},{
  31, 32, 33, 34, 35, 36, 37, 38,
  31, 32, 33, 34, 35, 36, 37, 38,
  31, 32, 33, 34, 35, 36, 37, 38,
  31, 32, 33, 34, 35, 36, 37, 38,
  31, 32, 33, 34, 35, 36, 37, 38,
  31, 32, 33, 34, 35, 36, 37, 38,
  31, 32, 33, 34, 35, 36, 37, 38,
  31, 32, 33, 34, 35, 36, 37, 38
},{
  41, 42, 43, 44, 45, 46, 47, 48,
  41, 42, 43, 44, 45, 46, 47, 48,
  41, 42, 43, 44, 45, 46, 47, 48,
  41, 42, 43, 44, 45, 46, 47, 48,
  41, 42, 43, 44, 45, 46, 47, 48,
  41, 42, 43, 44, 45, 46, 47, 48,
  41, 42, 43, 44, 45, 46, 47, 48,
  41, 42, 43, 44, 45, 46, 47, 48
},{
  51, 52, 53, 54, 55, 56, 57, 58,
  51, 52, 53, 54, 55, 56, 57, 58,
  51, 52, 53, 54, 55, 56, 57, 58,
  51, 52, 53, 54, 55, 56, 57, 58,
  51, 52, 53, 54, 55, 56, 57, 58,
  51, 52, 53, 54, 55, 56, 57, 58,
  51, 52, 53, 54, 55, 56, 57, 58,
  51, 52, 53, 54, 55, 56, 57, 58
}
};


int out[64] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

#endif
