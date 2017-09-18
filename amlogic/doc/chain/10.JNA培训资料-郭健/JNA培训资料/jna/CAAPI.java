package com.sdmc.dtv.ca;

import java.util.ArrayList;
import java.util.List;

import com.sdmc.jni.CoreTVAPI;
import com.sun.jna.Callback;
import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;

public class CAAPI {
	
	public static final int SDMCCA_PUBLIC_EVENT = 0;
	public static final int PUBLIC_EVENT_REPLY_NIT          = SDMCCA_PUBLIC_EVENT; 	    //处理nit表的应答，参数为SDMCCA_Error_Code
	public static final int PUBLIC_EVENT_REPLY_PAT          = SDMCCA_PUBLIC_EVENT + 1;  //处理pat表的应答，参数为SDMCCA_Error_Code
	public static final int PUBLIC_EVENT_REPLY_PMT          = SDMCCA_PUBLIC_EVENT + 2;  //处理pmt表的应答，参数为SDMCCA_Error_Code
	public static final int PUBLIC_EVENT_CAT                = SDMCCA_PUBLIC_EVENT + 3;  //处理cat表的应答，参数为SDMCCA_Error_Code
	public static final int PUBLIC_EVENT_BAT                = SDMCCA_PUBLIC_EVENT + 4;  //处理bat表的应答，参数为SDMCCA_Error_Code
	public static final int PUBLIC_EVENT_START              = SDMCCA_PUBLIC_EVENT + 5;  //处理startservice的应答，参数为SDMCCA_Error_Code
	public static final int PUBLIC_EVENT_STOP               = SDMCCA_PUBLIC_EVENT + 6;  //处理stopservice的应答，参数为SDMCCA_Error_Code
	public static final int PUBLIC_EVENT_SCINFO             = SDMCCA_PUBLIC_EVENT + 7;
	public static final int PUBLIC_EVENT_UNKNOW_ERROR       = SDMCCA_PUBLIC_EVENT + 8;  //CA 未知错误通知 
	public static final int PUBLIC_EVENT_CARD_READY         = SDMCCA_PUBLIC_EVENT + 9;  //卡就绪 
	public static final int PUBLIC_EVENT_CARD_INSERT   	    = SDMCCA_PUBLIC_EVENT + 10;	//卡插入 
	public static final int PUBLIC_EVENT_CARD_REMOVE 		= SDMCCA_PUBLIC_EVENT + 11;	//卡拔出 
	public static final int PUBLIC_EVENT_CARD_ERROR 		= SDMCCA_PUBLIC_EVENT + 12;	//卡出错 
	public static final int PUBLIC_EVENT_CARD_INVALID 		= SDMCCA_PUBLIC_EVENT + 13;	//卡无效  
	public static final int PUBLIC_EVENT_NOT_SUPPORT 		= SDMCCA_PUBLIC_EVENT + 14;	//CA不支持  
	public static final int PUBLIC_EVENT_NOT_AUTHORIZED 	= SDMCCA_PUBLIC_EVENT + 15;	//码流没有授权
	public static final int PUBLIC_EVENT_CARD_REMOVE_START 	= SDMCCA_PUBLIC_EVENT + 16;	//播放节目当时卡被拔出
	public static final int PUBLIC_EVENT_CARD_ERROR_START 	= SDMCCA_PUBLIC_EVENT + 17;	//播放节目当时卡错误
	public static final int PUBLIC_EVENT_PARENT_CTR 		= SDMCCA_PUBLIC_EVENT + 18;	//this program is locked by parent control para2=locked level a int-value 
	public static final int PUBLIC_EVENT_STBCARD_NOT_MATCH  = SDMCCA_PUBLIC_EVENT + 19;	//机卡不匹配
	
	public static final int SDMCCA_FAILURE = -1;                                        //操作失败
	public static final int SDMCCA_SUCCESS = 0;											//操作成功
	
