#include "LoadMyLibrary.h"
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <string>
using namespace std;
CLoadMyLibrary g_LoadMyLibrary;

//-------------------------------------------------------------------------------------------
bool bFelica = false;
int menu()
{
	int i = 0;
    int iRet = 0;
	int iNums = 0;
	
	printf("    Welcome to CRT_603_CZX Demo:\n");
	printf("    ---------Communication Settings----------------------\n");
	printf("    1:  Open the CRT_603_CZX CardReader.\n");
	printf("    2:  Get  the CardReader List.\n");
	printf("    3:  Set  the Current Work CardReaderList.\n");
	printf("    4:  Get  the CardStatus .\n");
	printf("    5:  CardReader Connect Card.\n");
	printf("    6:  CardReader Eject Card.\n");
	printf("    7:  CardReader Send Apdu.\n");
		
	printf("    ---------CardReader Inter ControlCMD Operation--------\n");
	printf("    9:  CardReader HotReset .\n");
	printf("   10:  Set CardReader Work Type .\n");
	printf("   11:  Get CardReader Work Type .\n");
	printf("   12:  Get CardReader VersionInfo .\n");
	printf("   13:  Set AutoBeel Mode .\n");
	printf("   14:  Set Beel Time .\n");
	printf("   15:  Set Light Mode .\n");
	printf("   16:  Get Light Mode .\n");
	printf("   17:  Set Light Status .\n");
	printf("   18:  Get Light Status .\n");
	printf("   19:  Ben/Select TypeB capability.\n");
		
	printf("    ---------CardReader Inter Apdu Operation---------------\n");
	printf("   20:  S50/S70 LoadKey.\n");
	printf("   21:  S50/S70 CheckKey.\n");
	printf("   22:  S50/S70/Felica Read.\n");
	printf("   23:  S50/S70/Felica Write.\n");
	printf("   24:  Get Card UID.\n");
	printf("   25:  SAM Select And Activation Slot.\n\n");

    printf("    ---------CardReader Magcard Operation---------------\n");
	printf("   26:  Read Mag Tracks.\n");

	printf("    ---------CardReader IDCard Operation---------------\n");
	printf("   27:  Read IDCard Info.\n");
		
	printf("    0:  Exit (Close the CRT_603_CZX CardReader).\n");
	
	
	while(1)
	{
		printf("Please select a menu: ");
		scanf("%d",&i);
		
			
		if (i==0)
		{
		    g_LoadMyLibrary.CRT_CloseConnect();
			printf("Byebye.\n\n");
			exit(1);
		}
		switch(i)
		{
			case 1:
			{
				iRet = g_LoadMyLibrary.CRT_OpenConnect(&iNums);
				if(iRet != 0 || iNums <1)
				{
					fprintf(stderr,"CRT_OpenConnect Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_OpenConnect success! iNums=%d\n\n",iNums);
				}
			}
			break;
			case 2:
			{
				char szListName[128] = {0};
				for(int i=0;i<iNums;i++)
				{
					iRet = g_LoadMyLibrary.CRT_GetReaderListName(i, szListName);
					if(iRet != 0)
					{
						fprintf(stderr,"CRT_GetReaderListName Error iRet:%d\n\n", iRet);
						break;
					}				
					printf("%d :%s\n",i, szListName);
					memset(szListName, 0x00, sizeof(szListName));
				}
				
			}
			break;
			case 3:
			{
				printf("Please select Current Work List Num: ");
				scanf("%d",&i);
				if(i>=iNums || i<0 )
				{
					printf("you chosen is error.\n\n");
				}
				else
				{
					iRet = g_LoadMyLibrary.CRT_SetReaderName(i);
					if(iRet != 0 )
					{
						fprintf(stderr,"CRT_SetReaderName Error iRet:%d\n\n", iRet);
					}
					else
					{
						printf("CRT_SetReaderName success! List Num=%d\n\n",i);
					}
				}
			}
			break;
			case 4:
			{
				iRet = g_LoadMyLibrary.CRT_GetCardStatus();
				if(iRet == 1)
				{
					printf("Have Card\n\n");
				}
				else if(iRet == 2)
				{
					printf("NO Card\n\n");
				}
				else
				{
					printf("Unknown\n\n");
				}
			}
			break;
			case 5:
			{
				BYTE byAtrData[1024] =  {0};
				int iAtrLen = 0;
				iRet = g_LoadMyLibrary.CRT_ReaderConnect(byAtrData, &iAtrLen);
				if(iRet != 0 ||  iAtrLen <=0)
				{
					fprintf(stderr,"CRT_ReaderConnect Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_ReaderConnect success! \n");
					printf("ATR:");
					for(int i=0; i<iAtrLen; i++)
					{
						printf(" %02x",byAtrData[i]);
					}
					printf("\n\n");
				}
			}
			break;
			case 6:
			{
				iRet = g_LoadMyLibrary.CRT_EjectCard();
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_EjectCard Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_EjectCard success! \n\n");
				}
			}
			break;
			case 7:
			{
				BYTE byRecvData[1024] =  {0};
				int iRecvData = 0;
				char szSendData[1024] = {0};
				int iSendData = 0;
				printf("Please Input APDU Commend(example: 0084000004)\n: ");
		
				scanf("%s", szSendData);	
				//string strSendData = szSendData;
				//strSendData = strSendData.Replace(" ", "");  
				iSendData = strlen(szSendData);
				
				printf("Send Data:%s, len=%d",szSendData,iSendData);
	
				printf("\n");
				iRet = g_LoadMyLibrary.CRT_SendApdu((BYTE*)szSendData, iSendData, byRecvData, &iRecvData);
				if(iRet != 0 || iRecvData<2)
				{
					fprintf(stderr,"CRT_SendApdu Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_SendApdu success! \n");
					printf("Recv Data:");
					for(int i=0; i<iRecvData; i++)
					{
						printf(" %02x",byRecvData[i]);
					}
					printf("\n\n");
				}
			}
			break;
			case 9:
			{
				iRet = g_LoadMyLibrary.CRT_HotReset();
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_HotReset Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_HotReset success! \n\n");
				}
			}
			break;
			case 10:
			{
				printf("1: Normal RF mode\n");
				printf("2: Felica mode\n");
				printf("3: PointToPoint mode\n");
				printf("4: ID card mode\n");
				printf("5: Card emulation mode\n");
				printf("Please Input Reader Type\n:");
				
				bFelica = false;
				int iMode =0;
				scanf("%d", &iMode);
				iRet = g_LoadMyLibrary.CRT_SetReaderType(iMode);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_SetReaderType Error iRet:%d\n\n", iRet);
				}
				else
				{
					if(iMode == 2)
					{
						bFelica = true;
					}
					printf("CRT_SetReaderType success! \n\n");
				}
			}
			break;
			case 11:
			{
				printf("1: Normal RF mode\n");
				printf("2: Felica mode\n");
				printf("3: PointToPoint mode\n");
				printf("4: ID card mode\n");
				printf("5: Card emulation mode\n");
				printf("Please Input Reader Type\n:");
				
				bFelica = false;
				int iMode =0;
				iMode = g_LoadMyLibrary.CRT_GetReaderType();
				if(iMode <= 0)
				{
					fprintf(stderr,"CRT_GetReaderType Error iRet:%d\n\n", iMode);
				}
				else
				{
					if(iMode == 1)
					{
						printf("Normal RF mode\n");
					}
					else if(iMode == 2)
					{
						bFelica = true;
						printf("Felica mode\n");
					}
					else if(iMode == 3)
					{
						printf("PointToPoint mode\n");
					}
					else if(iMode == 4)
					{
						printf("ID card mode\n");
					}
					else if(iMode == 5)
					{
						printf("Card emulation mode\n");
					}	
					printf("CRT_SetReaderType success! \n\n");					
				}
			}
			break;
			case 12:
			{			
				printf("0: P/N information\n");
				printf("1: SN information\n");
				printf("2: Firmware version\n");
				printf("3: Build version information\n");
				printf("4: EMID information\n");
				printf("5: DLL version information\n");
				printf("Please Input The information to be queried\n:");
		
				int iMode =0;
				char szVersionInfo[256] = {0};
				scanf("%d", &iMode);
				iRet = g_LoadMyLibrary.CRT_GetVersionInfo(iMode, szVersionInfo);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_GetVersionInfo Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("szVersionInfo=%s\n",szVersionInfo);
					printf("CRT_GetVersionInfo success! \n\n");
				}
			}
			break;
			case 13:
			{
				printf("0: close AutoBeel\n");
				printf("1: open  AutoBeel\n");
				printf("Please Set Open/Close AutoBeel\n:");
				
				int iMode =0;
				scanf("%d", &iMode);
				iRet = g_LoadMyLibrary.CRT_AutoBeel(iMode);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_AutoBeel Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_AutoBeel success! \n\n");
				}
			}
			break;
			case 14:
			{
				iRet = g_LoadMyLibrary.CRT_Beel(1);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_Beel Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_Beel success! \n\n");
				}
			}
			break;
			case 15:
			{
				printf("0: Auto mode\n");
				printf("1: Manual mode\n");
				printf("Please Input The Light Mode\n:");
				
				int iMode =0;
				scanf("%d", &iMode);
				iRet = g_LoadMyLibrary.CRT_SetLightMode(iMode);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_SetLightMode Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_SetLightMode success! \n\n");
				}
			}
			break;
			case 16:
			{			
				iRet = g_LoadMyLibrary.CRT_GetLightMode();
				if(iRet < 0)
				{
					fprintf(stderr,"CRT_GetLightMode Error iRet:%d\n\n", iRet);
				}
				else
				{
					if(iRet == 0)
					{
						printf("Auto mode\n");
					}
					else if(iRet == 1)
					{
						printf("Manual mode\n");
					}
					else
					{
						printf("Unknown mode\n");
					}
					printf("CRT_GetLightMode success! \n\n");
				}
			}
			break;
			case 17:
			{
				printf("Yellow Status: 0 close, 1 open, 2 flashing\n");
				printf("Blue Status: 0 close, 1 open, 2 flashing\n");
				printf("Green Status: 0 close, 1 open, 2 flashing\n");
				printf("Red Status: 0 close, 1 open, 2 flashing\n");
				printf("Please Set The Light Status(','Split)\n:");
				
				int iModeYellow =0;
				int iModeBlue =0;
				int iModeGreen =0;
				int iModeRed =0;
				scanf("%d,%d,%d,%d", &iModeYellow,&iModeBlue,&iModeGreen,&iModeRed);
				//printf("%d,%d,%d,%d",iModeYellow, iModeBlue,iModeGreen,iModeRed);
				iRet = g_LoadMyLibrary.CRT_SetLightStatus(iModeYellow, iModeBlue, iModeGreen, iModeRed);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_SetLightStatus Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_SetLightStatus success! \n\n");
				}
			}
			break;
			case 18:
			{			
				int iModeYellow =0;
				int iModeBlue =0;
				int iModeGreen =0;
				int iModeRed =0;
				iRet = g_LoadMyLibrary.CRT_GetLightStatus(&iModeYellow, &iModeBlue, &iModeGreen, &iModeRed);
				if(iRet < 0)
				{
					fprintf(stderr,"CRT_GetLightStatus Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("LED Status:");
					if(iModeYellow == 0)
					{
						printf("Yellow Close,  ");
					}
					else if(iModeYellow == 1)
					{
						printf("Yellow Open,  ");
					}
					else
					{
						printf("Yellow Flashing,  ");
					}
					
					if(iModeBlue == 0)
					{
						printf("Blue Close,  ");
					}
					else if(iModeYellow == 1)
					{
						printf("Blue Open,  ");
					}
					else
					{
						printf("Blue Flashing,  ");
					}
					
					if(iModeGreen == 0)
					{
						printf("Green Close,  ");
					}
					else if(iModeGreen == 1)
					{
						printf("Green Open,  ");
					}
					else
					{
						printf("Green Flashing,  ");
					}
					
					if(iModeRed == 0)
					{
						printf("Red Close\n");
					}
					else if(iModeRed == 1)
					{
						printf("Red Open\n");
					}
					else
					{
						printf("Red Flashing\n");
					}
					
					printf("CRT_GetLightStatus success! \n\n");
				}
			}
			break;
			case 19:
			{
				printf("0: Open Read TypeB capability\n");
				printf("1: Close Read TypeB capability\n");
				printf("Please Set The Ban TypeB capability\n:");
				
				int iMode =0;
				scanf("%d", &iMode);
				iRet = g_LoadMyLibrary.CRT_BanTypeBCap(iMode);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_BanTypeBCap Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_BanTypeBCap success! \n\n");
				}
			}
			break;
			case 20:
			{
				int ilocal = 1;
				int iKeyType = 0;
				int iKeyNum = 2;
				BYTE byKeyData[20] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
				iRet = g_LoadMyLibrary.CRT_LoadMifareKey(ilocal, iKeyType, iKeyNum, byKeyData);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_LoadMifareKey Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_LoadMifareKey success! \n\n");
				}
			}
			break;
			case 21:
			{
				int iKeyType = 0;
				int iKeyNum = 2;
				int iBlockNum = 0;
				printf("Please Input the Process BlockNums(0-31)\n:");
				scanf("%d", &iBlockNum);

				iRet = g_LoadMyLibrary.CRT_CheckMifareKey( iKeyType, iKeyNum, iBlockNum);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_CheckMifareKey Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_CheckMifareKey success! \n\n");
				}
			}
			break;
			case 22:
			{

				int iBlockNum = 0;
				BYTE byRecvData[1024] =  {0};
			    int iRecvData = 0;
				printf("Please Input the Process BlockNums(0-31)\n:");
				scanf("%d", &iBlockNum);

				iRet = g_LoadMyLibrary.CRT_Read( bFelica, iBlockNum, byRecvData, &iRecvData);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_Read Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("Read Data:");
					for(int i=0; i<iRecvData; i++)
					{
						printf(" %02x",byRecvData[i]);
					}
					printf("\n");
					printf("CRT_Read success! \n\n");
				}
			}
			break;
			case 23:
			{

				int iBlockNum = 0;
				BYTE byWriteData[1024] =  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
			    int iWriteData = 16;
				printf("Please Input the Process BlockNums(0-31)\n:");
				scanf("%d", &iBlockNum);

				iRet = g_LoadMyLibrary.CRT_Write( bFelica, iBlockNum, byWriteData, iWriteData);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_Write Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_Write success! \n\n");
				}
			}
			break;
			case 24:
			{
			    char szUid[256] = {0};
				
				iRet = g_LoadMyLibrary.CRT_GetCardUID(szUid);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_GetCardUID Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("UID:%s\n",szUid);
					printf("CRT_GetCardUID success! \n\n");
				}
			}
			break;
			case 25:
			{
			    printf("Please Input the Process SAM Slot(1-4)\n:");
				int iMode = 0;
				scanf("%d", &iMode);
				
				iRet = g_LoadMyLibrary.CRT_SAMSlotActivation(iMode);
				if(iRet != 0)
				{
					fprintf(stderr,"CRT_SAMSlotActivation Error iRet:%d\n\n", iRet);
				}
				else
				{
					printf("CRT_SAMSlotActivation success! \n\n");
				}
			}
			break;
			case 26:
			{
			    printf("Please Swipe Mag card,TimeOut:20s \n");
			
                char szTrack1[512] = {0};
                char szTrack2[512] = {0};
                char szTrack3[512] = {0};
				struct timeval tvpre, tvcur;
				gettimeofday(&tvpre, NULL);
				gettimeofday(&tvcur, NULL);
			    while(1)
               {
				   if(((tvcur.tv_sec*1000+tvcur.tv_usec/1000)-(tvpre.tv_sec*1000+tvpre.tv_usec/1000)) > 20000)
				   {
					   printf("TimeOut... \n");
					   break;
				   }
				   iRet = g_LoadMyLibrary.CRT_ReadMagAllTracks(szTrack1, szTrack2, szTrack3);
                   if(iRet != 0)
                   {
					   
                       usleep(300);
					   gettimeofday(&tvcur, NULL);
			           continue;
                   }
              
			       printf("szTrack1: %s \n", szTrack1);
				   printf("szTrack2: %s \n", szTrack2);
				   printf("szTrack3: %s \n", szTrack3);
                   break;                              
              }			
			}
			break;
			case 27:
			{
				if(g_LoadMyLibrary.CRT_GetReaderType() != 4){
					iRet = g_LoadMyLibrary.CRT_SetReaderType(4);
					if(iRet != 0){
						printf("CRT_SetReaderType-IDCard Type Error iRet:%d\n\n", iRet);
						break;
					}
					usleep(300*1000);
				}

				BYTE byAtrData[1024] =  {0};
				int iAtrLen = 0;
				iRet = g_LoadMyLibrary.CRT_ReaderConnect(byAtrData, &iAtrLen);
				if(iRet != 0){
					printf("CRT_ReaderConnect Error iRet:%d\n\n", iRet);
					g_LoadMyLibrary.CRT_SetReaderType(1);
					break;
				}

				CRTDef_IDInfo crtdef_idinfo;
				iRet = g_LoadMyLibrary.CRT_ReadIDCardInifo(&crtdef_idinfo);
				if(iRet != 0){
					printf("CRT_ReadIDCardInifo Error iRet:%d\n\n", iRet);
					g_LoadMyLibrary.CRT_SetReaderType(1);
					break;
				}

				char szIDInfo[1024] = {0};
				printf("name:%s, sex:%s, nation:%s, bornday:%s\n  \ 
					    address:%s\n idnum:%s\n issued:%s, vaild:%s-%s\n", \
					    crtdef_idinfo.szName,crtdef_idinfo.szSex, crtdef_idinfo.szNation, \
					    crtdef_idinfo.szBornDay,crtdef_idinfo.szAddress,crtdef_idinfo.szIDNum, \
					    crtdef_idinfo.szIssued,crtdef_idinfo.szBeginValidity,crtdef_idinfo.szEndValidity);

				g_LoadMyLibrary.CRT_SetReaderType(1);
			}
			break;
			default:
			printf("you chosen is error.\n\n");
			break;
			
		}
	}
}

int main()
{
	char szErrInfo[256] = {0};
	if(!g_LoadMyLibrary.LoadMyLibrary("./CRT_603_CZ7.so", szErrInfo))
	{
		fprintf(stderr,"LoadMyLibrary:%s\n\n",szErrInfo);
		exit(0);
	}
	
	menu();
	
	return 0;
}
