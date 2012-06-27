/**
 * Licensed to Open-Ones Group under one or more contributor license
 * agreements. See the NOTICE file distributed with this work
 * for additional information regarding copyright ownership.
 * Open-Ones Group licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a
 * copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
package aop.video;

import aop.control.*;
import android.content.Context;
import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.widget.FrameLayout;

/**
 * @author khoinguyen67
 *
 */
public class VideoControl extends Thread {
    
    ControlActivity controlActivity;
    private Camera mCamera;
    private CameraPreview mPreview;
    FrameLayout preview;
    
    public VideoControl(ControlActivity control){
        
        this.controlActivity = control;     
    }
    
    public VideoControl(){  
    }
    
    public void run(){
     //   while(true);
      startStream();
    }
    
    public void startStream(){
        
        if (checkCameraHardware(controlActivity)) {
        
            // Create an instance of Camera
            mCamera = getCameraInstance();
            mPreview = new CameraPreview(controlActivity, mCamera);
            controlActivity.preview.addView(mPreview);  
            mCamera.startPreview();       // Start preview 
        }
    }
    
    /** Check if this device has a camera */
    private boolean checkCameraHardware(Context context) {
        if (context.getPackageManager().hasSystemFeature(
                PackageManager.FEATURE_CAMERA)) {
            // this device has a camera
            return true;
        } else {
            // no camera on this device
            return false;
        }
    }

    /** A safe way to get an instance of the Camera object. */
    public static Camera getCameraInstance() {
        Camera c = null;
        try {
            c = Camera.open(); // attempt to get a Camera instance
        } catch (Exception e) {
            // Camera is not available (in use or does not exist)
        }
        return c; // returns null if camera is unavailable
    }

    /** Release the camera **/
    private void releaseCamera() {
        if (mCamera != null) {
            mCamera.setPreviewCallback(null);
            mCamera.release(); // release the camera for other applications
            mCamera = null;
        }
    }
    
    public void stopStream() {
        // check if the system has a camera
        if (checkCameraHardware(controlActivity)) {
            // in case user forget to push the stop button
            if (mCamera != null) {
                // Stoppreview first
                mCamera.stopPreview();
                // release camera
                releaseCamera();
            }
        }
    }
}
