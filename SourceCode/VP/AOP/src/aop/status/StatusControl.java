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
package aop.status;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * @author khoinguyen67
 *
 */
public class StatusControl extends Thread{
    
    Socket statusSocket;
    PrintWriter out;  
    String statusMessage;
    
    public StatusControl(){}
    public StatusControl(Socket statusSocket){
        this.statusSocket = statusSocket;
    }
    
    public void run(){
        
        try {
            out = new PrintWriter(statusSocket.getOutputStream());
            waitStatusFromFUFO();
            sendStatusToAOC();
        } catch (IOException ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }
    
    public void waitStatusFromFUFO(){
        
    }
    
    public void sendStatusToAOC(){
        out.println(statusMessage);
    }
    
    

}
