//
//  load_frame.hpp
//  player
//
//  Created by Shilei Mao on 11/05/2024.
//

#ifndef __VIDEO_READER__
#define __VIDEO_READER__
extern "C" {
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
  #include <inttypes.h>
}


struct VideoReaderState {
  // Public for other parts of the program
  int width;
  int height;
  uint8_t* frame_buffer;

  // private internal state
  AVFormatContext* av_format_ctx = NULL;
  AVCodecContext* av_codec_ctx = NULL;
  int video_stream_index = -1;
  AVFrame* av_frame = NULL;
  AVPacket* av_packet = NULL;
  SwsContext* sws_scaler_ctx = NULL;
};

bool video_reader_open(VideoReaderState* state, const char* filename);
bool video_reader_read_frame(VideoReaderState* state, uint8_t* frame_buffer);
bool video_reader_close(VideoReaderState* state);
void video_reader_free(VideoReaderState* state);

#endif
