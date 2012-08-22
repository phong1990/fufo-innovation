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
package aoc.status;

import aoc.control.Control;
import aoc.gui.AOC;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

import javax.swing.ImageIcon;

/**
 * This class uses to start a thread to receive status of FUFO from Android phone via TCP.
 * @author khoinguyen67
 * 
 */
public class StatusControl extends Thread {

    //Create server socket to control command
    AOC aoc;                                  //Initiate GUI aoc.
    Socket statusSocket = null;               //Initiate Socket to receive status
    BufferedReader in;                        //Initiate BufferedReader to save status
    StatusMessage sm;
    public double pitchAngle = 0 ;            //Initiate Pitch Angle  
    public double rollAngle = 0;              //Initiate Roll Angle 
    public double height = 0; 
    public String statusMessage;              //Status message receive from phone via TCP socket

    //Constructor
    public StatusControl(){}

    //Constructor receive 2 arguments Socket to send command and aoc
    public StatusControl(Socket statusSocket, AOC aoc){

        this.aoc = aoc;
        this.statusSocket = statusSocket;
    }

    /*
     * This method is called when this thread starts.
     */
    public void run(){

        try {

            in = new BufferedReader(new InputStreamReader(
                    statusSocket.getInputStream()));

            while(true){

                   updateStatusOnScreen(pitchAngle,rollAngle,height);
                waitStatusFromeAOP();
            }
        } catch (Exception ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }

    /*
     * This method uses to receive status from AOP via TCP socket and update it to screen
     */
    public void waitStatusFromeAOP() throws IOException{

        statusMessage = in.readLine();
        Control.svSetting = true;

        if(statusMessage.equals("ff1")){
        //    aoc.lb_status.setIcon(new ImageIcon("pic\\lb_status_Green.png"));
            Control.ffSetting = true;
            Control.checkConnect = true;
            // Control.alert.start();
        }else if(statusMessage.equals("y")){
            Control.flagY = true;

        }else{
            System.out.println(statusMessage);
            String[] abc = statusMessage.split(",");
            if(abc.length == 3){
                sm = new StatusMessage();
                sm.getStatus(statusMessage);
                pitchAngle = sm.pitchAngle;
                rollAngle = sm.rollAngle;
                height = sm.height;
            }
            Control.ffSetting = true;
            Control.svSetting = true;
        }
    }

    /*
     * This method uses to update status on screen when new status receive
     */
    public void updateStatusOnScreen(double PitchAngle,double RollAngle, double height){

        aoc.lb_ai.PitchAngle = PitchAngle;
        aoc.lb_ai.RollAngle = RollAngle/100;
        aoc.lb_height.height = height;
        aoc.frame.repaint();
    }
}
