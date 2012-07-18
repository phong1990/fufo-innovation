package aoc.gui;

import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import aoc.control.Control;

/**
 * @author khoinguyen67
 *
 */
public class AOC{

    public JFrame frame;
    JLayeredPane pane;
    public JLabel lb_background, lb_circle, lb_status, lb_picture;
    public AILabel lb_ai;
    public JButton bt_start, bt_right, bt_left, bt_forward, bt_backward, 
    bt_up, bt_down, bt_rotateLeft, bt_rotateRight;
    JPanel panel;
    int flag = 0;

    public AOC(){

        frame = new JFrame();
        frame.setSize(1240 , 690);
        frame.setTitle("FUFO APP");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setVisible(true);
        pane = new JLayeredPane();
        pane.setPreferredSize(new Dimension(1240 , 690));
        lb_background = new JLabel(new ImageIcon("pic\\interface.png"));
        pane.add(lb_background,1);
        lb_background.setBounds(0, 0, 1240 , 690);

        try {
            lb_ai = new AILabel();
        } catch (IOException ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }

        pane.add(lb_ai,2);
        lb_circle = new JLabel(new ImageIcon("pic\\Altitude_Indicator.png"));
        pane.add(lb_circle,0);
        lb_circle.setBounds(10, 150,200, 200);

        lb_status = new JLabel(new ImageIcon("pic\\Text_Bar_Red.png"));
        pane.add(lb_status,0);
        lb_status.setBounds(220, 630, 800, 50);

        lb_picture = new JLabel(new ImageIcon("pic\\1009.jpg"));
        pane.add(lb_picture,0);
        lb_picture.setBounds(220, 10, 800, 600);

        bt_start = createButton("bt_start", "pic\\bt_start_Normal.png", 60 , 450, 100 ,100);
        bt_right = createButton("bt_right","pic\\bt_right_Disable.png", 1160 , 110, 65 ,65);       
        bt_left = createButton("bt_left","pic\\bt_left_Disable.png", 1060 , 110, 65 ,65);       
        bt_forward = createButton("bt_forward","pic\\bt_forward_Disable.png", 1110 , 55, 65 ,65);       
        bt_backward = createButton("bt_backward","pic\\bt_backward_Disable.png", 1110, 160, 65, 65);
        bt_up = createButton("bt_up","pic\\bt_up_Disable.png", 1105, 315, 60, 80);
        bt_down = createButton("bt_down","pic\\bt_down_Disable.png", 1105, 435, 60, 80);
        bt_rotateLeft = createButton("bt_rotateLeft","pic\\bt_rotateLeft_Disable.png", 1050, 380, 60, 60);
        bt_rotateRight = createButton("bt_rotateRight","pic\\bt_rotateRight_Disable.png", 1165, 380, 60, 60);
        bt_start.setEnabled(false);
        frame.add(pane);      

    }


    public JButton createButton(String text, String path, int x, int y, int width, int height){

        JButton button = new JButton( new ImageIcon(path));
        pane.add(button, 0);
        button.setName(text);
        button.setBounds(x , y, width , height);
        button.setContentAreaFilled(false);
        button.setBorder(BorderFactory.createEmptyBorder());
        button.addMouseListener(mouseListener);
        button.addKeyListener(keyListener);
        return button;
    }

    public class AILabel extends JLabel {

        /**  . */
        private static final long serialVersionUID = 1L;
        Image image;
        public double PitchAngle = 0;   // Phi
        public double RollAngle = 0;    // Theta

        public AILabel() throws IOException{

            image = ImageIO.read(new File("pic\\ai3.png"));
            this.setBounds(30, 16,163, 468);
        }

        @Override
        public void paintComponent(Graphics g) {

            Point ptBoule = new Point(30, 16);
            Point ptRotation = new Point(110, 250);
            InstrumentControl is = new InstrumentControl();
            is.RotateAndTranslate(g, image, RollAngle, (double) 0, ptBoule, 
                    (int)(PitchAngle*468/180), ptRotation, 1);
        }
    }

