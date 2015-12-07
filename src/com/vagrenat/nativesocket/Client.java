package com.vagrenat.nativesocket;

public class Client {
	public native boolean connect(String ipAddr, String port);
	public native void disconnect();
	public native byte[] recv(int len);
	public native int send(byte[] buff, int len);
	static{
		System.loadLibrary("client");
	}
}
