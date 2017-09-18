
#ifndef _SDMCCA_CONAXINFEX_H_
#define _SDMCCA_CONAXINFEX_H_

#include "SDMCCAInf_prv.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define ConaxCA_MAX_FINGERPRINT_LEN		256/*32*/    //指纹信息的最大长度
#define ConaxCA_MAX_LABEL_NAME_LEN       32    //描述信息的最大长度
#define ConaxCA_MAX_DEBIT_NUM         	100   //DEBIT最大记录数
#define ConaxCA_MAX_CREDIT_NUM         	100   //credit最大记录数
#define ConaxCA_MAX_TEXT_SIZE			256   //短消息最大长度
#define ConaxCA_MAX_ES_NUM				16    //最多可解的ES个数
#define ConaxCA_MAX_CASYSTEMID_NUM       256   //最大CA系统ID个数
#define ConaxCA_MAX_CURRENCY_LEN			8     //CURRENCY最大长度

//父母级
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
    SDMCCA_EMAIL_NO_SEQ = 0,        //无顺序要求
    SDMCCA_EMAIL_TIME_ASC,          //创建时间早的邮件放在前面
    SDMCCA_EMAIL_TIME_DESC,         //创建时间早的邮件放在后面
    SDMCCA_EMAIL_UNREAD_ASC,        //未读邮件放在前面
    SDMCCA_EMAIL_UNREAD_DESC,       //未读邮件放在后面    
    SDMCCA_EMAIL_UNREAD_TIME_ASC,   //未读邮件且时间晚的邮件放在前面
    SDMCCA_EMAIL_UNREAD_TIME_DESC,  //未读邮件且时间晚的邮件放在后面,第0封是未读的新来邮件
    SDMCCA_EMAIL_MAIL_ID_ASC,       //mail id升序排列  
    SDMCCA_EMAIL_MAIL_ID_DESC,      //mail id降序排列
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
	unsigned short      m_wPurseBalance;         // 当前使用钱包的余额
	unsigned char       m_cInsufficientTokens;   // 1: 卡内余额不足
	unsigned char       m_cTokensMode;           // 0: ppv per event       1: ppv per time
	unsigned int		m_dwEventcost;           // 节目价格
	unsigned int		m_dwEventTag;
	unsigned char       m_acProgramLabel[ConaxCA_MAX_LABEL_NAME_LEN];// 节目名称，字符串
	unsigned char		m_acPurseLabel[ConaxCA_MAX_LABEL_NAME_LEN]; //钱包名称，字符串
}SDMCCaPPVRequestInfo;

typedef struct
{
	unsigned int 		m_dwProductRef; //no need to display for the moment
	float 				m_fPrice;       // 节目价格
    unsigned char       m_acCurrency[ConaxCA_MAX_CURRENCY_LEN];
	unsigned char  		m_acProductLabel[ConaxCA_MAX_LABEL_NAME_LEN];//名称
}SDMCCaOrderInfo;

//购买记录
typedef struct
{ 
    SDMCCaDateTime			m_stStart;        //  年、月、日有效，其他无效
    SDMCCaDateTime			m_stEnd;          //  年、月、日有效，其他无效
    unsigned int	        m_dwEntitlement;  //标识卡的授权信息
} SDMCCaAuthPeriod;

typedef struct
{
    unsigned char                m_szLabel[ConaxCA_MAX_LABEL_NAME_LEN];//名称
    unsigned short	            m_wRefID;           //节目代号
    SDMCCaAuthPeriod   	m_astAuthPeriod[2]; //授权信息
}SDMCCaSubscriptionInfo;

//ppv Event 记录
typedef struct
{   
    unsigned char		   	m_szLabel[ConaxCA_MAX_LABEL_NAME_LEN];//名称
    unsigned int	   		m_dwEventID;                     //节目代号
    SDMCCaDateTime			m_stStart;                       // 秒、厘秒无效。其他有效
    SDMCCaDateTime			m_stEnd;                         // 秒、厘秒无效。其他有效
    unsigned short          m_MinutesOrCreditsLeft;          //剩余金额或点数
    unsigned short          m_wAuthType;                     //0:time-limited access; 1:unlimited access; 2:credit-based access; 3:reserved
} SDMCCaPPVEventInfo;

