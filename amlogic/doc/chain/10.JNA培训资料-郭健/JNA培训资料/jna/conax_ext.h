 /******************************************************************************  
* Filename:    sdmc_conax.h  
* Author:      X.Q.CHEN
* Date:        Nov 2016
* Description: Conax CA APP interface & data struct & message type 
*******************************************************************************/

#ifndef _SDMC_CONAX_H_
#define _SDMC_CONAX_H_

#include "SDMCCAPublic.h"

#define CONAX_LABEL_NAME_MAX    		32 //描述信息的最大长度
#define CONAX_DEBIT_MAX         		100 //DEBIT最大记录数
#define CONAX_CREDIT_MAX      			100 //credit最大记录数
#define CONAX_TEXT_SIZE				256 //短消息最大长度
#define CONAX_ES_NUM					16 //最多可解的ES个数
#define CONAX_ID_NUM       			256 //最大CA系统ID个数
#define CONAX_CURRENCY_LEN				8 //CURRENCY最大长度
#define CONAX_PIN_MAX               	4 //最大pin码位数
#define CONAX_FINGERPRINT_LEN			32//指纹最大长度

//Conax需要处理的私有消息
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

//父母级
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
    CONAX_EMAIL_NO_SEQ = 0,        //无顺序要求
    CONAX_EMAIL_TIME_ASC,          //创建时间早的邮件放在前面
    CONAX_EMAIL_TIME_DESC,         //创建时间早的邮件放在后面
    CONAX_EMAIL_UNREAD_ASC,        //未读邮件放在前面
    CONAX_EMAIL_UNREAD_DESC,       //未读邮件放在后面    
    CONAX_EMAIL_UNREAD_TIME_ASC,   //未读邮件且时间晚的邮件放在前面
    CONAX_EMAIL_UNREAD_TIME_DESC,  //未读邮件且时间晚的邮件放在后面,第0封是未读的新来邮件
    CONAX_EMAIL_MAIL_ID_ASC,       //mail id升序排列  
    CONAX_EMAIL_MAIL_ID_DESC,      //mail id降序排列
    CONAX_EMAIL_SHOW_TIME_ASC,
    CONAX_EMAIL_MAX
}ConaxEmailSeq_E;

//第一字段标示消息来自CONAX，第二字段标示通知类型，第三字段标示通知内容
typedef struct
{   
    unsigned char   	ucSmcStatus;      //卡的状态(插卡还是未插卡)
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
	unsigned char		ucId;                     //消息ID
	unsigned short	wDuration;               //每次显示持续时间
	unsigned char		ucRepetition;             //显示次数
	unsigned char		ucInterval;               //显示间隔时间
	ConaxDateTime_S    	stShowTime;              //开始显示时间，厘秒无效、其他有效
	unsigned char		ucTextLen;                //内容长度
	unsigned char		aucText[CONAX_TEXT_SIZE];//短消息内容
}ConaxShortMsg_S;

typedef struct
{
	unsigned short			wDuration;    //持续时间,单位为厘秒（百分之一秒)
	unsigned short			wPosition_x;  //左上角X坐标
	unsigned short			wPosition_y;  //左上角y坐标
	unsigned char				ucHeight;     //高度
	ConaxDateTime_S				stShowTime;   //年、月、日无效，其他有效
	unsigned char				aucFingerText[CONAX_FINGERPRINT_LEN];//指纹内容
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
	float 					fPrice;       // 节目价格
    unsigned char        aucCurrency[CONAX_CURRENCY_LEN];
	unsigned char  		aucProductLabel[CONAX_LABEL_NAME_MAX];//名称
}ConaxOrderInfo_S;

typedef struct
{
	unsigned short		wPurseBalance;         // 当前使用钱包的余额
	unsigned char       	ucInsufficientTokens;   // 1: 卡内余额不足
	unsigned char       	ucTokensMode;           // 0: ppv per event       1: ppv per time
	unsigned short      	wEventcost;           // 节目价格
	unsigned short      	wEventTag;
	unsigned char       	aucProgramLabel[CONAX_LABEL_NAME_MAX];// 节目名称，字符串
	unsigned char			aucPurseLabel[CONAX_LABEL_NAME_MAX]; //钱包名称，字符串
}ConaxPPVRequestInfo_S;



