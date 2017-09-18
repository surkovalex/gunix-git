package com.sdmc.jni;

import android.annotation.SuppressLint;
import java.util.HashMap;
import java.util.Map;

public class CoreTVCA {
	/** CoreTVCA_MULTICASEx_ConxMatrat_E */
	public static final int CoreTVCA_MULTICASEx_CONX_MATRAT_G = 0x01;
	public static final int CoreTVCA_MULTICASEx_CONX_MATRAT_PG = 0x02;
	public static final int CoreTVCA_MULTICASEx_CONX_MATRAT_A = 0x04;
	public static final int CoreTVCA_MULTICASEx_CONX_MATRAT_X = 0x08;
	public static final int CoreTVCA_MULTICASEx_CONX_MATRAT_XXX = 0x09;
	
	/** CORETV_CA_PROPERTY_ID */
	public static final int CORETV_CA_PROPERTY_MIN = 0;
	public static final int CORETV_CA_PROPERTY_CAS_INFORMATION = 1;
	public static final int CORETV_CA_PROPERTY_CAS_EXTEND_INFORMATION = 2;
	public static final int CORETV_CA_PROPERTY_CAS_VERSION = 3;
	public static final int CORETV_CA_PROPERTY_CARD_INFORMATION = 4;
	public static final int CORETV_CA_PROPERTY_CARD_EXTEND_INFORMATION = 5;
	public static final int CORETV_CA_PROPERTY_CARD_SUBSCRIPTION = 6;
	public static final int CORETV_CA_PROPERTY_CAS_Type = 7;
	public static final int CORETV_CA_PROPERTY_MAX = 8;
	
	/** CoreTVCA_MULTICASEx_CasInfo_S Type */
	public static final int CoreTVCA_TYPE_CTI = 0;
	public static final int CoreTVCA_TYPE_CONAX = 1;
	public static final int CoreTVCA_TYPE_BETACRYPT = 2;
	public static final int CoreTVCA_TYPE_DVN = 3;
	public static final int CoreTVCA_TYPE_TOPREAL = 4;
	public static final int CoreTVCA_TYPE_CAS001 = 5;
	public static final int CoreTVCA_TYPE_SHADT = 6;
	public static final int CoreTVCA_TYPE_ISHTAR = 7;
	public static final int CoreTVCA_TYPE_IRDETO = 8;
	public static final int CoreTVCA_TYPE_VIACCESS = 9;
	public static final int CoreTVCA_TYPE_CRYPTOWORKS = 10;
	public static final int CoreTVCA_TYPE_MGRD = 11;
	public static final int CoreTVCA_TYPE_MAGV = 12;
	public static final int CoreTVCA_TYPE_NDS = 13;
	public static final int CoreTVCA_TYPE_CDCAS = 14;//�����Ӳ�
	public static final int CoreTVCA_TYPE_DRE = 15;
	public static final int CoreTVCA_TYPE_MAX = 16;
	
	public static final int CORETVCA_IS_NOT_AVALABLE = 0;
	public static final int CORETVCA_IS_AVALABLE = 1;
	public static final int CONAXCA_MAX_LABEL_NAME_LEN = 32;

	// ��ĸ��
	public static final int ConaxRAT_G = 0; // for the family
	public static final int ConaxRAT_PG = 1; // with parental guidance
	public static final int ConaxRAT_A = 2; // over 18
	public static final int ConaxRAT_X = 3; // erotic
	public static final int ConaxRAT_XXX = 4; // erotic//hyb@090817

	@SuppressLint("UseSparseArrays")
	private static final Map<Integer, String> CoreTVCA_TYPE_MAP = new HashMap<Integer, String>() { 
		/**
		 * 
		 */
		private static final long serialVersionUID = 8635825437129884285L;

	{
		put(CoreTVCA_TYPE_CTI, "CTI");
		put(CoreTVCA_TYPE_CONAX, "CONAX");
		put(CoreTVCA_TYPE_BETACRYPT, "BETACRYPT");
		put(CoreTVCA_TYPE_DVN, "DVN");
		put(CoreTVCA_TYPE_TOPREAL, "TOPREAL");
		put(CoreTVCA_TYPE_CAS001, "CAS001");
		put(CoreTVCA_TYPE_SHADT, "SHADT");
		put(CoreTVCA_TYPE_ISHTAR, "ISHTAR");
		put(CoreTVCA_TYPE_IRDETO, "IRDETO");
		put(CoreTVCA_TYPE_VIACCESS, "VIACCESS");
		put(CoreTVCA_TYPE_CRYPTOWORKS, "CRYPTOWORKS");
		put(CoreTVCA_TYPE_MGRD, "MGRD");
		put(CoreTVCA_TYPE_MAGV, "MAGV");
		put(CoreTVCA_TYPE_NDS, "NDS");
		put(CoreTVCA_TYPE_DRE, "DRE");
	} };
	
