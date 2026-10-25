/* The Miles Sound System calls the game makes (mss32.dll, Miles 6). The SDK header is not
   available; these follow its API, and every parameter list adds up to the byte count in the
   DLL's stdcall export name (_AIL_set_3D_position@16 ...): tools/pipeline/make_importlibs.py checks that.

   F32 parameters are declared int: the decompiled calls pass the float's bits (LODWORD(v)),
   which an int parameter forwards unchanged. */
#pragma once

typedef unsigned long HPROVIDER;
typedef int MSS_F32BITS;

int        __stdcall AIL_startup(void);
void       __stdcall AIL_shutdown(void);
char      *__stdcall AIL_set_redist_directory(const char *dir);
HDIGDRIVER __stdcall AIL_open_digital_driver(unsigned int frequency, int bits, int channels, unsigned int flags);

int        __stdcall AIL_enumerate_3D_providers(HPROENUM *next, HPROVIDER *dest, char **name);
int        __stdcall AIL_open_3D_provider(HPROVIDER lib);
void       __stdcall AIL_close_3D_provider(HPROVIDER lib);
void       __stdcall AIL_set_3D_speaker_type(HPROVIDER lib, int speaker_type);

H3DSAMPLE  __stdcall AIL_allocate_3D_sample_handle(HPROVIDER lib);
void       __stdcall AIL_release_3D_sample_handle(H3DSAMPLE S);
int        __stdcall AIL_set_3D_sample_info(H3DSAMPLE S, const AILSOUNDINFO *info);
void       __stdcall AIL_set_3D_sample_offset(H3DSAMPLE S, unsigned int offset);
unsigned int __stdcall AIL_3D_sample_offset(H3DSAMPLE S);
void       __stdcall AIL_set_3D_sample_loop_count(H3DSAMPLE S, unsigned int loops);
void       __stdcall AIL_set_3D_sample_occlusion(H3DSAMPLE S, MSS_F32BITS occlusion);
void       __stdcall AIL_set_3D_sample_distances(H3DSAMPLE S, MSS_F32BITS max_dist, MSS_F32BITS min_dist);
void       __stdcall AIL_set_3D_sample_volume(H3DSAMPLE S, MSS_F32BITS volume);
void       __stdcall AIL_set_3D_sample_playback_rate(H3DSAMPLE S, int playback_rate);
void       __stdcall AIL_set_3D_position(H3DPOBJECT obj, MSS_F32BITS X, MSS_F32BITS Y, MSS_F32BITS Z);
void       __stdcall AIL_set_3D_velocity(H3DPOBJECT obj, MSS_F32BITS dX, MSS_F32BITS dY, MSS_F32BITS dZ, MSS_F32BITS magnitude);
unsigned int __stdcall AIL_3D_sample_status(H3DSAMPLE S);
void       __stdcall AIL_end_3D_sample(H3DSAMPLE S);
void       __stdcall AIL_stop_3D_sample(H3DSAMPLE S);
void       __stdcall AIL_resume_3D_sample(H3DSAMPLE S);

HSAMPLE    __stdcall AIL_allocate_sample_handle(HDIGDRIVER dig);
void       __stdcall AIL_release_sample_handle(HSAMPLE S);
void       __stdcall AIL_init_sample(HSAMPLE S);
int        __stdcall AIL_set_named_sample_file(HSAMPLE S, const char *file_type_suffix, const void *file_image, int file_size, int block);
void       __stdcall AIL_set_sample_address(HSAMPLE S, const void *start, unsigned int len);
void       __stdcall AIL_set_sample_type(HSAMPLE S, int format, unsigned int flags);
void       __stdcall AIL_set_sample_playback_rate(HSAMPLE S, int playback_rate);
void       __stdcall AIL_set_sample_loop_count(HSAMPLE S, int loop_count);
void       __stdcall AIL_set_sample_ms_position(HSAMPLE S, int milliseconds);
void       __stdcall AIL_sample_ms_position(HSAMPLE S, int *total_milliseconds, int *current_milliseconds);
void       __stdcall AIL_set_sample_volume_pan(HSAMPLE S, MSS_F32BITS volume, MSS_F32BITS pan);
unsigned int __stdcall AIL_sample_status(HSAMPLE S);
void       __stdcall AIL_stop_sample(HSAMPLE S);
void       __stdcall AIL_resume_sample(HSAMPLE S);

HSTREAM    __stdcall AIL_open_stream(HDIGDRIVER dig, const char *filename, int stream_mem);
void       __stdcall AIL_close_stream(HSTREAM stream);
void       __stdcall AIL_start_stream(HSTREAM stream);
void       __stdcall AIL_pause_stream(HSTREAM stream, int onoff);
void       __stdcall AIL_set_stream_loop_count(HSTREAM stream, int count);
void       __stdcall AIL_set_stream_volume_pan(HSTREAM stream, MSS_F32BITS volume, MSS_F32BITS pan);
int        __stdcall AIL_stream_status(HSTREAM stream);
