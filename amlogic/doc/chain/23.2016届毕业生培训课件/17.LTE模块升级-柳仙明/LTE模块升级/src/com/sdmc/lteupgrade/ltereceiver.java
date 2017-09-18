package com.sdmc.lteupgrade;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class LTEReceiver extends BroadcastReceiver {
	@Override
	public void onReceive(Context context, Intent intent) {
		Log.d("LTEUpgrade", "boot complete ");
		context.startService(new Intent(context, LTEService.class));
	}
}
