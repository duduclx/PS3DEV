/*******************************************************************************************
  Font name: Bitstream Vera Sans Mono
  Font width: 7 (monospaced font)
  Font height: 13
  Encode: ANSI+

  Data length: 8 bits
  Data format: Big Endian, Row based, Row preferred, Packed
 *******************************************************************************************/

/*******************************************************************************************
  Data table provides the bitmap data of each character.

  To get the starting data offset of character 'A', you can use the following expression:

     const unsigned char index = index_table['A'];
     const unsigned int offset = offset_table[index];
     const unsigned char *pData = data_table[offset];

 *******************************************************************************************/
const unsigned char BitStreamVeraSansMono8Width = 7;
const unsigned int BitStreamVeraSansMono8Offset = 12;
const unsigned short BitStreamVeraSansMono8DataLength = 8;//bits
const unsigned short BitStreamVeraSansMono8CharHeight = 13;
const unsigned char BitStreamVeraSansMono8Data_table[] = {

/* character 0x0020 (' '): (width=7, offset=0) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x0021 ('!'): (width=7, offset=12) */
0x00, 0x00, 0x40, 0x81, 0x02, 0x04, 0x08, 0x00, 
0x20, 0x00, 0x00, 0x00, 

/* character 0x0022 ('"'): (width=7, offset=24) */
0x00, 0x00, 0xA1, 0x42, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x0023 ('#'): (width=7, offset=36) */
0x00, 0x00, 0x51, 0x27, 0xE5, 0x0A, 0x7E, 0x48, 
0xA0, 0x00, 0x00, 0x00, 

/* character 0x0024 ('$'): (width=7, offset=48) */
0x00, 0x00, 0x41, 0xE5, 0x0A, 0x0E, 0x0A, 0x14, 
0xF0, 0x40, 0x80, 0x00, 

/* character 0x0025 ('%'): (width=7, offset=60) */
0x00, 0x03, 0x85, 0x0E, 0x43, 0x08, 0x6E, 0x14, 
0x38, 0x00, 0x00, 0x00, 

/* character 0x0026 ('&'): (width=7, offset=72) */
0x00, 0x00, 0xE1, 0x02, 0x06, 0x16, 0xA5, 0x44, 
0x7C, 0x00, 0x00, 0x00, 

/* character 0x0027 ('''): (width=7, offset=84) */
0x00, 0x00, 0x40, 0x81, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x0028 ('('): (width=7, offset=96) */
0x00, 0x20, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20, 
0x40, 0x40, 0x00, 0x00, 

/* character 0x0029 (')'): (width=7, offset=108) */
0x00, 0x40, 0x80, 0x81, 0x02, 0x04, 0x08, 0x10, 
0x40, 0x80, 0x00, 0x00, 

/* character 0x002A ('*'): (width=7, offset=120) */
0x00, 0x00, 0x42, 0xA3, 0x87, 0x15, 0x08, 0x00, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x002B ('+'): (width=7, offset=132) */
0x00, 0x00, 0x00, 0x01, 0x02, 0x1F, 0x08, 0x10, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x002C (','): (width=7, offset=144) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
0x20, 0x80, 0x00, 0x00, 

/* character 0x002D ('-'): (width=7, offset=156) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x002E ('.'): (width=7, offset=168) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
0x20, 0x00, 0x00, 0x00, 

/* character 0x002F ('/'): (width=7, offset=180) */
0x00, 0x00, 0x10, 0x40, 0x82, 0x04, 0x08, 0x20, 
0x41, 0x00, 0x00, 0x00, 

/* character 0x0030 ('0'): (width=7, offset=192) */
0x00, 0x00, 0xF3, 0x34, 0x29, 0x50, 0xA1, 0x66, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0031 ('1'): (width=7, offset=204) */
0x00, 0x01, 0xC0, 0x81, 0x02, 0x04, 0x08, 0x10, 
0xF8, 0x00, 0x00, 0x00, 

/* character 0x0032 ('2'): (width=7, offset=216) */
0x00, 0x00, 0xF2, 0x10, 0x20, 0xC3, 0x0C, 0x20, 
0xFC, 0x00, 0x00, 0x00, 

/* character 0x0033 ('3'): (width=7, offset=228) */
0x00, 0x00, 0xF2, 0x10, 0x27, 0x81, 0x81, 0x42, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0034 ('4'): (width=7, offset=240) */
0x00, 0x00, 0x30, 0x61, 0x44, 0x99, 0x3F, 0x04, 
0x08, 0x00, 0x00, 0x00, 

/* character 0x0035 ('5'): (width=7, offset=252) */
0x00, 0x01, 0xF2, 0x04, 0x0F, 0x81, 0x81, 0x02, 
0xF8, 0x00, 0x00, 0x00, 

/* character 0x0036 ('6'): (width=7, offset=264) */
0x00, 0x00, 0x79, 0x04, 0x0B, 0x98, 0xA1, 0x42, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0037 ('7'): (width=7, offset=276) */
0x00, 0x01, 0xF8, 0x20, 0x41, 0x02, 0x08, 0x10, 
0x40, 0x00, 0x00, 0x00, 

/* character 0x0038 ('8'): (width=7, offset=288) */
0x00, 0x00, 0xF2, 0x14, 0x27, 0x90, 0xA1, 0x42, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0039 ('9'): (width=7, offset=300) */
0x00, 0x00, 0xF2, 0x14, 0x28, 0x4F, 0x81, 0x04, 
0xF0, 0x00, 0x00, 0x00, 

/* character 0x003A (':'): (width=7, offset=312) */
0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x10, 
0x20, 0x00, 0x00, 0x00, 

/* character 0x003B (';'): (width=7, offset=324) */
0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x10, 
0x20, 0x80, 0x00, 0x00, 

/* character 0x003C ('<'): (width=7, offset=336) */
0x00, 0x00, 0x00, 0x00, 0x23, 0x98, 0x0C, 0x06, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x003D ('='): (width=7, offset=348) */
0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x7E, 0x00, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x003E ('>'): (width=7, offset=360) */
0x00, 0x00, 0x00, 0x04, 0x07, 0x01, 0x8C, 0x60, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x003F ('?'): (width=7, offset=372) */
0x00, 0x00, 0xF0, 0x20, 0xC3, 0x04, 0x08, 0x00, 
0x20, 0x00, 0x00, 0x00, 

/* character 0x0040 ('@'): (width=7, offset=384) */
0x00, 0x00, 0x71, 0x34, 0x29, 0xD4, 0xA9, 0x4E, 
0xC0, 0x80, 0xE0, 0x00, 

/* character 0x0041 ('A'): (width=7, offset=396) */
0x00, 0x00, 0x60, 0xC1, 0x84, 0x89, 0x1E, 0x42, 
0x84, 0x00, 0x00, 0x00, 

/* character 0x0042 ('B'): (width=7, offset=408) */
0x00, 0x01, 0xF2, 0x14, 0x2F, 0x90, 0xA1, 0x42, 
0xF8, 0x00, 0x00, 0x00, 

/* character 0x0043 ('C'): (width=7, offset=420) */
0x00, 0x00, 0x71, 0x14, 0x08, 0x10, 0x20, 0x22, 
0x38, 0x00, 0x00, 0x00, 

/* character 0x0044 ('D'): (width=7, offset=432) */
0x00, 0x01, 0xE2, 0x24, 0x28, 0x50, 0xA1, 0x44, 
0xF0, 0x00, 0x00, 0x00, 

/* character 0x0045 ('E'): (width=7, offset=444) */
0x00, 0x01, 0xFA, 0x04, 0x0F, 0xD0, 0x20, 0x40, 
0xFC, 0x00, 0x00, 0x00, 

/* character 0x0046 ('F'): (width=7, offset=456) */
0x00, 0x01, 0xFA, 0x04, 0x0F, 0xD0, 0x20, 0x40, 
0x80, 0x00, 0x00, 0x00, 

/* character 0x0047 ('G'): (width=7, offset=468) */
0x00, 0x00, 0x71, 0x14, 0x08, 0x11, 0xA1, 0x22, 
0x38, 0x00, 0x00, 0x00, 

/* character 0x0048 ('H'): (width=7, offset=480) */
0x00, 0x01, 0x0A, 0x14, 0x2F, 0xD0, 0xA1, 0x42, 
0x84, 0x00, 0x00, 0x00, 

/* character 0x0049 ('I'): (width=7, offset=492) */
0x00, 0x01, 0xF0, 0x81, 0x02, 0x04, 0x08, 0x10, 
0xF8, 0x00, 0x00, 0x00, 

/* character 0x004A ('J'): (width=7, offset=504) */
0x00, 0x00, 0x70, 0x20, 0x40, 0x81, 0x02, 0x44, 
0x70, 0x00, 0x00, 0x00, 

/* character 0x004B ('K'): (width=7, offset=516) */
0x00, 0x01, 0x12, 0x45, 0x0C, 0x14, 0x24, 0x44, 
0x84, 0x00, 0x00, 0x00, 

/* character 0x004C ('L'): (width=7, offset=528) */
0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 
0xFC, 0x00, 0x00, 0x00, 

/* character 0x004D ('M'): (width=7, offset=540) */
0x00, 0x01, 0x0B, 0x36, 0x6B, 0x56, 0xA1, 0x42, 
0x84, 0x00, 0x00, 0x00, 

/* character 0x004E ('N'): (width=7, offset=552) */
0x00, 0x01, 0x0B, 0x15, 0x2A, 0x52, 0xA5, 0x46, 
0x84, 0x00, 0x00, 0x00, 

/* character 0x004F ('O'): (width=7, offset=564) */
0x00, 0x00, 0xF3, 0x34, 0x28, 0x50, 0xA1, 0x66, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0050 ('P'): (width=7, offset=576) */
0x00, 0x01, 0xF2, 0x14, 0x28, 0x5F, 0x20, 0x40, 
0x80, 0x00, 0x00, 0x00, 

/* character 0x0051 ('Q'): (width=7, offset=588) */
0x00, 0x00, 0xF3, 0x34, 0x28, 0x50, 0xA1, 0x66, 
0x78, 0x18, 0x00, 0x00, 

/* character 0x0052 ('R'): (width=7, offset=600) */
0x00, 0x01, 0xF2, 0x14, 0x28, 0x5F, 0x22, 0x42, 
0x80, 0x00, 0x00, 0x00, 

/* character 0x0053 ('S'): (width=7, offset=612) */
0x00, 0x00, 0xF2, 0x14, 0x0F, 0x01, 0x81, 0x42, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0054 ('T'): (width=7, offset=624) */
0x00, 0x03, 0xF8, 0x81, 0x02, 0x04, 0x08, 0x10, 
0x20, 0x00, 0x00, 0x00, 

/* character 0x0055 ('U'): (width=7, offset=636) */
0x00, 0x01, 0x0A, 0x14, 0x28, 0x50, 0xA1, 0x42, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0056 ('V'): (width=7, offset=648) */
0x00, 0x01, 0x0A, 0x12, 0x44, 0x89, 0x0C, 0x18, 
0x30, 0x00, 0x00, 0x00, 

/* character 0x0057 ('W'): (width=7, offset=660) */
0x00, 0x02, 0x0C, 0x99, 0x35, 0x5B, 0x36, 0x44, 
0x88, 0x00, 0x00, 0x00, 

/* character 0x0058 ('X'): (width=7, offset=672) */
0x00, 0x01, 0x09, 0x22, 0x43, 0x06, 0x12, 0x24, 
0x84, 0x00, 0x00, 0x00, 

/* character 0x0059 ('Y'): (width=7, offset=684) */
0x00, 0x03, 0x1A, 0x22, 0x87, 0x04, 0x08, 0x10, 
0x20, 0x00, 0x00, 0x00, 

/* character 0x005A ('Z'): (width=7, offset=696) */
0x00, 0x01, 0xF8, 0x20, 0x41, 0x04, 0x18, 0x20, 
0xFC, 0x00, 0x00, 0x00, 

/* character 0x005B ('['): (width=7, offset=708) */
0x00, 0x60, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20, 
0x40, 0xC0, 0x00, 0x00, 

/* character 0x005C ('\'): (width=7, offset=720) */
0x00, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x08, 
0x10, 0x10, 0x00, 0x00, 

/* character 0x005D (']'): (width=7, offset=732) */
0x00, 0x60, 0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 
0x20, 0xC0, 0x00, 0x00, 

/* character 0x005E ('^'): (width=7, offset=744) */
0x00, 0x00, 0xC2, 0x48, 0x40, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x005F ('_'): (width=7, offset=756) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x0F, 0xC0, 

/* character 0x0060 ('`'): (width=7, offset=768) */
0x00, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x0061 ('a'): (width=7, offset=780) */
0x00, 0x00, 0x00, 0x07, 0x80, 0x8F, 0x22, 0x44, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0062 ('b'): (width=7, offset=792) */
0x00, 0x81, 0x02, 0x07, 0x88, 0x91, 0x22, 0x44, 
0xF0, 0x00, 0x00, 0x00, 

/* character 0x0063 ('c'): (width=7, offset=804) */
0x00, 0x00, 0x00, 0x03, 0xCC, 0x10, 0x20, 0x60, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0064 ('d'): (width=7, offset=816) */
0x00, 0x08, 0x10, 0x23, 0xC8, 0x91, 0x22, 0x44, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0065 ('e'): (width=7, offset=828) */
0x00, 0x00, 0x00, 0x03, 0x88, 0x9F, 0x20, 0x40, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0066 ('f'): (width=7, offset=840) */
0x00, 0x18, 0x40, 0x87, 0xC2, 0x04, 0x08, 0x10, 
0x20, 0x00, 0x00, 0x00, 

/* character 0x0067 ('g'): (width=7, offset=852) */
0x00, 0x00, 0x00, 0x03, 0xC8, 0x91, 0x22, 0x44, 
0x78, 0x11, 0xC0, 0x00, 

/* character 0x0068 ('h'): (width=7, offset=864) */
0x00, 0x81, 0x02, 0x05, 0x8C, 0x91, 0x22, 0x44, 
0x88, 0x00, 0x00, 0x00, 

/* character 0x0069 ('i'): (width=7, offset=876) */
0x00, 0x20, 0x00, 0x07, 0x02, 0x04, 0x08, 0x10, 
0xF8, 0x00, 0x00, 0x00, 

/* character 0x006A ('j'): (width=7, offset=888) */
0x00, 0x20, 0x00, 0x07, 0x02, 0x04, 0x08, 0x10, 
0x20, 0x43, 0x00, 0x00, 

/* character 0x006B ('k'): (width=7, offset=900) */
0x00, 0x81, 0x02, 0x04, 0x8A, 0x18, 0x28, 0x48, 
0x88, 0x00, 0x00, 0x00, 

/* character 0x006C ('l'): (width=7, offset=912) */
0x01, 0xC0, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20, 
0x30, 0x00, 0x00, 0x00, 

/* character 0x006D ('m'): (width=7, offset=924) */
0x00, 0x00, 0x00, 0x07, 0xCA, 0x95, 0x2A, 0x54, 
0xA8, 0x00, 0x00, 0x00, 

/* character 0x006E ('n'): (width=7, offset=936) */
0x00, 0x00, 0x00, 0x05, 0x8C, 0x91, 0x22, 0x44, 
0x88, 0x00, 0x00, 0x00, 

/* character 0x006F ('o'): (width=7, offset=948) */
0x00, 0x00, 0x00, 0x03, 0x88, 0x91, 0x22, 0x44, 
0x70, 0x00, 0x00, 0x00, 

/* character 0x0070 ('p'): (width=7, offset=960) */
0x00, 0x00, 0x00, 0x07, 0x88, 0x91, 0x22, 0x44, 
0xF1, 0x02, 0x00, 0x00, 

/* character 0x0071 ('q'): (width=7, offset=972) */
0x00, 0x00, 0x00, 0x03, 0xC8, 0x91, 0x22, 0x44, 
0x78, 0x10, 0x20, 0x00, 

/* character 0x0072 ('r'): (width=7, offset=984) */
0x00, 0x00, 0x00, 0x03, 0xC4, 0x88, 0x10, 0x20, 
0x40, 0x00, 0x00, 0x00, 

/* character 0x0073 ('s'): (width=7, offset=996) */
0x00, 0x00, 0x00, 0x03, 0xC8, 0x1C, 0x06, 0x04, 
0xF0, 0x00, 0x00, 0x00, 

/* character 0x0074 ('t'): (width=7, offset=1008) */
0x00, 0x00, 0x81, 0x0F, 0x84, 0x08, 0x10, 0x20, 
0x70, 0x00, 0x00, 0x00, 

/* character 0x0075 ('u'): (width=7, offset=1020) */
0x00, 0x00, 0x00, 0x04, 0x48, 0x91, 0x22, 0x44, 
0x78, 0x00, 0x00, 0x00, 

/* character 0x0076 ('v'): (width=7, offset=1032) */
0x00, 0x00, 0x00, 0x04, 0x48, 0x8A, 0x14, 0x28, 
0x20, 0x00, 0x00, 0x00, 

/* character 0x0077 ('w'): (width=7, offset=1044) */
0x00, 0x00, 0x00, 0x08, 0x30, 0x55, 0x2A, 0x28, 
0x50, 0x00, 0x00, 0x00, 

/* character 0x0078 ('x'): (width=7, offset=1056) */
0x00, 0x00, 0x00, 0x06, 0xC5, 0x04, 0x08, 0x28, 
0xD8, 0x00, 0x00, 0x00, 

/* character 0x0079 ('y'): (width=7, offset=1068) */
0x00, 0x00, 0x00, 0x04, 0x49, 0x0A, 0x14, 0x30, 
0x20, 0x83, 0x00, 0x00, 

/* character 0x007A ('z'): (width=7, offset=1080) */
0x00, 0x00, 0x00, 0x07, 0xC1, 0x06, 0x18, 0x20, 
0xF8, 0x00, 0x00, 0x00, 

/* character 0x007B ('{'): (width=7, offset=1092) */
0x00, 0x38, 0x40, 0x81, 0x0C, 0x04, 0x08, 0x10, 
0x20, 0x70, 0x00, 0x00, 

/* character 0x007C ('|'): (width=7, offset=1104) */
0x00, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 
0x20, 0x40, 0x80, 0x00, 

/* character 0x007D ('}'): (width=7, offset=1116) */
0x00, 0xE0, 0x40, 0x81, 0x01, 0x84, 0x08, 0x10, 
0x21, 0xC0, 0x00, 0x00, 

/* character 0x007E ('~'): (width=7, offset=1128) */
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x07, 0x00, 
0x00, 0x00, 0x00, 0x00, 

/* character 0x007F (''): (width=7, offset=1140) */
0x00, 0x00, 0x07, 0x0A, 0x14, 0x28, 0x50, 0xA1, 
0x43, 0x80, 0x00, 0x00, 

};