typedef struct
{
	unsigned short			m_wPurseRef;//钱包代号
	unsigned int			m_dwBalance;//余额
	unsigned char			m_acLabel[ConaxCA_MAX_LABEL_NAME_LEN]; //名称
}SDMCCaPurseInfo;

typedef struct
{
	unsigned int			m_dwEventTag;
	unsigned int			m_dwConsumedTokens;              //已消费的金额
	unsigned char			m_acLabel[ConaxCA_MAX_LABEL_NAME_LEN];//名称
	SDMCCaDateTime			m_stLastAccessTime;              //厘秒无效、其他有效
}SDMCCaDebitStatus;

typedef struct
{
	unsigned int		    m_dwTotalNum;                     //记录个数
	SDMCCaDebitStatus		m_stDebitStatus[ConaxCA_MAX_DEBIT_NUM];//消费记录
}SDMCCaDebitInfo;

typedef struct
{
	unsigned int		  	m_dwCreditTokens;                //点数
	unsigned char		  	m_acLabel[ConaxCA_MAX_LABEL_NAME_LEN];//名称
}SDMCCaCreditStatus;

typedef struct
{
	unsigned int		           m_dwTotalNum;                       //信息个数
	SDMCCaCreditStatus       m_stCreditStatus[ConaxCA_MAX_CREDIT_NUM];//交易信息
}SDMCCaCreditInfo;

typedef struct
{
	unsigned char		    m_cId;                     //消息ID
	unsigned short		    m_wDuration;               //每次显示持续时间
	unsigned char		    m_cRepetition;             //显示次数
	unsigned char		    m_cInterval;               //显示间隔时间
	SDMCCaDateTime    m_stShowTime;              //开始显示时间，厘秒无效、其他有效
	unsigned char		    m_cTextLen;                //内容长度
	unsigned char		    m_acText[ConaxCA_MAX_TEXT_SIZE];//短消息内容
}SDMCCaMessage;

typedef struct
{
	SDMCCA_BOOL			m_bRead;            //已读标识
	unsigned char			m_cMailId;          //邮件ID
	SDMCCaDateTime	m_stShowFlagTime;   //FLAG开始显示(UTC时间),邮件为直接显示邮件图标
	SDMCCaDateTime	m_stReceiveTime;    //接收时间
	unsigned char			m_cTextLen;         //内容长度
	unsigned char			m_acText[ConaxCA_MAX_TEXT_SIZE]; //邮件内容
}SDMCCaEmail;

typedef struct
{
	unsigned short			m_wDuration;    //持续时间,单位为厘秒（百分之一秒)
	unsigned short			m_wPosition_x;  //左上角X坐标
	unsigned short			m_wPosition_y;  //左上角X坐标
	unsigned char			m_cHeight;      //左上角Y坐标
	SDMCCaDateTime	m_stShowTime;   //年、月、日无效，其他有效
	unsigned char			m_acFingerText[ConaxCA_MAX_FINGERPRINT_LEN];//指纹内容
	int             m_nLength;
}SDMCCaFingerprint;
/**************************************************************************
* Function Name: SDMCCA_GetSubscriptionTotalNum
*   获取购买记录总数
*
*Parameters
*
*Return Values
*		成功返回记录总数，失败返回-1
**************************************************************************/
int SDMCCA_GetSubscriptionTotalNum(void);

/**************************************************************************
* Function Name: SDMCCA_GetSubscriptionInfo
*   获取指定序号购买记录的内容
*
*Parameters	
*	       dwRecordIndex
*                   [in]   序号(从1开始)
*          pstSubRecord
*                   [out]  内容
*Return Values
*		SUCCESS	成功
*		FAILURE		失败
**************************************************************************/
int SDMCCA_GetSubscriptionInfo(unsigned int dwRecordIndex, SDMCCaSubscriptionInfo *pstSubRecord);

