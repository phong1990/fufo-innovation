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
package aoc.command;

import aoc.gui.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * @author khoinguyen67
 * This class uses to start a thread to receive pressing keyboard 
 * from users and send it to Android phone via TCP. 
 */
public class CommandControl extends Thread implements KeyListener{

    //Create server socket to control command
    AOC aoc;                                  //Initiate GUI aoc.
    Socket commandSocket = null;              //Initiate Socket to send command
    PrintWriter out;                          //Initiate PrinWriter to send via TCP socket
    private int command ;                     //Initiate command

    //Constructor
    public CommandControl(){}

    //Constructor receive 2 arguments Socket to send command and aoc to add KeyListener
    public CommandControl(Socket commandSocket, AOC aoc){

        this.commandSocket = commandSocket;
        this.aoc = aoc;
    }

    public void run(){
        
        try {
            aoc.frmFufo.addKeyListener(this);       //Add KeyListener to main frame
            out = new PrintWriter(commandSocket.getOutputStream(),true);
        } catch (IOException ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }
    
    /**
     * When users pressing keyboard, this method will be called. 
     * @param e
     * @see java.awt.event.KeyListener#keyPressed(java.awt.event.KeyEvent)
     */
    @Override
    public void keyPressed(KeyEvent e) {

        command = e.getKeyCode();           //Get key code of pressed key
        out.println(command);               //Send command to phone via TCP socket
    }
    
    /**
     * [Explain the description for this method here].
     * @param arg0
     * @see java.awt.event.KeyListener#keyReleased(java.awt.event.KeyEvent)
     */
    @Override
    public void keyReleased(KeyEvent arg0) {
        // TODO Auto-generated method stub

    }
    
    /**
     * [Explain the description for this method here].
     * @param arg0
     * @see java.awt.event.KeyListener#keyTyped(java.awt.event.KeyEvent)
     */
    @Override
    public void keyTyped(KeyEvent arg0) {
        // TODO Auto-generated method stub

    }

}