	public static class Mpcount {
		public int mPcount;
	};

	public static class Pcount {
		public int pcount;
	}

	public static class CaPPVEventInfo {
		public String m_szLabel = new String();// ����
		public int m_dwEventID; // ��Ŀ����
		public SDMCCaDateTime m_stStart = new SDMCCaDateTime(); // �롢������Ч��������Ч
		public SDMCCaDateTime m_stEnd = new SDMCCaDateTime(); // �롢������Ч��������Ч
		public short m_MinutesOrCreditsLeft; // ʣ��������
		public short m_wAuthType;
	}

	public static class CaPurseInfo {
		public short m_wPurseRef;// Ǯ������
		public int m_dwBalance;// ���
		public String m_acLabel = new String();
	}

	public static class SDMCCaPPVRequestInfo {
		public short m_wPurseBalance; // ��ǰʹ��Ǯ�������
		public char m_cInsufficientTokens; // 1: ��������
		public char m_cTokensMode; // 0: ppv per event 1: ppv per time
		public int m_dwEventcost; // ��Ŀ�۸�
		public int m_dwEventTag;
		public char m_acProgramLabel[] = new char[CONAXCA_MAX_LABEL_NAME_LEN];// ��Ŀ���ƣ��ַ���
		public char m_acPurseLabel[] = new char[CONAXCA_MAX_LABEL_NAME_LEN]; // Ǯ�����ƣ��ַ���
	}

	public static class CORETVCACARDEXTENDINFO_CONAX_S {
		public short m_wLanguage; // language,should be displayed as a decimal
									// number with 1-3 digits
		public char m_cInterfaceVer; // interface version
		public char m_cNumOfSession; // number of session,should be displayed as
										// a decimal number
		public String m_CALibVersion = new String();// CAlib Info
		public String m_cSoftVersion = new String();// software version
		public String m_szCardId = new String(); // card number, should be
													// displayed as a decimal
													// number,
													// like" XXX XXXX XXXX - X"
		public String m_acChipId = new String();// ca system id, each one should
												// be displayed as a hexadecimal
												// number with four digits
		public short m_awCaSysId[] = new short[256]; // ca system id, each one
														// should be displayed
														// as a hexadecimal
														// number with four
														// digits
		public char m_cCaSysIdNum; // number of ca system id
	}

	public static class CORETVCACARDEXTENDINFO_SHADT_S {
		public short m_usCASotfVersion; // CAS����汾��,���緵��0x(0412),��Ӧ��ʾΪV4.1.2
		public byte[] m_aucCardSN = new byte[8]; // 8�ֽ����ܿ����ţ��˵���Ӧ����"%02x%02x..."��ʽ��ʾ
		public int m_ucPariedStatus; // �������״̬��1�������л������ܿ��Ѿ���ԣ�0�����к����ܿ���δ���
		public int m_ucZoneCode; // ������ƴ��룬���緵��ֵΪint��9������ʾΪ9
		public short m_usCtrlCode; // ���ܿ��޲��룬���緵��ֵΪ0d(0015),����ʾΪ"0015"

		public int m_uiCardConsume; // ��ȡ���ܿ�����Ǯ������������
		public short m_usRecentExpireDay; // ��ȡ�����Ȩ��������
		public byte[] m_aucCardEigenValue = new byte[32];// 32�ֽ����ܿ������룬�˵���Ӧ����"%02x%02x..."��ʾ
		public int m_uiCardQuota; // ��ȡ����Ǯ���ܶ��λΪ���㡱
	}

	public static class SDMCCaDateTime {
		public int m_dwYear;
		public int m_dwMonth;
		public int m_dwDay;
		public int m_dwHour;
		public int m_dwMinute;
		public int m_dwSecond;
		public int m_dwCentisecond;
	}