/**************************************************************************
* Function Name: SDMCCA_GetPpvEventTotalNum
*   获取PPV EVENT 记录总数
*
*Parameters	
*	
*Return Values
*		成功返回记录总数，失败返回-1
**************************************************************************/
int SDMCCA_GetPpvEventTotalNum(void);

/**************************************************************************
* Function Name: SDMCCA_GetPpvEventInfo
*   获取指定序号PPV EVENT  记录的内容
*
*Parameters	
*	       dwRecordIndex
*                    [in]  序号(从1开始)
*          pstPpvRecord
*                    [out] 内容
*Return Values
*		SUCCESS	成功
*		FAILURE		失败
**************************************************************************/
int SDMCCA_GetPpvEventInfo(unsigned int dwRecordIndex, SDMCCaPPVEventInfo* pstPpvRecord);

/**************************************************************************
* Function Name: SDMCCA_GetPurseTotalNum
*   获取钱包总数
*
*Parameters	
*	
*Return Values
*		成功返回总数，失败返回-1
**************************************************************************/
int SDMCCA_GetPurseTotalNum(void);

/**************************************************************************
* Function Name: SDMCCA_GetPurseInfo
*   获取指定序号钱包 状态
*
*Parameters	
*	       dwRecordIndex
*                     [in]  钱包序号(从1开始)
*          pstCaPurseInfo
*                     [out] 状态内容
*Return Values
*		SUCCESS	成功
*		FAILURE		失败
**************************************************************************/
int SDMCCA_GetPurseInfo(unsigned int dwPurseIndex,SDMCCaPurseInfo* pstCaPurseInfo);

/**************************************************************************
* Function Name: SDMCCA_GetDebitInfo
*   获取指定序号钱包 的Debit 状态
*
*Parameters	
*	       dwRecordIndex
*                     [in]  钱包序号(从1开始)
*          pstCaDebitInfo
*                     [out] 状态内容
*Return Values
*		SUCCESS	成功
*		FAILURE		失败
**************************************************************************/
int SDMCCA_GetDebitInfo(unsigned int dwPurseIndex,SDMCCaDebitInfo** pstCaDebitInfo);

/**************************************************************************
* Function Name: SDMCCA_GetCreditInfo
*   获取指定序号钱包 的Credit 状态
*
*Parameters	
*	       dwRecordIndex
*                      [in]  钱包序号(从1开始)
*          pstCaCreditInfo
*                      [out] 状态内容
*Return Values
*		SUCCESS	成功
*		FAILURE		失败
**************************************************************************/
int SDMCCA_GetCreditInfo(unsigned int dwPurseIndex,SDMCCaCreditInfo** pstCaCreditInfo);

/**************************************************************************
* Function Name: SDMCCA_GetCardMaturityRating
*   获取卡当前的父母级
*
*Parameters	
*           pMat [out] 父母级别
*Return Values
*		SUCCESS	成功
*		FAILURE		失败
**************************************************************************/
int SDMCCA_GetCardMaturityRating(ConaxCaMaturityRating *pMat);

/**************************************************************************
* Function Name: SDMCCA_ChangCardMaturityRating
*   修改卡的父母级
*
*Parameters	
*	       eMatRat
*                 [in]  父母级
*          pSzPin
*                 [in] 卡密码
*Return Values
*		SUCCESS(0)	修改成功
*		1			密码错误
*		OTHER       	修改失败
**************************************************************************/
int SDMCCA_ChangeCardMaturityRating(ConaxCaMaturityRating eMatRat,unsigned char *pSzPin);

/**************************************************************************
* Function Name: CSCAAcceptMaturityRat
*   输入密码确认收看父母级限制节目
*
*Parameters	
*          pSzPin
*                 [in] 卡密码
*           hService
*                 [in]节目handle
*Return Values
*		SUCCESS(0)	成功
*		1			密码错误
*		OTHER	        失败
**************************************************************************/
int SDMCCA_AcceptMaturityRat( unsigned char *pSzPin );


