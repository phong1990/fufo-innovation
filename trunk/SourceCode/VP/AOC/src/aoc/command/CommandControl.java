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
import java.net.ServerSocket;
import java.net.Socket;

/**
 * @author khoinguyen67
 *
 */
public class CommandControl extends Thread implements KeyListener{

    //Create server socket to control command
    ServerSocket svsk = null;
    Socket cmsk = null;
    private byte command ;
    private int key = 0;
    private KeyEvent e;
    public CommandControl(){}
    public CommandControl(Socket sk){
        cmsk = sk;
    }

    public void run(){
        command = waitCommandFromUser();
        sendCommandToAOP(command);
        keyPressed(e);
    }

    public byte waitCommandFromUser(){
        return command;
    }

    public void sendCommandToAOP(byte command){
        System.out.print("Sent command to AOP!");
    }
    /**
     * [Explain the description for this method here].
     * @param arg0
     * @see java.awt.event.KeyListener#keyPressed(java.awt.event.KeyEvent)
     */
    @Override
    public void keyPressed(KeyEvent arg0) {
        // TODO Auto-generated method stub
        if(arg0.getID() == KeyEvent.KEY_PRESSED){
            key = arg0.getKeyCode();
            command = (byte)(arg0.getKeyChar());
            System.out.print(command);
        }
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
