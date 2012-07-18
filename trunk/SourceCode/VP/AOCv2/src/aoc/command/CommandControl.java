package aoc.command;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * @author khoinguyen67
 * This class uses to start a thread to receive pressing keyboard 
 * from users and send it to Android phone via TCP. 
 */
public class CommandControl extends Thread{

    Socket commandSocket = null;              //Initiate Socket to send command
    PrintWriter out;                          //Initiate PrinWriter to send via TCP socket
    int command = 0 ;                         //Initiate command

    //Constructor
    public CommandControl(){}

    //Constructor receive 2 arguments Socket to send command and aoc to add KeyListener
    public CommandControl(Socket commandSocket){

        this.commandSocket = commandSocket;
    }

    public void run(){
        
        try {
           
            out = new PrintWriter(commandSocket.getOutputStream(),true);
            
            while(true){
                
                if(command != 0){
                    out.println(command);
                    System.out.println(command);
                    command = 0;
                }                  
            }
        } catch (IOException ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
    }
    
    public void setCommand(int command){
        
        this.command = command;
    }
    
public void setCommandSocket(Socket commandSocket){
        
        this.commandSocket = commandSocket;
    }
}
