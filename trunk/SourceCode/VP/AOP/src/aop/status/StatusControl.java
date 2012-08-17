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
package aop.status;

import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import android.bluetooth.BluetoothSocket;
import android.os.Environment;
import android.util.Log;
import aop.control.Control;

/**
 * @author khoinguyen67
 *
 */
public class StatusControl extends Thread{

 //   public int pitchAngle = 0 ;                     //Initiate pitch Angle  
 //   public int rollAngle = 0 ;                     //Initiate roll Angle
    public BluetoothSocket bluetoothSocket;
    public Socket statusSocket;
    public PrintWriter out;  
    String statusMessage = null;
    byte buf[] = null;
    byte[] buffer = new byte[1024]; 
    InputStream is;
    BufferedReader in;
    public StatusControl(){}
    String temp = null;
    boolean flagOutput = false;
    
    public StatusControl(BluetoothSocket bluetoothSocket){

        this.bluetoothSocket = bluetoothSocket;
    }

    public StatusControl(Socket statusSocket, BluetoothSocket bluetoothSocket){

        this.statusSocket = statusSocket;
        this.bluetoothSocket = bluetoothSocket;
    }
    public void run(){
        Log.d("stct", "vo thread" );
        try {
            if (statusSocket != null){

                out = new PrintWriter(statusSocket.getOutputStream(),true);
            }
            if(bluetoothSocket != null){
                //  is = bluetoothSocket.getInputStream();
                in = new BufferedReader(new InputStreamReader(
                        bluetoothSocket.getInputStream()));
            }

            while(Control.whileStatus){

                if (statusSocket != null && flagOutput == false){

                    out = new PrintWriter(statusSocket.getOutputStream(),true);
                    flagOutput = true;
                }
                temp = in.readLine();
                Control.ffSetting = 1;
                if(temp.equals("y")){
                    Control.connectFF = true;
                } else
                    
             //      if(temp.getBytes().length >= 24 && temp.getBytes().length <= 27){
                        writeToFile((temp + "\r\n").getBytes());
                        Log.d("stct",": " + temp.getBytes().length);
                        
                        Control.ffSetting = 1;
                        //  writeToFile(("\r\n").getBytes());
                        if (statusSocket != null){
                            out.println(temp);
                        }
            //       }
                Log.d("stct", " : " + System.currentTimeMillis() + " :" + temp + ":" );

                //   waitStatusFromFUFO();
                //  sendStatusToAOC();
            }
        } catch (IOException ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }

   /* public void waitStatusFromFUFO(){
        try {

            Log.d("stct", " : " + System.currentTimeMillis() + " : " );
            int bread = is.read(buffer);
            Log.d("stct", " : " + System.currentTimeMillis() + " : " + bread );
            buf = new byte[bread];
            System.arraycopy(buffer, 0, buf, 0, bread);
            writeToFile(buf);
            Log.d("stct", " : " + System.currentTimeMillis() + " : e" );

        } catch (IOException ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }

    public void sendStatusToAOC(){

        String temp = new String(buf);
        String[] arrayMessage = temp.split(";");
        for(int i = 1; i < arrayMessage.length-1; i++){

            if (statusSocket != null){
                try {
                    //  StatusControl.sleep(200);
                } catch (Exception ex) {
                    // TODO Auto-generated catch block
                    ex.printStackTrace();
                }
                if(arrayMessage.length > 1){
                    Log.d("stct", " : 55" +arrayMessage.length );
                out.println(arrayMessage[1]);
                //   arrayMessage[i] = arrayMessage[i]+ "\r"+"\n";
                out.println(arrayMessage[i]);
                Log.d("stct", System.getProperty("line.separator")+" : 55" +arrayMessage[i]);
            }
        }
        //     Log.d("stct3", " : " + arrayMessage[1] );
    }
    */

    public static void writeToFile(byte[] buffer){
        String state = android.os.Environment.getExternalStorageState();
        try{
            if(state.equals(android.os.Environment.MEDIA_MOUNTED))   
            { 
                String sdcard_path = Environment.getExternalStorageDirectory().getAbsolutePath(); 
             //   String sdcard_path = Environment
             //   .getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES).getAbsolutePath();
                String file_path = sdcard_path; 
                //   Log.d("FUFO",file_path);
                FileOutputStream os = new FileOutputStream(file_path + "/" + "status2.txt",true);

                os.write(buffer);
                os.close(); 
            }
        }catch(Exception e){
            e.getMessage();
        }
    }

    /*
     * This method uses to create message from horizontal status and vertical status. 
     */
    public String setStatusMessage(int pitchAngle, int rollAngle){

        statusMessage = Integer.toString(pitchAngle)+ "," + Integer.toString(rollAngle) ;
        return statusMessage;
    }
}
