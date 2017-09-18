
#ifndef _SDMCCA_CONAXINFEX_H_
#define _SDMCCA_CONAXINFEX_H_

#include "SDMCCAInf_prv.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define ConaxCA_MAX_FINGERPRINT_LEN		256/*32*/    //ָ����Ϣ����󳤶�
#define ConaxCA_MAX_LABEL_NAME_LEN       32    //������Ϣ����󳤶�
#define ConaxCA_MAX_DEBIT_NUM         	100   //DEBIT����¼��
#define ConaxCA_MAX_CREDIT_NUM         	100   //credit����¼��
#define ConaxCA_MAX_TEXT_SIZE			256   //����Ϣ��󳤶�
#define ConaxCA_MAX_ES_NUM				16    //���ɽ��ES����
#define ConaxCA_MAX_CASYSTEMID_NUM       256   //���CAϵͳID����
#define ConaxCA_MAX_CURRENCY_LEN			8     //CURRENCY��󳤶�

//��ĸ��
typedef enum
{
	ConaxRAT_G,                //for the family
	ConaxRAT_PG,               //with parental guidance
	ConaxRAT_A,                //over 18
	ConaxRAT_X,                //erotic
    ConaxRAT_XXX               //erotic//hyb@090817
}ConaxCaMaturityRating;

typedef enum
{
    SDMCCA_EMAIL_NO_SEQ = 0,        //��˳��Ҫ��
    SDMCCA_EMAIL_TIME_ASC,          //����ʱ������ʼ�����ǰ��
    SDMCCA_EMAIL_TIME_DESC,         //����ʱ������ʼ����ں���
    SDMCCA_EMAIL_UNREAD_ASC,        //δ���ʼ�����ǰ��
    SDMCCA_EMAIL_UNREAD_DESC,       //δ���ʼ����ں���    
    SDMCCA_EMAIL_UNREAD_TIME_ASC,   //δ���ʼ���ʱ������ʼ�����ǰ��
    SDMCCA_EMAIL_UNREAD_TIME_DESC,  //δ���ʼ���ʱ������ʼ����ں���,��0����δ���������ʼ�
    SDMCCA_EMAIL_MAIL_ID_ASC,       //mail id��������  
    SDMCCA_EMAIL_MAIL_ID_DESC,      //mail id��������
    SDMCCA_EMAIL_SHOW_TIME_ASC,
    SDMCCA_EMAIL_MAX
}SDMCCA_Email_Seq_E;

//conax part start 
typedef struct
{
	unsigned int		   m_dwYear; 
	unsigned int		   m_dwMonth;
	unsigned int		   m_dwDay;
	unsigned int		   m_dwHour;
	unsigned int		   m_dwMinute;
	unsigned int		   m_dwSecond;
	unsigned int		   m_dwCentisecond;
}SDMCCaDateTime;

typedef struct
{   
    unsigned short              m_wLanguage;        //language,should be displayed as a decimal number with 1-3 digits
    unsigned char         		m_cInterfaceVer;    //interface version
    unsigned char         		m_cNumOfSession;    //number of session,should be displayed as a decimal number
    unsigned char			    m_cSoftVersion[20]; //software version
    unsigned char               m_szCardId[16];     //card number, should be displayed as a decimal number, like" XXX XXXX XXXX - X"
    unsigned char			    m_acChipId[16];     //chip id,display as 3-4-4 format,interval space.eg:123 4567 8901
    unsigned short              m_awCaSysId[ConaxCA_MAX_CASYSTEMID_NUM];//ca system id, each one should be displayed as a hexadecimal number with four digits
    unsigned char               m_cCaSysIdNum;      //number of ca system id
} SDMCCaConaxInfo;

typedef struct
{
	unsigned short		m_wMinutesLeft;
	unsigned char		m_acLabel[ConaxCA_MAX_LABEL_NAME_LEN];//program name
	unsigned int		m_dwProductRef;                  //no need to display for the moment
}SDMCCaAcceptViewInfo;

typedef struct
{
	unsigned short      m_wPurseBalance;         // ��ǰʹ��Ǯ�������
	unsigned char       m_cInsufficientTokens;   // 1: ��������
	unsigned char       m_cTokensMode;           // 0: ppv per event       1: ppv per time
	unsigned int		m_dwEventcost;           // ��Ŀ�۸�
	unsigned int		m_dwEventTag;
	unsigned char       m_acProgramLabel[ConaxCA_MAX_LABEL_NAME_LEN];// ��Ŀ���ƣ��ַ���
	unsigned char		m_acPurseLabel[ConaxCA_MAX_LABEL_NAME_LEN]; //Ǯ�����ƣ��ַ���
}SDMCCaPPVRequestInfo;

