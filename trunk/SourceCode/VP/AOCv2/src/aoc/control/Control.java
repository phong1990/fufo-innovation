package aoc.control;

import aoc.gui.*;
import aoc.status.StatusControl;
import aoc.video.VideoControl;
import java.net.ServerSocket;
import java.net.Socket;
import javax.swing.ImageIcon;
import aoc.command.CommandControl;

/**
 * This class is main class uses to control all of threads and GUI
 *  in application on computer.
 * @author khoinguyen67
 *
 */
public class Control {

    private static ServerSocket serverSocket = null;        //Initiate ServerSocket to create server
    private static Socket tcpSocket = null;                 //Used to send command and receive status
    public static final int PORT = 8888;                    //Port of server
    //   public static StatusControl stct;                       //Thread to control status
    public static CommandControl cmct;                      //Thread to control command
    //  public static VideoControl vdct;                        //Thread to control video
    public static boolean svSetting = false;                 //Flag to check socket between AOP and AOC 
    public static boolean ffSetting = false;                 //Flag to check socket between AOP and FUFO 
    public static int start = 0;                            //Flag to check socket whether start button pressed
    public static Thread alert;
    public static boolean flagY = false;
    public static boolean checkConnect = false;
    //    public static int command = 0;
    /*
     * Used to start GUI and threads 
     */
    public static void main(String args[]){

        try {

            final AOC aoc = new AOC();                              //Initiate GUI aoc
            aoc.frame.pack();
            aoc.frame.setVisible(true);                             //Set components in GUI can visible   
            //  cmct = new CommandControl();
            aoc.frame.addKeyListener(aoc.keyListener);
            serverSocket = new ServerSocket(PORT);                  //Start server
            tcpSocket =  serverSocket.accept();                     //Wait for client connecting
            serverSocket.close();                                   //Close server socket
            //  aoc.lb_text.setText("Connected!");
            svSetting = true;                             
            aoc.lb_status.setIcon(new ImageIcon("pic\\lb_status_Green.png"));  //Set color for panel of gui when connecting successful

            StatusControl stct = new StatusControl(tcpSocket, aoc);
       //     cmct.setPriority(8);
            stct.start();

            //Initiate thread to control command with 2 arguments TCP socket and  GUI aoc 
            //   cmct.setCommandSocket(tcpSocket);
            cmct = new CommandControl(tcpSocket);
         //   cmct.setPriority(10);
            cmct.start();                                            //Start this thread.

            VideoControl vdct = new VideoControl(aoc);
       //     cmct.setPriority(9);
            vdct.start();

            /*
             * Thread to check connection error between AOP and AOC
             */
            alert = new Thread(){

                public void run(){

                    try {

                        while(true){
                            if(Control.start == 1 && Control.flagY == true){
                                sleep(2000); 
                                if(checkConnect){

                                     aoc.lb_status.setIcon(new ImageIcon("pic\\lb_status_Green.png"));
                                     checkConnect = false;
                                }else {

                                    aoc.lb_status.setIcon(new ImageIcon("pic\\Text_Bar_Red.png"));
                                  //  aoc.setButtonDisable();
                                  //  aoc.bt_start.setIcon(new ImageIcon("pic\\bt_start_Normal.png"));
                               
                                }
                            }
                        }
                    } catch (InterruptedException ex) {

                        ex.printStackTrace();
                    }

                }
            };
            alert.start();
        }catch(Exception e){

            e.printStackTrace();
        }
    }
}
