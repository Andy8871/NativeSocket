package com.vagrenat.nativesocket;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

public class DiagnoseService extends Service {
	private final static String TAG = DiagnoseService.class.getSimpleName();
	/* 供绑定诊断服务的UI去调用 */
	/* 为UI获取诊断服务对象便于UI和诊断进行数据交互提供接口 */
	private class DiagnoseBinder extends Binder{
		public DiagnoseService getService()
		{	
			Log.i(TAG, "UI activity get the instance");
			return DiagnoseService.this;
		}
	}
	
	private final IBinder mBinder = new DiagnoseBinder();
	
	@Override
	public IBinder onBind(Intent intent) {
		
		return mBinder;
	}

	@Override
	public void onCreate() {
		super.onCreate();
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
	}
	
	

}