typedef struct
{
	unsigned int 		m_dwProductRef; //no need to display for the moment
	float 				m_fPrice;       // ��Ŀ�۸�
    unsigned char       m_acCurrency[ConaxCA_MAX_CURRENCY_LEN];
	unsigned char  		m_acProductLabel[ConaxCA_MAX_LABEL_NAME_LEN];//����
}SDMCCaOrderInfo;

//�����¼
typedef struct
{ 
    SDMCCaDateTime			m_stStart;        //  �ꡢ�¡�����Ч��������Ч
    SDMCCaDateTime			m_stEnd;          //  �ꡢ�¡�����Ч��������Ч
    unsigned int	        m_dwEntitlement;  //��ʶ������Ȩ��Ϣ
} SDMCCaAuthPeriod;

typedef struct
{
    unsigned char                m_szLabel[ConaxCA_MAX_LABEL_NAME_LEN];//����
    unsigned short	            m_wRefID;           //��Ŀ����
    SDMCCaAuthPeriod   	m_astAuthPeriod[2]; //��Ȩ��Ϣ
}SDMCCaSubscriptionInfo;

//ppv Event ��¼
typedef struct
{   
    unsigned char		   	m_szLabel[ConaxCA_MAX_LABEL_NAME_LEN];//����
    unsigned int	   		m_dwEventID;                     //��Ŀ����
    SDMCCaDateTime			m_stStart;                       // �롢������Ч��������Ч
    SDMCCaDateTime			m_stEnd;                         // �롢������Ч��������Ч
    unsigned short          m_MinutesOrCreditsLeft;          //ʣ��������
    unsigned short          m_wAuthType;                     //0:time-limited access; 1:unlimited access; 2:credit-based access; 3:reserved
} SDMCCaPPVEventInfo;

typedef struct
{
	unsigned short			m_wPurseRef;//Ǯ������
	unsigned int			m_dwBalance;//���
	unsigned char			m_acLabel[ConaxCA_MAX_LABEL_NAME_LEN]; //����
}SDMCCaPurseInfo;

typedef struct
{
	unsigned int			m_dwEventTag;
	unsigned int			m_dwConsumedTokens;              //�����ѵĽ��
	unsigned char			m_acLabel[ConaxCA_MAX_LABEL_NAME_LEN];//����
	SDMCCaDateTime			m_stLastAccessTime;              //������Ч��������Ч
}SDMCCaDebitStatus;

typedef struct
{
	unsigned int		    m_dwTotalNum;                     //��¼����
	SDMCCaDebitStatus		m_stDebitStatus[ConaxCA_MAX_DEBIT_NUM];//���Ѽ�¼
}SDMCCaDebitInfo;

typedef struct
{
	unsigned int		  	m_dwCreditTokens;                //����
	unsigned char		  	m_acLabel[ConaxCA_MAX_LABEL_NAME_LEN];//����
}SDMCCaCreditStatus;

typedef struct
{
	unsigned int		           m_dwTotalNum;                       //��Ϣ����
	SDMCCaCreditStatus       m_stCreditStatus[ConaxCA_MAX_CREDIT_NUM];//������Ϣ
}SDMCCaCreditInfo;

typedef struct
{
	unsigned char		    m_cId;                     //��ϢID
	unsigned short		    m_wDuration;               //ÿ����ʾ����ʱ��
	unsigned char		    m_cRepetition;             //��ʾ����
	unsigned char		    m_cInterval;               //��ʾ���ʱ��
	SDMCCaDateTime    m_stShowTime;              //��ʼ��ʾʱ�䣬������Ч��������Ч
	unsigned char		    m_cTextLen;                //���ݳ���
	unsigned char		    m_acText[ConaxCA_MAX_TEXT_SIZE];//����Ϣ����
}SDMCCaMessage;

typedef struct
{
	SDMCCA_BOOL			m_bRead;            //�Ѷ���ʶ
	unsigned char			m_cMailId;          //�ʼ�ID
	SDMCCaDateTime	m_stShowFlagTime;   //FLAG��ʼ��ʾ(UTCʱ��),�ʼ�Ϊֱ����ʾ�ʼ�ͼ��
	SDMCCaDateTime	m_stReceiveTime;    //����ʱ��
	unsigned char			m_cTextLen;         //���ݳ���
	unsigned char			m_acText[ConaxCA_MAX_TEXT_SIZE]; //�ʼ�����
}SDMCCaEmail;

