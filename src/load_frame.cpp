//
//  load_frame.cpp
//  player
//
//  Created by Shilei Mao on 11/05/2024.
//

#include "load_frame.hpp"

// tell the compiler compile the ffmpeg library as C code as they are written in C
// do not try to compile as C++
extern "C" {
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
  #include <inttypes.h>
}

bool load_frame(const char* filename, int* width, int* height, unsigned char** data){
  AVFormatContext * av_format_ctx = avformat_alloc_context();
  if(!av_format_ctx) {
    printf("Could not read AVFormatContext\n");
    return false;
  }

  if(avformat_open_input(&av_format_ctx, filename, NULL, NULL) != 0) {
    printf("Couldn't open video file\n");
    return false;
  }

  // find the first valid video stream from the file
  int video_stream_index = -1;
  AVCodecParameters* av_codec_params = NULL;
  const AVCodec* av_codec;
  
  for(int i = 0; i < av_format_ctx->nb_streams; i ++) {
    auto stream = av_format_ctx->streams[i];
    av_codec_params = av_format_ctx->streams[i]->codecpar;
    av_codec = avcodec_find_decoder(av_codec_params->codec_id);
    
    if(!av_codec) {
      // not support codec
      continue;
    }
    
    if(av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO) {
      video_stream_index = i;
      break;
    }
    
    if(av_codec_params->codec_type == AVMEDIA_TYPE_AUDIO) {
      
    }
  }
  
  if(video_stream_index == -1) {
    printf("Failed to read stream from file\n");
    return false;
  }
  
  // setup a codex contex for the decoder
  AVCodecContext* av_codec_ctx = avcodec_alloc_context3(av_codec);
  if(!av_codec_ctx) {
    printf("Couldn't create AVCodecContext\n");
    return false;
  }
  
  if(avcodec_parameters_to_context(av_codec_ctx, av_codec_params) < 0) {
    printf("Couldn't initialize AVCodecContext\n");
    return false;
  }
  
  if(avcodec_open2(av_codec_ctx, av_codec, NULL) < 0) {
    printf("Couldn't open codec\n");
    return false;
  }
  
  // decode the data
  AVFrame* av_frame = av_frame_alloc();
  if(!av_frame) {
    printf("Coulnd't allocate AVPackte\n");
    return false;
  }
  
  AVPacket* av_packet = av_packet_alloc();
  if(!av_packet) {
    printf("Couldn't allocate AVPacket\n");
    return false;
  }
  
  while(av_read_frame(av_format_ctx, av_packet) >= 0) {
    if(av_packet->stream_index != video_stream_index) {
      // we skip if this is not video stream
      continue;
    }
    int response = avcodec_send_packet(av_codec_ctx, av_packet);
    if(response < 0) {
      printf("Failed to decode packet 1: %s\n", av_err2str(response));
      return false;
    }
    
    response = avcodec_receive_frame(av_codec_ctx, av_frame);
    if(response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
      printf("");
      continue;
    }
    
    if(response < 0) {
      printf("Failed to decode packet: %s\n", av_err2str(response));
      return false;
    }
    
    av_packet_unref(av_packet);
    break;
  }
  
  *data = new unsigned char[av_frame->width * av_frame->height * 3];
  
  // this frame is usign YUV color
  //  for(int x = 0; x < av_frame->width; x ++) {
  //    for(int y = 0; y < av_frame->height; y ++) {
  //      (*data)[y * av_frame->width * 3 + x * 3 ] = av_frame->data[0][y * av_frame->linesize[0] + x];
  //      (*data)[y * av_frame->width * 3 + x * 3 + 1] = av_frame->data[0][y * av_frame->linesize[0] + x];
  //      (*data)[y * av_frame->width * 3 + x * 3 + 2] = av_frame->data[0][y * av_frame->linesize[0] + x];
  //    }
  //  }
  
  // convert to RGB color, you can scale the image size from here as well
  SwsContext* sws_scaler_ctx = sws_getContext(av_frame->width, av_frame->height, av_codec_ctx->pix_fmt,
                                              av_frame->width, av_frame->height,AV_PIX_FMT_RGB0,
                                              SWS_BILINEAR, NULL, NULL, NULL);
  
  if(!sws_scaler_ctx) {
    printf("Failed to initialize scaler Context\n");
    return false;
  }
  *data = new uint8_t[av_frame->width * av_frame->height * 4];
  uint8_t* dest[4] = { *data, NULL, NULL, NULL };
  int dest_linesize[4] = { av_frame->width * 4, 0, 0, 0};
  
  sws_scale(sws_scaler_ctx, av_frame->data, av_frame->linesize, 0, av_frame->height, dest, dest_linesize);
  sws_freeContext(sws_scaler_ctx);
  
  *width = av_frame->width;
  *height = av_frame->height;
  
  // clean up the resource
  avformat_close_input(&av_format_ctx);
  avformat_free_context(av_format_ctx);
  av_frame_free(&av_frame);
  av_packet_free(&av_packet);
  avcodec_free_context(&av_codec_ctx);
  
  return true;
}


