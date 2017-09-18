package com.sdmc.dtv.programsend;

interface IUpdate4GListener {
	void onDownloadProgress(int percent, boolean iscomplete);
	void onCkeckFile(boolean result);
	void onCheckUpgrade();
	void onQueryResponse(String data);
}