/*
	frame: Central data structures and opmitization hooks.

	copyright 2007 by the mpg123 project - free software under the terms of the LGPL 2.1
	see COPYING and AUTHORS files in distribution or http://mpg123.org
	initially written by Thomas Orgis
*/

#ifndef MPG123_FRAME_H
#define MPG123_FRAME_H

#include <stdio.h>
#include "config.h"
#include "mpg123.h"
#include "id3.h"
#include "icy.h"
#include "reader.h"
#include "optimize.h"

/* max = 1728 */
#define MAXFRAMESIZE 3456

struct al_table
{
  short bits;
  short d;
};

#ifdef FRAME_INDEX
struct frame_index
{
	off_t data[INDEX_SIZE];
	size_t fill;
	off_t step;
};
#endif

/* the output buffer, used to be pcm_sample, pcm_point and audiobufsize */
struct outbuffer
{
	unsigned char *data;
	unsigned char *p; /* read pointer  */
	size_t fill; /* fill from read pointer */
	size_t size; /* that's actually more like a safe size, after we have more than that, flush it */
};

struct audioformat
{
	int encoding;
	int channels;
	long rate;
};

enum optdec { autodec=-1, nodec=0, generic, idrei, ivier, ifuenf, ifuenf_dither, mmx, dreidnow, dreidnowext, altivec, sse };
enum optcla { nocla=0, normal, mmxsse };

struct mpg123_pars_struct
{
	int verbose;    /* verbose level */
	long flags; /* combination of above */
	long force_rate;
	int down_sample;
	int rva; /* (which) rva to do: 0: nothing, 1: radio/mix/track 2: album/audiophile */
	long halfspeed;
	long doublespeed;
#ifndef WIN32
	long timeout;
#endif
#define NUM_CHANNELS 2
	char audio_caps[NUM_CHANNELS][MPG123_RATES+1][MPG123_ENCODINGS];
/*	long start_frame; */ /* frame offset to begin with */
/*	long frame_number;*/ /* number of frames to decode */
	long icy_interval;
	scale_t outscale;
	long resync_limit;
};

/* There is a lot to condense here... many ints can be merged as flags; though the main space is still consumed by buffers. */
struct mpg123_handle_struct
{
	int fresh; /* to be moved into flags */
	int new_format;
	real hybrid_block[2][2][SBLIMIT*SSLIMIT];
	int hybrid_blc[2];
	/* the scratch vars for the decoders, sometimes real, sometimes short... sometimes int/long */ 
	short *short_buffs[2][2];
	real *real_buffs[2][2];
	unsigned char *rawbuffs;
	int rawbuffss;
	int bo[2]; /* i486 and dither need a second value */
	unsigned char* rawdecwin; /* the block with all decwins */
	real *decwin; /* _the_ decode table */
#ifdef OPT_MMXORSSE
	/* I am not really sure that I need both of them... used in assembler */
	float *decwin_mmx;
	float *decwins;
#endif
	int have_eq_settings;
	real equalizer[2][32];

	/* for halfspeed mode */
	unsigned char ssave[34];
	int halfphase;

	/* a raw buffer and a pointer into the middle for signed short conversion, only allocated on demand */
	unsigned char *conv16to8_buf;
	unsigned char *conv16to8;

	/* There's some possible memory saving for stuff that is not _really_ dynamic. */

	/* layer3 */
	int longLimit[9][23];
	int shortLimit[9][14];
	real gainpow2[256+118+4]; /* not really dynamic, just different for mmx */

	/* layer2 */
	real muls[27][64];	/* also used by layer 1 */

	/* decode_ntom */
	unsigned long ntom_val[2];
	unsigned long ntom_step;