	public static class SDMCCaAuthPeriod {
		public SDMCCaDateTime m_stStart = new SDMCCaDateTime();// �ꡢ�¡�����Ч��������Ч
		public SDMCCaDateTime m_stEnd = new SDMCCaDateTime();// �ꡢ�¡�����Ч��������Ч
		public int m_dwEntitlement;// ��ʶ������Ȩ��Ϣ
	}

	public static class SDMCCaSubscriptionInfo {
		public SDMCCaSubscriptionInfo() {
			for (int i = 0; i < 2; i++) {
				m_astAuthPeriod[i] = new SDMCCaAuthPeriod();
			}
		}

		public String m_szLabel = new String();// ����
		public short m_wRefID; // ��Ŀ����
		public SDMCCaAuthPeriod m_astAuthPeriod[] = new SDMCCaAuthPeriod[2];// ��Ȩ��Ϣ
	}

	public static class CORETVCASINFORMATION_S {
		public short mCasystemid;
		public byte[] mCasystemversion = new byte[64];
		/** char������ca_system_version[64]; */
		public byte[] mCasystemvendor = new byte[128];
		/** char������ca_system_vendor[128] */
	};

	public static class CORETVCACARDINFORMATION_S {
		public byte mCacardslotid;
		public byte mCacardstatus; /* ȡֵ�μ� CORETV_CA_CARD_STATUS */

		public byte[] mCacardid = new byte[8];
		/** char������ ca_card_id[8]; */
		public byte[] mCacardversion = new byte[64];
		/** char������ca_card_version[64]; */
	}

	public static class CoreTVCA_Email_Title_S {
		int CTICAMAXBMAILNUM = 30;

		public CoreTVCA_Email_Title_S() {
			int i;
			for (i = 0; i < CTICAMAXBMAILNUM; i++) {
				mSEmailInfo[i] = new CoreTVCA_Email_Data_S();
			}
		}

		public byte mCaucTotleMailNum; // ��ǰ�ʼ������ʼ�����
		public byte mCaucNotReadNum; // ��ǰ�ʼ�����δ���ʼ�����
		public CoreTVCA_Email_Data_S[] mSEmailInfo = new CoreTVCA_Email_Data_S[CTICAMAXBMAILNUM];
		/** �������нṹ�嶨��ΪsEmailInfo[CTICA_MAX_BMAIL_NUM,Ϊ30]; */
	};

	public static class CoreTVCA_Email_Data_S {
		int CTICAMAXMAILTITLELENGTH = 256;
		public byte mCaucMailID; // �ʼ�ID��1������ʼ�����,���ʼ��б���ǰ����ʾ�����
		public int mCaucNewMailFlag; // �Ƿ��Ѷ���ʶ,1��ʾ�µ�δ���ʼ���0��ʾ�Ѷ��ʼ�
		public byte[] mCaacSendtime = new byte[8];
		/** ��char������ca_acSend_time[8];����ʱ�� 8bit��ʾһ����λ����BCD���룬����20 11 06 28 13 25 */
		public int mCaucTitlelen; // �ʼ����ⳤ��
		public String mCaacTitlecontext = new String();
		/** ��char������ca_acTitle_context[CTICA_MAX_MAIL_TITLE_LENGTH]���ʼ��������� */
	};

	public static class CoreTVCA_Email_Body_S {
		public short mCawBodylen; // �ʼ����ݳ���
		public String mCaacBodycontext = new String();
		/** char������ca_acBody_context[CTICA_MAX_MAIL_LENGTH]�ʼ����� */
	};

	public static class CoreTVCA_Osd_Subtitle_S {
		public CoreTVCA_Osd_Subtitle_S() {
			mMsOsdShowMode = new CoreTVCA_OSD_Display_Mode_S();
		}

		public byte mMucShowModeFlag;// OSD ������ʽ��־��Ϊ0��SDMCCA_OSD_Display_Mode_S
										// ��Ч��Ϊ1��ʾ������ʾ��ʾ��
		public byte[] mMuaBodycontext = new byte[2048];
		/** char������m_uaBody_context[2048]��OSD���������� */
		public short mMWBodylen;// OSD������Ļ�ĳ���

