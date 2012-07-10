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

/**
 * This class is uses to get status from message received from phone 
 * via TCP socket and set message to send to computer. The message type 
 * is String containing two first characters is horizontal status and two continuous 
 * characters is vertical status.
 * @author khoinguyen67
 * 
 */
public class StatusMessage {

    public int pitchAngle = 0 ;                     //Initiate pitch Angle  
    public int rollAngle = 0 ;                     //Initiate roll Angle
    public String statusMessage;                  //Message receive via TCP socket 

    /*
     * This method uses to create message from horizontal status and vertical status. 
     */
    public String setStatusMessage(int hoStatus, int veStatus){

        statusMessage = Integer.toString(hoStatus) + Integer.toString(veStatus) ;
        return statusMessage;
    }

    /*
     * This method uses to get horizontal status and vertical status from message.
     */
    public void getStatus(String message){
        
        try {
            pitchAngle = Integer.parseInt(message.substring(0,2));
            rollAngle = Integer.parseInt(message.substring(2,4));          
        } catch (Exception ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }

}
