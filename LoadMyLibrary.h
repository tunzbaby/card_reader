#ifndef  __LOADMYLIBRARY_H__
#define  __LOADMYLIBRARY_H__


#include <stdio.h>       //标准输入输出定义
#include <string.h>
#include <stdlib.h>      //标准函数库定义
#include <unistd.h>      //Unix标准函数定义
#include <sys/types.h>
#include <sys/stat.h>  
#include <fcntl.h>       //文件控制定义
#include <termios.h>     //PPSIX终端控制定义
#include <errno.h>       //错误号定义

#include <dlfcn.h>

#define BYTE unsigned char

//二代证信息
typedef struct
{
	char szName[31];   //姓名
	char szSex[5];     //性别
	char szNation[20]; //民族
	char szBornDay[10]; //出生
	char szAddress[128]; //地址
	char szIDNum[20];   //身份证编号
	char szIssued[51];  //签发机关
	char szBeginValidity[10]; //开始有效日期
	char szEndValidity[10];   //截止有效日期
	char szImgData[1024];      //头文件数据
}CRTDef_IDInfo, *pCRTDef_IDInf;


/** 
 * @fn		CRT_OpenConnect 
 * @detail	打开CRT智能读卡器
 * @see		...
 * @param	iListNums:输出 连接的读卡器列表个数
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_OpenConnect)(int* iListNums);




/** 
 * @fn		CRT_CloseConnect 
 * @detail	关闭CRT智能读卡器
 * @see		...
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_CloseConnect)();




/** 
 * @fn		CRT_GetReaderListName 
 * @detail	获取智能读卡器列表名字
 * @see		...
 * @param	iListNum:需获取的读卡器序列号（0为起始）
 * @param	szListName:输出 获取到的读卡器名字
 * @return	0 成功， 非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_GetReaderListName)(int iListNum, char szListName[]);




/** 
 * @fn		CRT_SetReaderName 
 * @detail	设置当前工作的读卡器序列号（打开时，默认设置为第一个读卡器）
 * @see		...
 * @param	iListNum:需设置的读卡器序列号（0为起始）
 * @return	0 成功， 非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_SetReaderName)(int iListNum);




/** 
 * @fn		CRT_GetCardStatus 
 * @detail	获取读卡器上卡状态
 * @see		...
 * @return	1 有卡， 2 无卡， 9 状态未知
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_GetCardStatus)();




/** 
 * @fn		CRT_EjectCard 
 * @detail	弹卡下电，读卡器断开连接
 * @see		...
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_EjectCard)();




/** 
 * @fn		CRT_ReaderConnect 
 * @detail	读卡器卡片上电
 * @see		...
 * @param	byAtrData:输出 上电成功返回的ATR数据
 * @param	iAtrLen: 输出 上电成功返回的ATR数据长度
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_ReaderConnect)(BYTE byAtrData[], int* iAtrLen);




/** 
 * @fn		CRT_SendApdu 
 * @detail	读卡器发送APDU指令
 * @see		...
 * @param	bySendData:需发送的APDU指令（支持acsii码与BCD码）
 * @param	iSendDataLen: 需发送的APDU指令长度
 * @param	byRecvData:输出 APDU通讯后返回的数据
 * @param	iRecvDataLen: 输出 APDU通讯后返回的数据长度
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_SendApdu)(BYTE bySendData[], int iSendDataLen, BYTE byRecvData[], int* iRecvDataLen);




/** 
 * @fn		CRT_SendControlCMD 
 * @detail	读卡器发送扩展控制命令
 * @see		...
 * @param	bySendData:需发送的扩展控制命令数据（支持acsii码与BCD码）
 * @param	iSendDataLen: 需发送的扩展控制命令数据长度
 * @param	byRecvData:输出 扩展控制命令通讯后返回的数据
 * @param	iRecvDataLen: 输出 扩展控制命令通讯后返回的数据长度
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_SendControlCMD)(BYTE bySendData[], int iSendDataLen, BYTE byRecvData[], int* iRecvDataLen);




//***********************发送CRT603具体功能扩展命令****************************
/** 
 * @fn		CRT_HotReset 
 * @detail	读卡器热复位
 * @see		...
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_HotReset)();




/** 
 * @fn		CRT_SetReaderType 
 * @detail	设置读卡器操作模式
 * @see		...
 * @param	iType: 1 正常RF卡模式， 2 Felica模式， 3 点对点模式， 4 二代证模式， 5 卡模拟模式
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_SetReaderType)(int iType);




/** 
 * @fn		CRT_GetReaderType 
 * @detail	获取读卡器操作模式
 * @see		...
 * @return	>0 失败 1 正常RF卡模式， 2 Felica模式， 3 点对点模式， 4 二代证模式， 5 卡模拟模式
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_GetReaderType)();




/** 
 * @fn		CRT_GetVersionInfo 
 * @detail	获取读卡器版本信息
 * @see		...
 * @param	iVerType: 需获取的版本 0 P/N信息， 1 SN信息， 2, 固件版本信息， 3 生成版本信息， 4 EMID信息， 5 动态库版本信息
 * @param	szVersionInfo: 输出 返回的版本信息
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_GetVersionInfo)(int iVerType, char szVersionInfo[]);




/** 
 * @fn		CRT_AutoBeel 
 * @detail	读卡器自动蜂鸣
 * @see		...
 * @param	bAutoBeel: 是否自动蜂鸣，true 开启，false 关闭
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_AutoBeel)(bool bAutoBeel);




/** 
 * @fn		CRT_Beel 
 * @detail	读卡器蜂鸣设置
 * @see		...
 * @param	MultipleTime: 蜂鸣时间：0.25秒的倍数，比如2，蜂鸣时间：2*0.25 即0.5秒（0-20 默认为1)
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_Beel)(int MultipleTime);




/** 
 * @fn		CRT_SetLightMode 
 * @detail	设置读卡器指示灯模式
 * @see		...
 * @param	iType: 指示灯模式 0 自动模式， 1 手动模式
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_SetLightMode)(int iType);




/** 
 * @fn		CRT_GetLightMode 
 * @detail	获取读卡器指示灯模式
 * @see		...
 * @return	0 自动模式，1 手动模式， 9模式未知
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_GetLightMode)();




/** 
 * @fn		CRT_SetLightStatus 
 * @detail	设置读卡器指示灯状态
 * @see		...
 * @param	iYellowType: 黄色指示灯状态 0 关， 1 开， 2 闪烁
 * @param	iBlueType:   蓝色指示灯状态 0 关， 1 开， 2 闪烁
 * @param	iGreenType:  绿色指示灯状态 0 关， 1 开， 2 闪烁
 * @param	iRedType:    红色指示灯状态 0 关， 1 开， 2 闪烁
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_SetLightStatus)(int iYellowType, int iBlueType, int iGreenType,  int iRedType);




/** 
 * @fn		CRT_SetLightStatus 
 * @detail	获取读卡器指示灯状态
 * @see		...
 * @param	iYellowType: 输出 黄色指示灯状态 0 关， 1 开， 2 闪烁
 * @param	iBlueType:   输出 蓝色指示灯状态 0 关， 1 开， 2 闪烁
 * @param	iGreenType:  输出 绿色指示灯状态 0 关， 1 开， 2 闪烁
 * @param	iRedType:    输出 红色指示灯状态 0 关， 1 开， 2 闪烁
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_GetLightStatus)(int* iYellowType, int* iBlueType, int* iGreenType,  int* iRedType);




/** 
 * @fn		CRT_BanTypeBCap 
 * @detail	设置读卡器读取TYPE B卡能力
 * @see		...
 * @param	bBan: 是否关闭读TYPE B卡能力。 true 关闭， false 打开 
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_BanTypeBCap)(bool bBan);




//***********************发送CRT603具体功能APDU命令****************************
/** 
 * @fn		CRT_LoadMifareKey 
 * @detail	Mifare卡下载密码
 * @see		...
 * @param	ilocal:   密码存储位置。 0 临时性存储器， 1 非易失存储器
 * @param	iKeyType: 密钥类型。 0 TYPE A类型， 1 TYPE B类型 
 * @param	iKeyNum:  将保存到密钥组号（共0-15组） 
 * @param	byInKeyData: 密码信息。 （共6位，如0xFF,0xFF,0xFF,0xFF,0xFF,0xFF）
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_LoadMifareKey)(int ilocal, int iKeyType, int iKeyNum, BYTE byInKeyData[]);




/** 
 * @fn		CRT_CheckMifareKey 
 * @detail	Mifare卡校验密码
 * @see		...
 * @param	iKeyType: 密钥类型。 0 TYPE A类型， 1 TYPE B类型 
 * @param	iKeyNum:  已下载好的密钥组号（共0-15组） 
 * @param	iBlockNum: 需校验的Mifare卡块号(0为起始位)
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_CheckMifareKey)(int iKeyType, int iKeyNum, int iBlockNum);




/** 
 * @fn		CRT_Read 
 * @detail	非CPU卡读数据操作
 * @see		...
 * @param	bFilica: 是否为filica卡读操作。 true 是filica， false 非filica 
 * @param	iBlockNum: 需读取的卡块号(0为起始位)
 * @param	byReadData: 输出 读取到的数据
 * @param	iReadDataLen: 输出 读取到的数据长度
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_Read)(bool bFilica, int iBlockNum, BYTE byReadData[], int* iReadDataLen);




/** 
 * @fn		CRT_Write 
 * @detail	非CPU卡写数据操作
 * @see		...
 * @param	bFilica: 是否为filica卡读操作。 true 是filica， false 非filica 
 * @param	iBlockNum: 需写入的卡块号(0为起始位)
 * @param	byWriteData: 写入到读卡器上的数据
 * @param	iWriteLen: 写入到读卡器上的数据长度
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_Write)(bool bFilica, int iBlockNum, BYTE byWriteData[], int iWriteLen);




/** 
 * @fn		CRT_GetCardUID 
 * @detail	获取卡片UID信息
 * @see		...
 * @param	szUID: 输出 卡片的UID信息
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_GetCardUID)(char szUID[]);




//***********************发送CRT603具体功能SAM卡命令****************************
/** 
 * @fn		CRT_SAMSlotActivation 
 * @detail	SAM卡切换并激活卡座
 * @see		...
 * @param	iSlotNum: 需切换激活的卡座号 （1-4个，如 1表示SAM1卡座） 
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_SAMSlotActivation)(int iSlotNum);



//***********************磁条卡操作命令****************************
/** 
 * @fn		CRT_ReadMagAllTracks
 * @detail	读所有磁道操作
 * @see		...
 * @param	szTrack1: 磁道1数据 ‘Not’未读取到
 * @param	szTrack2: 磁道2数据 ‘Not’未读取到
 * @param	szTrack3: 磁道3数据 ‘Not’未读取到
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_ReadMagAllTracks)(char szTrack1[], char szTrack2[], char szTrack3[]);


//***********************获取RF卡类型****************************
/** 
 * @fn		CRT_GetRFCardType 
 * @detail	获取RF卡类型
 * @see		...
 * @return	0 无卡，1 TYPE A类型卡， 2 TYPE B类型卡， 3 身份证， 其他 失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_GetRFCardType)();


//***********************读二代证信息命令****************************
/** 
 * @fn		CRT_ReadIDCardInifo 
 * @detail	读二代证信息
 * @see		...
 * @param	crtdef_IdInfo: 输出，读取到的二代证信息
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef int (*pCRT_ReadIDCardInifo)(CRTDef_IDInfo* crtdef_IdInfo);




/** 
 * @fn		CRT_M1ValueProcess 
 * @detail	M1卡值操作
 * @see		...
 * @param	iMode: 输入，操作模式。 1 初始化钱包， 2 增值， 3 减值
 * @param	iBlock: 输入，操作块区。 需绝对地址
 * @param	iValue: 输入，操作金额
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2016/9/19
 */
