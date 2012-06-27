package aop.video;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

import android.content.Context;
import android.graphics.ImageFormat;
import android.graphics.Rect;
import android.graphics.YuvImage;
import android.hardware.Camera;
import android.hardware.Camera.Parameters;
import android.hardware.Camera.PreviewCallback;
import android.hardware.Camera.Size;
import android.os.Environment;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/** A basic Camera preview class */
public class CameraPreview extends SurfaceView implements
		SurfaceHolder.Callback, PreviewCallback {
   //data buffer of picture to stream
    byte[] picBuffer;
    
    public Client client;
	public SurfaceHolder mHolder;
	private Camera mCamera;
	private String TAG = "CameraPreview.";
	// This variable is responsible for getting and setting the camera settings
	private Parameters parameters;
	// this variable stores the camera preview size
	private Size previewSize;
	// this array stores the pixels as hexadecimal pairs
	// The file name of NV21 byte array:
	private String filename = "sample_jpeg_Q50_320x240.";
	// the number of the outfile:
	private int fileNumber = 0;
	// this timestamp is to calculate the time gap of processing each frame
	// buffer
	private long timestamp = 0;

	
	public CameraPreview(Context context, Camera camera) {
		super(context);
		mCamera = camera;

		// Install a SurfaceHolder.Callback so we get notified when the
		// underlying surface is created and destroyed.
		mHolder = getHolder();
		mHolder.addCallback(this);
		// deprecated setting, but required on Android versions prior to 3.0
		mHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		 client = new Client();
         client.creatClient();
	}

	@Override
    public void surfaceCreated(SurfaceHolder holder) {
		// The Surface has been created, now tell the camera where to draw the
		// preview.
		try {
			mCamera.setPreviewDisplay(holder);
			// mCamera.startPreview();
			// sets the camera callback to be the one defined in this class
			mCamera.setPreviewCallback(this);

			parameters = mCamera.getParameters();
			// get preview size for calculation of the back buffer
			// compute the back buffer size according to the preview format. In
			// this case we use NV21 format
			// so the following formula should be equal to ( width x height x 3
			// / 2 )
			previewSize = mCamera.getParameters().getPreviewSize();
			int dataBufferSize = (int) (previewSize.height * previewSize.width * (ImageFormat
					.getBitsPerPixel(mCamera.getParameters().getPreviewFormat()) / 8.0));
			mCamera.setParameters(parameters);
			Log.v("CameraTest", "dataBufferSize = " + dataBufferSize);

		} catch (IOException e) {
			if (mCamera != null) {
				// handle the exception here
				e.printStackTrace();
			}
		}
	}

	@Override
    public void surfaceDestroyed(SurfaceHolder holder) {
		// Surface will be destroyed when we return, so stop the preview.
		// Because the CameraDevice object is not a shared resource, it's very
		// important to release it when the activity is paused.
	}

	@Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
		// If your preview can change or rotate, take care of those events here.
		// Make sure to stop the preview before resizing or reformatting it.

		if (mHolder.getSurface() == null) {
			// preview surface does not exist
			return;
		}

		// stop preview before making changes
		try {
			mCamera.stopPreview();
		} catch (Exception e) {
			// ignore: tried to stop a non-existent preview
		}

		// Now that the size is known, set up the camera parameters and begin
		// the preview.
		// parameters.setPreviewSize(w, h);
		// set the camera's settings
		// mCamera.setParameters(parameters);

		// start preview with new settings
		try {
		    SurfaceView view = new SurfaceView(getContext());
		    mCamera.setPreviewDisplay(view.getHolder());
		  //  mCamera.startPreview();
		    
			//mCamera.setPreviewDisplay(mHolder);
			mCamera.startPreview();

		} catch (Exception e) {
			Log.d(TAG
					+ "surfaceChanged(SurfaceHolder holder, int format, int w, int h)",
					"Error starting camera preview: " + e.getMessage());
		}
	}

	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {
	    Log.d("aop", "da vao6");
		Log.d("FUFO", "Time Gap = "
				+ (System.currentTimeMillis() - timestamp));
		timestamp = System.currentTimeMillis();
		// NV21toRGB24Converter(pixels, data, previewSize.width,
		// previewSize.height);
		final YuvImage imgPreview = new YuvImage(data, ImageFormat.NV21,
				mCamera.getParameters().getPreviewSize().width, mCamera
						.getParameters().getPreviewSize().height, null);
		byte[] buffer;
		ByteArrayOutputStream jpegOutStream = new ByteArrayOutputStream();
		// Compress image into JPEG
		imgPreview.compressToJpeg(new Rect(0, 0, imgPreview.getWidth(),
				imgPreview.getHeight()), 50, jpegOutStream);

		// This buffer can be sent to another computer.
		buffer = jpegOutStream.toByteArray();

		// increase the file number
		fileNumber++;
		 //Sendfile to Server
        Log.d("FUFO", "package = "
                + fileNumber);
	   
	       
		    client.sendPackage(buffer);
	}
}