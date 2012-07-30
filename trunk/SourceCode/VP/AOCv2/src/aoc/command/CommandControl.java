package aoc.command;

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
    int countY = 0;

    //Constructor
    public CommandControl(){}

    //Constructor receive 2 arguments Socket to send command and aoc to add KeyListener
    public CommandControl(Socket commandSocket){

        this.commandSocket = commandSocket; 
    }

    public void run(){

        try {

            //Initiate PrintWriter to send command to Android phone
            out = new PrintWriter(commandSocket.getOutputStream(),true);

            while(true){

                /*
                 * Command doesn't equal zero when users control FUFO via GUI on AOC
                 */
                if(command != 0){
                    out.println(command);
                    System.out.println(command);
                    command = 0;
                    sleep(500);         //Time between 2 send command is 500 millisecond. 
                    countY = 0;

                    /*
                     * if users don't control. Application will automatic send byte 'y' 
                     * to AOP 1 second per time.
                     */
                }else {
                    sleep(10);
                    if(countY == 100){
                        out.println("y");
                        countY = 0;
                    } else {
                        countY ++;  
                    }
                }
            }
        } catch (Exception ex) {
            
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
