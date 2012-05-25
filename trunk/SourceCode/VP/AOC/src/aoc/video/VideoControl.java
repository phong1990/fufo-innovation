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
package aoc.video;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import aoc.gui.AOC;

/**
 * @author khoinguyen67
 *
 */
public class VideoControl extends Thread {
    
    AOC aoc;
    DatagramSocket udpSocket;
    DatagramPacket udpPackage;
    UDPpackage pk;
    int packNum;
    
    byte[] frameBuffer = new byte[15000];
    byte[] pacBuffer = new byte[15001];
   
    public VideoControl(){ };
    
    public VideoControl(AOC aoc){
        
        this.aoc = aoc;
    }
 
    /*
     * This method is called when this thread starts.
     */
    public void run(){
        try {
            udpSocket = new DatagramSocket(4444);
            udpPackage = new DatagramPacket(pacBuffer, pacBuffer.length);
            
            while(true){
                udpSocket.receive(udpPackage);
                showOnScreen(udpPackage);
                System.out.println("received!");
            }
       
        } catch (Exception ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }
    
    public void showOnScreen(DatagramPacket udpPackage){
        
        frameBuffer = pacBuffer;       
        AOC.lblFramePicture.setIcon(new ImageIcon(frameBuffer));  
    }
}
