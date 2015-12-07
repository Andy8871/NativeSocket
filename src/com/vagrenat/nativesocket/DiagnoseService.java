package com.vagrenat.nativesocket;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

public class DiagnoseService extends Service {
	private final static String TAG = DiagnoseService.class.getSimpleName();
	/* ������Ϸ����UIȥ���� */
	/* ΪUI��ȡ��Ϸ���������UI����Ͻ������ݽ����ṩ�ӿ� */
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