    public KeyListener keyListener = new KeyListener() {

        @Override
        public void keyTyped(KeyEvent arg0) {
            // TODO Auto-generated method stub

        }

        @Override
        public void keyReleased(KeyEvent arg0) {

            // TODO Auto-generated method stub
           
            if(Control.ffSetting && Control.svSetting){
                
                int command = arg0.getKeyCode();           //Get key code of pressed key
                switch(command){

                    case KeyEvent.VK_RIGHT:
                        bt_rotateRight.setIcon(new ImageIcon("pic\\bt_rotateRight_Normal.png"));
                        break;

                    case KeyEvent.VK_LEFT:
                        bt_rotateLeft.setIcon(new ImageIcon("pic\\bt_rotateLeft_Normal.png"));
                        break;

                    case KeyEvent.VK_UP:
                        bt_up.setIcon(new ImageIcon("pic\\bt_up_Normal.png"));
                        break;

                    case KeyEvent.VK_DOWN:
                        bt_down.setIcon(new ImageIcon("pic\\bt_down_Normal.png"));
                        break;

                    case KeyEvent.VK_D:
                        bt_right.setIcon(new ImageIcon("pic\\bt_right_Normal.png"));
                        break;

                    case KeyEvent.VK_A:
                        bt_left.setIcon(new ImageIcon("pic\\bt_left_Normal.png"));
                        break;

                    case KeyEvent.VK_W:
                        bt_forward.setIcon(new ImageIcon("pic\\bt_forward_Normal.png"));
                        break;

                    case KeyEvent.VK_S:
                        bt_backward.setIcon(new ImageIcon("pic\\bt_backward_Normal.png"));
                        break; 
                }
            } else{
                
                JOptionPane.showMessageDialog(frame, "Please check connection!",
                        "Connection error", JOptionPane.ERROR_MESSAGE);
            }

        }

        @Override
        public void keyPressed(KeyEvent arg0) {

            int command = arg0.getKeyCode();           //Get key code of pressed key
            Control.cmct.setCommand(command);               //Send command to phone via TCP socket
            System.out.println(command);
            if(Control.ffSetting && Control.svSetting)
            switch(command){
                case KeyEvent.VK_RIGHT:
                    bt_rotateRight.setIcon(new ImageIcon("pic\\bt_rotateRight_Clicked.png"));
                    break;
                case KeyEvent.VK_LEFT:
                    bt_rotateLeft.setIcon(new ImageIcon("pic\\bt_rotateLeft_Clicked.png"));
                    break;
                case KeyEvent.VK_UP:
                    bt_up.setIcon(new ImageIcon("pic\\bt_up_Clicked.png"));
                    break;
                case KeyEvent.VK_DOWN:
                    bt_down.setIcon(new ImageIcon("pic\\bt_down_Clicked.png"));
                    break;
                case KeyEvent.VK_D:
                    bt_right.setIcon(new ImageIcon("pic\\bt_right_Clicked.png"));
                    break;
                case KeyEvent.VK_A:
                    bt_left.setIcon(new ImageIcon("pic\\bt_left_Clicked.png"));
                    break;
                case KeyEvent.VK_W:
                    bt_forward.setIcon(new ImageIcon("pic\\bt_forward_Clicked.png"));
                    break;
                case KeyEvent.VK_S:
                    bt_backward.setIcon(new ImageIcon("pic\\bt_backward_Clicked.png"));
                    break;
            }

        }
    };

    MouseListener mouseListener = new MouseListener() {

        @Override
        public void mousePressed(MouseEvent e) {
            // TODO Auto-generated method stub

            ((JButton) e.getComponent()).setIcon(new ImageIcon("pic\\"
                    + e.getComponent().getName()+"_Clicked.png"));
            JButton button = (JButton)e.getComponent();

            if(button == bt_backward){

                Control.cmct.setCommand(KeyEvent.VK_S);
            }else if(button == bt_forward){

                Control.cmct.setCommand(KeyEvent.VK_W);
            }else if(button == bt_left){

                Control.cmct.setCommand(KeyEvent.VK_A);
            }else if(button == bt_right){

                Control.cmct.setCommand(KeyEvent.VK_D);
            }else if(button == bt_down){

                Control.cmct.setCommand(KeyEvent.VK_DOWN);
            }else if(button == bt_up){

                Control.cmct.setCommand(KeyEvent.VK_UP);
            }else if(button == bt_rotateLeft){

                Control.cmct.setCommand(KeyEvent.VK_LEFT);
            }else if(button == bt_rotateRight){

                Control.cmct.setCommand(KeyEvent.VK_RIGHT);
            }else if(button == bt_start){

                Control.cmct.setCommand(KeyEvent.VK_F);
            }
        }

        @Override
        public void mouseReleased(MouseEvent e) {

            // TODO Auto-generated method stub
            ((JButton) e.getComponent()).setIcon(new ImageIcon("pic\\"
                    + e.getComponent().getName()+"_Normal.png"));

        }

        @Override
        public void mouseExited(MouseEvent arg0) {
            // TODO Auto-generated method stub

        }

        @Override
        public void mouseEntered(MouseEvent arg0) {
            // TODO Auto-generated method stub

        }

        @Override
        public void mouseClicked(MouseEvent arg0) {
            // TODO Auto-generated method stub

        }
    };
}
