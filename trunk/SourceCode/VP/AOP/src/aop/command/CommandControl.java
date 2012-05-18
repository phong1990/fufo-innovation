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

import android.util.Log;

/**
 * @author khoinguyen67
 *
 */
public class CommandControl extends Thread {
    //Create server socket to control command
    Socket commandSocket = null;               //Initiate Socket to receive command
    BufferedReader in;                        //Initiate BufferedReader to save command
    int command;

    
    //Constructor
    public CommandControl(){}
    
    //Constructor receive argument Socket to send command
    public CommandControl(Socket commandSocket){

        this.commandSocket = commandSocket;
    }

    /*
     * This method is called when this thread starts.
     */
    public void run(){
        
        try {
            while(true){
            waitCommandFromeAOC();
            sendCommandToFUFO();
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
    
    }
    
    /*
     * This method uses to send command to FUFO when new command receive
     */
    public void sendCommandToFUFO(){
        Log.d("aop", "" + command);

    }


}