typedef struct
{
	unsigned short			m_wDuration;    //����ʱ��,��λΪ���루�ٷ�֮һ��)
	unsigned short			m_wPosition_x;  //���Ͻ�X����
	unsigned short			m_wPosition_y;  //���Ͻ�X����
	unsigned char			m_cHeight;      //���Ͻ�Y����
	SDMCCaDateTime	m_stShowTime;   //�ꡢ�¡�����Ч��������Ч
	unsigned char			m_acFingerText[ConaxCA_MAX_FINGERPRINT_LEN];//ָ������
	int             m_nLength;
}SDMCCaFingerprint;
/**************************************************************************
* Function Name: SDMCCA_GetSubscriptionTotalNum
*   ��ȡ�����¼����
*
*Parameters
*
*Return Values
*		�ɹ����ؼ�¼������ʧ�ܷ���-1
**************************************************************************/
int SDMCCA_GetSubscriptionTotalNum(void);

/**************************************************************************
* Function Name: SDMCCA_GetSubscriptionInfo
*   ��ȡָ����Ź����¼������
*
*Parameters	
*	       dwRecordIndex
*                   [in]   ���(��1��ʼ)
*          pstSubRecord
*                   [out]  ����
*Return Values
*		SUCCESS	�ɹ�
*		FAILURE		ʧ��
**************************************************************************/
int SDMCCA_GetSubscriptionInfo(unsigned int dwRecordIndex, SDMCCaSubscriptionInfo *pstSubRecord);

/**************************************************************************
* Function Name: SDMCCA_GetPpvEventTotalNum
*   ��ȡPPV EVENT ��¼����
*
*Parameters	
*	
*Return Values
*		�ɹ����ؼ�¼������ʧ�ܷ���-1
**************************************************************************/
int SDMCCA_GetPpvEventTotalNum(void);

/**************************************************************************
* Function Name: SDMCCA_GetPpvEventInfo
*   ��ȡָ�����PPV EVENT  ��¼������
*
*Parameters	
*	       dwRecordIndex
*                    [in]  ���(��1��ʼ)
*          pstPpvRecord
*                    [out] ����
*Return Values
*		SUCCESS	�ɹ�
*		FAILURE		ʧ��
**************************************************************************/
int SDMCCA_GetPpvEventInfo(unsigned int dwRecordIndex, SDMCCaPPVEventInfo* pstPpvRecord);

/**************************************************************************
* Function Name: SDMCCA_GetPurseTotalNum
*   ��ȡǮ������
*
*Parameters	
*	
*Return Values
*		�ɹ�����������ʧ�ܷ���-1
**************************************************************************/
int SDMCCA_GetPurseTotalNum(void);

/**************************************************************************
* Function Name: SDMCCA_GetPurseInfo
*   ��ȡָ�����Ǯ�� ״̬
*
*Parameters	
*	       dwRecordIndex
*                     [in]  Ǯ�����(��1��ʼ)
*          pstCaPurseInfo
*                     [out] ״̬����
*Return Values
*		SUCCESS	�ɹ�
*		FAILURE		ʧ��
**************************************************************************/
int SDMCCA_GetPurseInfo(unsigned int dwPurseIndex,SDMCCaPurseInfo* pstCaPurseInfo);

/**************************************************************************
* Function Name: SDMCCA_GetDebitInfo
*   ��ȡָ�����Ǯ�� ��Debit ״̬
*
*Parameters	
*	       dwRecordIndex
*                     [in]  Ǯ�����(��1��ʼ)
*          pstCaDebitInfo
*                     [out] ״̬����
*Return Values
*		SUCCESS	�ɹ�
*		FAILURE		ʧ��
**************************************************************************/
int SDMCCA_GetDebitInfo(unsigned int dwPurseIndex,SDMCCaDebitInfo** pstCaDebitInfo);

/**************************************************************************
* Function Name: SDMCCA_GetCreditInfo
*   ��ȡָ�����Ǯ�� ��Credit ״̬
*
*Parameters	
*	       dwRecordIndex
*                      [in]  Ǯ�����(��1��ʼ)
*          pstCaCreditInfo
*                      [out] ״̬����
*Return Values
*		SUCCESS	�ɹ�
*		FAILURE		ʧ��
**************************************************************************/
int SDMCCA_GetCreditInfo(unsigned int dwPurseIndex,SDMCCaCreditInfo** pstCaCreditInfo);

/**************************************************************************
* Function Name: SDMCCA_GetCardMaturityRating
*   ��ȡ����ǰ�ĸ�ĸ��
*
*Parameters	
*           pMat [out] ��ĸ����
*Return Values
*		SUCCESS	�ɹ�
*		FAILURE		ʧ��
**************************************************************************/
int SDMCCA_GetCardMaturityRating(ConaxCaMaturityRating *pMat);

/**************************************************************************
* Function Name: SDMCCA_ChangCardMaturityRating
*   �޸Ŀ��ĸ�ĸ��
*
*Parameters	
*	       eMatRat
*                 [in]  ��ĸ��
*          pSzPin
*                 [in] ������
*Return Values
*		SUCCESS(0)	�޸ĳɹ�
*		1			�������
*		OTHER       	�޸�ʧ��
**************************************************************************/
int SDMCCA_ChangeCardMaturityRating(ConaxCaMaturityRating eMatRat,unsigned char *pSzPin);