typedef int (*pCRT_M1ValueProcess)(int iMode, int iBlock, int iValue);



/** 
 * @fn		CRT_M1InquireBalance 
 * @detail	M1卡查询余额
 * @see		...
 * @param	iBlock: 输入，操作块区。 需绝对地址
 * @param	iValue: 输出，查询到的金额值
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2016/9/19
 */
typedef int (*pCRT_M1InquireBalance)(int iBlock, int* iValue);



/** 
 * @fn		CRT_M1BackBlock 
 * @detail	M1卡备份钱包
 * @see		...
 * @param	iBlock: 输入，需备份块区。 需绝对地址
 * @param	iBackBlock: 输入，备份到块区。 需绝对地址
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2016/9/19
 */
typedef int (*pCRT_M1BackBlock)(int iBlock, int iBackBlock);



/** 
 * @fn		CRT_GetIDFinger 
 * @detail	获取二代证指纹信息
 * @see		...
 * @param	byFinger: 输出，获取到的指纹信息(一般为1024个字节)
 * @param	iFingerLen: 输出，指纹信息长度
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2016/10/27
 */
typedef int (*pCRT_GetIDFinger)(BYTE byFinger[], int *iFingerLen);



/** 
 * @fn		CRT_GetIDFinger 
 * @detail	获取二代证DN号
 * @see		...
 * @param	szDNNums: 输出，获取到的DN号
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2016/10/30
 */
