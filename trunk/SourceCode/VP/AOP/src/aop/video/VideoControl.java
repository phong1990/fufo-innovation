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

import android.app.Activity;
import android.hardware.Camera;

/**
 * @author khoinguyen67
 *
 */
public class VideoControl extends Thread {
    
    Activity control;
    private Camera mCamera;
    private CameraPreview mPreview;
    
    public VideoControl(Activity control){
        
        this.control = control;     
    }
    
    public VideoControl(){
    
        
    }
    
    public void run(){
        mCamera = getCameraInstance();
        mPreview = new CameraPreview(control, mCamera);
        
        mCamera.startPreview();
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
}