		public CoreTVCA_OSD_Display_Mode_S mMsOsdShowMode;
	};

	public static class GetmName {
		public String property = new String();
	}

	public static class GetnName {
		public String pParam = new String();
	}

	public static class SetmName {
		public String pRoperty = new String();
	}

	public static class SetnName {
		public String pparam = new String();
	}

	public static class CoreTVCA_OSD_Display_Mode_S {
		public byte mAvail; // δ֪

		public short mMwRectxlt; // ������Ļ��ʾ��������Ͻ������Xֵ�����ֵΪ1920����
		public short mMwRectylt; // ������Ļ��ʾ��������Ͻ������Yֵ�����ֵΪ1280����
		public short mMwRectxrt; // ������Ļ��ʾ��������½������Xֵ�����ֵΪ1920����
		public short mMwRectyrt; // ������Ļ��ʾ��������½������Yֵ�����ֵΪ1280����
		public byte mLoopnum; // ������Ļ��������ʾ������

		public short mMwLoopinterval; // ��Ļ��ͬ��ʾ����֮����ʾ�������λΪ�룩

		public byte mLoopspeed; // ��Ļ�����ٶȣ�ȡֵ��Χ1��2��3����Ӧ���١����١����٣���
		public byte mFontsize; // ��Ļ���ֺţ�ȡֵ��Χ��18-48��ȱʡֵΪ24����
		public byte mFontR; // ��Ļ��������ɫ��32λ��ʾ��RGBֵ����
		public byte mFontG;
		public byte mFontB;
		public byte mFontZ;
		public byte mBackR; // ��Ļ�ı�����ɫ��32λ��ʾ��RGBֵ����
		public byte mBackG;
		public byte mBackB;
		public byte mBackZ;
	};

	public static class CoreTVCA_MULTICASEx_CasInfo_S {
		public int eCardType;
		public CAS eCAS = new CAS();

	}

	public static class CAS {
		public CONX mConx = new CONX();
		public IRDT mIRDT = new IRDT();
		public VICS mVICS = new VICS();
		public CRYW mCRYW = new CRYW();
		public MGRD mMGRD = new MGRD();
		public NAGV mNAGV = new NAGV();
		public NDS mNDS = new NDS();
		public INVALID mINVALID = new INVALID();
	}

	public static class CONX {
		public CONX() {
			for (int i = 0; i < 16; i++) {
				mConxPro[i] = new CoreTVCA_MULTICASEx_ConxProvider_S();
			}
		}

		public int u8Version;
		public int eMaturityRating;
		public int u8ProviderNumber;
		public CoreTVCA_MULTICASEx_ConxProvider_S[] mConxPro = new CoreTVCA_MULTICASEx_ConxProvider_S[16];
	}

	public static class CoreTVCA_MULTICASEx_ConxProvider_S {
		public CoreTVCA_MULTICASEx_ConxProvider_S() {
			for (int i = 0; i < 2; i++) {
				astDate[i] = new CoreTVCA_MULTICASEx_ConxDate_S();
			}
		}

		public int u16Id;
		public String acName = new String();
		public int u8NameLen;
		public CoreTVCA_MULTICASEx_ConxDate_S astDate[] = new CoreTVCA_MULTICASEx_ConxDate_S[2];

		@Override
		public String toString() {
			String str = Integer.toHexString(u16Id) + ". " + acName + "\n"
					+ astDate[0].toString();
			return str;
		}
	}

	public static class CoreTVCA_MULTICASEx_ConxDate_S {
		public int u8StartDay;
		public int u8StartMonth;
		public int u16StartYear;
		public int u8EndDay;
		public int u8EndMonth;
		public int u16EndYear;

		@Override
		public String toString() {
			String str = "start time: " + u16StartYear + "." + u8StartMonth
					+ "." + u8StartDay + "   end time: " + u16EndYear + "."
					+ u8EndMonth + "." + u8EndDay;
			return str;
		}
	}

	public static class IRDT {
		public int u16Version;
		public int u8ProviderNumber;
		public byte[] au8Nationality = new byte[6];
		public byte[] au8CardNo = new byte[22];
	}

	public static class VICS {
		public VICS() {
			for (int i = 0; i < 16; i++) {
				astProviders[i] = new CoreTVCA_MULTICASEx_VicsProvider_S();
			}
		}

