/*
 * FLV common header
 *
 * Copyright (c) 2006 The FFmpeg Project
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file
 * FLV common header
 */

#ifndef AVFORMAT_FLV_H
#define AVFORMAT_FLV_H

/* offsets for packed values */
#define FLV_AUDIO_SAMPLESSIZE_OFFSET 1
#define FLV_AUDIO_SAMPLERATE_OFFSET  2
#define FLV_AUDIO_CODECID_OFFSET     4

#define FLV_VIDEO_FRAMETYPE_OFFSET   4

/* Extended VideoTagHeader
 * defined in reference link:
 * https://github.com/veovera/enhanced-rtmp/blob/main/enhanced-rtmp-v1.pdf
 * */
#define FLV_IS_EX_HEADER 0x80

#define FRAME_HEADER_EX              (8 << FLV_VIDEO_FRAMETYPE_OFFSET)

enum video_frametype_t {
	FT_KEY = 1 << FLV_VIDEO_FRAMETYPE_OFFSET,
	FT_INTER = 2 << FLV_VIDEO_FRAMETYPE_OFFSET,
};

enum packet_type_t {
	PACKETTYPE_SEQ_START = 0,
	PACKETTYPE_FRAMES = 1,
	PACKETTYPE_SEQ_END = 2,
	PACKETTYPE_FRAMESX = 3,
	PACKETTYPE_METADATA = 4
};

/* bitmasks to isolate specific values */
#define FLV_AUDIO_CHANNEL_MASK    0x01
#define FLV_AUDIO_SAMPLESIZE_MASK 0x02
#define FLV_AUDIO_SAMPLERATE_MASK 0x0c
#define FLV_AUDIO_CODECID_MASK    0xf0

#define FLV_VIDEO_CODECID_MASK    0x0f
#define FLV_VIDEO_FRAMETYPE_MASK  0xf0

#define AMF_END_OF_OBJECT         0x09

#define KEYFRAMES_TAG            "keyframes"
#define KEYFRAMES_TIMESTAMP_TAG  "times"
#define KEYFRAMES_BYTEOFFSET_TAG "filepositions"

#define IS_EXT_HEADER(x) (((x) & FRAME_HEADER_EX) == FRAME_HEADER_EX)
#define GET_PACKET_TYPE(x) ((x) & FLV_VIDEO_CODECID_MASK)
#define EXT_HEADER_IS_SEQFRAME(x) (((x) & FLV_VIDEO_CODECID_MASK) == PACKETTYPE_SEQ_START)
#define EXT_HEADER_IS_FRAMES(x) (((x) & FLV_VIDEO_CODECID_MASK) == PACKETTYPE_FRAMES)
#define EXT_HEADER_IS_FRAMESX(x) (((x) & FLV_VIDEO_CODECID_MASK) == PACKETTYPE_FRAMESX)
#define EXT_HEADER_IS_ENDFRAME(x) (((x) & FLV_VIDEO_CODECID_MASK) == PACKETTYPE_SEQ_END)

#define EXT_HEADER_IS_KEYFRAME(x) (((x) & FLV_VIDEO_FRAMETYPE_MASK) == FT_KEY)
#define EXT_HEADER_IS_INTERFRAME(x) (((x) & FLV_VIDEO_FRAMETYPE_MASK) == FT_INTER)


enum {
    FLV_HEADER_FLAG_HASVIDEO = 1,
    FLV_HEADER_FLAG_HASAUDIO = 4,
};

enum FlvTagType {
    FLV_TAG_TYPE_AUDIO = 0x08,
    FLV_TAG_TYPE_VIDEO = 0x09,
    FLV_TAG_TYPE_META  = 0x12,
};

enum {
    FLV_STREAM_TYPE_VIDEO,
    FLV_STREAM_TYPE_AUDIO,
    FLV_STREAM_TYPE_SUBTITLE,
    FLV_STREAM_TYPE_DATA,
    FLV_STREAM_TYPE_NB,
};

