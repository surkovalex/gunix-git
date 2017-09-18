package com.sdmc.dtv.ca;

import java.util.ArrayList;
import java.util.List;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;

public class ConaxCA {
	
	public static final String MINE_TYPE = "CONAX";
	
	public static final int CONAX_LABEL_NAME_MAX = 32;
	public static final int CONAX_DEBIT_MAX = 100;
	public static final int CONAX_CREDIT_MAX = 100;
	public static final int CONAX_TEXT_SIZE = 256;
	public static final int CONAX_ES_NUM = 16;
	public static final int CONAX_ID_NUM = 256;
	public static final int CONAX_CURRENCY_LEN = 8;
	public static final int CONAX_PIN_MAX = 4;	

	public static final int SDMCCA_CONAX_EVENT = 0x100;
	
	/** ConaxAppNotify_E */
	public static final int CONAX_EVENT_NEW_EMAIL             = SDMCCA_CONAX_EVENT;
	public static final int	CONAX_EVENT_SHORT_MSG             = SDMCCA_CONAX_EVENT + 1;              	
	public static final int CONAX_EVENT_FINGER_PRINT          = SDMCCA_CONAX_EVENT + 2;           	
	public static final int CONAX_EVENT_PPV_PREVIEW           = SDMCCA_CONAX_EVENT + 3;       	
	public static final int CONAX_EVENT_PPV_EXPIRED           = SDMCCA_CONAX_EVENT + 4;          	
	public static final int CONAX_EVENT_NO_ACCESS_TO_NETWORK  = SDMCCA_CONAX_EVENT + 5;      	
	public static final int CONAX_EVENT_ACCEPT_VIEW           = SDMCCA_CONAX_EVENT + 6;         	    
	public static final int CONAX_EVENT_ORDER_INFO            = SDMCCA_CONAX_EVENT + 7;					  	
	public static final int CONAX_EVENT_PPV_REQUEST           = SDMCCA_CONAX_EVENT + 8;   
	public static final int CONAX_EVENT_OTHER_CA              = SDMCCA_CONAX_EVENT + 9;   
       
	
	/** ConaxMaturityRating_E */
	public static final int CONAX_RAT_G = 0;
	public static final int CONAX_RAT_PG = 1;
	public static final int	CONAX_RAT_A = 2;
	public static final int CONAX_RAT_X = 3;
	public static final int CONAX_RAT_XXX = 4;
	
	/** ConaxEmailSeq_E */
	public static final int CONAX_EMAIL_NO_SEQ = 0;
	public static final int CONAX_EMAIL_TIME_ASC = 1;
	public static final int	CONAX_EMAIL_TIME_DESC = 2;
	public static final int CONAX_EMAIL_UNREAD_ASC = 3;
	public static final int CONAX_EMAIL_UNREAD_DESC = 4;
	public static final int CONAX_EMAIL_UNREAD_TIME_ASC = 5;
	public static final int CONAX_EMAIL_UNREAD_TIME_DESC = 6;
	public static final int	CONAX_EMAIL_MAIL_ID_ASC = 7;
	public static final int CONAX_EMAIL_MAIL_ID_DESC = 8; 
	public static final int CONAX_EMAIL_SHOW_TIME_ASC = 9;
	public static final int CONAX_EMAIL_MAX = 10;

	/** ConaxReturnType_E */
	public static final int CONAX_SUCCESS = 0;                     //²Ù×÷³É¹¦
	public static final int CONAX_WRONG_PASSWORD = 1;              //ÃÜÂë´íÎó
	public static final int	CONAX_FAILURE = -1;                    //²Ù×÷Ê§°Ü

	public interface IConaxCA extends Library {
		IConaxCA INSTANCE = (IConaxCA) Native.loadLibrary("dtv_jna", IConaxCA.class);
		public int ConaxGetCardInfo(CardInfo cardInfo);
		public int ConaxGetSubscriptionNum(IntByReference recordNum);
		public int ConaxGetSubscriptionInfo(IntByReference recordIndex, SubscriptionInfo subRecord);
		public int ConaxGetPpvEventNum(IntByReference eventNum);
		public int ConaxGetPpvEventInfo(IntByReference recordIndex, PPVEventInfo ppvRecord);
		public int ConaxGetPurseNum(IntByReference purseNum);
		public int ConaxGetPurseInfo(IntByReference purseIndex, PurseInfo purseInfo);
		public int ConaxGetDebitInfo(IntByReference purseIndex, DebitInfo debitInfo); 
		public int ConaxGetCreditInfo(IntByReference purseIndex, CreditInfo creditInfo);
		public int CONAXGetMaturityRat(IntByReference mat);
		public int ConaxChangeMaturityRat(ChangeMatRat matRat);
		public int ConaxAcceptMaturityRat(String pin);
		public int ConaxCancelMaturityRat();
		public int ConaxAcceptStartView(String pin);
		public int CONAXCancelStartView();
		public int CONAXAcceptOrderInfo(String pin);
		public int CONAXCancelOrderInfo();
		public int CONAXAcceptPPVRequest(String pin);
		public int CONAXCancelPPVRequest();
		public int CONAXChangeCardPin(ChangePassword changePinCode);
		public int CONAXSetEmailReadFlag(IntByReference mailID);
		public int CONAXSetEmailSequence(IntByReference mSeq); 	
    }
	
