package com.sdmc.lteupgrade;


import java.io.UnsupportedEncodingException;

import android.app.AlertDialog;
import android.app.Service;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.graphics.Color;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.RemoteException;
import android.os.SystemClock;
import android.os.SystemProperties;
import android.util.Log;
import android.view.ViewGroup.LayoutParams;
import android.view.WindowManager;
import android.widget.TextView;
import android.widget.Toast;

import com.sdmc.coress.SystemShell;
import com.sdmc.coress.SystemShell.ExecResultListener;
import com.sdmc.dtv.programsend.IUpdate4GListener;
import com.sdmc.dtv.programsend.IUpdateBinder;
import com.sdmc.lteupgrade.util.ParseJSON;
import com.sdmc.lteupgrade.util.ShellCommand;
import com.sdmc.lteupgrade.util.UpgradeInfo;

public class LTEService extends Service {
	private static final String TAG = "LTEService";
	private static final String BIND_INTENT = "com.sdmc.service.IUpdate";
	private static final String ID = "LTE";
	private static final int REGIST_4GLISTENER = 0;
	private static final int RECEIVE_JSON_SUCCESS = 1;
	private static final int RECYCLE_QUERY = 2;
	private static final int RECYCLE_READ_PROPERTY = 3;
	private static final int DOWNLOAD_CHECK_SUCCESS = 4;
	private static final int REBOOT_SYSTEM = 5;
	private static final int ALERTDIALOG_DISMISS = 6;
	private static final int DOWNLOAD_INTERRUPT = 7;
	private static final int UPGRADE_SUCCESS = 8;
	private static final int UNZIP_PACKAGE = 9;
	
	private static IUpdateBinder mIBinderUpgrade;
	private UpgradeInfo mUpgradeInfo;
	private ParseJSON mParseJSON;
	private ShellCommand mShellCommand;
	private SharedPreferences mSharedPreferences;
	private Editor editor;

