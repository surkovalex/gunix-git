 /******************************************************************************  
* Filename:    sdmc_conax.h  
* Author:      X.Q.CHEN
* Date:        Nov 2016
* Description: Conax CA APP interface & data struct & message type 
*******************************************************************************/

#ifndef _SDMC_CONAX_H_
#define _SDMC_CONAX_H_

#include "SDMCCAPublic.h"

#define CONAX_LABEL_NAME_MAX    		32 //������Ϣ����󳤶�
#define CONAX_DEBIT_MAX         		100 //DEBIT����¼��
#define CONAX_CREDIT_MAX      			100 //credit����¼��
#define CONAX_TEXT_SIZE				256 //����Ϣ��󳤶�
#define CONAX_ES_NUM					16 //���ɽ��ES����
#define CONAX_ID_NUM       			256 //���CAϵͳID����
#define CONAX_CURRENCY_LEN				8 //CURRENCY��󳤶�
#define CONAX_PIN_MAX               	4 //���pin��λ��
#define CONAX_FINGERPRINT_LEN			32//ָ����󳤶�

//Conax��Ҫ�����˽����Ϣ
typedef enum
{
	CONAX_EVENT_NEW_EMAIL = SDMCCA_CONAX_EVENT,				//new email 
    CONAX_EVENT_SHORT_MSG,              					// from Emm/ECM ulParm2 = (unsigned long)&ConaxShortMsg_S
    CONAX_EVENT_FINGER_PRINT,           					// from Emm/ECM ulParm2 = (unsigned long)&ConaxFingerprint_S 
    CONAX_EVENT_PPV_PREVIEW,               	//"PPV Preview"
    CONAX_EVENT_PPV_EXPIRED,					// "PPV Expired"
    CONAX_EVENT_NO_ACCESS_TO_NETWORK,      	// "No access - network block"
    CONAX_EVENT_ACCEPT_VIEW,               	// start viewing dialog box, ulParm2 = ConaxAcceptViewInfo_S
    CONAX_EVENT_ORDER_INFO,                	// ordering dialog box, ulParm2 = ConaxOrderInfo_S
    CONAX_EVENT_PPV_REQUEST,               	// token access dialog box, ulParm2 = ConaxPPVRequestInfo_S
    CONAX_EVENT_OTHER_CA,					//other CA program
}CAConaxEvent_E;

//��ĸ��
typedef enum
{
    CONAX_RAT_G,                //for the family
    CONAX_RAT_PG,               //with parental guidance
    CONAX_RAT_A,                //over 18
    CONAX_RAT_X,                //erotic
    CONAX_RAT_XXX               //erotic//hyb@090817
}ConaxMaturityRating_E;

typedef struct
{
    ConaxMaturityRating_E eMatRat;
    unsigned char aucPin[CONAX_PIN_MAX]; //max password num is 4
}ConaxChangeMatRat_S;

typedef struct
{
    unsigned char aucOldPin[CONAX_PIN_MAX];
    unsigned char aucNewPin[CONAX_PIN_MAX];
}ConaxChangePassword_S;

typedef enum
{
    CONAX_EMAIL_NO_SEQ = 0,        //��˳��Ҫ��
    CONAX_EMAIL_TIME_ASC,          //����ʱ������ʼ�����ǰ��
    CONAX_EMAIL_TIME_DESC,         //����ʱ������ʼ����ں���
    CONAX_EMAIL_UNREAD_ASC,        //δ���ʼ�����ǰ��
    CONAX_EMAIL_UNREAD_DESC,       //δ���ʼ����ں���    
    CONAX_EMAIL_UNREAD_TIME_ASC,   //δ���ʼ���ʱ������ʼ�����ǰ��
    CONAX_EMAIL_UNREAD_TIME_DESC,  //δ���ʼ���ʱ������ʼ����ں���,��0����δ���������ʼ�
    CONAX_EMAIL_MAIL_ID_ASC,       //mail id��������  
    CONAX_EMAIL_MAIL_ID_DESC,      //mail id��������
    CONAX_EMAIL_SHOW_TIME_ASC,
    CONAX_EMAIL_MAX
}ConaxEmailSeq_E;

