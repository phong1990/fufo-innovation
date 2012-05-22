
/**
 * @author khoinguyen67
 *
 */
package aoc.video;
//Server

import java.io.IOException;
import java.net.*;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class ServerTest {
    static ImageIcon icon;
    static JFrame frame = new JFrame("Client");
    static JLabel iconLabel ;
    private static void createAndShowGUI() throws IOException {
        //Create and set up the window.
        
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       
      
         iconLabel = new JLabel();
        icon = new ImageIcon("F://489.jpg");
        iconLabel.setIcon(icon);
        frame.getContentPane().add(iconLabel);
        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args)
    {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                try {
                    createAndShowGUI();
                } catch (IOException ex) {
                    // TODO Auto-generated catch block
                    ex.printStackTrace();
                }
            }
        });
    
        try
        {
            byte[] buf;
            DatagramSocket sckReceiver = new DatagramSocket(4444);
            DatagramPacket pktReceiver ;
  //          String path = "D:\\FUFO\\Pictures2\\";
            int fileNum = 0;
            while(true)
            {   
                ++fileNum;
                buf = new byte[15000];
                pktReceiver = new DatagramPacket(buf, buf.length);
                System.out.println("dang doi packet");
                sckReceiver.receive(pktReceiver);
                System.out.println("da nhan packet");
                long time1 = System.currentTimeMillis();
                System.out.println("After receive: " + time1);
                icon = new ImageIcon(buf);
                iconLabel.setIcon(icon);
                frame.getContentPane().add(iconLabel);
                long time2 = System.currentTimeMillis();
                System.out.println("After view " + fileNum + " : " + System.currentTimeMillis());
                System.out.println("Time cost: " + (time2 - time1));
/*                fos = new FileOutputStream(path + fileNum +".jpg");
                fos.write(buf);
                fos.close();*/
            }
            
         
        }catch(Exception e)
        {
            e.printStackTrace();
        }
    }
}