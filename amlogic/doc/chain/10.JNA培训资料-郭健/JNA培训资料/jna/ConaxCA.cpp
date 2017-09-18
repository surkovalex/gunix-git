#include "CoreTV_Error.h"
#include "JNACommon.h"
#include "CoreTV_CA.h"
#include "conax_ext.h"

extern "C" {

int ConaxGetCardInfo(ConaxCardInfo_S *pstCardInfo) {
	return CoreTVCASetProperty(SDMCCA_PROPERTY_CA_INFO, 0, pstCardInfo);
}

int ConaxGetSubscriptionNum(int *puRecordNum) {
	return CoreTVCASetProperty(SDMCCA_PROPERTY_SUBSCRIPTION_NUM, 0, puRecordNum);
}

int ConaxGetSubscriptionInfo(unsigned int *puRecordIndex, ConaxSubscriptionInfo_S *pstSubRecord) {
	return CoreTVCASetProperty(SDMCCA_PROPERTY_SUBSCRIPTION_INFO, puRecordIndex, pstSubRecord);
}

int ConaxGetPpvEventNum(int *piEventNum) {
	return CoreTVCASetProperty(SDMCCA_PROPERTY_PPV_EVENT_NUM, 0, piEventNum);
}

int ConaxGetPpvEventInfo(unsigned int *puRecordIndex, ConaxPPVEventInfo_S* pstPpvRecord) {
	return CoreTVCASetProperty(SDMCCA_PROPERTY_PPVEVENT_INFO, puRecordIndex, pstPpvRecord);
}

int ConaxGetPurseNum(int *piPurseNum) {
	return CoreTVCASetProperty(SDMCCA_PROPERTY_PURSE_NUM, 0, piPurseNum);
}

int ConaxGetPurseInfo(unsigned int *puPurseIndex, ConaxPurseInfo_S *pstPurseInfo) {
	return CoreTVCASetProperty(SDMCCA_PROPERTY_PURSE_INFO, puPurseIndex, pstPurseInfo);
}

int ConaxGetDebitInfo(unsigned int *puPurseIndex, ConaxDebitInfo_S *ppstDebitInfo) {
	return CoreTVCASetProperty(SDMCCA_PROPERTY_DEBIT_INFO, puPurseIndex, &ppstDebitInfo);
}

int ConaxGetCreditInfo(unsigned int *puPurseIndex, ConaxCreditInfo_S* ppstCreditInfo) {
	return CoreTVCASetProperty(SDMCCA_PROPERTY_CREDIT_INFO, puPurseIndex, &ppstCreditInfo);
}

int CONAXGetMaturityRat(ConaxMaturityRating_E *peMat) {
	return CoreTVCASetProperty(SDMCCA_PROPERTY_MATURITY_RAT, 0, peMat);
}

int ConaxChangeMaturityRat(ConaxChangeMatRat_S *pstMatRat) {
	return CoreTVCASetProperty(SDMCCA_CHANGE_MATURITY_RAT, pstMatRat, 0);
}

int ConaxAcceptMaturityRat(unsigned char *pucPin) {
	return CoreTVCASetProperty(SDMCCA_ACCEPT_MATURITY_RAT, pucPin, 0);
}

int ConaxCancelMaturityRat() {
	return CoreTVCASetProperty(SDMCCA_CANCEL_MATURITY_RAT, 0, 0);
}

int ConaxAcceptStartView(unsigned char *pucPin) {
	return CoreTVCASetProperty(SDMCCA_ACCEPT_START_VIEW, pucPin, 0);
}

int CONAXCancelStartView() {
	return CoreTVCASetProperty(SDMCCA_CANCEL_START_VIEW, 0, 0);
}

int CONAXAcceptOrderInfo(unsigned char *pucPin) {
	return CoreTVCASetProperty(SDMCCA_ACCEPT_ORDER_INFO, pucPin, 0);
}

int CONAXCancelOrderInfo() {
	return CoreTVCASetProperty(SDMCCA_CANCEL_ORDER_INFO, 0, 0);
}

int CONAXAcceptPPVRequest(unsigned char *pucPin) {
	return CoreTVCASetProperty(SDMCCA_ACCEPT_PPV_REQUEST, pucPin, 0);
}

int CONAXCancelPPVRequest() {
	return CoreTVCASetProperty(SDMCCA_CANCEL_PPV_REQUEST, 0, 0);
}

int CONAXChangeCardPin(ConaxChangePassword_S *pstChangePinCode) {
	return CoreTVCASetProperty(SDMCCA_CHANGE_CARD_PIN, pstChangePinCode, 0);
}

int CONAXSetEmailReadFlag(unsigned int *puMailID) {
	return CoreTVCASetProperty(SDMCCA_SET_EMAIL_READ_FLAG, puMailID, 0);
}

int CONAXSetEmailSequence(ConaxEmailSeq_E *peMSeq) {
	return CoreTVCASetProperty(SDMCCA_SET_EMAIL_SEQUENCE, peMSeq, 0);
}

}
