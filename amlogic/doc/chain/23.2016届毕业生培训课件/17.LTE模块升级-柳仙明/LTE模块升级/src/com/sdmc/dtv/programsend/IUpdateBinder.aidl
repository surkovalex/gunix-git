package com.sdmc.dtv.programsend;

import com.sdmc.dtv.programsend.IUpdateListener;
import com.sdmc.dtv.programsend.IUpdate4GListener;

interface IUpdateBinder {
	int checkUpdate(in IUpdateListener listener);
	boolean checkFirmWare(in String path);
	boolean updateFirmWare(in String path);
	void wipeUserapp();
	void rebootSystem();
	
	void query4GUpgrade(in String id, in String facturerid, in String version);
	void download4G(in String id, in String uri, in String localPath, in String md5);
	boolean  register4GListener(in String id, in IUpdate4GListener listener);
	void unregister4GListener(in String id);
	void upgrade4GResultReport(in String upgradeid, in String id, in String oldversion, in String curversion, in String result);
}