	private ServiceConnection cnnBinderUpgrade = new ServiceConnection() {
		@Override
		public void onServiceConnected(ComponentName name, IBinder binder) {
			// Access to remote Service's onBind() method , returns the object
			// of the agent
			mIBinderUpgrade = IUpdateBinder.Stub.asInterface(binder);
			Log.v(TAG, " mIBinderUpgrade= " + mIBinderUpgrade);
			initService();
		}
		@Override
		public void onServiceDisconnected(ComponentName arg0) {
			// set the object of remote null
			Log.v(TAG, "bind failed");
			mIBinderUpgrade = null;
		}
	};
	private IUpdate4GListener mIUpdate4GListener = new IUpdate4GListener.Stub() {
		@Override
		public void onDownloadProgress(int percent, boolean iscomplete)
				throws RemoteException {
			Log.v(TAG, "onDownloadProgress oncreate");
			if (percent >= -1 && percent <= 100) {
				mUpgradeInfo.setPercent(percent);
			}
			mUpgradeInfo.setComplete(iscomplete);
			if (percent == -1) {
				//download failed
				mIUpdate4GListenerHandler.sendEmptyMessageDelayed(DOWNLOAD_INTERRUPT ,10000 );
			}
		}
		@Override
		public void onCkeckFile(boolean result) throws RemoteException {
			Log.v(TAG, "onCkeckFile oncreate");
			Log.v(TAG, "onCkeckFile result "+result);
			mUpgradeInfo.setCheckFile(result);
			Message message = Message.obtain();
			message.what = DOWNLOAD_CHECK_SUCCESS;
			mIUpdate4GListenerHandler.sendMessage(message);
		}
		@Override
		public void onCheckUpgrade() throws RemoteException {
			Log.v(TAG, "Web client sends message");
			mIUpdate4GListenerHandler.removeMessages(RECYCLE_QUERY);
			mIBinderUpgrade.query4GUpgrade(ID, mShellCommand.getFacturerID(),
					mShellCommand.getVersion());
		}
		@Override
		public void onQueryResponse(String data) throws RemoteException {
			Log.v(TAG, "onQueryResponse data :"+data);
			if (data == null || data.equals("{}") || data.equals("")) {
				Log.v(TAG, "onQueryResponse to RECYCLE_QUERY");
				mIUpdate4GListenerHandler.sendEmptyMessageDelayed(
						RECYCLE_QUERY, 7200000 );
			} else {
				Message message = Message.obtain();
				message.obj = data;
				message.what = RECEIVE_JSON_SUCCESS;
				mIUpdate4GListenerHandler.sendMessage(message);
			}
		}
	};
	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}
	private Handler mIUpdate4GListenerHandler = new Handler() {
		public void handleMessage(Message msg) {
			Log.v(TAG, "what:" + msg.what);
			switch (msg.what) {
			case REGIST_4GLISTENER:
				try {
					Log.v(TAG, "mIUpdate4GListener"+mIUpdate4GListener);
					if (!mIBinderUpgrade.register4GListener(ID,
							mIUpdate4GListener)) {
						mIUpdate4GListenerHandler.sendEmptyMessageDelayed(
								REGIST_4GLISTENER, 2000);
					} else {
						checkUpdrade();
					}
				} catch (RemoteException e) {
					e.printStackTrace();
				}
				break;
			case RECEIVE_JSON_SUCCESS:
				String data = (String) msg.obj;
				Log.v(TAG, "handler send data:"+data);
				if (data != null && !data.equals("") && !data.equals("{}")) {
					mUpgradeInfo.setData(data);
					mParseJSON.parseJsonType(data);
				} 
				try{
					Log.v(TAG,"RECEIVE_JSON_SUCCESS download4G");
					mIBinderUpgrade.download4G(ID, mParseJSON.getUrl(), mShellCommand.getLocalPath(),
							mParseJSON.getMd5());
				} catch (RemoteException e) {
					e.printStackTrace();
				}
				break;
			case RECYCLE_QUERY:
				Log.v(TAG, "RECYCLE_QUERY");
					try {
						mIBinderUpgrade.query4GUpgrade(ID, mShellCommand.getFacturerID(),
								mShellCommand.getVersion());
						Log.v(TAG, ""+mShellCommand.getFacturerID()+" "+mShellCommand.getVersion());
					} catch (RemoteException e) {
						e.printStackTrace();
					}
				break;
			case RECYCLE_READ_PROPERTY:
				Log.v(TAG, "RECYCLE_READ_PROPERTY");
				String originalModuleInfo = SystemProperties.get("gsm.version.baseband", "");
				if (originalModuleInfo == null ||originalModuleInfo.equals("")) {
					mIUpdate4GListenerHandler.sendEmptyMessageDelayed(RECYCLE_READ_PROPERTY, 2000);
				} else {
					Log.v(TAG, "originalModuleInfo"+originalModuleInfo);
					mShellCommand = new ShellCommand(LTEService.this ,originalModuleInfo.trim());
					Log.v(TAG, "****************ShellCommand*************************");
					mIUpdate4GListenerHandler.sendEmptyMessageDelayed(REGIST_4GLISTENER,1000);
				}
				break;
			case DOWNLOAD_CHECK_SUCCESS:
				if (mUpgradeInfo.isCheckFile()) {
					if (mParseJSON.isEnforce()) {
						unzipUpgradePackage();
						//upgradeAndClearReboot();
					} else {
						editor.putString("UpgradeID", mParseJSON.getUpgradeId());
						editor.putString("CurrentVersion", mParseJSON.getVersionInServer());
						editor.putBoolean("isSetTask", true);
						editor.commit();
					}
				} else {
					Log.v(TAG,"EMSService check file error! clear package ");
					mShellCommand.clearPackage();
				}
				break;
			case REBOOT_SYSTEM:
				mShellCommand.rebootSystem();
				break;
			case ALERTDIALOG_DISMISS:
				mLTEDialog.dismiss();
				Toast.makeText(LTEService.this, getResources().getString(R.string.prompt_update_fail), 
						Toast.LENGTH_SHORT).show();
				break;
			case DOWNLOAD_INTERRUPT:
				try {
					mIBinderUpgrade.query4GUpgrade(ID, mShellCommand.getFacturerID(),mShellCommand.getVersion());
				} catch (RemoteException e) {
					e.printStackTrace();
				}
				break;
			case UPGRADE_SUCCESS :
				showLTEDialog(R.string.prompt_update_success);
				break;
			case UNZIP_PACKAGE :
				mShellCommand.chmodUpgradePackage();
				upgradeAndClearReboot();
				break;
			default:
				break;
			}
		};
	};

	@Override
	public void onCreate() {
		super.onCreate();
		Log.v(TAG, "LTEUpgrade oncreate !!!");
		Intent intent = new Intent();
		intent.setAction(BIND_INTENT);
		bindService(intent, cnnBinderUpgrade, Service.BIND_AUTO_CREATE);
		Log.v(TAG,"Bind service:"+ bindService(intent, cnnBinderUpgrade,Service.BIND_AUTO_CREATE));
		while (!bindService(intent, cnnBinderUpgrade, Service.BIND_AUTO_CREATE)) {
			SystemClock.sleep(100);
		}
	}
	private void initService() {
		mUpgradeInfo = new UpgradeInfo();
		mParseJSON = new ParseJSON();
		mSharedPreferences = this.getSharedPreferences("LTEUpgrade",MODE_PRIVATE);
		editor = mSharedPreferences.edit();
		mIUpdate4GListenerHandler.sendEmptyMessage(RECYCLE_READ_PROPERTY);
	}
	private void checkUpdrade() {
		if (mSharedPreferences.getBoolean("isSetTask", false)) {
			Log.v(TAG,"Check local task:"+ mSharedPreferences.getBoolean("isSetTask", false));
			unzipUpgradePackage();
			//upgradeAndClearReboot();
		} else {
			Log.v(TAG,"Check local task:"+ mSharedPreferences.getBoolean("isSetTask", false));
			if (mShellCommand.checkVersion()) {
				// 检查模组版本成功
				Log.v(TAG,"Check Module Result :" + mShellCommand.checkVersion());
				try {
					mIBinderUpgrade.query4GUpgrade(ID, mShellCommand.getFacturerID(),mShellCommand.getVersion());
				} catch (RemoteException e) {
					Log.v(TAG, "******query failed !");
					e.printStackTrace();
				}
			} else {
				Log.v(TAG,"Check Module Result :" + mShellCommand.checkVersion());
				// 检测模组版本失败,传回厂商ID为：MeiG_SLM750,版本号为:0.0.0
				try {
					mIBinderUpgrade.query4GUpgrade(ID, "MeiG_SLM750", "0.0.0");
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
		}
	}
	// compare version of module ,return isUpgrade or not
	private boolean compareVersion(String oldversion, String currentVersion) {
		boolean mCompareVersionSuccess = true;
		if (oldversion != null && !oldversion.equals("") && currentVersion != null && !currentVersion.equals("")) {
			String spiltOld[] = oldversion.split("\\.");
			String spiltCurrent[] = currentVersion.split("\\.");
			// 版本从低往高升级
			if (Integer.parseInt(spiltOld[0]) >= Integer.parseInt(spiltCurrent[0])) {
				if (Integer.parseInt(spiltOld[1]) >= Integer
						.parseInt(spiltCurrent[1])) {
					if (Integer.parseInt(spiltOld[2]) >= Integer
							.parseInt(spiltCurrent[2])) {
						mCompareVersionSuccess = false;
					}
				}
			}
		} else {
			Log.v(TAG,"CompareVersion Fail  ");
			mCompareVersionSuccess =false;
		}
		return mCompareVersionSuccess;
	}
	
	private void upgradeAndClearReboot() {
		Log.v(TAG, "upgradeAndClearReboot  has started");
		showLTEDialog(R.string.prompt_upgrade);
		mShellCommand.Upgrade();
		Log.v(TAG, "mShellCommand.Upgrade(); waiting......");
		new Thread () {
			public void run() {
				SystemShell systemShell = new SystemShell(new ExecResultListener() {
					public void onExecResult(int type, byte[] bytes) {
						Log.v(TAG,"pushApUpgradeFile onExecResult");
						handleCommandResult(type ,bytes);
					}
				});
				String upgradeCommand ="cd "+mShellCommand.getOtaPath()+"&& sh "+"meig*.bin";
				systemShell.exec(upgradeCommand);
				Log.v(TAG, "mShellCommand  command: " + upgradeCommand);
			};
		}.start();
	}

	private void unzipUpgradePackage(){
		
		Log.v(TAG, "unzipUpgradePackage  has started");
		new Thread () {
			public void run() {
				SystemShell systemShell = new SystemShell(new ExecResultListener() {
					public void onExecResult(int type, byte[] bytes) {
						Log.v(TAG,"unzipUpgradePackage onExecResult");
						
						mIUpdate4GListenerHandler.sendEmptyMessageDelayed(UNZIP_PACKAGE , 8000);
					}
				});
				String unzipUpgradePkgCmd = "cd "+mShellCommand.getOtaPath()+"&& unzip  "+mShellCommand.getLocalPath();
				Log.i(TAG, "unzipUpgradePkgCmd="+unzipUpgradePkgCmd);
				systemShell.exec(unzipUpgradePkgCmd);	
				//mShellCommand.chmodUpgradePackage();
			};
		}.start();
	}
	
	private void handleCommandResult(int type, byte[] bytes) {
		String str = "";
		try {
			str = new String(bytes, "GB2312");
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}	
		Log.i(TAG,"handltransinfo:resultString = "+str);
		if (str.contains("sucess")) {
			//upgrade success
			mIUpdate4GListenerHandler.sendEmptyMessage(UPGRADE_SUCCESS);
			if (mSharedPreferences.getBoolean("isSetTask", false)) {
				try {
					Log.v(TAG, "Upgrade4GResultReport "+"success");
					mIBinderUpgrade.upgrade4GResultReport(
							mSharedPreferences.getString("UpgradeID", ""), ID,
							mShellCommand.getVersion(), mSharedPreferences.getString("CurrentVersion", ""),
							"success");
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			} else {
				try {
					Log.v(TAG, "Upgrade4GResultReport "+"success");
					mIBinderUpgrade.upgrade4GResultReport(
							mParseJSON.getUpgradeId(), ID,
							mShellCommand.getVersion(), mParseJSON.getVersionInServer(),
							"success");
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
			editor.putBoolean("isSetTask", false);
			editor.commit();
			Log.v(TAG, "clearPackage start");
			mShellCommand.clearPackage();
			Log.v(TAG, "rebootSystem start");
			mIUpdate4GListenerHandler.sendEmptyMessageDelayed(REBOOT_SYSTEM ,2000);
		} else if (str.contains("fail")) {
			if (mSharedPreferences.getBoolean("isSetTask", false)) {
				try {
					Log.v(TAG, "Upgrade4GResultReport "+"fail");
					mIBinderUpgrade.upgrade4GResultReport(
							mSharedPreferences.getString("UpgradeID", ""), ID,
							mShellCommand.getVersion(), mSharedPreferences.getString("CurrentVersion", ""),
							"fail");
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			} else {
				try {
					Log.v(TAG, "Upgrade4GResultReport "+"fail");
					mIBinderUpgrade.upgrade4GResultReport(
							mParseJSON.getUpgradeId(), ID,
							mShellCommand.getVersion(), mParseJSON.getVersionInServer(),
							"fail");
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
			editor.putBoolean("isSetTask", false);
			editor.commit();
			Log.v(TAG, "clearPackage start");
			mShellCommand.clearPackage();
			mIUpdate4GListenerHandler.sendEmptyMessageDelayed(ALERTDIALOG_DISMISS, 2000);
		}
	}			
	private AlertDialog mLTEDialog;
    private void showLTEDialog(int prompt) {
    	if(mLTEDialog == null){
    		mLTEDialog = new AlertDialog.Builder(LTEService.this , R.style.AlertDialogCustom).create();
    		mLTEDialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
    		
    	}
    	mLTEDialog.setCancelable(false);
		mLTEDialog.show();
		WindowManager.LayoutParams layoutParams = mLTEDialog.getWindow().getAttributes();  
        layoutParams.width = 1200;  
        layoutParams.height = 350;
        mLTEDialog.getWindow().setAttributes(layoutParams);
        TextView contentView = new TextView(getApplicationContext());
		contentView.setText(prompt);
		contentView.setTextSize(35);
		contentView.setTextColor(Color.BLACK);
		contentView.setLayoutParams(layoutParams);
		mLTEDialog.setContentView(contentView);
	}
	
}