/**************************************************************************
* Function Name: CSCAAcceptMaturityRat
*   ��������ȷ���տ���ĸ�����ƽ�Ŀ
*
*Parameters	
*          pSzPin
*                 [in] ������
*           hService
*                 [in]��Ŀhandle
*Return Values
*		SUCCESS(0)	�ɹ�
*		1			�������
*		OTHER	        ʧ��
**************************************************************************/
int SDMCCA_AcceptMaturityRat( unsigned char *pSzPin );


/**************************************************************************
* Function Name: CSCACancelMaturityRat
*   ȡ����ĸ��������ʾ�򣬲��տ���ǰ��Ŀ
*
*Parameters   hService
*                 [in]��Ŀhandle
*Return Values
*		SUCCESS	�ɹ�
*		FAILURE		����
**************************************************************************/
int SDMCCA_CancelMaturityRat(void );

/**************************************************************************
* Function Name: CSCAAcceptStartView
*   ��������ȷ���տ��۷�
*
*Parameters	
*          pSzPin
*                 [in] ������
*           hService
*                 [in]��Ŀhandle
*Return Values
*		SUCCESS(0)	�ɹ�
*		1			�������
*		OTHER	        ʧ��
**************************************************************************/
int SDMCCA_AcceptStartView( unsigned char *pSzPin );

/**************************************************************************
* Function Name: CSCACancelStartView
*   ȡ���۷ѽ�Ŀ�ۿ���ʾ�򣬲��տ���ǰ��Ŀ
*
*Parameters	hService
*                 [in]��Ŀhandle
*Return Values
*		SUCCESS	�ɹ�
*		FAILURE		����
**************************************************************************/
int SDMCCA_CancelStartView(void);

/**************************************************************************
* Function Name: CSCAChangCardMaturityRating
*   ��������ȷ�϶�����ǰ��Ŀ
*
*Parameters	
*          pSzPin
*                 [in] ������
*           hService
*                 [in]��Ŀhandle
*Return Values
*		SUCCESS(0)	�ɹ�
*		1			�������
*		OTHER	        ʧ��
**************************************************************************/
int SDMCCA_AcceptOrderInfo( unsigned char *pSzPin  );

/**************************************************************************
* Function Name: CSCACancelOrderInfo
*   ȡ����Ŀ������ʾ�򣬲��տ���ǰ��Ŀ
*
*Parameters	
*           hService
*                 [in]��Ŀhandle

*Return Values
*		SUCCESS	�ɹ�
*		FAILURE		����
**************************************************************************/
int SDMCCA_CancelOrderInfo(void);

/**************************************************************************
* Function Name: CSCAAcceptPPVRequest
*   ��������ȷ�Ϲ���PPV��Ŀ
*
*Parameters	
*          pSzPin
*                 [in] ������
*           hService
*                 [in]��Ŀhandle

*Return Values
*		SUCCESS(0)	�ɹ�
*		1			�������
*		OTHER       	ʧ��
**************************************************************************/
int SDMCCA_AcceptPPVRequest( unsigned char *pSzPin );

/**************************************************************************
* Function Name: SDMCCA_CancelPPVRequest
*   ȡ��PPV������ʾ�򣬲��տ���ǰ��Ŀ
*
*Parameters	

*Return Values
*		SDMCCA_SUCCESS					�ɹ�
*		SDMCCA_ERROR_SystemError		����
**************************************************************************/
int SDMCCA_CancelPPVRequest(void);

/**************************************************************************
* Function Name: SDMCCA_ChangeCardPin
*   �޸Ŀ�����
*
*Parameters	
*	       pSzPinOld
*                  [in]  ������
*          pSzPinNew
*                  [in]  ������
*Return Values
*		SUCCESS(0)	�޸ĳɹ�
*		1			��������� "Incorrect old PIN"
*		OTHER       	�޸�ʧ��"Change CA PIN failed"
*note: example dialogue:
*    //////////////////////////////////////////
*    Change PIN Please enter CA PIN   ****
*    Please enter new CA PIN  ****
*    Please confirm new CA PIN  ****
*    /////////////////////////////////////////
*if the user has entered two new PINs that do not match,"PIN confirmation does not match" should be displayed
**************************************************************************/
int SDMCCA_ChangeCardPin(unsigned char * pSzPinOld, unsigned char *pSzPinNew);


//��ָ���ʼ�����Ϊ�Ѷ�
int SDMCCA_SetReadFlag_Email (int nMailID );
//�����ʼ�����˳��
int SDMCCA_SetSequence_Email (SDMCCA_Email_Seq_E eMSeq );

#ifdef __cplusplus
}
#endif

#endif