//购买记录
typedef struct
{ 
    ConaxDateTime_S stStart;        //  年、月、日有效，其他无效
    ConaxDateTime_S stEnd;          //  年、月、日有效，其他无效
    unsigned int    uEntitlement;  //标识卡的授权信息
}ConaxAuthPeriod_S;

typedef struct
{
    unsigned char       aucLabel[CONAX_LABEL_NAME_MAX];
    unsigned short      wRefID;           //节目代号
    ConaxAuthPeriod_S   astAuthPeriod[2]; //授权信息
}ConaxSubscriptionInfo_S;

//ppv Event 记录
typedef struct
{   
    unsigned char   	aucLabel[CONAX_LABEL_NAME_MAX]; //名称
    unsigned int    	uEventID;                       //节目代号
    ConaxDateTime_S  	stStart;                       // 秒、厘秒无效。其他有效
    ConaxDateTime_S  	stEnd;                         // 秒、厘秒无效。其他有效
    unsigned short  	wNumLeft;                       //剩余金额或点数
    unsigned short  	wAuthType;                      //0:time-limited access; 1:unlimited access; 2:credit-based access; 3:reserved
}ConaxPPVEventInfo_S;

typedef struct
{
    unsigned short  wPurseRef;//钱包代号
    unsigned int    uBalance;//余额
    unsigned char   aucLabel[CONAX_LABEL_NAME_MAX]; //名称
 }ConaxPurseInfo_S;

typedef struct
{
	unsigned int		  	uCreditTokens;                  //点数
	unsigned char		  	aucLabel[CONAX_LABEL_NAME_MAX]; //名称
}ConaxCreditStatus_S;

typedef struct
{
    unsigned int        uTotalNum;                     //记录个数
    ConaxCreditStatus_S astDebitStatus[CONAX_DEBIT_MAX];//消费记录
}ConaxDebitInfo_S;

typedef struct
{
	unsigned int    uTotalNum;                       //信息个数
	ConaxCreditStatus_S  astCreditStatus[CONAX_CREDIT_MAX];//交易信息
}ConaxCreditInfo_S;

//此枚举还没完善，后续增补
typedef enum
{
	CONAX_SUCCESS = 0,						//操作成功
	CONAX_WRONG_PASSWORD,					//密码错误
	CONAX_FAILURE = -1                      //操作失败
}ConaxReturnType_E;	


/*
//Note:使用如下接口时注意：
//1、一定要使用枚举来调用，后续可能会修改
//2、使用ConaxPlugIn->getProperty接口通过ConaxAPI_E来调用如下指定接口，注意数据类型的转换，特别是结构体存在对齐情况
*/

/*
  @brief SDMCCA_PROPERTY_CA_INFO 获取CA卡的信息函数接口
  @param[in] pVoid 不使用此参数,传参数时使用NULL
  @param[out] ConaxCardInfo_S *pstCardInfo指向CA卡的信息结构体指针
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_SUBSCRIPTION_NUM 获取购买记录总数
  @param[in] pVoid 不使用此参数,传参数时使用NULL
  @param[out]unsigned int * puNum返回购买记录总数
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/
	
/*
  @brief SDMCCA_PROPERTY_SUBSCRIPTION_INFO获取指定序号购买记录的内容
  @param[in]unsigned int * puRecordIndex   序号从1开始
  @param[out]ConaxSubscriptionInfo_S * pstSubRecord 
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_PPV_EVENT_NUM获取PPV EVENT 记录总数
  @param[in] pVoid 不使用此参数,传参数时使用NULL
  @param[out] int * piEventNum 返回EVENT记录总数 
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_PPVEVENT_INFO获取指定序号PPV EVENT  记录的内容
  @param[in] unsigned int * puRecordIndex 
  @param[out] ConaxPPVEventInfo_S * pstPpvRecord 
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_PURSE_NUM获取钱包总数容
  @param[in] pVoid 不使用此参数,传参数时使用NULL  
  @param[out] int * piPurseNum 
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_PURSE_INFO获取指定序号钱包 状态
  @param[in] unsigned int * puPurseIndex 序号从1开始
  @param[out] ConaxPurseInfo_S * pstPurseInfo 
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_DEBIT_INFO获取指定序号钱包 的Debit 状态
  @param[in] unsigned int * puPurseIndex 序号从1开始
  @param[out] ConaxDebitInfo_S ** ppstDebitInfo 
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_CREDIT_INFO获取指定序号钱包 的Credit 状态
  @param[in] unsigned int * puPurseIndex 序号从1开始
  @param[out] ConaxCreditInfo_S** ppstCreditInfo 
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_PROPERTY_MATURITY_RAT获取卡当前的父母级
  @param[in] pVoid 不使用此参数,传参数时使用NULL
  @param[out] ConaxMaturityRating_E * peMat父母级别 
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_CHANGE_MATURITY_RAT修改卡的父母级
  @param[in] ConaxChangeMatRat_S * pstMatRat 父母级别及卡密码
  @param[out] pVoid 不使用此参数，传参数时使用NULL
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_ACCEPT_MATURITY_RAT输入密码确认收看父母级限制节目
  @param[in] unsigned char * pucPin 卡密码 
  @param[out] pVoid 不使用此参数，传参数时使用NULL
  @return 返回CONAX_WRONG_PASSWORD表示密码错误
  Note:
*/

