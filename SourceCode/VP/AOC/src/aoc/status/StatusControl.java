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

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

import aoc.gui.AOC;

/**
 * This class uses to start a thread to receive status of FUFO from Android phone via TCP.
 * 
 * @author khoinguyen67
 */
public class StatusControl extends Thread {
    // Create server socket to control command
    // AOC aoc; //Initiate GUI aoc.
    Socket statusSocket = null; // Initiate Socket to receive status
    BufferedReader in; // Initiate BufferedReader to save status
    StatusMessage sm;
    public int hoStatus; // Initiate horizontal status
    public int veStatus; // Initiate vertical status
    public String statusMessage; // Status message receive from phone via TCP socket

    // Constructor
    public StatusControl() {
    }

    // Constructor receive 2 arguments Socket to send command and aoc
    public StatusControl(Socket statusSocket) {

        this.statusSocket = statusSocket;
    }

    /*
     * This method is called when this thread starts.
     */
    @Override
    public void run() {

        try {
            while (true) {
                updateStatusOnScreen(90, 40);
                waitStatusFromeAOP();
            }
        } catch (IOException ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }

    /*
     * This method uses to receive status from FUFO via TCP socket and update it to screen
     */
    public void waitStatusFromeAOP() throws IOException {

        in = new BufferedReader(new InputStreamReader(statusSocket.getInputStream()));
        statusMessage = in.readLine();
        sm = new StatusMessage();
        sm.getStatus(statusMessage);
        hoStatus = sm.hoStatus;
        veStatus = sm.veStatus;
    }

    /*
     * This method uses to update status on screen when new status receive
     */
    public void updateStatusOnScreen(int hoStatus, int veStatus) {
        // float x = hoStatus/100;
        // float y = veStatus/100;
        AOC.lblFramePicture.setAlignmentX(0.6f);
        AOC.lblFramePicture.setAlignmentY(0.9f);
        AOC.panel.add(AOC.lblFramePicture);

        System.out.println(hoStatus + " : " + veStatus + " : ");
    }

}
