package aop.video;

public final class Videokit {

  static {
    System.loadLibrary("videokit");
  }

  public native void run(String[] args);

}