/*
  @brief SDMCCA_CANCEL_MATURITY_RAT取消父母级限制提示框，不收看当前节目
  @param[in] pVoid 不使用此参数，传参数时使用NULL
  @param[out] pVoid 不使用此参数，传参数时使用NULL
  @return 返回CONAX_WRONG_PASSWORD表示密码错误
  Note:
*/

/*
  @brief SDMCCA_ACCEPT_START_VIEW输入密码确认收看扣费
  @param[in] unsigned char * pucPin 卡密码 
  @param[out]pVoid 不使用此参数，传参数时使用NULL
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_CANCEL_START_VIEW取消扣费节目观看提示框，不收看当前节目
  @param[int]pInVoid 不使用此参数，传参数时使用NULL
  @param[out]pOutVoid 不使用此参数，传参数时使用NULL
  @return 返回CONAX_WRONG_PASSWORD表示密码错误
  Note:
*/

/*
  @brief SDMCCA_ACCEPT_ORDER_INFO输入密码确认订购当前节目
  @param[in] unsigned char * pucPin 卡密码 
  @param[out]pVoid 不使用此参数，传参数时使用NULL  
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_CANCEL_ORDER_INFO取消节目订购提示框，不收看当前节目
  @param[in]pInVoid 不使用此参数，传参数时使用NULL
  @param[out]pOutVoid 不使用此参数，传参数时使用NULL
  @return 返回CONAX_WRONG_PASSWORD表示密码错误
  Note:
*/

/*
  @brief SDMCCA_ACCEPT_PPV_REQUEST输入密码确认购买PPV节目
  @param[in] unsigned char * pucPin 卡密码 
  @param[out]pVoid 不使用此参数，传参数时使用NULL
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

/*
  @brief SDMCCA_CANCEL_PPV_REQUEST取消PPV购买提示框，不收看当前节目
  @param[int]pInVoid 不使用此参数，传参数时使用NULL
  @param[out]pOutVoid 不使用此参数，传参数时使用NULL
  @return 返回CONAX_WRONG_PASSWORD表示密码错误
  Note:
*/

/*
  @brief SDMCCA_CHANGE_CARD_PIN修改卡密码
  @param[in] ConaxChangePassword_S * pstChangePinCode 旧密码，新密码 
  @param[out]pVoid 不使用此参数，传参数时使用NULL
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:if the user has entered two new PINs that do not match,"PIN confirmation does not match" should be displayed
*/

/*
  @brief SDMCCA_SET_EMAIL_READ_FLAG将指定邮件设置为已读
  @param[in] unsigned int * puMailID 邮件ID 
  @param[out]pVoid 不使用此参数，传参数时使用NULL
  @return 返回CONAX_WRONG_PASSWORD表示密码错误
  Note:
*/

/*
  @brief SDMCCA_SET_EMAIL_SEQUENCE设置邮件排列顺序
  @param[in] ConaxEmailSeq_E * peMSeq 排序方式 
  @param[out]pVoid 不使用此参数，传参数时使用NULL
  @return 参考CONAX_Return_Type_E错误代码定义
  Note:
*/

#endif


