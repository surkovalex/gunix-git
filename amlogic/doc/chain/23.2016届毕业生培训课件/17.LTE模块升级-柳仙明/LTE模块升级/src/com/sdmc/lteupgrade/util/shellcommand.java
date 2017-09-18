package com.sdmc.lteupgrade.util;

import android.content.Context;
import android.os.Handler;
import android.os.SystemProperties;
import android.util.Log;
import android.widget.TextView;

import com.sdmc.coress.SystemShell;
import com.sdmc.coress.SystemUpgrade;
import com.sdmc.coress.SystemShell.ExecResultListener;

public class ShellCommand {
		private static final String TAG = "ShellCommand";
		private static final String COMMAND = "busybox echo 0 > /proc/sys/kernel/printk";
		private SystemUpgrade mSystemUpgrade;
		private SystemShell mSystemShell;
		private boolean mCheckUpdateSuccess;
		private boolean mCheckFactoryIDSuccess;
		private boolean mCheckVersionSuccess;
		private String mOtaPath;
		private String mOriginalModuleInfo;
		private String mLocalPath;
		private String mVersion;
		private String mFacturerID;
		
		public ShellCommand(Context context, String originalModuleInfo) {
			mSystemUpgrade = new SystemUpgrade(context);
			mOriginalModuleInfo =originalModuleInfo;
			Log.v(TAG, "Local module mVersion "+mOriginalModuleInfo);
			getVersion();
			getFacturerID();
			mOtaPath = mSystemUpgrade.getOTAdir()+"/";
			Log.v(TAG, "mOtaPath "+mOtaPath);
			mLocalPath = mOtaPath + mOriginalModuleInfo+".zip";
			mSystemShell = new SystemShell(new ExecResultListener() {
				@Override
				public void onExecResult(int arg0, byte[] info) {
					Log.v(TAG, "onExecResult() has started");
					Log.v(TAG, "byte of  info"+info);
				}
			});
		}
		public void Upgrade() {
			String mStepFirst = "ls /dev/ttyUSB*";
			String mStepTwo = "chmod 777 "+mLocalPath;
			mSystemShell.exec(COMMAND);
			mSystemShell.exec(mStepFirst);
			mSystemShell.exec(mStepTwo);
		}
		
		
		//byte to string
		private  String bytesToString(byte[] bt) {
		       StringBuffer strBuff = new StringBuffer();
		       int length = bt.length;
		       char[] chars = new char[length];
		       for (int i = 0; i < length; i++ ) {
		           chars[i] = (char) (0xFF & bt[i]);
		       }
		       strBuff.append(chars);
		       return strBuff.toString();
		}
		public  boolean checkVersion() {
			return mCheckVersionSuccess;
		}
		public boolean checkFactoryID() {
			return mCheckFactoryIDSuccess;
		}
		public boolean upgradeSuccess() {
			return mCheckUpdateSuccess;
		}
		public void clearPackage() {
			String clearCommand = "rm -rf "+getLocalPath();
			mSystemShell.exec(clearCommand);
		}
		public void rebootSystem() {
			mSystemShell.reboot();
		}
		public void chmodUpgradePackage() {
			String chmodUpgradepackage = "chmod 777 "+getOtaPath()+"meig*";
			Log.v(TAG, "chmodUpgradepackage"+chmodUpgradepackage);
			mSystemShell.exec(chmodUpgradepackage);	
		}
		public String getLocalPath() {
			return mLocalPath;
		}
		
		public String getOtaPath() {
			return mOtaPath;
		}
		
		public String getVersion() {
			if (mOriginalModuleInfo != null && !mOriginalModuleInfo.equals("")) {
				String split[] = mOriginalModuleInfo.split("_");
				mVersion = split[2];
				mCheckVersionSuccess = true;
			} else {
				mCheckVersionSuccess = false;
			}
			Log.v(TAG, "Version of module "+mVersion+" check version:"+mCheckVersionSuccess );
			return mVersion;
		}
		
//		public String getVersion() {
//			if (mOriginalModuleInfo != null && !mOriginalModuleInfo.equals("")) {
//				String split[] = mOriginalModuleInfo.split("_");
//				mVersion = split[1];
//				mCheckVersionSuccess = true;
//			} else {
//				mCheckVersionSuccess = false;
//			}
//			Log.v(TAG, "Version of module "+mVersion+" check version:"+mCheckVersionSuccess );
//			return mVersion;
//		}
		
		public String getFacturerID() {
			if (mOriginalModuleInfo != null && !mOriginalModuleInfo.equals("")) {
				String split[] = mOriginalModuleInfo.split("_");
				mFacturerID = split[0] + "_" + split[1];
				mCheckFactoryIDSuccess = true;
			} else {
				mCheckFactoryIDSuccess = false;
			}
			Log.v(TAG, "Factorer of module "+mVersion+" check version:"+mCheckVersionSuccess );
			return mFacturerID;
		}
//		public String getFacturerID() {
//			if (mOriginalModuleInfo != null && !mOriginalModuleInfo.equals("")) {
//				String split[] = mOriginalModuleInfo.split("_");
//				mFacturerID = split[0] ;
//				mCheckFactoryIDSuccess = true;
//			} else {
//				mCheckFactoryIDSuccess = false;
//			}
//			Log.v(TAG, "Factorer of module "+mVersion+" check version:"+mCheckVersionSuccess );
//			return mFacturerID;
//		}
}