//��һ�ֶα�ʾ��Ϣ����CONAX���ڶ��ֶα�ʾ֪ͨ���ͣ������ֶα�ʾ֪ͨ����
typedef struct
{   
    unsigned char   	ucSmcStatus;      //����״̬(�忨����δ�忨)
    unsigned short  	wLanguage;        //language,should be displayed as a decimal number with 1-3 digits
    unsigned char   	ucInterfaceVer;    //interface version
    unsigned char		ucNumOfSession;    //number of session,should be displayed as a decimal number
    unsigned char		aucLibVersion[128]; //lib version from the casGetLibVersion
    unsigned char		aucSoftVersion[20]; //software version
    unsigned char		aucCardId[16];     //card number, should be displayed as a decimal number, like" XXX XXXX XXXX - X"
    unsigned char		aucChipId[16];     //chip id,display as 3-4-4 format,interval space.eg:123 4567 8901
    unsigned short	awCaSysId[CONAX_ID_NUM];	//ca system id, each one should be displayed as a hexadecimal number with four digits
    unsigned char		ucCaSysIdNum;      //number of ca system id
}ConaxCardInfo_S;

typedef struct
{
    unsigned int    uYear; 
    unsigned int    uMonth;
    unsigned int    uDay;
    unsigned int    uHour;
    unsigned int    uMinute;
    unsigned int    uSecond;
    unsigned int    uCentisecond;
}ConaxDateTime_S;

typedef struct
{
	unsigned char		ucId;                     //��ϢID
	unsigned short	wDuration;               //ÿ����ʾ����ʱ��
	unsigned char		ucRepetition;             //��ʾ����
	unsigned char		ucInterval;               //��ʾ���ʱ��
	ConaxDateTime_S    	stShowTime;              //��ʼ��ʾʱ�䣬������Ч��������Ч
	unsigned char		ucTextLen;                //���ݳ���
	unsigned char		aucText[CONAX_TEXT_SIZE];//����Ϣ����
}ConaxShortMsg_S;

typedef struct
{
	unsigned short			wDuration;    //����ʱ��,��λΪ���루�ٷ�֮һ��)
	unsigned short			wPosition_x;  //���Ͻ�X����
	unsigned short			wPosition_y;  //���Ͻ�y����
	unsigned char				ucHeight;     //�߶�
	ConaxDateTime_S				stShowTime;   //�ꡢ�¡�����Ч��������Ч
	unsigned char				aucFingerText[CONAX_FINGERPRINT_LEN];//ָ������
	signed int             	iLength;
}ConaxFingerprint_S;

typedef struct
{
	unsigned short		wMinutesLeft;
	unsigned char			aucLabel[CONAX_LABEL_NAME_MAX];//program name
	unsigned short		wProductRef;                  //no need to display for the moment
}ConaxAcceptViewInfo_S;

typedef struct
{
	unsigned short 		wProductRef; //no need to display for the moment
	float 					fPrice;       // ��Ŀ�۸�
    unsigned char        aucCurrency[CONAX_CURRENCY_LEN];
	unsigned char  		aucProductLabel[CONAX_LABEL_NAME_MAX];//����
}ConaxOrderInfo_S;

typedef struct
{
	unsigned short		wPurseBalance;         // ��ǰʹ��Ǯ�������
	unsigned char       	ucInsufficientTokens;   // 1: ��������
	unsigned char       	ucTokensMode;           // 0: ppv per event       1: ppv per time
	unsigned short      	wEventcost;           // ��Ŀ�۸�
	unsigned short      	wEventTag;
	unsigned char       	aucProgramLabel[CONAX_LABEL_NAME_MAX];// ��Ŀ���ƣ��ַ���
	unsigned char			aucPurseLabel[CONAX_LABEL_NAME_MAX]; //Ǯ�����ƣ��ַ���
}ConaxPPVRequestInfo_S;



//�����¼
typedef struct
{ 
    ConaxDateTime_S stStart;        //  �ꡢ�¡�����Ч��������Ч
    ConaxDateTime_S stEnd;          //  �ꡢ�¡�����Ч��������Ч
    unsigned int    uEntitlement;  //��ʶ������Ȩ��Ϣ
}ConaxAuthPeriod_S;

