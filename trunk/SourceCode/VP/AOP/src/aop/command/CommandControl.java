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
import aop.control.R;

/**
 * @author khoinguyen67
 *
 */
public class CommandControl extends Thread implements OnClickListener {
    //Create server socket to control command
    Socket commandSocket = null;               //Initiate Socket to receive command
    BufferedReader in;                        //Initiate BufferedReader to save command
    int command;
    BluetoothSocket bluetoothSocket = null;
    public int controlMode;
    int buttonID;
    byte control;
    int flagDelay = 1;

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

        try {
            Log.d("FUFO", "vo roi1" + command);
            while(true){
                waitCommandFromeAOC();
                if (controlMode == 0) {
            
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

        in = new BufferedReader(new InputStreamReader(
                commandSocket.getInputStream()));
        command = Integer.parseInt(in.readLine());
        switch(command){
            case 37:
                control = 'n';
                break;
            case 38:
                control = 'o';
                break;
            case 39:
                control = 'k';
                break;
            case 40:
                control = 'p';
                break;
            case 65:
                control = 'a';
                break;
            case 87:
                control = 'w';
                break;
            case 68:
                control = 'd';
                break;
            case 83:
                control = 's';
                break;

        }
    }

    /*
     * This method uses to send command to FUFO when new command receive
     */
    public void sendCommandToFUFO(){
        Log.d("FUFO", "Control:" + control + " .Command : " + command + " .CtM: " + controlMode);
        if (bluetoothSocket != null && flagDelay == 1)
            try {
                flagDelay = 2;
                bluetoothSocket.getOutputStream().write(control);
                sleep(500);
                flagDelay =1;
            } catch (Exception e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
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
                control = 'a'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_fwd:
                control = 'w'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_rgt:
                control = 'd'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_bwd:
                control = 's'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_up:
                control = 'o'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_dwn:
                control = 'p'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_ct:
                control = 'c'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_nkdt:
                control = 'n'; 
                sendCommandToFUFO();
                break;
            case R.id.bt_kdh:
                control = 'k'; 
                sendCommandToFUFO();
                break;
        }
    }

}
