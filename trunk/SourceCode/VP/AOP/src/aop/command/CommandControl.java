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
package aop.command;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import android.bluetooth.BluetoothSocket;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import aop.control.Control;
import aop.control.R;

/**
 * @author khoinguyen67
 *
 */
public class CommandControl extends Thread implements OnClickListener {
    
    //Create server socket to control command
    public Socket commandSocket = null;               //Initiate Socket to receive command
    BufferedReader in;                        //Initiate BufferedReader to save command
    int command;
    public BluetoothSocket bluetoothSocket = null;
    public int controlMode;
    int buttonID;
  //  byte Control.controlByte = 'e';
    public static int flagDelay = 1;
    public boolean flagWhile = true;
    int countY = 0;
    
    //Constructor
    public CommandControl(){}

    //Constructor receive argument Socket to send command
    public CommandControl(Socket commandSocket, BluetoothSocket bluetoothSocket, 
            int controlMode){

        this.commandSocket = commandSocket;
        this.bluetoothSocket = bluetoothSocket;
        this.controlMode = controlMode;
    }

    /*
     * This method is called when this thread starts.
     */
    public void run(){
        
        Log.d("cmct","Da vo Thread cmct: " + controlMode +Control.ffSetting+ Control.svSetting);
        try {

            while(Control.whileCommand){

                if(Control.svSetting == 1 && controlMode == 1){

                    waitCommandFromeAOC();
                    bluetoothSocket.getOutputStream().write(Control.controlByte);
                    Log.d("cmct","da send: " + Control.controlByte);
                    Control.controlByte = 'y';
                }else if(controlMode == 2){

                    if(Control.controlByte != 'y'){

                        bluetoothSocket.getOutputStream().write(Control.controlByte);
                        Log.d("cmct","da send: " + Control.controlByte + "  " + Control.connectFF);
                        Control.controlByte = 'y';
                        sleep(500);
                        countY = 0;
                    } else if (Control.connectFF == true){

                        sleep(10);
                        if(countY == 100){
                            bluetoothSocket.getOutputStream().write(Control.controlByte);
                            Log.d("cmct","da send10 y");
                            countY = 0;
                        } else {
                            
                            countY ++;  
                        }
                    }
                }
            }
        } catch (Exception ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }

    /*
     * This method uses to receive command from AOC via TCP socket
     */
    public void waitCommandFromeAOC() throws IOException{

        in = new BufferedReader(new InputStreamReader(
                commandSocket.getInputStream()));
        String temp = in.readLine();
        command = Integer.parseInt(temp);
        Control.svSetting = 1;
        switch(command){
            
            case 37:
                Control.controlByte = 'n';
                break;
                
            case 38:
                Control.controlByte = 'o';
                break;
                
            case 39:
                Control.controlByte = 'k';
                break;
            case 40:
                Control.controlByte = 'p';
                break;
                
            case 65:
                Control.controlByte = 'a';
                break;
                
            case 87:
                Control.controlByte = 'w';
                break;
                
            case 68:
                Control.controlByte = 'd';
                break;
                
            case 83:
                Control.controlByte = 's';
                break;
                
            case 89:
                Control.controlByte = 'y';
                break;
            case 10: 
                Control.controlByte = 'f';
                break;
            case 82: 
                Control.controlByte = 'r';
                break;
            
        }
    }

    /*
     * This method uses to send command to FUFO when new command receive
     */
    public void sendCommandToFUFO(){

        if (Control.ffSetting == 1 && flagDelay == 1){

            Log.d("cmct", "Control:" + Control.controlByte + " .Command : " + command + " .CtM: " + controlMode + Control.ffSetting +Control.svSetting);
            try {
                
                flagDelay = 2;
                if (bluetoothSocket != null)
                    
                    bluetoothSocket.getOutputStream().write(Control.controlByte);
                sleep(500);
                flagDelay =1;
            } catch (Exception e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }

    /**
     * [Explain the description for this method here].
     * @param v
     * @see android.view.View.OnClickListener#onClick(android.view.View)
     */
    @Override
    public void onClick(View v) {

        buttonID = v.getId();
        switch (buttonID){
            case R.id.bt_lft:
                Control.controlByte = 'a'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_fwd:
                Control.controlByte = 'w'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_rgt:
                Control.controlByte = 'd'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_bwd:
                Control.controlByte = 's'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_up:
                Control.controlByte = 'o'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_dwn:
                Control.controlByte = 'p'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_start:
                Control.controlByte = 'f'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_nkdt:
                Control.controlByte = 'n'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_kdh:
                Control.controlByte = 'k'; 
                //                sendCommandToFUFO();
                break;
        }
    }
    public void setCommand(byte command){

        this.command = Control.controlByte;
    }
}
