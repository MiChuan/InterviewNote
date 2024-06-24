# MP4

## ISO 协议族

- ISO/IEC-14496：MPEG-4协议族，包括ISO容器格式、MPEG-4（H.264）视频压缩标准等。
- ISO/IEC-23008：MPEG-H协议族，包括H.265（HEVC）视频压缩标准等。

|       字段       |                  类型                   |                 含义                  |
| :--------------: | :-------------------------------------: | :-----------------------------------: |
| ISO/IEC-14496-1  |                 System                  |    MPEG-4 的复用、同步等系统级特性    |
| ISO/IEC-14496-2  |                  Video                  |             视频压缩标准              |
| ISO/IEC-14496-3  |                  Audio                  |             音频压缩标准              |
| ISO/IEC-14496-10 |       Advanced Video Coding (AVC)       |            H.264/AVC 标准             |
| ISO/IEC-14496-12 |         ISO based media format          | ISO 规定的基本文件封装容器的格式标准  |
| ISO/IEC-14496-14 |             MP4 file format             |          定义 MP4 的封装格式          |
| ISO/IEC-14496-15 | Advanced Video Coding (AVC) file format | 规定保存 H.264/AVC 标准的视频容器格式 |

## MP4 封装格式

> MP4 格式的文件是由一个个嵌套形式的“Box 结构”构成的。
>
> Box 结构为一种由头结构（Box Header）和负载数据（Box Data）组成的能容纳特定信息的数据结构。

## Box类型

> MP4协议中定义的Box类型超过70种，它们都定义在标准文档ISO/IEC 14496-12中。

| 字段名 | 上级容器 |        全称         |                           含义                           |
| :----: | :------: | :-----------------: | :------------------------------------------------------: |
|  ftyp  |   文件   |      file type      |                         文件类型                         |
|  moov  |   文件   |      movie box      |                音视频文件的媒体信息头结构                |
|  mdat  |   文件   |     media data      |            媒体数据结构，保存实际的音视频数据            |
|  mvhd  |   moov   |    movie header     |              视频头结构，保存文件的全局信息              |
|  trak  |   moov   |     media track     |    音频轨或视频轨，表示音视频文件中的某一路媒体流结构    |
|  tkhd  |   trak   |    track header     | 音频轨、视频轨头结构，表示当前流的总体信息，如图像宽、高 |
|  edts  |   trak   | edit list container |               编辑列表容器，用于保存 elst                |
|  elst  |   edts   |      edit list      |             编辑列表，用于编辑流的播放时间轴             |
|  mdia  |   trak   |     media info      |                  媒体流中的详细参数信息                  |

MP4 文件中保存的每一路媒体流的底层参数信息都保存在 mdia。

## MP4文件结构

```mermaid
graph LR;
test.mp4---ftyp;
test.mp4---moov;
	moov---mvhd;
	moov---trak1;
		trak1---tkhd1;
		trak1---edts1;
			edts1---elst1;
		trak1---mdia1;
			mdia1---mdhd1;
			mdia1---hdlr1;
			mdia1---minf1;
				minf1---vmhd1;
				minf1---dinf1;
				minf1---stbl1;
					stbl1---stsd1;
						stsd1---avc1;
							avc1---avcC1;
					stbl1---stts1;
					stbl1---stss1;
					stbl1---ctts1;
					stbl1---stsc1;
					stbl1---stsz1;
					stbl1---stco1;
        moov---trak2;
            trak2---tkhd2;
            trak2---edts2;
                edts2---elst2;
            trak2---mdia2;
                mdia2---mdhd2;
                mdia2---hdlr2;
                mdia2---minf2;
                    minf2---smhd2;
                    minf2---dinf2;
                    minf2---stbl2;
                        stbl2---stsd2;
                            stsd2---mp4a2;
                                mp4a2---esds2;
                        stbl2---stts2;
                        stbl2---stsc2;
                        stbl2---stsz2;
                        stbl2---stco2;
	moov---udta;
test.mp4---free;
test.mp4---mdat;
```

### ftyp（文件类型）

ISO 媒体文件所必备的，用于说明当前媒体文件的类型、版本号及兼容的协议类型。

### moov（音视频文件的媒体信息头结构）

包含了音频文件和视频文件的总体描述信息，以及音视频流的播放控制信息等。

- mvhd：即 movie header，保存文件的全局信息，如创建时间、修改时间或整体播放时长等。
- trak：即 track header，表示音视频文件中的某一路媒体流信息，如音频流、视频流或字幕流等。

### mdat（媒体数据结构）

保存了二进制的音频流或视频流数据。一个媒体文件可能包含0个或多个媒体数据结构，分别对应多路音频流或视频流。每路音频流或视频流的音视频码流包在媒体数据结构中的位置都由媒体信息头结构中的信息指定。