	public static final int SDMCCA_ERROR_UNKNOWN = 0x100;								//未知错误
	public static final int SDMCCA_ERROR_NO_SUPPORT_CA 		= SDMCCA_ERROR_UNKNOWN + 1; //不支持的CA
	public static final int SDMCCA_ERROR_INPUT_PARAM_ERROR 	= SDMCCA_ERROR_UNKNOWN + 2; //输入参数错误
	public static final int SDMCCA_ERROR_INIT_FAILD 		= SDMCCA_ERROR_UNKNOWN + 3; //初始化失败
	public static final int SDMCCA_ERROR_NO_SUCH_PROPERTY 	= SDMCCA_ERROR_UNKNOWN + 4; //无效的property

	static {  
        System.loadLibrary("dtv_jna");
    }
	
	private static CAEventListener mCAEventListener;
	
	private static CAEventCallback sCAEventCallback = new CAEventCallback() {
		
		@Override
		public void onEvent(int type, int eventID, CAEvent.ByReference event) {
			if (mCAEventListener != null) {
				CAEvent cEvent = event;
				mCAEventListener.onEvent(type, eventID, cEvent);
			}
		}
	};
	
	public static CASupportInfo[] getSupportCAS() {
		CASupportInfo[] result = new CASupportInfo[0];
		int count = 8;
		CASupportInfo[] pSuppportInfos = (CASupportInfo[]) new CASupportInfo().toArray(count);
		IntByReference pValidCount = new IntByReference(0);
		
		if (CoreTVAPI.CORETV_SUCCESS == 
				ICAAPI.INSTANCE.CAAPIGetSupportCAS(pSuppportInfos, count, pValidCount)) {
			if (pValidCount.getValue() > 0) {
				result = new CASupportInfo[pValidCount.getValue()];
				for (int i = 0; i < pValidCount.getValue(); i++) {
					result[i] = pSuppportInfos[i];
				}
			}
		}
		
		for (CASupportInfo info : pSuppportInfos) {
			info.clear();
		}
		
		return result;
	}
	
	public static boolean setCurrentCA(String type) {
		return CoreTVAPI.CORETV_SUCCESS == ICAAPI.INSTANCE.CAAPISetCurrentCA(type);
	}
	
	public static boolean setCAEventListener(CAEventListener listener) {
		if (mCAEventListener != null) {
			return false;
		}
		mCAEventListener = listener;
		return CoreTVAPI.CORETV_SUCCESS == ICAAPI.INSTANCE.CAAPISetListener(sCAEventCallback);
	}
	
	public static void removeListener() {
		if (mCAEventListener != null) {
			mCAEventListener = null;
			ICAAPI.INSTANCE.CAAPIRemoveListener();
		}
	}
	
	public interface ICAAPI extends Library {
		ICAAPI INSTANCE = (ICAAPI) Native.loadLibrary("dtv_jna", ICAAPI.class);
		
        public int CAAPIGetSupportCAS(CASupportInfo[] suppportInfos, 
        		int count, IntByReference validCount);
        public int CAAPISetCurrentCA(String type);
        public int CAAPISetListener(CAEventCallback callback);
        public int CAAPIRemoveListener();
    }
	
	public static class CASupportInfo extends Structure {
    	public static class ByReference extends CASupportInfo implements Structure.ByReference { }
    	
    	public byte[] mMineType = new byte[32];
        
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mMineType");
            return names;
		}
		
		public String getMineType() {
			return new String(mMineType).trim();
		}
	}
	
	public static class CAEvent extends Structure {
    	public static class ByReference extends CAEvent implements Structure.ByReference { }
    	
    	public int mNumber;
    	public byte[] mMsg = new byte[512];
    	public int mMsgLength;
    	
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mNumber");
            names.add("mMsg");
            names.add("mMsgLength");
            return names;
		}
	}
	
	public interface CAEventCallback extends Callback {
		public void onEvent(int type, int eventID, CAEvent.ByReference event);
	}
	
	public static interface CAEventListener {
		public void onEvent(int type, int eventID, CAEvent evnet);
	}
	
}