typedef struct
{
    unsigned char       aucLabel[CONAX_LABEL_NAME_MAX];
    unsigned short      wRefID;           //��Ŀ����
    ConaxAuthPeriod_S   astAuthPeriod[2]; //��Ȩ��Ϣ
}ConaxSubscriptionInfo_S;

//ppv Event ��¼
typedef struct
{   
    unsigned char   	aucLabel[CONAX_LABEL_NAME_MAX]; //����
    unsigned int    	uEventID;                       //��Ŀ����
    ConaxDateTime_S  	stStart;                       // �롢������Ч��������Ч
    ConaxDateTime_S  	stEnd;                         // �롢������Ч��������Ч
    unsigned short  	wNumLeft;                       //ʣ��������
    unsigned short  	wAuthType;                      //0:time-limited access; 1:unlimited access; 2:credit-based access; 3:reserved
}ConaxPPVEventInfo_S;

typedef struct
{
    unsigned short  wPurseRef;//Ǯ������
    unsigned int    uBalance;//���
    unsigned char   aucLabel[CONAX_LABEL_NAME_MAX]; //����
 }ConaxPurseInfo_S;

typedef struct
{
	unsigned int		  	uCreditTokens;                  //����
	unsigned char		  	aucLabel[CONAX_LABEL_NAME_MAX]; //����
}ConaxCreditStatus_S;

typedef struct
{
    unsigned int        uTotalNum;                     //��¼����
    ConaxCreditStatus_S astDebitStatus[CONAX_DEBIT_MAX];//���Ѽ�¼
}ConaxDebitInfo_S;

typedef struct
{
	unsigned int    uTotalNum;                       //��Ϣ����
	ConaxCreditStatus_S  astCreditStatus[CONAX_CREDIT_MAX];//������Ϣ
}ConaxCreditInfo_S;

//��ö�ٻ�û���ƣ���������
typedef enum
{
	CONAX_SUCCESS = 0,						//�����ɹ�
	CONAX_WRONG_PASSWORD,					//�������
	CONAX_FAILURE = -1                      //����ʧ��
}ConaxReturnType_E;	


/*
//Note:ʹ�����½ӿ�ʱע�⣺
//1��һ��Ҫʹ��ö�������ã��������ܻ��޸�
//2��ʹ��ConaxPlugIn->getProperty�ӿ�ͨ��ConaxAPI_E����������ָ���ӿڣ�ע���������͵�ת�����ر��ǽṹ����ڶ������
*/

/*
  @brief SDMCCA_PROPERTY_CA_INFO ��ȡCA������Ϣ�����ӿ�
  @param[in] pVoid ��ʹ�ô˲���,������ʱʹ��NULL
  @param[out] ConaxCardInfo_S *pstCardInfoָ��CA������Ϣ�ṹ��ָ��
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_SUBSCRIPTION_NUM ��ȡ�����¼����
  @param[in] pVoid ��ʹ�ô˲���,������ʱʹ��NULL
  @param[out]unsigned int * puNum���ع����¼����
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/
	
/*
  @brief SDMCCA_PROPERTY_SUBSCRIPTION_INFO��ȡָ����Ź����¼������
  @param[in]unsigned int * puRecordIndex   ��Ŵ�1��ʼ
  @param[out]ConaxSubscriptionInfo_S * pstSubRecord 
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_PPV_EVENT_NUM��ȡPPV EVENT ��¼����
  @param[in] pVoid ��ʹ�ô˲���,������ʱʹ��NULL
  @param[out] int * piEventNum ����EVENT��¼���� 
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_PPVEVENT_INFO��ȡָ�����PPV EVENT  ��¼������
  @param[in] unsigned int * puRecordIndex 
  @param[out] ConaxPPVEventInfo_S * pstPpvRecord 
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_PURSE_NUM��ȡǮ��������
  @param[in] pVoid ��ʹ�ô˲���,������ʱʹ��NULL  
  @param[out] int * piPurseNum 
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_PURSE_INFO��ȡָ�����Ǯ�� ״̬
  @param[in] unsigned int * puPurseIndex ��Ŵ�1��ʼ
  @param[out] ConaxPurseInfo_S * pstPurseInfo 
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_DEBIT_INFO��ȡָ�����Ǯ�� ��Debit ״̬
  @param[in] unsigned int * puPurseIndex ��Ŵ�1��ʼ
  @param[out] ConaxDebitInfo_S ** ppstDebitInfo 
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_CREDIT_INFO��ȡָ�����Ǯ�� ��Credit ״̬
  @param[in] unsigned int * puPurseIndex ��Ŵ�1��ʼ
  @param[out] ConaxCreditInfo_S** ppstCreditInfo 
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_MATURITY_RAT��ȡ����ǰ�ĸ�ĸ��
  @param[in] pVoid ��ʹ�ô˲���,������ʱʹ��NULL
  @param[out] ConaxMaturityRating_E * peMat��ĸ���� 
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_CHANGE_MATURITY_RAT�޸Ŀ��ĸ�ĸ��
  @param[in] ConaxChangeMatRat_S * pstMatRat ��ĸ���𼰿�����
  @param[out] pVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_ACCEPT_MATURITY_RAT��������ȷ���տ���ĸ�����ƽ�Ŀ
  @param[in] unsigned char * pucPin ������ 
  @param[out] pVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @return ����CONAX_WRONG_PASSWORD��ʾ�������
  Note:
*/