/*******************************************************************************************
  The offset talbe is skipped.

  This is a monospaced font, the bitmap data size of each character is the same.
  You can calculate the offset of each character easily.

  For example:

  To get the starting offset of character 'A', you can use the following expression:

     const unsigned char index = index_table['A'];
     const unsigned int offset = index * sizeGlyph;
                                 (here sizeGlyph is the data size of single character)
 *******************************************************************************************/


/*******************************************************************************************
  Index table is used to find the mapping index of a character.

  If you can find a simple mathematical expression for index mapping, you can use that.
  If you do not have such a mathematical expression, this index table is just for you.

  To get the index of character 'A', you can use the following expression:

     const unsigned char index = index_table['A'];

 *******************************************************************************************/
const unsigned char BitStreamVeraSansMono8Index_table[] = {
/*		index   hexcode   decimal  char */
/*		=====   =======   =======  ==== */
  		  0, /*   00          0     .   */
  		  0, /*   01          1     .   */
  		  0, /*   02          2     .   */
  		  0, /*   03          3     .   */
  		  0, /*   04          4     .   */
  		  0, /*   05          5     .   */
  		  0, /*   06          6     .   */
  		  0, /*   07          7     .   */
  		  0, /*   08          8     .   */
  		  0, /*   09          9     .   */
  		  0, /*   0A         10     .   */
  		  0, /*   0B         11     .   */
  		  0, /*   0C         12     .   */
  		  0, /*   0D         13     .   */
  		  0, /*   0E         14     .   */
  		  0, /*   0F         15     .   */
  		  0, /*   10         16     .   */
  		  0, /*   11         17     .   */
  		  0, /*   12         18     .   */
  		  0, /*   13         19     .   */
  		  0, /*   14         20     .   */
  		  0, /*   15         21     .   */
  		  0, /*   16         22     .   */
  		  0, /*   17         23     .   */
  		  0, /*   18         24     .   */
  		  0, /*   19         25     .   */
  		  0, /*   1A         26     .   */
  		  0, /*   1B         27     .   */
  		  0, /*   1C         28     .   */
  		  0, /*   1D         29     .   */
  		  0, /*   1E         30     .   */
  		  0, /*   1F         31     .   */
  		  0, /*   20         32         */
  		  1, /*   21         33     !   */
  		  2, /*   22         34     "   */
  		  3, /*   23         35     #   */
  		  4, /*   24         36     $   */
  		  5, /*   25         37     %   */
  		  6, /*   26         38     &   */
  		  7, /*   27         39     '   */
  		  8, /*   28         40     (   */
  		  9, /*   29         41     )   */
  		 10, /*   2A         42     *   */
  		 11, /*   2B         43     +   */
  		 12, /*   2C         44     ,   */
  		 13, /*   2D         45     -   */
  		 14, /*   2E         46     .   */
  		 15, /*   2F         47     /   */
  		 16, /*   30         48     0   */
  		 17, /*   31         49     1   */
  		 18, /*   32         50     2   */
  		 19, /*   33         51     3   */
  		 20, /*   34         52     4   */
  		 21, /*   35         53     5   */
  		 22, /*   36         54     6   */
  		 23, /*   37         55     7   */
  		 24, /*   38         56     8   */
  		 25, /*   39         57     9   */
  		 26, /*   3A         58     :   */
  		 27, /*   3B         59     ;   */
  		 28, /*   3C         60     <   */
  		 29, /*   3D         61     =   */
  		 30, /*   3E         62     >   */
  		 31, /*   3F         63     ?   */
  		 32, /*   40         64     @   */
  		 33, /*   41         65     A   */
  		 34, /*   42         66     B   */
  		 35, /*   43         67     C   */
  		 36, /*   44         68     D   */
  		 37, /*   45         69     E   */
  		 38, /*   46         70     F   */
  		 39, /*   47         71     G   */
  		 40, /*   48         72     H   */
  		 41, /*   49         73     I   */
  		 42, /*   4A         74     J   */
  		 43, /*   4B         75     K   */
  		 44, /*   4C         76     L   */
  		 45, /*   4D         77     M   */
  		 46, /*   4E         78     N   */
  		 47, /*   4F         79     O   */
  		 48, /*   50         80     P   */
  		 49, /*   51         81     Q   */
  		 50, /*   52         82     R   */
  		 51, /*   53         83     S   */
  		 52, /*   54         84     T   */
  		 53, /*   55         85     U   */
  		 54, /*   56         86     V   */
  		 55, /*   57         87     W   */
  		 56, /*   58         88     X   */
  		 57, /*   59         89     Y   */
  		 58, /*   5A         90     Z   */
  		 59, /*   5B         91     [   */
  		 60, /*   5C         92     \   */
  		 61, /*   5D         93     ]   */
  		 62, /*   5E         94     ^   */
  		 63, /*   5F         95     _   */
  		 64, /*   60         96     `   */
  		 65, /*   61         97     a   */
  		 66, /*   62         98     b   */
  		 67, /*   63         99     c   */
  		 68, /*   64        100     d   */
  		 69, /*   65        101     e   */
  		 70, /*   66        102     f   */
  		 71, /*   67        103     g   */
  		 72, /*   68        104     h   */
  		 73, /*   69        105     i   */
  		 74, /*   6A        106     j   */
  		 75, /*   6B        107     k   */
  		 76, /*   6C        108     l   */
  		 77, /*   6D        109     m   */
  		 78, /*   6E        110     n   */
  		 79, /*   6F        111     o   */
  		 80, /*   70        112     p   */
  		 81, /*   71        113     q   */
  		 82, /*   72        114     r   */
  		 83, /*   73        115     s   */
  		 84, /*   74        116     t   */
  		 85, /*   75        117     u   */
  		 86, /*   76        118     v   */
  		 87, /*   77        119     w   */
  		 88, /*   78        120     x   */
  		 89, /*   79        121     y   */
  		 90, /*   7A        122     z   */
  		 91, /*   7B        123     {   */
  		 92, /*   7C        124     |   */
  		 93, /*   7D        125     }   */
  		 94, /*   7E        126     ~   */
  		 95, /*   7F        127        */
  		  0, /*   80        128   ? */
  		  0, /*   81        129   Å */
  		  0, /*   82        130   ? */
  		  0, /*   83        131   ? */
  		  0, /*   84        132   ? */
  		  0, /*   85        133   ? */
  		  0, /*   86        134   ? */
  		  0, /*   87        135   ? */
  		  0, /*   88        136   ? */
  		  0, /*   89        137   ? */
  		  0, /*   8A        138   ? */
  		  0, /*   8B        139   ? */
  		  0, /*   8C        140   ? */
  		  0, /*   8D        141   ç */
  		  0, /*   8E        142   ? */
  		  0, /*   8F        143   è */
  		  0, /*   90        144   ê */
  		  0, /*   91        145   ? */
  		  0, /*   92        146   ? */
  		  0, /*   93        147   ? */
  		  0, /*   94        148   ? */
  		  0, /*   95        149   ? */
  		  0, /*   96        150   ? */
  		  0, /*   97        151   ? */
  		  0, /*   98        152   ? */
  		  0, /*   99        153   ? */
  		  0, /*   9A        154   ? */
  		  0, /*   9B        155   ? */
  		  0, /*   9C        156   ? */
  		  0, /*   9D        157   ù */
  		  0, /*   9E        158   ? */
  		  0, /*   9F        159   ? */
  		  0, /*   A0        160   † */
  		  0, /*   A1        161   ° */
  		  0, /*   A2        162   ¢ */
  		  0, /*   A3        163   £ */
  		  0, /*   A4        164   § */
  		  0, /*   A5        165   • */
  		  0, /*   A6        166   ¶ */
  		  0, /*   A7        167   ß */
  		  0, /*   A8        168   ® */
  		  0, /*   A9        169   © */
  		  0, /*   AA        170   ™ */
  		  0, /*   AB        171   ´ */
  		  0, /*   AC        172   ¨ */
  		  0, /*   AD        173   ≠ */
  		  0, /*   AE        174   Æ */
  		  0, /*   AF        175   Ø */
  		  0, /*   B0        176   ∞ */
  		  0, /*   B1        177   ± */
  		  0, /*   B2        178   ≤ */
  		  0, /*   B3        179   ≥ */
  		  0, /*   B4        180   ¥ */
  		  0, /*   B5        181   µ */
  		  0, /*   B6        182   ∂ */
  		  0, /*   B7        183   ∑ */
  		  0, /*   B8        184   ∏ */
  		  0, /*   B9        185   π */
  		  0, /*   BA        186   ∫ */
  		  0, /*   BB        187   ª */
  		  0, /*   BC        188   º */
  		  0, /*   BD        189   Ω */
  		  0, /*   BE        190   æ */
  		  0, /*   BF        191   ø */
  		  0, /*   C0        192   ¿ */
  		  0, /*   C1        193   ¡ */
  		  0, /*   C2        194   ¬ */
  		  0, /*   C3        195   √ */
  		  0, /*   C4        196   ƒ */
  		  0, /*   C5        197   ≈ */
  		  0, /*   C6        198   ∆ */
  		  0, /*   C7        199   « */
  		  0, /*   C8        200   » */
  		  0, /*   C9        201   … */
  		  0, /*   CA        202     */
  		  0, /*   CB        203   À */
  		  0, /*   CC        204   Ã */
  		  0, /*   CD        205   Õ */
  		  0, /*   CE        206   Œ */
  		  0, /*   CF        207   œ */
  		  0, /*   D0        208   – */
  		  0, /*   D1        209   — */
  		  0, /*   D2        210   “ */
  		  0, /*   D3        211   ” */
  		  0, /*   D4        212   ‘ */
  		  0, /*   D5        213   ’ */
  		  0, /*   D6        214   ÷ */
  		  0, /*   D7        215   ◊ */
  		  0, /*   D8        216   ÿ */
  		  0, /*   D9        217   Ÿ */
  		  0, /*   DA        218   ⁄ */
  		  0, /*   DB        219   € */
  		  0, /*   DC        220   ‹ */
  		  0, /*   DD        221   › */
  		  0, /*   DE        222   ﬁ */
  		  0, /*   DF        223   ﬂ */
  		  0, /*   E0        224   ‡ */
  		  0, /*   E1        225   · */
  		  0, /*   E2        226   ‚ */
  		  0, /*   E3        227   „ */
  		  0, /*   E4        228   ‰ */
  		  0, /*   E5        229   Â */
  		  0, /*   E6        230   Ê */
  		  0, /*   E7        231   Á */
  		  0, /*   E8        232   Ë */
  		  0, /*   E9        233   È */
  		  0, /*   EA        234   Í */
  		  0, /*   EB        235   Î */
  		  0, /*   EC        236   Ï */
  		  0, /*   ED        237   Ì */
  		  0, /*   EE        238   Ó */
  		  0, /*   EF        239   Ô */
  		  0, /*   F0        240    */
  		  0, /*   F1        241   Ò */
  		  0, /*   F2        242   Ú */
  		  0, /*   F3        243   Û */
  		  0, /*   F4        244   Ù */
  		  0, /*   F5        245   ı */
  		  0, /*   F6        246   ˆ */
  		  0, /*   F7        247   ˜ */
  		  0, /*   F8        248   ¯ */
  		  0, /*   F9        249   ˘ */
  		  0, /*   FA        250   ˙ */
  		  0, /*   FB        251   ˚ */
  		  0, /*   FC        252   ¸ */
  		  0, /*   FD        253   ˝ */
  		  0, /*   FE        254   ˛ */
  		  0, /*   FF        255   ˇ */
};

