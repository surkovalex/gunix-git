/*
 * CAAPI.h
 *
 *  Created on: 2016Äê11ÔÂ23ÈÕ
 *      Author: Sheldon
 */

#ifndef CAAPI_H_
#define CAAPI_H_

#include "CoreTV_CA.h"
#include "SDMCCAPublic.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct {
	char mMineType[32];
} CASupportInfo;

typedef void (*CAEventCallback) (int type, int eventID, CAEvent *pEvent);

extern int CAAPIGetSupportCAS(CASupportInfo *pCASupportInfos, int count, int *pValidCount);

extern int CAAPISetCurrentCA(const char* type);

extern int CAAPISetListener(CAEventCallback eventCallback);

extern int CAAPIRemoveListener();

extern int CAAPISetProperty(int type, void *pPropParam, void *pPropRes);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CAAPI_H_ */
