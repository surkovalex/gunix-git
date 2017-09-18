/*
 * SDMCCAPublic.cpp
 *
 *  Created on: 2016Äê11ÔÂ23ÈÕ
 *      Author: Sheldon
 */

#include "string.h"
#include "CoreTV_Error.h"
#include "JNACommon.h"
#include "CAAPI.h"

CAEventCallback sEventCallback;

static void CACallback(CoreTVCAEvent event, void *pvUserData) {
	if (sEventCallback) {
		CAEvent caEvent = {0};
		if (event.mEvent) {
			CAEvent* pCaEvent = (CAEvent*) event.mEvent;
			caEvent.mNumber = pCaEvent->mNumber;
			caEvent.mMsgLength = pCaEvent->mMsgLength;
			if (caEvent.mMsgLength > 0) {
				memcpy(caEvent.mMsg, pCaEvent->mMsg, pCaEvent->mMsgLength);
			}
		}

		sEventCallback(event.mType, event.mEventID, &caEvent);
	}
}

int CAAPIGetSupportCAS(CASupportInfo *pCASupportInfos, int count, int *pValidCount) {
	return CoreTVCAGetSupportCAS((CoreTVCASupportInfo *) pCASupportInfos, count, pValidCount);
}

int CAAPISetCurrentCA(const char* type) {
	return CoreTVCASetCurrentCA(type);
}

int CAAPISetListener(CAEventCallback eventCallback) {
	if (sEventCallback) {
		LOGE("CAAPI_SetListener faild: CAEventCallback is already set!");
		return CORETV_FAILURE;
	}
	sEventCallback = eventCallback;
	return CoreTVCASetListener(CACallback, 0);
}

int CAAPIRemoveListener() {
	sEventCallback = 0;
	return CoreTVCARemoveListener();
}