		public String au8CardNo = new String();
		public int u8ProviderNumber;
		public CoreTVCA_MULTICASEx_VicsProvider_S astProviders[] = new CoreTVCA_MULTICASEx_VicsProvider_S[16];
		public int u8AgeRating;
		public int bMatRatingLocked;
	}

	public static class CRYW {
		public String au8CardNo = new String();
		public int u8ProviderNumber;
		public CoreTVCA_MULTICASEx_CrywProvider_S mCryw = new CoreTVCA_MULTICASEx_CrywProvider_S();
	}

	public static class MGRD {
		public MGRD() {
			for (int i = 0; i < 16; i++) {
				mMgrdDate[i] = new CoreTVCA_MULTICASEx_MgrdDate_S();
			}
		}

		public String au8CardNo = new String();
		public int u8ProviderNumber;
		public CoreTVCA_MULTICASEx_MgrdDate_S[] mMgrdDate = new CoreTVCA_MULTICASEx_MgrdDate_S[16];
	}

	public static class NAGV {
		public int u32Reserved;
	}

	public static class NDS {
		public int u32Reserved;
	}

	public static class INVALID {
		public int u32Reserved;
	}

	public static class CoreTVCA_MULTICASEx_MgrdDate_S {
		public int u8EndDay;
		public int u8EndMonth;
		public int u16EndYear;
	}

	public static class CoreTVCA_MULTICASEx_CrywProvider_S {
		public int uu8Id;
		public String acName = new String();
		public int u8NameLen;
		public CoreTVCA_MULTICASEx_CrywDate_S mCrywDate = new CoreTVCA_MULTICASEx_CrywDate_S();

	}

	public static class CoreTVCA_MULTICASEx_CrywDate_S {
		public int u8StartDay;
		public int u8StartMonth;
		public int u16StartYear;
		public int u8EndDay;
		public int u8EndMonth;
		public int u16EndYear;
	}

	public static class CoreTVCA_MULTICASEx_VicsProvider_S {
		public int bAuthorized;
		public byte[] au8Id = new byte[6];
		public String acName = new String();
		public int u8NameLen;
		public CoreTVCA_MULTICASEx_VicsDate_S mVicsDate = new CoreTVCA_MULTICASEx_VicsDate_S();

		@Override
		public String toString() {
			String bytes = getKeyToString(au8Id).substring(0, 6).toUpperCase();
			String isAuthorized = bAuthorized == 1 ? "(Authorized)"
					: "(Unauthorized)";
			String str = bytes + " name: " + acName + " " + isAuthorized;
			if (bAuthorized == 1) {
				str += "\n " + mVicsDate.toString();
			}
			return str;
		}
	}

	private static String getKeyToString(byte[] keyCode) {
		StringBuffer sb = new StringBuffer();
		for (byte bt : keyCode) {
			sb.append(String.format("%02X", bt));
		}
		return sb.toString();
	}

	public static class CoreTVCA_MULTICASEx_VicsDate_S {
		public int u8Class;
		public int u8StartDay;
		public int u8StartMonth;
		public int u16StartYear;
		public int u8EndDay;
		public int u8EndMonth;
		public int u16EndYear;

		@Override
		public String toString() {
			String str = "";
			if (u8Class != 0) {
				str = "start time: " + u16StartYear + "." + u8StartMonth + "."
						+ u8StartDay + "   end time: " + u16EndYear + "."
						+ u8EndMonth + "." + u8EndDay + " :Class[" + u8Class
						+ "]";
			}
			return str;
		}
	}

	static {
		initCAIDs();
		initCAIDse();
	}

	public static native int initCAIDs();

	public static native int initCAIDse();

	/*
	 * =============================================================
	 * -------------------------------------------------------------
	 */

	public static native int coreTVCAGetCASCount(Mpcount pCount);

	public static native int coreTVCAGetCardCount(Pcount pCount);