	/* special i486 fun */
#ifdef OPT_I486
	int *int_buffs[2][2];
#endif
	/* special altivec... */
#ifdef OPT_ALTIVEC
	real *areal_buffs[4][4];
#endif
	struct
	{
#ifdef OPT_MULTI
		int (*synth_1to1)(real *,int, mpg123_handle *,int );
		int (*synth_1to1_mono)(real *, mpg123_handle *);
		int (*synth_1to1_mono2stereo)(real *, mpg123_handle *);
		int (*synth_1to1_8bit)(real *,int, mpg123_handle *,int );
		int (*synth_1to1_8bit_mono)(real *, mpg123_handle *);
		int (*synth_1to1_8bit_mono2stereo)(real *, mpg123_handle *);
#ifdef OPT_PENTIUM
		int (*synth_1to1_i586_asm)(real *,int,unsigned char *, unsigned char *, int *, real *decwin);
#endif
#ifdef OPT_MMXORSSE
		void (*make_decode_tables)(mpg123_handle *fr);
		real (*init_layer3_gainpow2)(mpg123_handle*, int);
		real* (*init_layer2_table)(mpg123_handle*, real*, DOUBLE);
#endif
#ifdef OPT_3DNOW
		void (*dct36)(real *,real *,real *,real *,real *);
#endif
		void (*dct64)(real *,real *,real *);
#ifdef OPT_MPLAYER
		void (*mpl_dct64)(real *,real *,real *);
#endif
#endif
		enum optdec type;
		enum optcla class;
	} cpu_opts;

	int verbose;    /* 0: nothing, 1: just print chosen decoder, 2: be verbose */

	/* mpg123_handle */
	const struct al_table *alloc;
	/* could use types from optimize.h */
	int (*synth)(real *,int, mpg123_handle*, int);
	int (*synth_mono)(real *, mpg123_handle*);
	int stereo; /* I _think_ 1 for mono and 2 for stereo */
	int jsbound;
#define SINGLE_STEREO -1
#define SINGLE_LEFT    0
#define SINGLE_RIGHT   1
#define SINGLE_MIX     3
	int single;
	int II_sblimit;
	int down_sample_sblimit;
	int lsf; /* 0: MPEG 1.0; 1: MPEG 2.0/2.5 -- both used as bool and array index! */
	/* Many flags in disguise as integers... wasting bytes. */
	int mpeg25;
	int down_sample;
	int header_change;
	int lay;
	int (*do_layer)(mpg123_handle *);
	int error_protection;
	int bitrate_index;
	int sampling_frequency;
	int padding;
	int extension;
	int mode;
	int mode_ext;
	int copyright;
	int original;
	int emphasis;
	int framesize; /* computed framesize */
	int freesize;  /* free format frame size */
	enum mpg123_vbr vbr; /* 1 if variable bitrate was detected */
	off_t num; /* frame offset ... */
	off_t audio_start; /* The byte offset in the file where audio data begins. */
	char accurate; /* Flag to see if we trust the frame number. */
	char silent_resync; /* Do not complain for the next n resyncs. */
	unsigned char* xing_toc; /* The seek TOC from Xing header. */

	/* bitstream info; bsi */
	int bitindex;
	unsigned char *wordpointer;
	/* temporary storage for getbits stuff */
	unsigned long ultmp;
	unsigned char uctmp;

	/* rva data, used in common.c, set in id3.c */
	
	scale_t lastscale;
	struct
	{
		int level[2];
		float gain[2];
		float peak[2];
	} rva;

	/* input data */
	off_t track_frames;
	off_t track_samples;
	DOUBLE mean_framesize;
	off_t mean_frames;
	int fsizeold;
	int ssize;
	unsigned int bitreservoir;
	unsigned char bsspace[2][MAXFRAMESIZE+512]; /* MAXFRAMESIZE */
	unsigned char *bsbuf;
	unsigned char *bsbufold;
	int bsnum;
	unsigned long oldhead;
	unsigned long firsthead;
	int abr_rate;
#ifdef FRAME_INDEX
	struct frame_index index;
#endif

