#ifndef MANGLE_SOUND_FFMPEG_H
#define MANGLE_SOUND_FFMPEG_H

#include "../input.h"
#include <exception>
#include <vector>
#include <assert.h>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

namespace Mangle {
namespace Sound {

class FFMpegSource : public SampleSource
{
  AVFormatContext *FmtCtx;
  AVCodecContext *CodecCtx;
  int StreamNum;

  std::vector<uint8_t> storage;

 public:
  /// Decode the given sound file
  FFMpegSource(const std::string &file);

  /// Decode the given sound stream (not supported by FFmpeg)
  FFMpegSource(Stream::StreamPtr src) { assert(0); }

  ~FFMpegSource();

  // Overrides
  void getInfo(int32_t *rate, int32_t *channels, int32_t *bits);
  size_t read(void *data, size_t length);
};

#include "loadertemplate.h"

/// A factory that loads FFMpegSources from file
class FFMpegLoader : public SSL_Template<AudiereSource,false,true>
{
 public:

  /// Sets up the libavcodec library. If you want to do your own
  /// setup, send a setup=false parameter.
  FFMpegLoader(bool setup=true);
};

}} // namespaces
#endif
