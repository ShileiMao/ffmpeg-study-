#include "video_reader.hpp"

#undef av_err2str
#define av_err2str(errnum) av_make_error_string((char*)__builtin_alloca(AV_ERROR_MAX_STRING_SIZE), AV_ERROR_MAX_STRING_SIZE, errnum)

static AVPixelFormat correct_for_deprecated_pixel_format(AVPixelFormat pix_fmt) {
    // Fix swscaler deprecated pixel format warning
    // (YUVJ has been deprecated, change pixel format to regular YUV)
    switch (pix_fmt) {
        case AV_PIX_FMT_YUVJ420P: return AV_PIX_FMT_YUV420P;
        case AV_PIX_FMT_YUVJ422P: return AV_PIX_FMT_YUV422P;
        case AV_PIX_FMT_YUVJ444P: return AV_PIX_FMT_YUV444P;
        case AV_PIX_FMT_YUVJ440P: return AV_PIX_FMT_YUV440P;
        default:                  return pix_fmt;
    }
}


bool video_reader_open(VideoReaderState* state, const char* filename) {
  auto& av_format_ctx = state->av_format_ctx;
  auto& av_codec_ctx = state->av_codec_ctx;
  auto& av_frame = state->av_frame;
  auto& av_packet = state->av_packet;
  auto& video_stream_index = state->video_stream_index;
  auto& width = state->width;
  auto& height = state->height;

 av_format_ctx = avformat_alloc_context();
 if(!av_format_ctx) {
   printf("Could not read AVFormatContext\n");
   return false;
 }

  if(avformat_open_input(&av_format_ctx, filename, NULL, NULL) != 0) {
    printf("Couldn't open video file\n");
    return false;
  }
  
  if(avformat_find_stream_info(av_format_ctx, NULL) != 0) {
    printf("Unable to find video stream!\n");
    return false;
  }

  // find the first valid video stream from the file
  video_stream_index = -1;
  AVCodecParameters* av_codec_params = NULL;
  
  for(int i = 0; i < av_format_ctx->nb_streams; i ++) {
    auto stream = av_format_ctx->streams[i];
    av_codec_params = av_format_ctx->streams[i]->codecpar;
    
    if(av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO) {
      video_stream_index = i;
      width = av_codec_params->width;
      height = av_codec_params->height;
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
  const AVCodec* av_codec;
  av_codec = avcodec_find_decoder(av_codec_params->codec_id);
  if(!av_codec) {
    // not support codec
    printf("Unsupported codedc\n");
    return false;
  }
    
  av_codec_ctx = avcodec_alloc_context3(av_codec);
  if(!av_codec_ctx) {
    printf("Couldn't create AVCodecContext\n");
    return false;
  }

  if(avcodec_parameters_to_context(av_codec_ctx, av_format_ctx->streams[video_stream_index]->codecpar) < 0) {
    printf("Couldn't initialize AVCodecContext\n");
    return false;
  }
  
  if(avcodec_open2(av_codec_ctx, av_codec, NULL) < 0) {
    printf("Couldn't open codec\n");
    return false;
  }
  
  width = av_codec_ctx->width;
  height = av_codec_ctx->height;

  printf("width: %d (%d), height: %d (%d)\n", av_codec_params->width, av_codec_ctx->width, av_codec_params->height, av_codec_ctx->height);

  return true;
}

bool video_reader_read_frame(VideoReaderState* state, uint8_t* frame_buffer) {
  auto& av_format_ctx = state->av_format_ctx;
  auto& av_codec_ctx = state->av_codec_ctx;
  auto& av_frame = state->av_frame;
  auto& av_packet = state->av_packet;
  auto& video_stream_index = state->video_stream_index;
  auto& sws_scaler_ctx = state->sws_scaler_ctx;
  auto& width = state->width;
  auto& height = state->height;
  

  // decode the data
  av_frame = av_frame_alloc();
  if(!av_frame) {
    printf("Coulnd't allocate AVPackte\n");
    return false;
  }
  
  av_packet = av_packet_alloc();
  if(!av_packet) {
    printf("Couldn't allocate AVPacket\n");
    return false;
  }

  int resp = 0;
  do {
    printf("*** read package ***\n");
    resp = av_read_frame(av_format_ctx, av_packet);
    
    if(av_packet->stream_index != video_stream_index) {
      // we skip if this is not video stream
      av_packet_unref(av_packet);
      continue;
    }
    
    int response = avcodec_send_packet(av_codec_ctx, av_packet);
    if(response < 0) {
      printf("Failed to decode packet 1: %s\n", av_err2str(response));
      av_packet_unref(av_packet);
      return false;
    }
    
    response = avcodec_receive_frame(av_codec_ctx, av_frame);
    if(response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
      printf("");
      av_packet_unref(av_packet);
      continue;
    }
    
    if(response < 0) {
      printf("Failed to decode packet: %s\n", av_err2str(response));
      av_packet_unref(av_packet);
      return false;
    }
    
    av_packet_unref(av_packet);
    break;
  } while (resp >= 0);
  
  printf("*** processed package ***\n");
  // setup video scaler
//  if (!sws_scaler_ctx) {
////      auto source_pix_fmt = correct_for_deprecated_pixel_format(av_codec_ctx->pix_fmt);
//      sws_scaler_ctx = sws_getContext(width, height, av_codec_ctx->pix_fmt,
//                                      width, height, AV_PIX_FMT_RGBA,
//                                      AV_PIX_FMT_YUV420P, NULL, NULL, NULL);
//  }
////  AVPixelFormat sourc_pixel_fmt = correct_for_deprecated_pixel_format(av_codec_ctx->pix_fmt);
////  sws_scaler_ctx = sws_getContext(width, height, sourc_pixel_fmt,
////                                  av_frame->width, av_frame->height,AV_PIX_FMT_RGB0,
////                                  SWS_BILINEAR, NULL, NULL, NULL);
//
//  if(!sws_scaler_ctx) {
//    printf("Failed to initialize scaler Context\n");
//    return false;
//  }
  
//  uint8_t* dest[1] = { frame_buffer };
//  int dest_linesize[1] = { width * 3 };
//  
////   this frame is usign YUV color
//    for(int x = 0; x < av_frame->width; x ++) {
//      for(int y = 0; y < av_frame->height; y ++) {
//        (frame_buffer)[y * av_frame->width * 4 + x * 4 ] = av_frame->data[0][y * av_frame->linesize[0] + x];
//        (frame_buffer)[y * av_frame->width * 4 + x * 4 + 1] = av_frame->data[0][y * av_frame->linesize[0] + x];
//        (frame_buffer)[y * av_frame->width * 4 + x * 4 + 2] = av_frame->data[0][y * av_frame->linesize[0] + x];
//        (frame_buffer)[y * av_frame->width * 4 + x * 4 + 3] = 1;
//      }
//    }
  
  // convert to RGB color, you can scale the image size from here as well
//  sws_scale(sws_scaler_ctx, av_frame->data, av_frame->linesize, 0, av_frame->height, dest, dest_linesize);
  
  // Set up sws scaler
   if (!sws_scaler_ctx) {
       auto source_pix_fmt = correct_for_deprecated_pixel_format(av_codec_ctx->pix_fmt);
       sws_scaler_ctx = sws_getContext(width, height, source_pix_fmt,
                                       width, height, AV_PIX_FMT_RGB0,
                                       SWS_BILINEAR, NULL, NULL, NULL);
   }
   if (!sws_scaler_ctx) {
       printf("Couldn't initialize sw scaler\n");
       return false;
   }

   uint8_t* dest[4] = { frame_buffer, NULL, NULL, NULL };
   int dest_linesize[4] = { width * 4, 0, 0, 0 };
   sws_scale(sws_scaler_ctx, av_frame->data, av_frame->linesize, 0, av_frame->height, dest, dest_linesize);


  return true;
}

bool video_reader_close(VideoReaderState* state) {
  avformat_close_input(&state->av_format_ctx);
  avformat_free_context(state->av_format_ctx);
  av_frame_free(&state->av_frame);
  av_packet_free(&state->av_packet);
  avcodec_free_context(&state->av_codec_ctx);
  sws_freeContext(state->sws_scaler_ctx);
}

void video_reader_free(VideoReaderState* state) {
  
}

