#include "LoadMyLibrary.h"

CLoadMyLibrary::CLoadMyLibrary(void)
{
	hModule = NULL;
	CRT_OpenConnect            = NULL;
	CRT_CloseConnect           = NULL;
	CRT_GetReaderListName      = NULL;
	CRT_SetReaderName          = NULL;
	CRT_GetReaderType          = NULL;
	CRT_GetCardStatus          = NULL;
	CRT_EjectCard              = NULL;
    CRT_ReaderConnect          = NULL;
    CRT_SendApdu               = NULL;
    CRT_SendControlCMD         = NULL;
    CRT_HotReset               = NULL;
    CRT_SetReaderType          = NULL;
    CRT_GetVersionInfo         = NULL;
    CRT_AutoBeel               = NULL;
	CRT_Beel                   = NULL;
    CRT_SetLightMode           = NULL;
	CRT_GetLightMode           = NULL;
	CRT_SetLightStatus         = NULL;
	CRT_GetLightStatus         = NULL;
	CRT_BanTypeBCap            = NULL;
	CRT_LoadMifareKey          = NULL;
	CRT_CheckMifareKey         = NULL;
	CRT_Read                   = NULL;
	CRT_Write                  = NULL;
	CRT_GetCardUID             = NULL;
	CRT_SAMSlotActivation      = NULL;
    CRT_ReadMagAllTracks       = NULL;
	CRT_GetRFCardType          = NULL;
	CRT_ReadIDCardInifo        = NULL;
	CRT_M1ValueProcess         = NULL;
	CRT_M1InquireBalance       = NULL;
	CRT_M1BackBlock            = NULL;
	CRT_GetIDFinger            = NULL;
	CRT_GetIDDNNums            = NULL;
	CRT_GetSAMID               = NULL;
	CRT_SwitchRF               = NULL;
	CRT_GetLastError           = NULL;

}

CLoadMyLibrary::~CLoadMyLibrary(void)
{
	if (hModule != NULL)
	{
		dlclose(hModule);
		hModule = NULL;
	}
}