	/*
	 * ============================================================= ��ȡCA����ϵͳ��Ϣ
	 * 
	 * ����˵�� �����Ի�õ�ǰCA����ϵͳ��Ϣ
	 * 
	 * ����˵����nIndex CA����ϵͳ������ֵ pCASInfo CA����ϵͳ��Ϣ�ṹ�壬���CORETVCASINFORMATION_S
	 * 
	 * ���ܵķ���ֵ CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAGetCASInformation(int nIndex,
			CORETVCASINFORMATION_S pCASInfo);

	/*
	 * ============================================================= ��ȡCA���Ļ�����Ϣ
	 * 
	 * ����˵�� �����Ի�õ�ǰCA���Ļ�����Ϣ
	 * 
	 * ����˵����nIndex CA����ID pCASInfo CA��������Ϣ��Ϣ�ṹ�壬���CORETVCASINFORMATION_S
	 * 
	 * ���ܵķ���ֵ CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAGetCACardInformation(int nSlotID,
			CORETVCACARDINFORMATION_S pCACardInfo);

	/*
	 * ============================================================= ��ȡCA�Ƿ����
	 * 
	 * ����˵�� �����Ի�õ�ǰCAϵͳ�Ƿ����
	 * 
	 * ����˵����
	 * 
	 * ���ܵķ���ֵ 1��ca system���� 0��ca system������
	 * -------------------------------------------------------------
	 */
	public static native int CoreTVCAIsAvalable();

	/*
	 * ============================================================= ��ȡCAϵͳ����
	 * 
	 * ����˵�� �����Ի�õ�ǰCAϵͳ����
	 * 
	 * ����˵����nPropertyID ��ȡ���Ե�ѡ�CORETV_CA_PROPERTY_ID��ֵ Property
	 * ָ��һ����Ҫ��ȡ����Ϣ��ֵ�����͵�ָ�� nSize ��Property�ṹ��Ĵ�С pParam ĳЩ������Ҫ�Ķ������ ���ܵķ���ֵ
	 * CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAGetProperty(int nPropertyID,
			CoreTVCA_MULTICASEx_CasInfo_S Property);
	public static native int getCoreTVCAType();

	 public static native int coreTVCAGetConaxProperty(int nPropertyID,
	 CORETVCACARDEXTENDINFO_CONAX_S Property);

	public static native int coreTVCAGetSHADTProperty(int nPropertyID,
			CORETVCACARDEXTENDINFO_SHADT_S Property);

	/*
	 * ============================================================= ����CAϵͳչ��Ϣ
	 * 
	 * ����˵�� �����Ի�õ�ǰCAϵͳ����
	 * 
	 * ����˵����nPropertyID ��ȡ���Ե�ѡ�CORETV_CA_PROPERTY_ID��ֵ Property
	 * ָ��һ����Ҫ��ȡ����Ϣ��ֵ�����͵�ָ�� nSize ��Property�ṹ��Ĵ�С pParam ĳЩ������Ҫ�Ķ������ ���ܵķ���ֵ
	 * CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCASetProperty(int nPropertyID,
			SetmName Property, int nSize, SetnName pParam);

	/************************************************************************/
	/* CA �ʼ��ӿڲ��ֶ��� */
	/************************************************************************/

	/*
	 * ============================================================= CA��ȡ�ʼ��б�
	 * 
	 * ����˵�� �����Ի�õ�ǰCAϵͳ�õ����ʼ��б�
	 * 
	 * ����˵����*sEmailList ָ��CoreTVCA_Email_List_S���ʹ�С��һƬ�ڴ棬 ������ȡ�б�
	 * 
	 * ���ܵķ���ֵ CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAGetEmailList(
			CoreTVCA_Email_Title_S sEmailList);

	/*
	 * =============================================================
	 * CA��ȡ�б���ĳ���ʼ�������
	 * 
	 * ����˵�� �����ʼ�ID����ȡ���ʼ�����ϸ����
	 * 
	 * ����˵����cMailID ĳ���ʼ���IDֵsEmailBody ָ��CoreTVCA_Email_Body_S�ṹ�������ָ��
	 * 
	 * ���ܵķ���ֵ CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAGetEmailContent(int cMailID,
			CoreTVCA_Email_Body_S sEmailBody);

	/*
	 * ============================================================= CAָ��ID���ʼ�
	 * 
	 * ����˵�� ɾ��ָ��ID���ʼ�
	 * 
	 * ����˵����cMailID ĳ���ʼ���IDֵ
	 * 
	 * ���ܵķ���ֵ CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCADelEmailByID(int cMailID);

	/*
	 * ============================================================= CAɾ�������ʼ�
	 * 
	 * ����˵�� ɾ�������ʼ�
	 * 
	 * ����˵����
	 * 
	 * ���ܵķ���ֵ CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCADelAllEmail();

	/************************************************************************/
	/* CA OSD�ӿڲ��ֶ��� */
	/************************************************************************/

