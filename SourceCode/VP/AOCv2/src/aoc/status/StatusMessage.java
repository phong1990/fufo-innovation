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

    public double pitchAngle = 0 ;                     //Initiate pitch Angle  
    public double rollAngle = 0 ;                     //Initiate roll Angle
    public double height = 0;
    public String statusMessage;                  //Message receive via TCP socket 

    /*
     * This method uses to create message from pitch angel and roll angel. 
     */
    public String setStatusMessage(int pitchAngle, int rollAngle){

        statusMessage = Integer.toString(pitchAngle) + Integer.toString(rollAngle) ;
        return statusMessage;
    }

    /*
     * This method uses to get pitch angel and roll angel from message.
     */
    public void getStatus(String message){

        try {
            String[] abc = message.split(",");
            if(abc.length == 3){
                pitchAngle = Double.parseDouble(abc[0]) - 0.59;
                rollAngle = Double.parseDouble(abc[1]) + 13.16; 
                height = Double.parseDouble(abc[2]);
                if (height < 0) height = 0;
                if (height > 100) height = 100;
                //   pitchAngle = Integer.parseInt(message.substring(0,2));
                //  rollAngle = Integer.parseInt(message.substring(2,4)); 
            }
        } catch (Exception ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }

}