/*
  @brief SDMCCA_CANCEL_MATURITY_RATȡ����ĸ��������ʾ�򣬲��տ���ǰ��Ŀ
  @param[in] pVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @param[out] pVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @return ����CONAX_WRONG_PASSWORD��ʾ�������
  Note:
*/

/*
  @brief SDMCCA_ACCEPT_START_VIEW��������ȷ���տ��۷�
  @param[in] unsigned char * pucPin ������ 
  @param[out]pVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_CANCEL_START_VIEWȡ���۷ѽ�Ŀ�ۿ���ʾ�򣬲��տ���ǰ��Ŀ
  @param[int]pInVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @param[out]pOutVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @return ����CONAX_WRONG_PASSWORD��ʾ�������
  Note:
*/

/*
  @brief SDMCCA_ACCEPT_ORDER_INFO��������ȷ�϶�����ǰ��Ŀ
  @param[in] unsigned char * pucPin ������ 
  @param[out]pVoid ��ʹ�ô˲�����������ʱʹ��NULL  
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_CANCEL_ORDER_INFOȡ����Ŀ������ʾ�򣬲��տ���ǰ��Ŀ
  @param[in]pInVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @param[out]pOutVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @return ����CONAX_WRONG_PASSWORD��ʾ�������
  Note:
*/

/*
  @brief SDMCCA_ACCEPT_PPV_REQUEST��������ȷ�Ϲ���PPV��Ŀ
  @param[in] unsigned char * pucPin ������ 
  @param[out]pVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

/*
  @brief SDMCCA_CANCEL_PPV_REQUESTȡ��PPV������ʾ�򣬲��տ���ǰ��Ŀ
  @param[int]pInVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @param[out]pOutVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @return ����CONAX_WRONG_PASSWORD��ʾ�������
  Note:
*/

/*
  @brief SDMCCA_CHANGE_CARD_PIN�޸Ŀ�����
  @param[in] ConaxChangePassword_S * pstChangePinCode �����룬������ 
  @param[out]pVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @return �ο�CONAX_Return_Type_E������붨��
  Note:if the user has entered two new PINs that do not match,"PIN confirmation does not match" should be displayed
*/

/*
  @brief SDMCCA_SET_EMAIL_READ_FLAG��ָ���ʼ�����Ϊ�Ѷ�
  @param[in] unsigned int * puMailID �ʼ�ID 
  @param[out]pVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @return ����CONAX_WRONG_PASSWORD��ʾ�������
  Note:
*/

/*
  @brief SDMCCA_SET_EMAIL_SEQUENCE�����ʼ�����˳��
  @param[in] ConaxEmailSeq_E * peMSeq ����ʽ 
  @param[out]pVoid ��ʹ�ô˲�����������ʱʹ��NULL
  @return �ο�CONAX_Return_Type_E������붨��
  Note:
*/

#endif


