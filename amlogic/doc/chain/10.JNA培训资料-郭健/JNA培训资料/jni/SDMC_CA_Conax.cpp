#include "CoreTV_CA.h"
#include "SDMCCA_ConaxInfEx.h"
#include <malloc.h>
#include <string.h>
#include <jni.h>
#include <Log.h>

#undef JNIEXPORT
#define JNIEXPORT extern "C"


typedef struct
{
	jfieldID mSzLabelID;
	jfieldID mWRefID;
	jfieldID mAstAuthPeriodID;
} SDMCCaSubscriptionInfo_s ;
SDMCCaSubscriptionInfo_s mSDMCCaSubscriptionInfo;

typedef struct
{
	jfieldID mStStartID;
	jfieldID mStEndID;
	jfieldID mDwEntitlementID;
}SDMCCaAuthPeriod_s;
SDMCCaAuthPeriod_s mSDMCCaAuthPeriod;

typedef struct
{
	jfieldID jfm_dwYear; 
	jfieldID m_dwMonth;
	jfieldID m_dwDay;
	jfieldID m_dwHour;
	jfieldID m_dwMinute;
	jfieldID m_dwSecond;
	jfieldID m_dwCentisecond;
} SDMCCaDateTime_s;
SDMCCaDateTime_s mSDMCCaDateTime;

typedef struct{
	jfieldID m_wPurseBalance;
	jfieldID m_cInsufficientTokens;
	jfieldID m_cTokensMode;
	jfieldID m_dwEventcost;
	jfieldID m_dwEventTag;
	jfieldID m_acProgramLabel;
	jfieldID m_acPurseLabel;
} SDMCCaPPVRequestInfo_s;
SDMCCaPPVRequestInfo_s mSDMCCaPPVRequestInfo;

typedef struct{
	jfieldID m_wPurseRef;
	jfieldID m_dwBalance;
	jfieldID m_acLabel;
} SDMCCaPurseInfo_s;
SDMCCaPurseInfo_s mSDMCCaPurseInfo;

typedef struct{
	jfieldID  m_szLabel;//名称
	jfieldID  m_dwEventID;                     //节目代号
	jfieldID  m_stStart;                       // 秒、厘秒无效。其他有效
	jfieldID  m_stEnd;                         // 秒、厘秒无效。其他有效
	jfieldID  m_MinutesOrCreditsLeft;          //剩余金额或点数
	jfieldID  m_wAuthType;                     //0:time-limited access; 1:unlimited access; 2:credit-based access; 3:reserved
} SDMCCaPPVEventInfo_s;
SDMCCaPPVEventInfo_s mSDMCCaPPVEventInfo;

static void cacheGet_SDMCCaPPVEventInfo(JNIEnv *env, jclass thiz,SDMCCaPPVEventInfo_s &sSDMCCaPPVEventInfo)
{
	jclass cSDMCCaPPVEventInfo = env->FindClass("com/sdmc/jni/CoreTVCA$CaPPVEventInfo");
	sSDMCCaPPVEventInfo.m_dwEventID = env->GetFieldID(cSDMCCaPPVEventInfo, "m_dwEventID", "I");
	sSDMCCaPPVEventInfo.m_MinutesOrCreditsLeft = env->GetFieldID(cSDMCCaPPVEventInfo, "m_MinutesOrCreditsLeft", "S");
	sSDMCCaPPVEventInfo.m_stStart = env->GetFieldID(cSDMCCaPPVEventInfo, "m_stStart", "Lcom/sdmc/jni/CoreTVCA$SDMCCaDateTime;");
	sSDMCCaPPVEventInfo.m_stEnd = env->GetFieldID(cSDMCCaPPVEventInfo, "m_stEnd", "Lcom/sdmc/jni/CoreTVCA$SDMCCaDateTime;");
	sSDMCCaPPVEventInfo.m_szLabel = env->GetFieldID(cSDMCCaPPVEventInfo, "m_szLabel", "Ljava/lang/String;");
	sSDMCCaPPVEventInfo.m_wAuthType = env->GetFieldID(cSDMCCaPPVEventInfo, "m_wAuthType", "S");
}

