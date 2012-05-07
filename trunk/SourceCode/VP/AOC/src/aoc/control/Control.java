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

import java.net.ServerSocket;
import java.net.Socket;

import aoc.command.CommandControl;

/**
 * @author khoinguyen67
 *
 */
public class Control {
    private ServerSocket svsk = null;
    private Socket sk = null;
    private void createServer() throws Exception{
        svsk = new ServerSocket(6767);
       // sk = svsk.accept();
    }
    
    public static void main(String args[]){
        try{
        Control ct = new Control();
        ct.createServer();
        CommandControl cmct = new CommandControl(ct.sk);
        cmct.start();
        }catch(Exception e){
            System.out.print(e.getMessage());
        }
    }

}