const unsigned char BitStreamVeraSansMono8Width_table[] = {
/*		width    char    hexcode */
/*		=====    ====    ======= */
  		  7, /*          0020    */
  		  7, /*   !      0021    */
  		  7, /*   "      0022    */
  		  7, /*   #      0023    */
  		  7, /*   $      0024    */
		  7, /*   %      0025    */
  		  7, /*   &      0026    */
  		  7, /*   '      0027    */
  		  7, /*   (      0028    */
  		  7, /*   )      0029    */
  		  7, /*   *      002A    */
  		  7, /*   +      002B    */
  		  7, /*   ,      002C    */
  		  7, /*   -      002D    */
  		  7, /*   .      002E    */
  		  7, /*   /      002F    */
  		  7, /*   0      0030    */
  		  7, /*   1      0031    */
  		  7, /*   2      0032    */
  		  7, /*   3      0033    */
  		  7, /*   4      0034    */
  		  7, /*   5      0035    */
  		  7, /*   6      0036    */
  		  7, /*   7      0037    */
  		  7, /*   8      0038    */
  		  7, /*   9      0039    */
  		  7, /*   :      003A    */
  		  7, /*   ;      003B    */
  		  7, /*   <      003C    */
  		  7, /*   =      003D    */
  		  7, /*   >      003E    */
  		  7, /*   ?      003F    */
		  7, /*   @      0040    */
  		  7, /*   A      0041    */
  		  7, /*   B      0042    */
  		  7, /*   C      0043    */
  		  7, /*   D      0044    */
  		  7, /*   E      0045    */
  		  7, /*   F      0046    */
  		  7, /*   G      0047    */
  		  7, /*   H      0048    */
  		  7, /*   I      0049    */
  		  7, /*   J      004A    */
  		  7, /*   K      004B    */
  		  7, /*   L      004C    */
  		  7, /*   M      004D    */
  		  7, /*   N      004E    */
  		  7, /*   O      004F    */
  		  7, /*   P      0050    */
  		  7, /*   Q      0051    */
  		  7, /*   R      0052    */
  		  7, /*   S      0053    */
  		  7, /*   T      0054    */
  		  7, /*   U      0055    */
  		  7, /*   V      0056    */
		  7, /*   W      0057    */
  		  7, /*   X      0058    */
  		  7, /*   Y      007    */
  		  7, /*   Z      005A    */
  		  7, /*   [      005B    */
  		  7, /*   \      005C    */
  		  7, /*   ]      005D    */
  		  7, /*   ^      005E    */
  		  7, /*   _      005F    */
  		  7, /*   `      0060    */
  		  7, /*   a      0061    */
  		  7, /*   b      0062    */
  		  7, /*   c      0063    */
  		  7, /*   d      0064    */
  		  7, /*   e      0065    */
  		  7, /*   f      0066    */
  		  7, /*   g      0067    */
  		  7, /*   h      0068    */
  		  7, /*   i      0069    */
  		  7, /*   j      006A    */
  		  7, /*   k      006B    */
  		  7, /*   l      006C    */
		  7, /*   m      006D    */
  		  7, /*   n      006E    */
  		  7, /*   o      006F    */
  		  7, /*   p      0070    */
  		  7, /*   q      0071    */
  		  7, /*   r      0072    */
  		  7, /*   s      0073    */
  		  7, /*   t      0074    */
  		  7, /*   u      0075    */
  		  7, /*   v      0076    */
  		  7, /*   w      0077    */
  		  7, /*   x      0078    */
  		  7, /*   y      0079    */
  		  7, /*   z      007A    */
  		  7, /*   {      007B    */
  		  7, /*   |      007C    */
  		  7, /*   }      007D    */
  		  7, /*   ~      007E    */
  		  7, /*         007F    */
};