bool CLoadMyLibrary::LoadMyLibrary(const char* lpDllPath, char* ErrorInfo)
{
	//定义变量
	returnValue = false;

	//判断参数
	if(ErrorInfo == NULL)
	{
		goto ExitLine;
	}
	//加载动态库
	if(hModule)
	{
		returnValue = true;
		goto ExitLine;
	}

	hModule = dlopen(lpDllPath, RTLD_LAZY);
	if(hModule == NULL)
	{
		sprintf(ErrorInfo, "加载传入:%s失败!",lpDllPath);
		//加载传入路径失败，再加载一次当前路径默认DLL
		hModule = dlopen("./CRT_603_CZ7.so", RTLD_LAZY);
		if(hModule == NULL)
		{
			sprintf(ErrorInfo, "加载默认及传入路径失败!");
			goto ExitLine;
		}
	}

	//******************************************************************************************************************
	//加载CRT_OpenConnect
	CRT_OpenConnect = (pCRT_OpenConnect)dlsym(hModule, "CRT_OpenConnect");
	if(!CRT_OpenConnect)
	{
		sprintf(ErrorInfo, "加载'CRT_OpenConnect'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_CloseConnect
	CRT_CloseConnect = (pCRT_CloseConnect)dlsym(hModule, "CRT_CloseConnect");
	if(!CRT_CloseConnect)
	{
		sprintf(ErrorInfo, "加载'CRT_CloseConnect'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_GetReaderListName
	CRT_GetReaderListName = (pCRT_GetReaderListName)dlsym(hModule, "CRT_GetReaderListName");
	if(!CRT_GetReaderListName)
	{
		sprintf(ErrorInfo, "加载'CRT_GetReaderListName'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_SetReaderName
	CRT_SetReaderName = (pCRT_SetReaderName)dlsym(hModule, "CRT_SetReaderName");
	if(!CRT_SetReaderName)
	{
		sprintf(ErrorInfo, "加载'CRT_SetReaderName'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_GetReaderType
	CRT_GetReaderType = (pCRT_GetReaderType)dlsym(hModule, "CRT_GetReaderType");
	if(!CRT_GetReaderType)
	{
		sprintf(ErrorInfo, "加载'CRT_GetReaderType'失败!");
		goto ExitLine;
	}

	//******************************************************************************************************************
	//加载CRT_GetCardStatus
	CRT_GetCardStatus = (pCRT_GetCardStatus)dlsym(hModule, "CRT_GetCardStatus");
	if(!CRT_GetCardStatus)
	{
		sprintf(ErrorInfo, "加载'CRT_GetCardStatus'失败!");
		goto ExitLine;
	}

	//******************************************************************************************************************
	//加载CRT_EjectCard
	CRT_EjectCard = (pCRT_EjectCard)dlsym(hModule, "CRT_EjectCard");
	if(!CRT_EjectCard)
	{
		sprintf(ErrorInfo, "加载'CRT_EjectCard'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_ReaderConnect
	CRT_ReaderConnect = (pCRT_ReaderConnect)dlsym(hModule, "CRT_ReaderConnect");
	if(!CRT_ReaderConnect)
	{
		sprintf(ErrorInfo, "加载'CRT_ReaderConnect'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_SendApdu
	CRT_SendApdu = (pCRT_SendApdu)dlsym(hModule, "CRT_SendApdu");
	if(!CRT_SendApdu)
	{
		sprintf(ErrorInfo, "加载'CRT_SendApdu'失败!");
		goto ExitLine;
	}
		
	//******************************************************************************************************************
	//加载CRT_SendControlCMD
	CRT_SendControlCMD = (pCRT_SendControlCMD)dlsym(hModule, "CRT_SendControlCMD");
	if(!CRT_SendControlCMD)
	{
		sprintf(ErrorInfo, "加载'CRT_SendControlCMD'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_HotReset
	CRT_HotReset = (pCRT_HotReset)dlsym(hModule, "CRT_HotReset");
	if(!CRT_HotReset)
	{
		sprintf(ErrorInfo, "加载'CRT_HotReset'失败!");
		goto ExitLine;
	}

	//******************************************************************************************************************
	//加载CRT_SetReaderType
	CRT_SetReaderType = (pCRT_SetReaderType)dlsym(hModule, "CRT_SetReaderType");
	if(!CRT_SetReaderType)
	{
		sprintf(ErrorInfo, "加载'CRT_SetReaderType'失败!");
		goto ExitLine;
	}

	//******************************************************************************************************************
	//加载CRT_GetVersionInfo
	CRT_GetVersionInfo = (pCRT_GetVersionInfo)dlsym(hModule, "CRT_GetVersionInfo");
	if(!CRT_GetVersionInfo)
	{
		sprintf(ErrorInfo, "加载'CRT_GetVersionInfo'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_AutoBeel
	CRT_AutoBeel = (pCRT_AutoBeel)dlsym(hModule, "CRT_AutoBeel");
	if(!CRT_AutoBeel)
	{
		sprintf(ErrorInfo, "加载'CRT_AutoBeel'失败!");
		goto ExitLine;
	}

	//******************************************************************************************************************
	//加载CRT_Beel
	CRT_Beel = (pCRT_Beel)dlsym(hModule, "CRT_Beel");
	if(!CRT_Beel)
	{
		sprintf(ErrorInfo, "加载'CRT_Beel'失败!");
		goto ExitLine;
	}

	//******************************************************************************************************************
	//加载CRT_SetLightMode
	CRT_SetLightMode = (pCRT_SetLightMode)dlsym(hModule, "CRT_SetLightMode");
	if(!CRT_SetLightMode)
	{
		sprintf(ErrorInfo, "加载'CRT_SetLightMode'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_GetLightMode
	CRT_GetLightMode = (pCRT_GetLightMode)dlsym(hModule, "CRT_GetLightMode");
	if(!CRT_GetLightMode)
	{
		sprintf(ErrorInfo, "加载'CRT_GetLightMode'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_SetLightStatus
	CRT_SetLightStatus = (pCRT_SetLightStatus)dlsym(hModule, "CRT_SetLightStatus");
	if(!CRT_SetLightStatus)
	{
		sprintf(ErrorInfo, "加载'CRT_SetLightStatus'失败!");
		goto ExitLine;
	}
		
	//******************************************************************************************************************
	//加载CRT_GetLightStatus
	CRT_GetLightStatus = (pCRT_GetLightStatus)dlsym(hModule, "CRT_GetLightStatus");
	if(!CRT_GetLightStatus)
	{
		sprintf(ErrorInfo, "加载'CRT_GetLightStatus'失败!");
		goto ExitLine;
	}

	//******************************************************************************************************************
	//加载CRT_BanTypeBCap
	CRT_BanTypeBCap = (pCRT_BanTypeBCap)dlsym(hModule, "CRT_BanTypeBCap");
	if(!CRT_BanTypeBCap)
	{
		sprintf(ErrorInfo, "加载'CRT_BanTypeBCap'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_LoadMifareKey
	CRT_LoadMifareKey = (pCRT_LoadMifareKey)dlsym(hModule, "CRT_LoadMifareKey");
	if(!CRT_LoadMifareKey)
	{
		sprintf(ErrorInfo, "加载'CRT_LoadMifareKey'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_CheckMifareKey
	CRT_CheckMifareKey = (pCRT_CheckMifareKey)dlsym(hModule, "CRT_CheckMifareKey");
	if(!CRT_CheckMifareKey)
	{
		sprintf(ErrorInfo, "加载'CRT_CheckMifareKey'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_Read
	CRT_Read = (pCRT_Read)dlsym(hModule, "CRT_Read");
	if(!CRT_Read)
	{
		sprintf(ErrorInfo, "加载'CRT_Read'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_Write
	CRT_Write = (pCRT_Write)dlsym(hModule, "CRT_Write");
	if(!CRT_Write)
	{
		sprintf(ErrorInfo, "加载'CRT_Write'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_GetCardUID
	CRT_GetCardUID = (pCRT_GetCardUID)dlsym(hModule, "CRT_GetCardUID");
	if(!CRT_GetCardUID)
	{
		sprintf(ErrorInfo, "加载'CRT_GetCardUID'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_SAMSlotActivation
	CRT_SAMSlotActivation = (pCRT_SAMSlotActivation)dlsym(hModule, "CRT_SAMSlotActivation");
	if(!CRT_SAMSlotActivation)
	{
		sprintf(ErrorInfo, "加载'CRT_SAMSlotActivation'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_ReadMagAllTracks
	CRT_ReadMagAllTracks = (pCRT_ReadMagAllTracks)dlsym(hModule, "CRT_ReadMagAllTracks");
	if(!CRT_ReadMagAllTracks)
	{
		sprintf(ErrorInfo, "加载'CRT_ReadMagAllTracks'失败!");
		goto ExitLine;
	}

	
	//******************************************************************************************************************
	//加载CRT_GetRFCardType
	CRT_GetRFCardType = (pCRT_GetRFCardType)dlsym(hModule, "CRT_GetRFCardType");
	if(!CRT_GetRFCardType)
	{
		sprintf(ErrorInfo, "加载'CRT_GetRFCardType'失败!");
		goto ExitLine;
	}
	
	
	//******************************************************************************************************************
	//加载CRT_ReadIDCardInifo
	CRT_ReadIDCardInifo = (pCRT_ReadIDCardInifo)dlsym(hModule, "CRT_ReadIDCardInifo");
	if(!CRT_ReadIDCardInifo)
	{
		sprintf(ErrorInfo, "加载'CRT_ReadIDCardInifo'失败!");
		goto ExitLine;
	}

	//******************************************************************************************************************
	//加载CRT_M1ValueProcess
	CRT_M1ValueProcess = (pCRT_M1ValueProcess)dlsym(hModule, "CRT_M1ValueProcess");
	if(!CRT_M1ValueProcess)
	{
		sprintf(ErrorInfo, "加载'CRT_M1ValueProcess'失败!");
		goto ExitLine;
	}

	//******************************************************************************************************************
	//加载CRT_M1InquireBalance
	CRT_M1InquireBalance = (pCRT_M1InquireBalance)dlsym(hModule, "CRT_M1InquireBalance");
	if(!CRT_M1InquireBalance)
	{
		sprintf(ErrorInfo, "加载'CRT_M1InquireBalance'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_M1BackBlock
	CRT_M1BackBlock = (pCRT_M1BackBlock)dlsym(hModule, "CRT_M1BackBlock");
	if(!CRT_M1BackBlock)
	{
		sprintf(ErrorInfo, "加载'CRT_M1BackBlock'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_GetIDFinger
	CRT_GetIDFinger = (pCRT_GetIDFinger)dlsym(hModule, "CRT_GetIDFinger");
	if(!CRT_GetIDFinger)
	{
		sprintf(ErrorInfo, "加载'CRT_GetIDFinger'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_GetIDDNNums
	CRT_GetIDDNNums = (pCRT_GetIDDNNums)dlsym(hModule, "CRT_GetIDDNNums");
	if(!CRT_GetIDDNNums)
	{
		sprintf(ErrorInfo, "加载'CRT_GetIDDNNums'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_GetSAMID
	CRT_GetSAMID = (pCRT_GetSAMID)dlsym(hModule, "CRT_GetSAMID");
	if(!CRT_GetSAMID)
	{
		sprintf(ErrorInfo, "加载'CRT_GetSAMID'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_SwitchRF
	CRT_SwitchRF = (pCRT_SwitchRF)dlsym(hModule, "CRT_SwitchRF");
	if(!CRT_SwitchRF)
	{
		sprintf(ErrorInfo, "加载'CRT_SwitchRF'失败!");
		goto ExitLine;
	}
	
	//******************************************************************************************************************
	//加载CRT_GetLastError
	CRT_GetLastError = (pCRT_GetLastError)dlsym(hModule, "CRT_GetLastError");
	if(!CRT_GetLastError)
	{
		sprintf(ErrorInfo, "加载'CRT_GetLastError'失败!");
		goto ExitLine;
	}

	returnValue = true;

ExitLine:
	if(!returnValue && hModule)
	{
		dlclose(hModule);
	}
	return returnValue;
}

bool CLoadMyLibrary::IsLoadSucceed()
{
	if (!hModule && !returnValue)
	{
		return false;
	}
	return true;
}