	/*
	 * ============================================================= CA OSD��ʾ����
	 * 
	 * ����˵�� ���û�õ�ǰOSD��Ҫ��ʾ�����ݺ���ʾ����
	 * 
	 * ����˵����sOsdDisplay:ָ��CoreTVCA_Osd_Subtitle_S���ͱ�����ָ��
	 * 
	 * ���ܵķ���ֵ CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAOsdDispaly(
			CoreTVCA_Osd_Subtitle_S sOsdDisplay);

	/************************************************************************/
	/* CA �����Խӿڲ��ֶ��� */
	/************************************************************************/

	/*
	 * ============================================================= CA����
	 * 
	 * ����˵�� �����лָ�Ĭ��ʱ����Ҫ���øú���������CA��ز��� ע��ĳЩ����CA���ܲ�֧�ָù���
	 * 
	 * ����˵����
	 * 
	 * ���ܵķ���ֵ CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAResetCAModule();

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetSubscriptionTotalNum ��ȡ�����¼����
	 * 
	 * Parameters
	 * 
	 * Return Values �ɹ����ؼ�¼������ʧ�ܷ���-1
	 * ************************************************************************
	 */
	public static native int getSubscriptionTotalNum();

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetSubscriptionInfo ��ȡָ����Ź����¼������
	 * 
	 * Parameters dwRecordIndex [in] ���(��1��ʼ) pstSubRecord [out] ����Return Values
	 * SUCCESS �ɹ� FAILURE ʧ��
	 * ************************************************************************
	 */
	public static native int getSubscriptionInfo(int dwRecordIndex,
			SDMCCaSubscriptionInfo pstSubRecord);

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetPurseTotalNum ��ȡǮ������
	 * 
	 * Parameters
	 * 
	 * Return Values �ɹ�����������ʧ�ܷ���-1
	 * ************************************************************************
	 */
	public static native int getPurseTotalNum();

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetPurseInfo ��ȡָ�����Ǯ�� ״̬
	 * 
	 * Parameters dwRecordIndex [in] Ǯ�����(��1��ʼ) pstCaPurseInfo [out] ״̬����Return
	 * Values SUCCESS �ɹ� FAILURE ʧ��
	 * ************************************************************************
	 */
	public static native int getPurseInfo(int dwPurseIndex,
			CaPurseInfo pstCaPurseInfo);

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetPpvEventTotalNum ��ȡPPV EVENT ��¼����
	 * 
	 * Parameters
	 * 
	 * Return Values �ɹ����ؼ�¼������ʧ�ܷ���-1
	 * ************************************************************************
	 */
	public static native int getPpvEventTotalNum();

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetPpvEventInfo ��ȡָ�����PPV EVENT ��¼������
	 * 
	 * Parameters dwRecordIndex [in] ���(��1��ʼ) pstPpvRecord [out] ����Return Values
	 * SUCCESS �ɹ� FAILURE ʧ��
	 * ************************************************************************
	 */
	public static native int getPpvEventInfo(int dwRecordIndex,
			CaPPVEventInfo pstPpvRecord);

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_ChangeCardPin �޸Ŀ�����
	 * 
	 * Parameters pSzPinOld [in] ������ pSzPinNew [in] ������Return Values SUCCESS(0)
	 * �޸ĳɹ� 1 ��������� "Incorrect old PIN" OTHER �޸�ʧ��"Change CA PIN failed"note:
	 * example dialogue: ////////////////////////////////////////// Change PIN
	 * Please enter CA PIN **** Please enter new CA PIN **** Please confirm new
	 * CA PIN **** /////////////////////////////////////////if the user has
	 * entered two new PINs that do not match,"PIN confirmation does not match"
	 * should be displayed
	 * ***********************************************************************
	 */
	public static native int changeCardPin(String pSzPinOld, String pSzPinNew);

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetCardMaturityRating ��ȡ����ǰ�ĸ�ĸ��
	 * 
	 * Return Values ��ĸ���ȼ�
	 * ************************************************************************
	 */
	public static native int getCardMaturityRating();

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_ChangCardMaturityRating �޸Ŀ��ĸ�ĸ��
	 * 
	 * Parameters eMatRat [in] ��ĸ�� pSzPin [in] ������Return Values SUCCESS(0) �޸ĳɹ�
	 * 1 ������� OTHER �޸�ʧ��
	 * ************************************************************************
	 */
	public static native int changeCardMaturityRating(int eMatRate,
			String pSzPin);

