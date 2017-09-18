package com.sdmc.lteupgrade.util;

import org.json.JSONException;
import org.json.JSONObject;

public class ParseJSON {
	private String mUpgradeID;
	private String mVersionInServer;
	private boolean mIsEnforce;
	private String mUrl;
	private String md5;
	public  void parseJsonType(String strResult) {
		try {
			JSONObject jsonObj = new JSONObject(strResult);
			mUpgradeID = jsonObj.getString("id");
			mVersionInServer = jsonObj.getString("version");
			mIsEnforce = jsonObj.getBoolean("isenforce");
			mUrl = jsonObj.getString("url");
			md5 = jsonObj.getString("md5");
			 
		} catch (JSONException e) {
			System.out.println("Json parse error");
			e.printStackTrace();
		}
	}
	public String getUpgradeId() {
		return mUpgradeID;
	}
	public String getVersionInServer() {
		return mVersionInServer;
	}
	public boolean isEnforce() {
		return mIsEnforce;
	}
	public String getUrl() {
		return mUrl;
	}
	public String getMd5() {
		return md5;
	}
}
