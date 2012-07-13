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
package aoc.control;

import aoc.gui.*;
import aoc.status.StatusControl;
import aoc.video.VideoControl;

import java.net.ServerSocket;
import java.net.Socket;
import javax.swing.ImageIcon;
import aoc.command.CommandControl;


/**
 * This class is main class uses to control all of threads and GUI
 *  in application on computer.
 * @author khoinguyen67
 *
 */
public class Control {
    
    private static ServerSocket serverSocket = null;               //Initiate ServerSocket to create server
    private static Socket tcpSocket = null;                        //Used to send command and receive status
    public static final int PORT = 8888;                           //Port of server
    
    /*
     * Used to start GUI and threads 
     */
    public static void main(String args[]){
        
        try {
            
        AOC aoc = new AOC();                                    //Initiate GUI aoc
        aoc.frame.pack();
        aoc.frame.setVisible(true);                             //Set components in GUI can visible       
        serverSocket = new ServerSocket(PORT);                  //Start server
        tcpSocket =  serverSocket.accept();                     //Wait for client connecting
        aoc.lb_status.setIcon(new ImageIcon("pic\\lb_status_Green.png"));  //Set color for panel of gui when connecting successful
        //aoc.lblConnectedToFufo.setText("Connected to FUFO!");  //Set text for label in GUI when connecting successful
        
        StatusControl stct = new StatusControl(tcpSocket, aoc);
        stct.start();
       
        //Initiate thread to control command with 2 arguments TCP socket and  GUI aoc 
        CommandControl cmct = new CommandControl(tcpSocket, aoc);    
        //cmct.setPriority(10);
        cmct.start();                                            //Start this thread.
               
        VideoControl vdct = new VideoControl(aoc);
        //vdct.setPriority(10);
        vdct.start();
        
        }catch(Exception e){
        
            System.out.print(e.getMessage());
        }
    }
}