	/*
	 * =*************************************************************************
	 * Function Name: CSCAAcceptMaturityRat ��������ȷ���տ���ĸ�����ƽ�Ŀ
	 * 
	 * Parameters pSzPin [in] ������ hService [in]��ĿhandleReturn Values SUCCESS(0)
	 * �ɹ� 1 ������� OTHER ʧ��
	 * ************************************************************************
	 */
	public static native int acceptMaturityRat(String pSzPin);

	/*
	 * =*************************************************************************
	 * Function Name: CSCACancelMaturityRat ȡ����ĸ��������ʾ�򣬲��տ���ǰ��Ŀ
	 * 
	 * Parameters hService [in]��ĿhandleReturn Values SUCCESS �ɹ� FAILURE ����
	 * ************************************************************************
	 */
	public static native int cancelMaturityRat();

	/*
	 * =*************************************************************************
	 * Function Name: CSCAAcceptStartView ��������ȷ���տ��۷�
	 * 
	 * Parameters pSzPin [in] ������ hService [in]��ĿhandleReturn Values SUCCESS(0)
	 * �ɹ� 1 ������� OTHER ʧ��
	 * ************************************************************************
	 */
	public static native int acceptStartView(String pSzPin);

	/*
	 * =*************************************************************************
	 * Function Name: CSCACancelStartView ȡ���۷ѽ�Ŀ�ۿ���ʾ�򣬲��տ���ǰ��Ŀ
	 * 
	 * Parameters hService [in]��ĿhandleReturn Values SUCCESS �ɹ� FAILURE ����
	 * ************************************************************************
	 */
	public static native int cancelStartView();

	/*
	 * =*************************************************************************
	 * Function Name: CSCAChangCardMaturityRating ��������ȷ�϶�����ǰ��Ŀ
	 * 
	 * Parameters pSzPin [in] ������ hService [in]��ĿhandleReturn Values SUCCESS(0)
	 * �ɹ� 1 ������� OTHER ʧ��
	 * ************************************************************************
	 */
	public static native int acceptOrderInfo(String pSzPin);

	/*
	 * =*************************************************************************
	 * Function Name: CSCACancelOrderInfo ȡ����Ŀ������ʾ�򣬲��տ���ǰ��Ŀ
	 * 
	 * Parameters hService [in]��Ŀhandle
	 * 
	 * Return Values SUCCESS �ɹ� FAILURE ����
	 * ************************************************************************
	 */
	public static native int cancelOrderInfo();

	/*
	 * =*************************************************************************
	 * Function Name: CSCAAcceptPPVRequest ��������ȷ�Ϲ���PPV��Ŀ
	 * 
	 * Parameters pSzPin [in] ������ hService [in]��Ŀhandle
	 * 
	 * Return Values SUCCESS(0) �ɹ� 1 ������� OTHER ʧ��
	 * ************************************************************************
	 */
	public static native int acceptPPVRequest(String pSzPin);

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_CancelPPVRequest ȡ��PPV������ʾ�򣬲��տ���ǰ��Ŀ
	 * 
	 * Parameters
	 * 
	 * Return Values SDMCCA_SUCCESS �ɹ� SDMCCA_ERROR_SystemError ����
	 * ************************************************************************
	 */
	public static native int cancelPPVRequest();

	/*
	 * ============================================================= CA�����ʼ�Ϊ�Ѷ�
	 * 
	 * ����˵�� �����ʼ�ID�����ʼ�����Ϊ�Ѷ�״̬
	 * 
	 * ����˵����cMailID ĳ���ʼ���IDֵ
	 * 
	 * ���ܵķ���ֵ CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int changeMailFlag(int mailId);
	
	public static String getCAName(int type) {
		return CoreTVCA_TYPE_MAP.get(new Integer(type));
	}
}
