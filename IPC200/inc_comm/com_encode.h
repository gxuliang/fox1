/*
 * com_encode.h
 *
 *  Created on: 2013-4-15
 *      Author: xul
 */

#ifndef COM_ENCODE_H_
#define COM_ENCODE_H_
typedef enum
{
	mt_main		= 0x01,
	mt_ext,
	mt_pic,
}MiType;//多媒体类型media type
typedef enum
{
	vt_ordinary = 0x01, //普通
	vt_alarm	= 0x02, //报警
}ViType;
typedef	enum
{
	vp_1080p	= 0x01,
	vp_720p		= 0x02,
	vp_D1		= 0x03,
	vp_vga		= 0x04,
}ViPx;
typedef	enum
{
	vc_h264		= 0x01,
	vc_mjpge	= 0x02,
	vc_jpge		= 0x03,
	vc_mpeg4	= 0x04,
}ViComp;
typedef	enum
{
	vs_fixed	= 0x01,//固定码流
	vs_dynamic	,		//动态码流
}ViSm;
typedef struct
{
	ViType	vi_type;
	ViPx	vi_px;//分辨率
	ViComp	vi_vc;//编码模式
	uint	fps;
	uint	gop;
	ViSm	vi_strm;//码流控制
	uint	stream;//码流大小
}ViCom;
typedef	enum
{
	ac_pcm		= 0x01,
}AioComp;
typedef	struct
{
	AioComp		aio_ac;//压缩码率
	uint		frequency;//采样深度
}AioCom;
////多媒体
typedef	struct
{
	uint	mitype;//主码流、辅码流、抓图码流
	bool 	vdenable;
	ViCom	vicom;
	bool	aienable;
	AioComp	aicom;
}EncodeCom;

typedef	struct
{
	uint Brightness;//亮度
	uint Contrast;//对比度
	uint Chromaticity;//色度
	uint Saturation;//饱和度
	uint GainMode;//增益模式
	uint GainUpline;//
	uint ExposureMode;//快门模式
	uint ExposureValue[2];//快门值
	uint AutoAperture;//自动曝光
	uint SceneMode;//情景模式
	uint DNMode;//日夜模式
	uint Revolving;//旋转模式
}CamGlobal;



#endif /* COM_ENCODE_H_ */
