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
package aop.control;

import java.util.Iterator;
import java.util.List;

import aop.video.*;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.hardware.Camera.Size;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TableLayout;

/**
 * @author khoinguyen67
 *
 */
public class ControlActivity extends Activity implements OnCheckedChangeListener {
    Button  bt_Fwd, bt_Bwd, bt_Rgt, 
    bt_Lft, bt_Up, bt_Dwn, bt_Nkdh, bt_Kdh, bt_Start;
   public static RadioButton rd_Computer,rd_Phone;
   FrameLayout preview;
    RadioGroup rd_Group;
    TableLayout tb_LO;
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tab_control);

        bt_Fwd = (Button)findViewById(R.id.bt_fwd);
        bt_Bwd = (Button)findViewById(R.id.bt_bwd);
        bt_Rgt = (Button)findViewById(R.id.bt_rgt);
        bt_Lft = (Button)findViewById(R.id.bt_lft);
        bt_Up = (Button)findViewById(R.id.bt_up);
        bt_Dwn = (Button)findViewById(R.id.bt_dwn);
        bt_Nkdh = (Button)findViewById(R.id.bt_nkdt);
        bt_Kdh = (Button)findViewById(R.id.bt_kdh);
        bt_Start = (Button)findViewById(R.id.bt_start);
        rd_Group = (RadioGroup)findViewById(R.id.radioGroup);
        rd_Computer = (RadioButton)findViewById(R.id.rd_computer);
        rd_Phone = (RadioButton)findViewById(R.id.rd_phone);
        tb_LO = (TableLayout)findViewById(R.id.tb_layout);
        preview = (FrameLayout) findViewById(R.id.camera_preview);
        rd_Group.setOnCheckedChangeListener(this);
        bt_Fwd.setOnClickListener(Control.cmct);
        bt_Bwd.setOnClickListener(Control.cmct);
        bt_Rgt.setOnClickListener(Control.cmct);
        bt_Lft.setOnClickListener(Control.cmct);
        bt_Up.setOnClickListener(Control.cmct);
        bt_Dwn.setOnClickListener(Control.cmct);
        bt_Nkdh.setOnClickListener(Control.cmct);
        bt_Kdh.setOnClickListener(Control.cmct);
        bt_Start.setOnClickListener(Control.cmct);
 
            tb_LO.setVisibility(4);
            settingCamera();
        
    }
    View.OnClickListener testOnClick = new View.OnClickListener() {
        
        @Override
        public void onClick(View v) {
            // TODO Auto-generated method stub
            Log.d("FUFO", "Fwd button pressed!1" + v.getId());
            if(v.getId() == 0x7f020003){
                
                Log.d("FUFO", "Fwd button pressed!2");
            }
        }
    };
    /**
     * [Explain the description for this method here].
     * @param arg0
     * @param arg1
     * @see android.widget.RadioGroup.OnCheckedChangeListener#onCheckedChanged(android.widget.RadioGroup, int)
     */
    @Override
    public void onCheckedChanged(RadioGroup arg0, int arg1) {
        Log.d("FUFO", "radio button pressed!");
        // TODO Auto-generated method stub
        try{
          if(arg0.getCheckedRadioButtonId() == R.id.rd_computer){
              Log.d("FUFO", "computer radio button pressed!");
          tb_LO.setVisibility(4); 
          Log.d("FUFO", "computer radio button pressed1!");
          
              Control.cmct.controlMode = 1;
              if(Control.cmct.bluetoothSocket != null){
                  Control.cmct.bluetoothSocket.getOutputStream().write('c');
              }
        }
        else {
            tb_LO.setVisibility(0);
            if(Control.cmct.bluetoothSocket != null){
                Control.cmct.bluetoothSocket.getOutputStream().write('n');
            }
            Control.cmct.controlMode = 2;
        }
    }catch(Exception e){
        
    }
}
    
    
    
    private Camera mCamera;
    private CameraPreview mPreview;
    
    public void settingCamera(){
        if (checkCameraHardware(this)) {
            //,// Create an instance of Camera
            mCamera = getCameraInstance();
            Log.d("aop", "da vao");
            // Create our Preview view and set it as the content of our
            // activity.
            mPreview = new CameraPreview(this, mCamera);
            Log.d("aop", "da vao2");
            
            preview.addView(mPreview);
            Log.d("aop", "da vao3");

            Log.d("aop", "da vao311");
            // get Camera parameters
            Camera.Parameters params = mCamera.getParameters();
            Log.d("aop", "da vao312");
  /*          List<int[]> supportedPreviewFps = params
                    .getSupportedPreviewFpsRange();
            Iterator<int[]> supportedPreviewFpsIterator = supportedPreviewFps
                    .iterator();
            Log.d("aop", "da vao31");
            while (supportedPreviewFpsIterator.hasNext()) {
                int[] tmpRate = supportedPreviewFpsIterator.next();
                StringBuffer sb = new StringBuffer();
                sb.append("supportedPreviewRate: ");
                for (int i = tmpRate.length, j = 0; j < i; j++) {
                    sb.append(tmpRate[j] + ", ");
                }
                Log.v("CameraTest", sb.toString());
            }*/
            Log.d("aop", "da vao32");
            // List the supported Preview Sizes
            List<Size> supportedPreviewSizes = params
                    .getSupportedPreviewSizes();
            Iterator<Size> supportedPreviewSizesIterator = supportedPreviewSizes
                    .iterator();
            Log.d("aop", "da vao33");
            while (supportedPreviewSizesIterator.hasNext()) {
                Size tmpSize = supportedPreviewSizesIterator.next();
                Log.v("CameraTest", "supportedPreviewSize.width = "
                        + tmpSize.width + "supportedPreviewSize.height = "
                        + tmpSize.height);
            }

            // Just show the current framerate for fun
            Log.v("CameraTest", "Camera PreviewFrameRate = "
                    + mCamera.getParameters().getPreviewFrameRate());
            Log.d("aop", "da vao4");
            // Start preview
            mCamera.startPreview();
            Log.d("aop", "da vao5");
            // Add a listener to the Capture button
           
        }
    }
    @Override
    public void onDestroy() {
        super.onDestroy();
        // check if the system has a camera
        if (checkCameraHardware(this)) {
            // in case user forget to push the stop button
            if (mCamera != null) {
                // Stoppreview first
                mCamera.stopPreview();
                // release camera
                releaseCamera();
            }
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
    
    
    
    
}