/**************************************************************************
* Function Name: CSCACancelMaturityRat
*   取消父母级限制提示框，不收看当前节目
*
*Parameters   hService
*                 [in]节目handle
*Return Values
*		SUCCESS	成功
*		FAILURE		错误
**************************************************************************/
int SDMCCA_CancelMaturityRat(void );

/**************************************************************************
* Function Name: CSCAAcceptStartView
*   输入密码确认收看扣费
*
*Parameters	
*          pSzPin
*                 [in] 卡密码
*           hService
*                 [in]节目handle
*Return Values
*		SUCCESS(0)	成功
*		1			密码错误
*		OTHER	        失败
**************************************************************************/
int SDMCCA_AcceptStartView( unsigned char *pSzPin );

/**************************************************************************
* Function Name: CSCACancelStartView
*   取消扣费节目观看提示框，不收看当前节目
*
*Parameters	hService
*                 [in]节目handle
*Return Values
*		SUCCESS	成功
*		FAILURE		错误
**************************************************************************/
int SDMCCA_CancelStartView(void);

/**************************************************************************
* Function Name: CSCAChangCardMaturityRating
*   输入密码确认订购当前节目
*
*Parameters	
*          pSzPin
*                 [in] 卡密码
*           hService
*                 [in]节目handle
*Return Values
*		SUCCESS(0)	成功
*		1			密码错误
*		OTHER	        失败
**************************************************************************/
int SDMCCA_AcceptOrderInfo( unsigned char *pSzPin  );

/**************************************************************************
* Function Name: CSCACancelOrderInfo
*   取消节目订购提示框，不收看当前节目
*
*Parameters	
*           hService
*                 [in]节目handle

*Return Values
*		SUCCESS	成功
*		FAILURE		错误
**************************************************************************/
int SDMCCA_CancelOrderInfo(void);

/**************************************************************************
* Function Name: CSCAAcceptPPVRequest
*   输入密码确认购买PPV节目
*
*Parameters	
*          pSzPin
*                 [in] 卡密码
*           hService
*                 [in]节目handle

*Return Values
*		SUCCESS(0)	成功
*		1			密码错误
*		OTHER       	失败
**************************************************************************/
int SDMCCA_AcceptPPVRequest( unsigned char *pSzPin );

/**************************************************************************
* Function Name: SDMCCA_CancelPPVRequest
*   取消PPV购买提示框，不收看当前节目
*
*Parameters	

*Return Values
*		SDMCCA_SUCCESS					成功
*		SDMCCA_ERROR_SystemError		错误
**************************************************************************/
int SDMCCA_CancelPPVRequest(void);

/**************************************************************************
* Function Name: SDMCCA_ChangeCardPin
*   修改卡密码
*
*Parameters	
*	       pSzPinOld
*                  [in]  旧密码
*          pSzPinNew
*                  [in]  新密码
*Return Values
*		SUCCESS(0)	修改成功
*		1			旧密码错误 "Incorrect old PIN"
*		OTHER       	修改失败"Change CA PIN failed"
*note: example dialogue:
*    //////////////////////////////////////////
*    Change PIN Please enter CA PIN   ****
*    Please enter new CA PIN  ****
*    Please confirm new CA PIN  ****
*    /////////////////////////////////////////
*if the user has entered two new PINs that do not match,"PIN confirmation does not match" should be displayed
**************************************************************************/
int SDMCCA_ChangeCardPin(unsigned char * pSzPinOld, unsigned char *pSzPinNew);


//将指定邮件设置为已读
int SDMCCA_SetReadFlag_Email (int nMailID );
//设置邮件排列顺序
int SDMCCA_SetSequence_Email (SDMCCA_Email_Seq_E eMSeq );

#ifdef __cplusplus
}
#endif

#endif