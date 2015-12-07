package com.vagrenat.nativesocket;

public class Server {
	public native boolean createServer();
	public native void destoryServer();
	public native byte[] recv(int len);
	public native int send(byte[]buff, int len);
	
	static{
		System.loadLibrary("server");
	}
}