	public static int getCardInfo(CardInfo cardInfo) {
		return IConaxCA.INSTANCE.ConaxGetCardInfo(cardInfo);
	}
	
	public static int getSubscriptionNum() {	
		IntByReference recordNum = new IntByReference(0);
		IConaxCA.INSTANCE.ConaxGetSubscriptionNum(recordNum);
		return recordNum.getValue();
	}
	
	public static int getSubscriptionInfo(int index, SubscriptionInfo subRecord) {
		IntByReference recordIndex = new IntByReference(index);
		return IConaxCA.INSTANCE.ConaxGetSubscriptionInfo(recordIndex, subRecord);
	}
	
	public static int getPpvEventNum() {
		IntByReference eventNum = new IntByReference(0);
		return IConaxCA.INSTANCE.ConaxGetPpvEventNum(eventNum);
	}
	
	public static int getPpvEventInfo(int index, PPVEventInfo ppvRecord) {
		IntByReference recordIndex = new IntByReference(index);
		return IConaxCA.INSTANCE.ConaxGetPpvEventInfo(recordIndex, ppvRecord);
	}
	
	public static int getPurseNum() {
		IntByReference purseNum = new IntByReference(0);
		IConaxCA.INSTANCE.ConaxGetPurseNum(purseNum);
		return purseNum.getValue();
	}
	
	public static int getPurseInfo(int index, PurseInfo purseInfo) {
		IntByReference purseIndex = new IntByReference(index);
		return IConaxCA.INSTANCE.ConaxGetPurseInfo( purseIndex, purseInfo);
	}
	
	public static int getDebitInfo(IntByReference purseIndex,
			DebitInfo debitInfo) {
		return IConaxCA.INSTANCE.ConaxGetDebitInfo(purseIndex, debitInfo);
	}
	
	public static int getCreditInfo(IntByReference purseIndex, 
			CreditInfo creditInfo) {
		return IConaxCA.INSTANCE.ConaxGetCreditInfo(purseIndex, creditInfo);
	}
	
	public static int getMaturityRat() {
		IntByReference mat = new IntByReference(0);
		return IConaxCA.INSTANCE.CONAXGetMaturityRat(mat);
	}
	
	public static int changeMaturityRat(ChangeMatRat matRat) {
		return IConaxCA.INSTANCE.ConaxChangeMaturityRat(matRat);
	}
	
	public static int acceptMaturityRat(String pin) {
		return IConaxCA.INSTANCE.ConaxAcceptMaturityRat(pin);
	}
	
	public static int cancelMaturityRat() {
		return IConaxCA.INSTANCE.ConaxCancelMaturityRat();
	}
	
	public static int acceptStartView(String pin) {
		return IConaxCA.INSTANCE.ConaxAcceptStartView(pin);
	}
	
	public static int cancelStartView() {
		return IConaxCA.INSTANCE.CONAXCancelStartView();
	}
	
	public static int acceptOrderInfo(String pin) {
		return IConaxCA.INSTANCE.CONAXAcceptOrderInfo(pin);
	}
	
	public static int cancelOrderInfo() {
		return IConaxCA.INSTANCE.CONAXCancelOrderInfo();
	}
	
	public static int acceptPPVRequest(String pin) {
		return IConaxCA.INSTANCE.CONAXAcceptPPVRequest(pin);
	}
	
	public static int cancelPPVRequest() {
		return IConaxCA.INSTANCE.CONAXCancelPPVRequest();
	}
	
	public static int changeCardPin(ChangePassword changePinCode) {
		return IConaxCA.INSTANCE.CONAXChangeCardPin(changePinCode);
	}
	
	public static int setEmailReadFlag(int id) {
		IntByReference mailID = new IntByReference(id);
		return IConaxCA.INSTANCE.CONAXSetEmailReadFlag(mailID);
	}
	
	public static int setEmailSequence(int seq) {
		IntByReference mSeq = new IntByReference(seq);
		return IConaxCA.INSTANCE.CONAXSetEmailSequence(mSeq);
	}
	
	public static class ChangeMatRat extends Structure {
    	public static class ByReference extends ChangeMatRat implements Structure.ByReference { }
    	