static void cacheGet_SDMCCaPurseInfo(JNIEnv *env, jclass thiz,SDMCCaPurseInfo_s &sSDMCCaPurseInfo){
	jclass cSDMCCaPurseInfo = env->FindClass("com/sdmc/jni/CoreTVCA$CaPurseInfo");
	sSDMCCaPurseInfo.m_acLabel = env->GetFieldID(cSDMCCaPurseInfo, "m_acLabel", "Ljava/lang/String;");
	sSDMCCaPurseInfo.m_dwBalance = env->GetFieldID(cSDMCCaPurseInfo, "m_dwBalance", "I");
	sSDMCCaPurseInfo.m_wPurseRef = env->GetFieldID(cSDMCCaPurseInfo, "m_wPurseRef", "S");
}

static void cacheGet_SDMCCaPPVRequestInfo(JNIEnv *env, jclass thiz,SDMCCaPPVRequestInfo_s &sSDMCCaPPVRequestInfo)
{
	jclass cSDMCCaPPVRequestInfo = env->FindClass("com/sdmc/jni/CoreTVCA$SDMCCaPPVRequestInfo");
	sSDMCCaPPVRequestInfo.m_acProgramLabel = env->GetFieldID(cSDMCCaPPVRequestInfo, "m_acProgramLabel", "[C");
	sSDMCCaPPVRequestInfo.m_acPurseLabel = env->GetFieldID(cSDMCCaPPVRequestInfo, "m_acPurseLabel", "[C");
	sSDMCCaPPVRequestInfo.m_cInsufficientTokens = env->GetFieldID(cSDMCCaPPVRequestInfo, "m_cInsufficientTokens", "C");
	sSDMCCaPPVRequestInfo.m_cTokensMode = env->GetFieldID(cSDMCCaPPVRequestInfo, "m_cTokensMode", "C");
	sSDMCCaPPVRequestInfo.m_dwEventcost = env->GetFieldID(cSDMCCaPPVRequestInfo, "m_dwEventcost", "I");
	sSDMCCaPPVRequestInfo.m_dwEventTag = env->GetFieldID(cSDMCCaPPVRequestInfo, "m_dwEventTag", "I");
	sSDMCCaPPVRequestInfo.m_wPurseBalance = env->GetFieldID(cSDMCCaPPVRequestInfo, "m_wPurseBalance", "S");
}

static void cacheGet_SubscriptionInfo_SIDS(JNIEnv *env, jclass thiz,SDMCCaSubscriptionInfo_s &sSDMCCaSubscriptionInfo)
{
	jclass cSDMCCaSubscriptionInfo = env->FindClass("com/sdmc/jni/CoreTVCA$SDMCCaSubscriptionInfo");
	sSDMCCaSubscriptionInfo.mSzLabelID = env->GetFieldID(cSDMCCaSubscriptionInfo, "m_szLabel", "Ljava/lang/String;");
	sSDMCCaSubscriptionInfo.mWRefID = env->GetFieldID(cSDMCCaSubscriptionInfo, "m_wRefID", "S");
	sSDMCCaSubscriptionInfo.mAstAuthPeriodID = env->GetFieldID(cSDMCCaSubscriptionInfo, "m_astAuthPeriod", "[Lcom/sdmc/jni/CoreTVCA$SDMCCaAuthPeriod;");
}

static void cacheGet_AuthPeriod_SIDS(JNIEnv *env, jclass thiz,SDMCCaAuthPeriod_s &sSDMCCaAuthPeriod)
{
	jclass cSDMCCaAuthPeriod = env->FindClass("com/sdmc/jni/CoreTVCA$SDMCCaAuthPeriod");
	sSDMCCaAuthPeriod.mStStartID = env->GetFieldID(cSDMCCaAuthPeriod, "m_stStart" ,"Lcom/sdmc/jni/CoreTVCA$SDMCCaDateTime;");
	sSDMCCaAuthPeriod.mStEndID = env->GetFieldID(cSDMCCaAuthPeriod, "m_stEnd", "Lcom/sdmc/jni/CoreTVCA$SDMCCaDateTime;");
	sSDMCCaAuthPeriod.mDwEntitlementID = env->GetFieldID(cSDMCCaAuthPeriod, "m_dwEntitlement", "I");
}


