package com.sdmc.lteupgrade.util;

public class UpgradeInfo {
	private String data;
	private boolean isComplete;
	private boolean isCheckFile;
	private int percent;
	
	public int getPercent() {
		return percent;
	}
	
	public void setPercent(int percent) {
		this.percent = percent;
	}

	public boolean isCheckFile() {
		return isCheckFile;
	}

	public void setCheckFile(boolean isCheckFile) {
		this.isCheckFile = isCheckFile;
	}

	public boolean isComplete() {
		return isComplete;
	}

	public void setComplete(boolean isComplete) {
		this.isComplete = isComplete;
	}

	public String getData() {
		return data;
	}

	public void setData(String data) {
		this.data = data;
	}
	
	
}
