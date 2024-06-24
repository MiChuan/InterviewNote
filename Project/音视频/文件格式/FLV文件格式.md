# FLV

## FLV 总体结构

FLV 文件由 `FLV文件头(FLV Header)`和 `FLV文件体(FLV Body)`组成。

FLV 文件体由若干级联的 `FLV标签(FLV Tag)`组成。标签使用一个 `PreviousTagSize`（uint32_t）来保存前一个 FLV 标签的大小，第一个 PreviousTagSize 值为0。

一个 FLV 文件中的所有数据，如 `视频头信息`、`音频流数据`和`视频流数据`等都封装在不同类型的 FLV 标签中，并且在同一个 FLV 文件中保存或传输。

## FLV 文件头

前 3Byte，uint8_t 形式保存 0x46、0x4C 和 0x56，即F、L和V的ASCII码。后面一个 uint8_t 值表示 FLV 文件版本。

FLV文件头的第 5 Byte中，`最低位 (Video Flag)` 和`倒数第三位 (Audio Flag)` 分别为 `视频 Tag 标识位` 和 `音频 Tag 标识位`，其余位均为0。Video Flag 为1时，文件存在视频 Tag；Audio Flag 为1时，文件中存在音频 Tag。FLV文件头的最后，用 4 Byte 表示整个 FLV 文件头的长度，如 FLV Version 1，该值通常为9。

## FLV 标签

FLV 标签 都由 `FLV标签头部信息(FLV Tag Header)` 和 `FLV标签载荷数据(FLV Tag Playload)` 组成。

FLV标签头部信息包含当前标签的 类型、体积、时间戳 等信息，FLV标签载荷数据保存了一个完整的 音频、视频或参数数据类型 的标签。

### FLV 标签头部信息

FLV 标签中，前 11 Byte 固定表示当前的头部信息：

- 保留位（Reserved）：2 bit，始终为0。
- 预处理标识（Filter）：1 bit，0表示无预处理，1表示需要加密等预处理。
- 标签类型（TagType）：5 bit，8表示音频，9表示视频，18表示参数数据。

以上三项组成了头部信息的第1 Byte。

- 数据体积（DataSize）：3 Byte，当前标签内载荷数据的体积。
- 时间戳（Timestamp）：3 Byte，当前标签的时间戳。
- 时间戳扩展（TimestampExtended）：1 Byte，时间戳扩展，可作为高位字节与Timestamp构成一个32位有符号整型值。
- SteamID：3 Byte，始终为0。

### FLV 标签载荷数据

#### 脚本标签

头部信息中的标签类型为18时，载荷数据就保存了一个脚本标签。脚本标签以不同类型的键值对形式保存了若干媒体文件的参数数据。脚本标签中的 `脚本标签体(ScriptTagBody)` 实际上是一个十分复杂的键值对结构，其 Name（键）和 Value（值）都用一个通用数据类型 `ScriptDataValue` 来表示

| 字段  |             类型             |   含义   |
| :---: | :--------------------------: | :------: |
| Name  |   ScriptDataValue (String)   | 参数名称 |
| Value | ScriptDataValue (ECMA Array) |  参数值  |

ScriptDataValue 由 Type 和 Data 两部分组成，Type 定义了数据类型。

| 类型索引 |      类型      |
| :------: | :------------: |
|    0     |  双精度浮点数  |
|    1     |     布尔值     |
|    2     |     字符串     |
|    3     |      对象      |
|    7     | 16位无符号整数 |
|    8     |   ECMA 数组    |
|    10    |    有序数组    |
|    11    |   日期/时间    |
|    12    |     长数组     |

#### FLV 视频标签

头部信息中的标签类型为9时，该标签的载荷数据中保存了一个视频标签。

##### 视频标签头

视频标签头中保存了视频流相关的 MetaData 数据。

|      字段       | 类型  |           含义           |
| :-------------: | :---: | :----------------------: |
|    FrameType    | UB[4] |        视频帧类型        |
|     CodecID     | UB[4] |      视频流编码格式      |
|  AVCPacketType  |  UI8  |      视频包数据类型      |
| CompositionTime | SI24  | 视频包的显式时间戳偏移量 |

##### 视频标签体

头部信息中的标签类型为9时，在视频标签头之后所保存的就是视频标签体，即视频码流数据。根据CodecID的不同，视频标签体中保存了不同格式的视频码流包。

#### FLV音频标签

头部信息中的标签类型为8时，该标签为一个音频标签。与视频标签类似，在一个音频标签中，紧随StreamID之后的为音频标签头和音频标签体。