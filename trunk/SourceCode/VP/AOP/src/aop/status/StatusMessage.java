/*package aop.status;

*//**
 * This class is uses to get status from message received from phone 
 * via TCP socket and set message to send to computer. The message type 
 * is String containing two first characters is horizontal status and two continuous 
 * characters is vertical status.
 * @author khoinguyen67
 * 
 *//*
public class StatusMessage {

    public int pitchAngle = 0 ;                     //Initiate pitch Angle  
    public int rollAngle = 0 ;                     //Initiate roll Angle
    public String statusMessage;                  //Message receive via TCP socket 

    
     * This method uses to create message from horizontal status and vertical status. 
     
    public String setStatusMessage(int pitchAngle, int rollAngle){

        statusMessage = Integer.toString(pitchAngle)+"," + Integer.toString(rollAngle) ;
        return statusMessage;
    }

    
     * This method uses to get horizontal status and vertical status from message.
     
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
*/