    	public int mMatRat;
    	public byte[] mPin = new byte[CONAX_PIN_MAX];
    
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mMatRat");
            names.add("mPin");
            return names;
		}	
	}
	
	public static class ChangePassword extends Structure {
    	public static class ByReference extends ChangePassword implements Structure.ByReference { }
    	
    	public byte[] mOldPin = new byte[CONAX_PIN_MAX];
    	public byte[] mNewPin = new byte[CONAX_PIN_MAX];
    
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mOldPin");
            names.add("mNewPin");
            return names;
		}	
	}
	
	public static class CardInfo extends Structure {
    	public static class ByReference extends CardInfo implements Structure.ByReference { }
    	
    	public byte mSmcStatus;
    	public short mLanguage;
    	public byte mInterfaceVer;
    	public byte mNumOfSession;
    	public byte[] mLibVersion = new byte[128];
    	public byte[] mSoftVersion = new byte[20];
    	public byte[] mCardId = new byte[16];
    	public byte[] mChipId = new byte[16];
    	public short[] mCaSysId = new short[256];
    	public byte mCaSysIdNum;
    
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mSmcStatus");
            names.add("mLanguage");
            names.add("mInterfaceVer");
            names.add("mNumOfSession");
            names.add("mLibVersion");
            names.add("mSoftVersion");
            names.add("mCardId");
            names.add("mChipId");
            names.add("mCaSysId");
            names.add("mCaSysIdNum");
            return names;
		}	
	}
	
	public static class DateTime extends Structure {
    	public static class ByReference extends DateTime implements Structure.ByReference { }
    	
    	public int mYear;
    	public int mMonth;
    	public int mDay;
    	public int mHour;
    	public int mMinute;
    	public int mSecond;
    	public int mCentisecond;
    
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mYear");
            names.add("mMonth");
            names.add("mDay");
            names.add("mHour");
            names.add("mMinute");
            names.add("mSecond");
            names.add("mCentisecond");
            return names;
		}	
	}
	
	public static class AuthPeriod extends Structure {
    	public static class ByReference extends AuthPeriod implements Structure.ByReference { }
    	
    	public DateTime mStart = new DateTime();
    	public DateTime mEnd = new DateTime();
    	public int mEntitlement;
    
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mStart");
            names.add("mEnd");
            names.add("mEntitlement");
            return names;
		}	
	}
	
	public static class SubscriptionInfo extends Structure {
    	public static class ByReference extends SubscriptionInfo implements Structure.ByReference { }
    	
    	public byte[] mLabel = new byte[CONAX_LABEL_NAME_MAX];
    	public short mRefID;
    	public AuthPeriod[] mAuthPeriod = new AuthPeriod[2];
    
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mLabel");
            names.add("mRefID");
            names.add("mAuthPeriod");
            return names;
		}	
	}
	
	public static class PPVEventInfo extends Structure {
    	public static class ByReference extends PPVEventInfo implements Structure.ByReference { }
    	
    	public byte[] mLabel = new byte[CONAX_LABEL_NAME_MAX];
    	public int mEventID;
    	public DateTime mStart = new DateTime();
    	public DateTime mEnd = new DateTime();
    	public short mNumLeft;
    	public short mAuthType;
    
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mLabel");
            names.add("mEventID");
            names.add("mStart");
            names.add("mEnd");
            names.add("mNumLeft");
            names.add("mAuthType");
            return names;
		}	
	}
	
	public static class PurseInfo extends Structure {
    	public static class ByReference extends PurseInfo implements Structure.ByReference { }
    	
    	public short mPurseRef;
    	public int mBalance;
    	public byte[] mLabel = new byte[CONAX_LABEL_NAME_MAX];
    
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mPurseRef");
            names.add("mBalance");
            names.add("mLabel");
            return names;
		}	
	}
	
	public static class CreditStatus extends Structure {
    	public static class ByReference extends CreditStatus implements Structure.ByReference { }
    	
    	public int mCreditTokens;
    	public byte[] mLabel = new byte[CONAX_LABEL_NAME_MAX];
    
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mCreditTokens");
            names.add("mLabel");
            return names;
		}	
	}
	
	public static class DebitInfo extends Structure {
    	public static class ByReference extends DebitInfo implements Structure.ByReference { }
    	
    	public int mTotalNum;
    	public CreditStatus[] mDebitStatus = new CreditStatus[CONAX_DEBIT_MAX];
    
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mTotalNum");
            names.add("mDebitStatus");
            return names;
		}	
	}
	
	public static class CreditInfo extends Structure {
    	public static class ByReference extends DebitInfo implements Structure.ByReference { }
    	
    	public int mTotalNum;
    	public CreditStatus[] mCreditStatus = new CreditStatus[CONAX_CREDIT_MAX];
    
		@Override
		protected List<String> getFieldOrder() {
            List<String> names = new ArrayList<String>();  
            names.add("mTotalNum");
            names.add("mCreditStatus");
            return names;
		}	
	}
		
}