typedef int (*pCRT_GetIDDNNums)(char szDNNums[]);



/** 
 * @fn		CRT_GetSAMID 
 * @detail	获取身份证盒子SAM ID
 * @see		...
 * @param	szSAMID: 输出，获取到的SAM ID
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2016/10/30
 */
typedef int (*pCRT_GetSAMID)(char szSAMID[]);



/** 
 * @fn		CRT_SwitchRF 
 * @detail	读卡器开关射频场
 * @see		...
 * @param	iMode: 输入 开关射频场方式，0 开启， 1 关闭
 * @return	0 成功，非0失败
 * @exception ...
 *
 * @author	luowei
 * @date	2016/10/30
 */
typedef int (*pCRT_SwitchRF)(int iMode);



//***********************获取最后一次错误描叙****************************
/** 
 * @fn		CRT_GetLastError 
 * @detail	获取最后一次错误描叙
 * @see		...
 * @return	获取信息
 * @exception ...
 *
 * @author	luowei
 * @date	2015/12/1
 */
typedef char* (*pCRT_GetLastError)();



class CLoadMyLibrary
{
//对外接口函数
public:
	bool LoadMyLibrary(const char* lpDllPath, char* ErrorInfo);
	bool IsLoadSucceed();
	pCRT_OpenConnect          CRT_OpenConnect ;
	pCRT_CloseConnect         CRT_CloseConnect;
	pCRT_GetReaderListName    CRT_GetReaderListName;
	pCRT_SetReaderName        CRT_SetReaderName;
	pCRT_GetReaderType        CRT_GetReaderType;
	pCRT_GetCardStatus        CRT_GetCardStatus;
	pCRT_EjectCard            CRT_EjectCard;
    pCRT_ReaderConnect        CRT_ReaderConnect;
    pCRT_SendApdu             CRT_SendApdu;
    pCRT_SendControlCMD       CRT_SendControlCMD;
    pCRT_HotReset             CRT_HotReset;
    pCRT_SetReaderType        CRT_SetReaderType;
    pCRT_GetVersionInfo       CRT_GetVersionInfo;
    pCRT_AutoBeel	          CRT_AutoBeel;
	pCRT_Beel                 CRT_Beel;
    pCRT_SetLightMode	      CRT_SetLightMode;
	pCRT_GetLightMode         CRT_GetLightMode;
	pCRT_SetLightStatus       CRT_SetLightStatus;
	pCRT_GetLightStatus       CRT_GetLightStatus;
	pCRT_BanTypeBCap          CRT_BanTypeBCap;
	pCRT_LoadMifareKey        CRT_LoadMifareKey;
	pCRT_CheckMifareKey       CRT_CheckMifareKey;
	pCRT_Read                 CRT_Read;
	pCRT_Write                CRT_Write;
	pCRT_GetCardUID           CRT_GetCardUID;
	pCRT_SAMSlotActivation    CRT_SAMSlotActivation;
    pCRT_ReadMagAllTracks     CRT_ReadMagAllTracks;
	pCRT_GetRFCardType        CRT_GetRFCardType;
	pCRT_ReadIDCardInifo      CRT_ReadIDCardInifo;
	pCRT_M1ValueProcess       CRT_M1ValueProcess;
	pCRT_M1InquireBalance     CRT_M1InquireBalance;
	pCRT_M1BackBlock          CRT_M1BackBlock;
	pCRT_GetIDFinger          CRT_GetIDFinger;
	pCRT_GetIDDNNums          CRT_GetIDDNNums;
	pCRT_GetSAMID             CRT_GetSAMID;
	pCRT_SwitchRF             CRT_SwitchRF;
	pCRT_GetLastError         CRT_GetLastError;


private:
	void *  hModule;
	bool returnValue;

public:
	CLoadMyLibrary(void);
	~CLoadMyLibrary(void);
};

#endif //__LOADMYLIBRARY_H__