static void cacheGet_CA_DATE_TIME_SIDS(JNIEnv *env, jclass thiz,SDMCCaDateTime_s &sSDMCCaDateTime)
{
	jclass cCADateTimeInfo = env->FindClass("com/sdmc/jni/CoreTVCA$SDMCCaDateTime");
	sSDMCCaDateTime.jfm_dwYear = env->GetFieldID(cCADateTimeInfo, "m_dwYear" ,"I");
	sSDMCCaDateTime.m_dwCentisecond = env->GetFieldID(cCADateTimeInfo, "m_dwCentisecond" ,"I");
	sSDMCCaDateTime.m_dwDay = env->GetFieldID(cCADateTimeInfo, "m_dwDay", "I");
	sSDMCCaDateTime.m_dwHour = env->GetFieldID(cCADateTimeInfo, "m_dwHour", "I");
	sSDMCCaDateTime.m_dwMinute = env->GetFieldID(cCADateTimeInfo, "m_dwMinute", "I");
	sSDMCCaDateTime.m_dwMonth = env->GetFieldID(cCADateTimeInfo, "m_dwMonth", "I");
	sSDMCCaDateTime.m_dwSecond = env->GetFieldID(cCADateTimeInfo, "m_dwSecond", "I");
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_initCAIDse
  (JNIEnv *env, jclass thiz)
{
	cacheGet_SubscriptionInfo_SIDS(env, thiz, mSDMCCaSubscriptionInfo);
	cacheGet_AuthPeriod_SIDS(env, thiz, mSDMCCaAuthPeriod);
	cacheGet_CA_DATE_TIME_SIDS(env, thiz, mSDMCCaDateTime);
	cacheGet_SDMCCaPPVRequestInfo(env, thiz, mSDMCCaPPVRequestInfo);
	cacheGet_SDMCCaPurseInfo(env, thiz, mSDMCCaPurseInfo);
	cacheGet_SDMCCaPPVEventInfo(env, thiz, mSDMCCaPPVEventInfo);
}

unsigned char* jstringToChar(JNIEnv* env, jstring jstr)
{
	unsigned char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0)
	{
		rtn = (unsigned char*)malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_cancelPPVRequest
(JNIEnv *env, jclass thiz){
	return SDMCCA_CancelPPVRequest();
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_acceptPPVRequest
(JNIEnv *env, jclass thiz,jstring pPin){
	jstring nPin = pPin;
	unsigned char* nPinChar = jstringToChar(env, nPin);
	int result = SDMCCA_AcceptPPVRequest(nPinChar);
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_cancelOrderInfo
(JNIEnv *env, jclass thiz){
	return SDMCCA_CancelOrderInfo();
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_acceptOrderInfo
(JNIEnv *env, jclass thiz, jstring pPin){
	jstring nPin = pPin;
	unsigned  char* nPinChar = jstringToChar(env, nPin);
	int result = SDMCCA_AcceptOrderInfo(nPinChar);
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_cancelStartView
(JNIEnv *env, jclass thiz){
	return SDMCCA_CancelStartView();
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_acceptStartView
(JNIEnv *env, jclass thiz, jstring pPin){
	jstring nPin = pPin;
	unsigned char* nPinChar = jstringToChar(env, nPin);
	int result = SDMCCA_AcceptStartView(nPinChar);
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_cancelMaturityRat
(JNIEnv *env, jclass thiz){
	return SDMCCA_CancelMaturityRat();
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_acceptMaturityRat
(JNIEnv *env, jclass thiz, jstring pPin)
{
	jstring nPin = pPin;
	unsigned char* nPinChar = jstringToChar(env, nPin);
	int result = SDMCCA_AcceptMaturityRat(nPinChar);
	return result;
};

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_changeCardMaturityRating
(JNIEnv *env, jclass thiz, jint jLevel, jstring pPin){
	jstring nPin = pPin;
	unsigned char* nPinChar = jstringToChar(env, nPin);
	ConaxCaMaturityRating sLevel = (ConaxCaMaturityRating) jLevel;
	int result = SDMCCA_ChangeCardMaturityRating(sLevel, nPinChar);
	return result; 
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_getCardMaturityRating
(JNIEnv *env, jclass thiz){
	ConaxCaMaturityRating sLevel;
	SDMCCA_GetCardMaturityRating(&sLevel);
	LOGI("accept rating level is %d",sLevel);
	return sLevel;
} 

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_changeCardPin
(JNIEnv *env, jclass thiz, jstring pSzPinOld, jstring pSzPinNew){
	jstring nPinOld = pSzPinOld;
	jstring nPinNew = pSzPinNew;
	unsigned char* nPinOldChar = jstringToChar(env,nPinOld);
	unsigned char* nPinNewChar = jstringToChar(env,nPinNew);
	LOGI("pin old = %c",nPinOldChar);
	LOGI("pin new = %c",nPinOldChar);
	int result = SDMCCA_ChangeCardPin(nPinOldChar, nPinNewChar);
	return result;
}

static void setTimeAndDate(JNIEnv *env, jobject startTimeObj, SDMCCaDateTime time){
	env->SetIntField(startTimeObj, mSDMCCaDateTime.jfm_dwYear, time.m_dwYear);
	env->SetIntField(startTimeObj, mSDMCCaDateTime.m_dwMonth, time.m_dwMonth);
	env->SetIntField(startTimeObj, mSDMCCaDateTime.m_dwDay, time.m_dwDay);
	env->SetIntField(startTimeObj, mSDMCCaDateTime.m_dwHour, time.m_dwHour);
	env->SetIntField(startTimeObj, mSDMCCaDateTime.m_dwMinute, time.m_dwMinute);
	env->SetIntField(startTimeObj, mSDMCCaDateTime.m_dwSecond, time.m_dwSecond);
	env->SetIntField(startTimeObj, mSDMCCaDateTime.m_dwCentisecond, time.m_dwCentisecond);
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_getPpvEventInfo
(JNIEnv *env, jclass thiz, jint dwRecordIndex, jobject pstPpvRecord){
	int nDwRecordIndex = dwRecordIndex;
	SDMCCaPPVEventInfo info = {0};
	memset(&info, 0x00, sizeof(SDMCCaPPVEventInfo));
	int result = SDMCCA_GetPpvEventInfo(nDwRecordIndex,&info);
	LOGI("Conax CA get Event Status label = %s",&info.m_szLabel[0]);
	env->SetIntField(pstPpvRecord, mSDMCCaPPVEventInfo.m_dwEventID,info.m_dwEventID);
//	jcharArray nLabelNameArray = (jcharArray)(env->GetObjectField(pstPpvRecord,mSDMCCaPPVEventInfo.m_szLabel));
//	env->SetCharArrayRegion(nLabelNameArray,0,ConaxCA_MAX_LABEL_NAME_LEN,(const jchar *)info.m_szLabel);
	env->SetObjectField(pstPpvRecord,mSDMCCaPPVEventInfo.m_szLabel,env->NewStringUTF((const char*)info.m_szLabel));
	env->SetShortField(pstPpvRecord, mSDMCCaPPVEventInfo.m_MinutesOrCreditsLeft,info.m_MinutesOrCreditsLeft);
	env->SetShortField(pstPpvRecord, mSDMCCaPPVEventInfo.m_wAuthType,info.m_wAuthType);

	jobject nStartTimeObj = env->GetObjectField(pstPpvRecord, mSDMCCaPPVEventInfo.m_stStart);
	setTimeAndDate(env, nStartTimeObj, info.m_stStart);
	jobject nEndTimeObj = env->GetObjectField(pstPpvRecord, mSDMCCaPPVEventInfo.m_stEnd);
	setTimeAndDate(env, nEndTimeObj, info.m_stEnd);
	env->DeleteLocalRef(nEndTimeObj);
	env->DeleteLocalRef(nStartTimeObj);
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_getPpvEventTotalNum
(JNIEnv *env, jclass thiz)
{
	return SDMCCA_GetPpvEventTotalNum();
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_coreTVCAGetCAEnable
(JNIEnv *env, jclass thiz)
{	
	return CoreTVCAIsAvalable();
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_getPurseInfo
(JNIEnv *env, jclass thiz, jint dwPurseIndex, jobject pstCaPurseInfo)
{
	int mPurseIndex = dwPurseIndex;
	SDMCCaPurseInfo info = {0};
	memset(&info, 0x00, sizeof(SDMCCaPurseInfo));
	int result = SDMCCA_GetPurseInfo(mPurseIndex, &info);
	env->SetObjectField(pstCaPurseInfo, mSDMCCaPurseInfo.m_acLabel, env->NewStringUTF((const char*)info.m_acLabel));
	env->SetIntField(pstCaPurseInfo, mSDMCCaPurseInfo.m_dwBalance, info.m_dwBalance);
	env->SetShortField(pstCaPurseInfo, mSDMCCaPurseInfo.m_wPurseRef, info.m_wPurseRef);
	return result;
};

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_getPurseTotalNum
(JNIEnv *env, jclass thiz)
{
	return SDMCCA_GetPurseTotalNum();
};

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_getSubscriptionTotalNum
(JNIEnv *env, jclass thiz)
{
	return SDMCCA_GetSubscriptionTotalNum();
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_getSubscriptionInfo
(JNIEnv *env, jclass thiz, jint dwRecordIndex, jobject jSubscriptionInfo)
{
	int mDwRecordIndex = dwRecordIndex;
	SDMCCaSubscriptionInfo info = {0};
	memset(&info, 0x00, sizeof(SDMCCaSubscriptionInfo));
	int result = SDMCCA_GetSubscriptionInfo(mDwRecordIndex, &info);
	env->SetObjectField(jSubscriptionInfo, mSDMCCaSubscriptionInfo.mSzLabelID, env->NewStringUTF((const char *)info.m_szLabel));
	env->SetShortField(jSubscriptionInfo, mSDMCCaSubscriptionInfo.mWRefID, info.m_wRefID);
	
	jobjectArray bridgeAuthPeriod = (jobjectArray)(env->GetObjectField (jSubscriptionInfo, mSDMCCaSubscriptionInfo.mAstAuthPeriodID));  //建立结构体内结构体数组CoreTVCA_Email_Data_S对象
	for (int i = 0; i < 2; i ++)
	{
		jobject mAuthPeriodinfo = env->GetObjectArrayElement(bridgeAuthPeriod, i);
		env->SetIntField(mAuthPeriodinfo, mSDMCCaAuthPeriod.mDwEntitlementID, info.m_astAuthPeriod[i].m_dwEntitlement);
		
		jobject bridgeStartTime = (jobject)(env->GetObjectField(mAuthPeriodinfo, mSDMCCaAuthPeriod.mStStartID));
		jobject bridgeEndTime = (jobject)(env->GetObjectField(mAuthPeriodinfo, mSDMCCaAuthPeriod.mStEndID));
		
		setTimeAndDate(env, bridgeStartTime, info.m_astAuthPeriod[i].m_stStart);
		setTimeAndDate(env, bridgeEndTime, info.m_astAuthPeriod[i].m_stEnd);
		
		env->DeleteLocalRef(bridgeStartTime);
		env->DeleteLocalRef(bridgeEndTime);
		env->DeleteLocalRef(mAuthPeriodinfo);
	}
	env->DeleteLocalRef(bridgeAuthPeriod);
	return result;
}


JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_coreTVCAGetSHADTProperty
  (JNIEnv *env, jclass thiz, jint jnPropertyID, jobject jCAInfo)
{
	int nPropertyID = jnPropertyID;
	CORETVCACARDEXTENDINFO_SHADT_S infor = {0};  //为出参赋值
	memset(&infor , 0x00 ,sizeof(CORETVCACARDEXTENDINFO_SHADT_S));
	LOGI(" in ==========\n");
	int nIndex = 0;
	int result = CoreTVCAGetProperty(nPropertyID, &infor, sizeof(CORETVCACARDEXTENDINFO_SHADT_S), &nIndex);

	LOGI("infor.m_uiCardQuota  %d" , infor.m_uiCardQuota);
	LOGI("infor.m_uiCardConsume %d " , infor.m_uiCardConsume);
	LOGI("infor.m_ucZoneCode %d" , infor.m_ucZoneCode);
	LOGI("infor.m_ucPariedStatus %d" , infor.m_ucPariedStatus);
	LOGI("infor.m_usRecentExpireDay %d" , infor.m_usRecentExpireDay);	
	LOGI("infor.m_usCtrlCode %d" , infor.m_usCtrlCode);	
	LOGI("infor.m_usCASotfVersion %d" , infor.m_usCASotfVersion);
	
	jclass objectID = env->FindClass ("com/sdmc/jni/CoreTVCA$CORETVCACARDEXTENDINFO_SHADT_S");
	jfieldID m_usCASotfVersionID = env->GetFieldID(objectID,"m_usCASotfVersion","S");
	jfieldID m_aucCardSNID = env->GetFieldID(objectID,"m_aucCardSN","[B");
	jfieldID m_ucPariedStatusID = env->GetFieldID(objectID,"m_ucPariedStatus","I");
	jfieldID m_ucZoneCodeID = env->GetFieldID(objectID,"m_ucZoneCode","I");
	
	jfieldID m_usCtrlCodeID = env->GetFieldID(objectID,"m_usCtrlCode","S");
	jfieldID m_uiCardConsumeID = env->GetFieldID(objectID,"m_uiCardConsume","I");
	jfieldID m_usRecentExpireDayID = env->GetFieldID(objectID,"m_usRecentExpireDay","S");
	jfieldID m_aucCardEigenValueID = env->GetFieldID(objectID,"m_aucCardEigenValue","[B");
	jfieldID m_uiCardQuotaID = env->GetFieldID(objectID,"m_uiCardQuota","I");

	env->SetShortField(jCAInfo,m_usCtrlCodeID,infor.m_usCtrlCode);
	env->SetShortField(jCAInfo,m_usCASotfVersionID,infor.m_usCASotfVersion);
	env->SetShortField(jCAInfo,m_usRecentExpireDayID,infor.m_usRecentExpireDay);

	env->SetIntField(jCAInfo,m_ucPariedStatusID,(jint)infor.m_ucPariedStatus);
	env->SetIntField(jCAInfo,m_ucZoneCodeID,(jint)infor.m_ucZoneCode);

	env->SetIntField(jCAInfo,m_uiCardConsumeID,infor.m_uiCardConsume);
	env->SetIntField(jCAInfo,m_uiCardQuotaID,infor.m_uiCardQuota);


	jbyteArray aucCardSNIDByteArray = (jbyteArray)(env->GetObjectField (jCAInfo, m_aucCardSNID));    
	env->SetByteArrayRegion(aucCardSNIDByteArray, 0, 8, (const jbyte *)infor.m_aucCardSN);
	jbyteArray m_aucCardEigenValueByteArray = (jbyteArray)(env->GetObjectField (jCAInfo, m_aucCardEigenValueID));    
	env->SetByteArrayRegion(m_aucCardEigenValueByteArray, 0, 32, (const jbyte *)infor.m_aucCardEigenValue);
	

	LOGI("infor.m_uiCardQuota  %d" , infor.m_uiCardQuota);
	LOGI("infor.m_uiCardConsume %d " , infor.m_uiCardConsume);
	LOGI("infor.m_ucZoneCode %d" , infor.m_ucZoneCode);
	LOGI("infor.m_ucPariedStatus %d" , infor.m_ucPariedStatus);
	LOGI("infor.m_usRecentExpireDay %d" , infor.m_usRecentExpireDay);	
	LOGI("infor.m_usCtrlCode %d" , infor.m_usCtrlCode);	
	LOGI("infor.m_usCASotfVersion %d" , infor.m_usCASotfVersion);
	env->DeleteLocalRef(aucCardSNIDByteArray);
	env->DeleteLocalRef(m_aucCardEigenValueByteArray);
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_coreTVCAGetConaxProperty
  (JNIEnv *env, jclass thiz, jint jnPropertyID, jobject jCAInfo)
{
	int nPropertyID = jnPropertyID;
	CORETVCACARDEXTENDINFO_CONAX_S infor = {0};  //为出参赋值
	memset(&infor , 0x00 ,sizeof(CORETVCACARDEXTENDINFO_CONAX_S));
	LOGI("infor.m_wLanguage  %d" , infor.m_wLanguage);
	LOGI("infor.m_cInterfaceVer %d " , infor.m_cInterfaceVer);
	LOGI("infor.m_cNumOfSession %d" , infor.m_cNumOfSession);
	LOGI("infor.m_CALibVersion %d" , infor.m_CALibVersion);
	LOGI("infor.m_cSoftVersion %s" , infor.m_cSoftVersion);	
	LOGI("infor.m_szCardId %s" , infor.m_szCardId);	
	LOGI("infor.m_awCaSysId %d" , infor.m_cCaSysIdNum);
	LOGI(" in ==========\n");
	int nIndex = 0;
	int result = CoreTVCAGetProperty(nPropertyID, &infor, sizeof(CORETVCACARDEXTENDINFO_CONAX_S), &nIndex);
	LOGI("infor.m_wLanguage  %d" , infor.m_wLanguage);
	LOGI("infor.m_cInterfaceVer %d " , infor.m_cInterfaceVer);
	LOGI("infor.m_cNumOfSession %d" , infor.m_cNumOfSession);
	LOGI("infor.m_CALibVersion %s" , infor.m_CALibVersion);
	LOGI("infor.m_cSoftVersion %s" , infor.m_cSoftVersion);	
	LOGI("infor.m_szCardId %s" , infor.m_szCardId);	
	LOGI("infor.m_awCaSysId %d" , infor.m_cCaSysIdNum);
	
	jclass objectID = env->FindClass ("com/sdmc/jni/CoreTVCA$CORETVCACARDEXTENDINFO_CONAX_S");
	jfieldID m_LanguageID = env->GetFieldID(objectID,"m_wLanguage","S");
	jfieldID mInterfaceVer = env->GetFieldID(objectID,"m_cInterfaceVer","C");
	jfieldID mNumOfSession = env->GetFieldID(objectID,"m_cNumOfSession","C");
	jfieldID mAwCaSysId = env->GetFieldID(objectID,"m_awCaSysId","[S");
	jfieldID mCaSysIdNum = env->GetFieldID(objectID,"m_cCaSysIdNum","C");
	
	jfieldID mCALibVersion = env->GetFieldID(objectID,"m_CALibVersion","Ljava/lang/String;");
	jfieldID mSoftVersion = env->GetFieldID(objectID,"m_cSoftVersion","Ljava/lang/String;");
	jfieldID mSzCardId = env->GetFieldID(objectID,"m_szCardId","Ljava/lang/String;");
	jfieldID mAcChipId = env->GetFieldID(objectID,"m_acChipId","Ljava/lang/String;");

	env->SetShortField(jCAInfo,m_LanguageID,infor.m_wLanguage);
	env->SetCharField(jCAInfo,mInterfaceVer,infor.m_cInterfaceVer);
	env->SetCharField(jCAInfo,mNumOfSession,infor.m_cNumOfSession);
	env->SetObjectField(jCAInfo,mCALibVersion,env->NewStringUTF((const char *)infor.m_CALibVersion));
	env->SetObjectField(jCAInfo,mSoftVersion,env->NewStringUTF((const char *)infor.m_cSoftVersion));
	env->SetObjectField(jCAInfo,mSzCardId,env->NewStringUTF((const char *)infor.m_szCardId));
	env->SetObjectField(jCAInfo,mAcChipId,env->NewStringUTF((const char *)infor.m_acChipId));
	env->SetCharField(jCAInfo,mCaSysIdNum,infor.m_cCaSysIdNum);

	jshortArray BridgeByteArray = (jshortArray)(env->GetObjectField (jCAInfo, mAwCaSysId));    
	env->SetShortArrayRegion(BridgeByteArray, 0, 64, (const jshort *)infor.m_awCaSysId);
	
	LOGI("infor.m_wLanguage  %d" , infor.m_wLanguage);
	LOGI("infor.m_cInterfaceVer %d " , infor.m_cInterfaceVer);
	LOGI("infor.m_cNumOfSession %d" , infor.m_cNumOfSession);
	LOGI("infor.m_CALibVersion %d" , infor.m_CALibVersion);
	LOGI("infor.m_cSoftVersion %s" , infor.m_cSoftVersion);	
	LOGI("infor.m_szCardId %s" , infor.m_szCardId);	
	LOGI("infor.m_awCaSysId %d" , infor.m_cCaSysIdNum);
	env->DeleteLocalRef(BridgeByteArray);
	return result;
}

JNIEXPORT jint JNICALL Java_com_sdmc_jni_CoreTVCA_changeMailFlag
  (JNIEnv *env, jclass thiz, jint mailId)
{
	return SDMCCA_SetReadFlag_Email(mailId);
}