enum {
    FLV_MONO   = 0,
    FLV_STEREO = 1,
};

enum {
    FLV_SAMPLESSIZE_8BIT  = 0,
    FLV_SAMPLESSIZE_16BIT = 1 << FLV_AUDIO_SAMPLESSIZE_OFFSET,
};

enum {
    FLV_SAMPLERATE_SPECIAL = 0, /**< signifies 5512Hz and 8000Hz in the case of NELLYMOSER */
    FLV_SAMPLERATE_11025HZ = 1 << FLV_AUDIO_SAMPLERATE_OFFSET,
    FLV_SAMPLERATE_22050HZ = 2 << FLV_AUDIO_SAMPLERATE_OFFSET,
    FLV_SAMPLERATE_44100HZ = 3 << FLV_AUDIO_SAMPLERATE_OFFSET,
};

enum {
    FLV_CODECID_PCM                  = 0,
    FLV_CODECID_ADPCM                = 1 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_MP3                  = 2 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_PCM_LE               = 3 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_NELLYMOSER_16KHZ_MONO = 4 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_NELLYMOSER_8KHZ_MONO = 5 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_NELLYMOSER           = 6 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_PCM_ALAW             = 7 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_PCM_MULAW            = 8 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_OPUS                 = 9 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_AAC                  = 10<< FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_SPEEX                = 11<< FLV_AUDIO_CODECID_OFFSET,
};

enum {
    FLV_CODECID_H263    = 2,
    FLV_CODECID_SCREEN  = 3,
    FLV_CODECID_VP6     = 4,
    FLV_CODECID_VP6A    = 5,
    FLV_CODECID_SCREEN2 = 6,
    FLV_CODECID_H264    = 7,
    FLV_CODECID_REALH263= 8,
    FLV_CODECID_MPEG4   = 9,
    FLV_CODECID_HEVC    = 12,
    FLV_CODECID_AV1     = 13,
    FLV_CODECID_VP8     = 14,
    FLV_CODECID_VP9     = 15,
};

enum {
    FLV_FRAME_KEY            = 1 << FLV_VIDEO_FRAMETYPE_OFFSET, ///< key frame (for AVC, a seekable frame)
    FLV_FRAME_INTER          = 2 << FLV_VIDEO_FRAMETYPE_OFFSET, ///< inter frame (for AVC, a non-seekable frame)
    FLV_FRAME_DISP_INTER     = 3 << FLV_VIDEO_FRAMETYPE_OFFSET, ///< disposable inter frame (H.263 only)
    FLV_FRAME_GENERATED_KEY  = 4 << FLV_VIDEO_FRAMETYPE_OFFSET, ///< generated key frame (reserved for server use only)
    FLV_FRAME_VIDEO_INFO_CMD = 5 << FLV_VIDEO_FRAMETYPE_OFFSET, ///< video info/command frame
};

typedef enum {
    AMF_DATA_TYPE_NUMBER      = 0x00,
    AMF_DATA_TYPE_BOOL        = 0x01,
    AMF_DATA_TYPE_STRING      = 0x02,
    AMF_DATA_TYPE_OBJECT      = 0x03,
    AMF_DATA_TYPE_NULL        = 0x05,
    AMF_DATA_TYPE_UNDEFINED   = 0x06,
    AMF_DATA_TYPE_REFERENCE   = 0x07,
    AMF_DATA_TYPE_MIXEDARRAY  = 0x08,
    AMF_DATA_TYPE_OBJECT_END  = 0x09,
    AMF_DATA_TYPE_ARRAY       = 0x0a,
    AMF_DATA_TYPE_DATE        = 0x0b,
    AMF_DATA_TYPE_LONG_STRING = 0x0c,
    AMF_DATA_TYPE_UNSUPPORTED = 0x0d,
} AMFDataType;

#endif /* AVFORMAT_FLV_H */
