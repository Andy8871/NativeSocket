package com.vagrenat.nativesocket;

public class Diagnose {
	public native void run();
	public native void exit();
	static{
		System.loadLibrary("diagnose");
	}
}
