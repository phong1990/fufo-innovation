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

    private static ServerSocket serverSocket = null;               //Initiate ServerSocket to create server
    private static Socket tcpSocket = null;                        //Used to send command and receive status
    public static final int PORT = 8888;                           //Port of server
    public static StatusControl stct;
    public static CommandControl cmct;
    public static VideoControl vdct;
    public static boolean svSetting = true;
    public static boolean ffSetting = true;   
    public static int start = 0;

    /*
     * Used to start GUI and threads 
     */
    public static void main(String args[]){

        try {

            final AOC aoc = new AOC();                              //Initiate GUI aoc
            aoc.frame.pack();
            aoc.frame.setVisible(true);                             //Set components in GUI can visible   
            cmct = new CommandControl();
            aoc.frame.addKeyListener(aoc.keyListener);
            serverSocket = new ServerSocket(PORT);                  //Start server
            tcpSocket =  serverSocket.accept();                     //Wait for client connecting
            serverSocket.close();
            svSetting = true;
            aoc.lb_status.setIcon(new ImageIcon("pic\\lb_status_Green.png"));  //Set color for panel of gui when connecting successful

            StatusControl stct = new StatusControl(tcpSocket, aoc);
            stct.start();

            //Initiate thread to control command with 2 arguments TCP socket and  GUI aoc 
            cmct.setCommandSocket(tcpSocket);
            cmct.start();                                            //Start this thread.

            VideoControl vdct = new VideoControl(aoc);
            vdct.start();

            Thread alert = new Thread(){

                public void run(){

                    try {

                        while(true){

                            sleep(1000); 
                            if(svSetting){

                                aoc.lb_status.setIcon(new ImageIcon("pic\\lb_status_Green.png"));
                                svSetting = false;
                            }else{

                                aoc.lb_status.setIcon(new ImageIcon("pic\\Text_Bar_Red.png"));
                                aoc.setButtonDisable();
                                aoc.bt_start.setIcon(new ImageIcon("pic\\bt_start_Normal.png"));
                            }
                        }
                    } catch (InterruptedException ex) {

                        ex.printStackTrace();
                    }

                }
            };
            //  alert.start();
        }catch(Exception e){

            e.printStackTrace();
        }
    }
}