	/* output data */
	struct outbuffer buffer;
	struct audioformat af;
	int own_buffer;
	size_t outblock; /* number of bytes that this frame produces (upper bound) */
	int to_decode;   /* this frame holds data to be decoded */
	int to_ignore;   /* the same, somehow */
	off_t firstframe;  /* start decoding from here */
	off_t lastframe;   /* last frame to decode (for gapless or num_frames limit) */
	off_t ignoreframe; /* frames to decode but discard before firstframe */
#ifdef GAPLESS
	off_t firstoff; /* number of samples to ignore from firstframe */
	off_t lastoff;  /* number of samples to use from lastframe */
	off_t begin_s;  /* overall begin offset in samples */
	off_t begin_os;
	off_t end_s;    /* overall end offset in samples */
	off_t end_os;
#endif
	unsigned int crc; /* Well, I need a safe 16bit type, actually. But wider doesn't hurt. */
	struct reader *rd; /* pointer to the reading functions */
	struct reader_data rdat; /* reader data and state info */
	struct mpg123_pars_struct p;
	int err;
	int decoder_change;
	int delayed_change;
	long clip;
	/* the meta crap */
	int metaflags;
	unsigned char id3buf[128];
	mpg123_id3v2 id3v2;
	struct icy_meta icy;
};

/* generic init, does not include dynamic buffers */
void frame_init(mpg123_handle *fr);
void frame_init_par(mpg123_handle *fr, mpg123_pars *mp);
/* output buffer and format */
int  frame_outbuffer(mpg123_handle *fr);
int  frame_output_format(mpg123_handle *fr);

int frame_buffers(mpg123_handle *fr); /* various decoder buffers, needed once */
int frame_reset(mpg123_handle* fr);   /* reset for next track */
int frame_buffers_reset(mpg123_handle *fr);
void frame_exit(mpg123_handle *fr);   /* end, free all buffers */

int mpg123_print_index(mpg123_handle *fr, FILE* out);
off_t frame_index_find(mpg123_handle *fr, off_t want_frame, off_t* get_frame);
int frame_cpu_opt(mpg123_handle *fr, const char* cpu);
enum optdec dectype(const char* decoder);

int set_synth_functions(mpg123_handle *fr);

void do_volume(mpg123_handle *fr, DOUBLE factor);
void do_rva(mpg123_handle *fr);

/* samples per frame ...
Layer I
Layer II
Layer III
MPEG-1
384
1152
1152
MPEG-2 LSF
384
1152
576
MPEG 2.5
384
1152
576
*/
#define spf(fr) ((fr)->lay == 1 ? 384 : ((fr)->lay==2 ? 1152 : ((fr)->lsf || (fr)->mpeg25 ? 576 : 1152)))

#ifdef GAPLESS
/* well, I take that one for granted... at least layer3 */
#define GAPLESS_DELAY 529
/* still fine-tuning the "real music" window... see read_frame */
void frame_gapless_init(mpg123_handle *fr, off_t b, off_t e);
void frame_gapless_realinit(mpg123_handle *fr);
/*void frame_gapless_position(mpg123_handle* fr);
void frame_gapless_bytify(mpg123_handle *fr);
void frame_gapless_ignore(mpg123_handle *fr, off_t frames);*/
/* void frame_gapless_buffercheck(mpg123_handle *fr); */
#endif

/*
	Seeking core functions:
	- convert input sample offset to output sample offset
	- convert frame offset to output sample offset
	- get leading frame offset for output sample offset
	The offsets are "unadjusted"/internal; resampling is being taken care of.
*/
off_t frame_ins2outs(mpg123_handle *fr, off_t ins);
off_t frame_outs(mpg123_handle *fr, off_t num);
off_t frame_offset(mpg123_handle *fr, off_t outs);
void frame_set_frameseek(mpg123_handle *fr, off_t fe);
void frame_set_seek(mpg123_handle *fr, off_t sp);
off_t frame_tell_seek(mpg123_handle *fr);
/* Take a copy of the Xing VBR TOC for fuzzy seeking. */
int frame_fill_toc(mpg123_handle *fr, unsigned char* in);


/* adjust volume to current outscale and rva values if wanted */
void do_rva(mpg123_handle *fr);
#endif
