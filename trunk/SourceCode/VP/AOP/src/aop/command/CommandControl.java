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
import android.widget.RadioGroup.OnCheckedChangeListener;
import aop.control.Control;
import aop.control.ControlActivity;
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
    byte controlByte;
    public static int flagDelay = 1;
    public boolean flagWhile = true;

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
        Log.d("cmct","Da vo Thread " + controlMode +Control.ffSetting+ Control.svSetting);
        try {
            
            while(true){
                           
                if(Control.svSetting == 1){
                    
                   waitCommandFromeAOC();
                }
                if (controlMode == 1) {
                    sendCommandToFUFO();
                }
            }
        } catch (IOException ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }

    /*
     * This method uses to receive command from AOC via TCP socket
     */
    public void waitCommandFromeAOC() throws IOException{
        Log.d("cmct","Da vo wait");
        Log.d("cmct", " : " + System.currentTimeMillis() + " : " );
        in = new BufferedReader(new InputStreamReader(
                commandSocket.getInputStream()));
        Log.d("cmct", " : " + System.currentTimeMillis() + " : " );
        command = Integer.parseInt(in.readLine());
        Log.d("cmct", " : " + System.currentTimeMillis() + " : " );
        switch(command){
            case 37:
                controlByte = 'n';
                break;
            case 38:
                controlByte = 'o';
                break;
            case 39:
                controlByte = 'k';
                break;
            case 40:
                controlByte = 'p';
                break;
            case 65:
                controlByte = 'a';
                break;
            case 87:
                controlByte = 'w';
                break;
            case 68:
                controlByte = 'd';
                break;
            case 83:
                controlByte = 's';
                break;

        }
    }

    /*
     * This method uses to send command to FUFO when new command receive
     */
    public void sendCommandToFUFO(){

        if (Control.ffSetting == 1 && flagDelay == 1){
            
            Log.d("cmct", "Control:" + controlByte + " .Command : " + command + " .CtM: " + controlMode + Control.ffSetting +Control.svSetting);
            try {
                flagDelay = 2;
                if (bluetoothSocket != null)
                bluetoothSocket.getOutputStream().write(controlByte);
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
        // TODO Auto-generated method stub

        buttonID = v.getId();
        switch (buttonID){
            case R.id.bt_lft:
                controlByte = 'a'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_fwd:
                controlByte = 'w'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_rgt:
                controlByte = 'd'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_bwd:
                controlByte = 's'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_up:
                controlByte = 'o'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_dwn:
                controlByte = 'p'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_start:
                controlByte = 'f'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_nkdt:
                controlByte = 'n'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_kdh:
                controlByte = 'k'; 
                sendCommandToFUFO();
                break;
        }
    }

}
