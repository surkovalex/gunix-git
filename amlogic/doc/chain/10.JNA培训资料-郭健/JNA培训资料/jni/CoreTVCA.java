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
	public static final int CoreTVCA_TYPE_CDCAS = 14;//永新视博
	public static final int CoreTVCA_TYPE_DRE = 15;
	public static final int CoreTVCA_TYPE_MAX = 16;
	
	public static final int CORETVCA_IS_NOT_AVALABLE = 0;
	public static final int CORETVCA_IS_AVALABLE = 1;
	public static final int CONAXCA_MAX_LABEL_NAME_LEN = 32;

	// 父母级
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
		public String m_szLabel = new String();// 名称
		public int m_dwEventID; // 节目代号
		public SDMCCaDateTime m_stStart = new SDMCCaDateTime(); // 秒、厘秒无效。其他有效
		public SDMCCaDateTime m_stEnd = new SDMCCaDateTime(); // 秒、厘秒无效。其他有效
		public short m_MinutesOrCreditsLeft; // 剩余金额或点数
		public short m_wAuthType;
	}

	public static class CaPurseInfo {
		public short m_wPurseRef;// 钱包代号
		public int m_dwBalance;// 余额
		public String m_acLabel = new String();
	}

	public static class SDMCCaPPVRequestInfo {
		public short m_wPurseBalance; // 当前使用钱包的余额
		public char m_cInsufficientTokens; // 1: 卡内余额不足
		public char m_cTokensMode; // 0: ppv per event 1: ppv per time
		public int m_dwEventcost; // 节目价格
		public int m_dwEventTag;
		public char m_acProgramLabel[] = new char[CONAXCA_MAX_LABEL_NAME_LEN];// 节目名称，字符串
		public char m_acPurseLabel[] = new char[CONAXCA_MAX_LABEL_NAME_LEN]; // 钱包名称，字符串
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
		public short m_usCASotfVersion; // CAS软件版本号,例如返回0x(0412),则应显示为V4.1.2
		public byte[] m_aucCardSN = new byte[8]; // 8字节智能卡卡号，菜单上应该以"%02x%02x..."方式显示
		public int m_ucPariedStatus; // 机卡配对状态，1，机顶盒或者智能卡已经配对，0机顶盒和智能卡都未配对
		public int m_ucZoneCode; // 区域控制代码，例如返回值为int型9，则显示为9
		public short m_usCtrlCode; // 智能卡限播码，例如返回值为0d(0015),则显示为"0015"

		public int m_uiCardConsume; // 获取智能卡电子钱包已消费总数
		public short m_usRecentExpireDay; // 获取最近授权到期天数
		public byte[] m_aucCardEigenValue = new byte[32];// 32字节智能卡特征码，菜单上应该以"%02x%02x..."显示
		public int m_uiCardQuota; // 获取电子钱包总额，单位为“点”
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
		public SDMCCaDateTime m_stStart = new SDMCCaDateTime();// 年、月、日有效，其他无效
		public SDMCCaDateTime m_stEnd = new SDMCCaDateTime();// 年、月、日有效，其他无效
		public int m_dwEntitlement;// 标识卡的授权信息
	}

	public static class SDMCCaSubscriptionInfo {
		public SDMCCaSubscriptionInfo() {
			for (int i = 0; i < 2; i++) {
				m_astAuthPeriod[i] = new SDMCCaAuthPeriod();
			}
		}

		public String m_szLabel = new String();// 名称
		public short m_wRefID; // 节目代号
		public SDMCCaAuthPeriod m_astAuthPeriod[] = new SDMCCaAuthPeriod[2];// 授权信息
	}

	public static class CORETVCASINFORMATION_S {
		public short mCasystemid;
		public byte[] mCasystemversion = new byte[64];
		/** char型数组ca_system_version[64]; */
		public byte[] mCasystemvendor = new byte[128];
		/** char型数组ca_system_vendor[128] */
	};

	public static class CORETVCACARDINFORMATION_S {
		public byte mCacardslotid;
		public byte mCacardstatus; /* 取值参见 CORETV_CA_CARD_STATUS */

		public byte[] mCacardid = new byte[8];
		/** char型数组 ca_card_id[8]; */
		public byte[] mCacardversion = new byte[64];
		/** char型数组ca_card_version[64]; */
	}

	public static class CoreTVCA_Email_Title_S {
		int CTICAMAXBMAILNUM = 30;

		public CoreTVCA_Email_Title_S() {
			int i;
			for (i = 0; i < CTICAMAXBMAILNUM; i++) {
				mSEmailInfo[i] = new CoreTVCA_Email_Data_S();
			}
		}

		public byte mCaucTotleMailNum; // 当前邮件箱中邮件总数
		public byte mCaucNotReadNum; // 当前邮件箱中未读邮件数量
		public CoreTVCA_Email_Data_S[] mSEmailInfo = new CoreTVCA_Email_Data_S[CTICAMAXBMAILNUM];
		/** 机构体中结构体定义为sEmailInfo[CTICA_MAX_BMAIL_NUM,为30]; */
	};

	public static class CoreTVCA_Email_Data_S {
		int CTICAMAXMAILTITLELENGTH = 256;
		public byte mCaucMailID; // 邮件ID从1到最大邮件数量,在邮件列表最前面显示的序号
		public int mCaucNewMailFlag; // 是否已读标识,1表示新的未读邮件，0表示已读邮件
		public byte[] mCaacSendtime = new byte[8];
		/** （char型数组ca_acSend_time[8];发送时间 8bit表示一个两位数的BCD编码，例：20 11 06 28 13 25 */
		public int mCaucTitlelen; // 邮件标题长度
		public String mCaacTitlecontext = new String();
		/** （char型数组ca_acTitle_context[CTICA_MAX_MAIL_TITLE_LENGTH]）邮件标题内容 */
	};

	public static class CoreTVCA_Email_Body_S {
		public short mCawBodylen; // 邮件内容长度
		public String mCaacBodycontext = new String();
		/** char型数组ca_acBody_context[CTICA_MAX_MAIL_LENGTH]邮件内容 */
	};

	public static class CoreTVCA_Osd_Subtitle_S {
		public CoreTVCA_Osd_Subtitle_S() {
			mMsOsdShowMode = new CoreTVCA_OSD_Display_Mode_S();
		}

		public byte mMucShowModeFlag;// OSD 滚动方式标志，为0：SDMCCA_OSD_Display_Mode_S
										// 无效，为1表示按照提示显示。
		public byte[] mMuaBodycontext = new byte[2048];
		/** char型数组m_uaBody_context[2048]；OSD滚动的内容 */
		public short mMWBodylen;// OSD滚动字幕的长度

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
		public byte mAvail; // 未知

		public short mMwRectxlt; // 滚动字幕显示区域的左上角坐标的X值（最大值为1920）。
		public short mMwRectylt; // 滚动字幕显示区域的左上角坐标的Y值（最低值为1280）。
		public short mMwRectxrt; // 滚动字幕显示区域的右下角坐标的X值（最大值为1920）。
		public short mMwRectyrt; // 滚动字幕显示区域的右下角坐标的Y值（最大值为1280）。
		public byte mLoopnum; // 滚动字幕的完整显示次数。

		public short mMwLoopinterval; // 字幕不同显示次数之间显示间隔（单位为秒）

		public byte mLoopspeed; // 字幕滚动速度，取值范围1、2、3，对应慢速、中速、快速）。
		public byte mFontsize; // 字幕的字号，取值范围（18-48，缺省值为24）。
		public byte mFontR; // 字幕的文字颜色（32位表示的RGB值）。
		public byte mFontG;
		public byte mFontB;
		public byte mFontZ;
		public byte mBackR; // 字幕的背景颜色（32位表示的RGB值）。
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
	 * ============================================================= 获取CA解扰系统信息
	 * 
	 * 函数说明 调用以获得当前CA解扰系统信息
	 * 
	 * 参数说明：nIndex CA解扰系统的索引值 pCASInfo CA解扰系统信息结构体，详见CORETVCASINFORMATION_S
	 * 
	 * 可能的返回值 CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAGetCASInformation(int nIndex,
			CORETVCASINFORMATION_S pCASInfo);

	/*
	 * ============================================================= 获取CA卡的基本信息
	 * 
	 * 函数说明 调用以获得当前CA卡的基本信息
	 * 
	 * 参数说明：nIndex CA卡的ID pCASInfo CA卡基本信息信息结构体，详见CORETVCASINFORMATION_S
	 * 
	 * 可能的返回值 CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAGetCACardInformation(int nSlotID,
			CORETVCACARDINFORMATION_S pCACardInfo);

	/*
	 * ============================================================= 获取CA是否可用
	 * 
	 * 函数说明 调用以获得当前CA系统是否可用
	 * 
	 * 参数说明：
	 * 
	 * 可能的返回值 1：ca system可用 0：ca system不可用
	 * -------------------------------------------------------------
	 */
	public static native int CoreTVCAIsAvalable();

	/*
	 * ============================================================= 获取CA系统属性
	 * 
	 * 函数说明 调用以获得当前CA系统属性
	 * 
	 * 参数说明：nPropertyID 获取属性的选项，CORETV_CA_PROPERTY_ID的值 Property
	 * 指向一个所要获取的信息的值的类型的指针 nSize 是Property结构体的大小 pParam 某些属性需要的额外参数 可能的返回值
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
	 * ============================================================= 设置CA系统展信息
	 * 
	 * 函数说明 调用以获得当前CA系统属性
	 * 
	 * 参数说明：nPropertyID 获取属性的选项，CORETV_CA_PROPERTY_ID的值 Property
	 * 指向一个所要获取的信息的值的类型的指针 nSize 是Property结构体的大小 pParam 某些属性需要的额外参数 可能的返回值
	 * CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCASetProperty(int nPropertyID,
			SetmName Property, int nSize, SetnName pParam);

	/************************************************************************/
	/* CA 邮件接口部分定义 */
	/************************************************************************/

	/*
	 * ============================================================= CA获取邮件列表
	 * 
	 * 函数说明 调用以获得当前CA系统得到的邮件列表
	 * 
	 * 参数说明：*sEmailList 指向CoreTVCA_Email_List_S类型大小的一片内存， 用来获取列表
	 * 
	 * 可能的返回值 CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAGetEmailList(
			CoreTVCA_Email_Title_S sEmailList);

	/*
	 * =============================================================
	 * CA获取列表中某条邮件的内容
	 * 
	 * 函数说明 传入邮件ID，获取该邮件的详细内容
	 * 
	 * 参数说明；cMailID 某条邮件的ID值sEmailBody 指向CoreTVCA_Email_Body_S结构体变量的指针
	 * 
	 * 可能的返回值 CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAGetEmailContent(int cMailID,
			CoreTVCA_Email_Body_S sEmailBody);

	/*
	 * ============================================================= CA指定ID的邮件
	 * 
	 * 函数说明 删除指定ID的邮件
	 * 
	 * 参数说明；cMailID 某条邮件的ID值
	 * 
	 * 可能的返回值 CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCADelEmailByID(int cMailID);

	/*
	 * ============================================================= CA删除所有邮件
	 * 
	 * 函数说明 删除所有邮件
	 * 
	 * 参数说明；
	 * 
	 * 可能的返回值 CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCADelAllEmail();

	/************************************************************************/
	/* CA OSD接口部分定义 */
	/************************************************************************/

	/*
	 * ============================================================= CA OSD显示函数
	 * 
	 * 函数说明 调用获得当前OSD需要显示的内容和显示属性
	 * 
	 * 参数说明；sOsdDisplay:指向CoreTVCA_Osd_Subtitle_S类型变量的指针
	 * 
	 * 可能的返回值 CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAOsdDispaly(
			CoreTVCA_Osd_Subtitle_S sOsdDisplay);

	/************************************************************************/
	/* CA 功能性接口部分定义 */
	/************************************************************************/

	/*
	 * ============================================================= CA重置
	 * 
	 * 函数说明 机顶盒恢复默认时候需要调用该函数，重置CA相关参数 注：某些厂家CA可能不支持该功能
	 * 
	 * 参数说明；
	 * 
	 * 可能的返回值 CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int coreTVCAResetCAModule();

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetSubscriptionTotalNum 获取购买记录总数
	 * 
	 * Parameters
	 * 
	 * Return Values 成功返回记录总数，失败返回-1
	 * ************************************************************************
	 */
	public static native int getSubscriptionTotalNum();

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetSubscriptionInfo 获取指定序号购买记录的内容
	 * 
	 * Parameters dwRecordIndex [in] 序号(从1开始) pstSubRecord [out] 内容Return Values
	 * SUCCESS 成功 FAILURE 失败
	 * ************************************************************************
	 */
	public static native int getSubscriptionInfo(int dwRecordIndex,
			SDMCCaSubscriptionInfo pstSubRecord);

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetPurseTotalNum 获取钱包总数
	 * 
	 * Parameters
	 * 
	 * Return Values 成功返回总数，失败返回-1
	 * ************************************************************************
	 */
	public static native int getPurseTotalNum();

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetPurseInfo 获取指定序号钱包 状态
	 * 
	 * Parameters dwRecordIndex [in] 钱包序号(从1开始) pstCaPurseInfo [out] 状态内容Return
	 * Values SUCCESS 成功 FAILURE 失败
	 * ************************************************************************
	 */
	public static native int getPurseInfo(int dwPurseIndex,
			CaPurseInfo pstCaPurseInfo);

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetPpvEventTotalNum 获取PPV EVENT 记录总数
	 * 
	 * Parameters
	 * 
	 * Return Values 成功返回记录总数，失败返回-1
	 * ************************************************************************
	 */
	public static native int getPpvEventTotalNum();

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_GetPpvEventInfo 获取指定序号PPV EVENT 记录的内容
	 * 
	 * Parameters dwRecordIndex [in] 序号(从1开始) pstPpvRecord [out] 内容Return Values
	 * SUCCESS 成功 FAILURE 失败
	 * ************************************************************************
	 */
	public static native int getPpvEventInfo(int dwRecordIndex,
			CaPPVEventInfo pstPpvRecord);

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_ChangeCardPin 修改卡密码
	 * 
	 * Parameters pSzPinOld [in] 旧密码 pSzPinNew [in] 新密码Return Values SUCCESS(0)
	 * 修改成功 1 旧密码错误 "Incorrect old PIN" OTHER 修改失败"Change CA PIN failed"note:
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
	 * Function Name: SDMCCA_GetCardMaturityRating 获取卡当前的父母级
	 * 
	 * Return Values 父母锁等级
	 * ************************************************************************
	 */
	public static native int getCardMaturityRating();

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_ChangCardMaturityRating 修改卡的父母级
	 * 
	 * Parameters eMatRat [in] 父母级 pSzPin [in] 卡密码Return Values SUCCESS(0) 修改成功
	 * 1 密码错误 OTHER 修改失败
	 * ************************************************************************
	 */
	public static native int changeCardMaturityRating(int eMatRate,
			String pSzPin);

	/*
	 * =*************************************************************************
	 * Function Name: CSCAAcceptMaturityRat 输入密码确认收看父母级限制节目
	 * 
	 * Parameters pSzPin [in] 卡密码 hService [in]节目handleReturn Values SUCCESS(0)
	 * 成功 1 密码错误 OTHER 失败
	 * ************************************************************************
	 */
	public static native int acceptMaturityRat(String pSzPin);

	/*
	 * =*************************************************************************
	 * Function Name: CSCACancelMaturityRat 取消父母级限制提示框，不收看当前节目
	 * 
	 * Parameters hService [in]节目handleReturn Values SUCCESS 成功 FAILURE 错误
	 * ************************************************************************
	 */
	public static native int cancelMaturityRat();

	/*
	 * =*************************************************************************
	 * Function Name: CSCAAcceptStartView 输入密码确认收看扣费
	 * 
	 * Parameters pSzPin [in] 卡密码 hService [in]节目handleReturn Values SUCCESS(0)
	 * 成功 1 密码错误 OTHER 失败
	 * ************************************************************************
	 */
	public static native int acceptStartView(String pSzPin);

	/*
	 * =*************************************************************************
	 * Function Name: CSCACancelStartView 取消扣费节目观看提示框，不收看当前节目
	 * 
	 * Parameters hService [in]节目handleReturn Values SUCCESS 成功 FAILURE 错误
	 * ************************************************************************
	 */
	public static native int cancelStartView();

	/*
	 * =*************************************************************************
	 * Function Name: CSCAChangCardMaturityRating 输入密码确认订购当前节目
	 * 
	 * Parameters pSzPin [in] 卡密码 hService [in]节目handleReturn Values SUCCESS(0)
	 * 成功 1 密码错误 OTHER 失败
	 * ************************************************************************
	 */
	public static native int acceptOrderInfo(String pSzPin);

	/*
	 * =*************************************************************************
	 * Function Name: CSCACancelOrderInfo 取消节目订购提示框，不收看当前节目
	 * 
	 * Parameters hService [in]节目handle
	 * 
	 * Return Values SUCCESS 成功 FAILURE 错误
	 * ************************************************************************
	 */
	public static native int cancelOrderInfo();

	/*
	 * =*************************************************************************
	 * Function Name: CSCAAcceptPPVRequest 输入密码确认购买PPV节目
	 * 
	 * Parameters pSzPin [in] 卡密码 hService [in]节目handle
	 * 
	 * Return Values SUCCESS(0) 成功 1 密码错误 OTHER 失败
	 * ************************************************************************
	 */
	public static native int acceptPPVRequest(String pSzPin);

	/*
	 * =*************************************************************************
	 * Function Name: SDMCCA_CancelPPVRequest 取消PPV购买提示框，不收看当前节目
	 * 
	 * Parameters
	 * 
	 * Return Values SDMCCA_SUCCESS 成功 SDMCCA_ERROR_SystemError 错误
	 * ************************************************************************
	 */
	public static native int cancelPPVRequest();

	/*
	 * ============================================================= CA设置邮件为已读
	 * 
	 * 函数说明 传入邮件ID，将邮件设置为已读状态
	 * 
	 * 参数说明；cMailID 某条邮件的ID值
	 * 
	 * 可能的返回值 CORETV_SUCCESS CORETV_FAILURE
	 * -------------------------------------------------------------
	 */
	public static native int changeMailFlag(int mailId);
	
	public static String getCAName(int type) {
		return CoreTVCA_TYPE_MAP.get(new Integer(type));
	}
}
