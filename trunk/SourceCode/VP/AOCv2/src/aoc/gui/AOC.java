package aoc.gui;

import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Point;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JOptionPane;
import aoc.control.Control;

/**
 * @author khoinguyen67
 * This class uses to create new Graphic User Interface 
 * for Application On Computer. It also Key Listener and Mouse Listener
 * to monitor behavior of user
 */
public class AOC{

    public JFrame frame;                   //Initiate main frame 
    JLayeredPane pane;                     //Pane contains all component of GUI  
    public JLabel lb_background;           //Set image background by this label
    public JLabel lb_circle;               //Use to check time to send y signal to AOP 
    public JLabel lb_status;               //This label checks connection status of system 
    public JLabel lb_picture;              //Video frame streamed from AOP
    public JLabel lb_setPoint;             //Height that user want 
    public JLabel lb_text;                 //Text in label status 
    public AILabel lb_ai;                  //Attitude indicator
    public HeightLabel lb_height;          //Height indicator 
    public JButton bt_start;               //Button start  
    public JButton bt_right;               //Button right
    public JButton bt_left;                //Button left
    public JButton bt_forward;             //Button forward
    public JButton bt_backward;            //Button backward 
    public JButton bt_up;                  //Button up
    public JButton bt_down;                //Button down
    public JButton bt_rotateLeft;          //Button rotate left 
    public JButton bt_rotateRight;         //Button rotate right
    public JButton bt_exit;                //Button exit    
    public JButton bt_minimize;            //Button minimize 
    //   JPanel panel;                          //panel used to move frame by mouse 
    //  int flag = 0;                          //Initiate pane to contain component         
    public boolean firstUP = true;
    /*
     * Constructor to initiate AOC
     */
    public AOC(){

        frame = new JFrame();
        frame.setSize(1240 , 690);
        frame.setUndecorated(true);                             //Remove title bar of main frame
        //   frame.setBackground(new Color(0, 0, 0, 0));             //Set transparent for frame
        frame.setTitle("FUFO APP");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setVisible(true);
        pane = new JLayeredPane();
        pane.setPreferredSize(new Dimension(1240 , 690));

        lb_background = new JLabel(new ImageIcon("pic\\interface.png"));
        pane.add(lb_background,1);
        lb_background.setBounds(0, 0, 1240 , 690);

        MoveMouseListener mml = new MoveMouseListener(pane);
        pane.addMouseListener(mml);
        pane.addMouseMotionListener(mml);

        try {

            lb_ai = new AILabel();
            lb_height = new HeightLabel();
        } catch (IOException ex) {

            ex.printStackTrace();
        }

        pane.add(lb_ai, 2);
        pane.add(lb_height, 2);

        lb_setPoint = new JLabel();
        lb_setPoint.setText("0.0");
        lb_setPoint.setFont(new Font("Serif", Font.BOLD, 33));
        pane.add(lb_setPoint, 2);
        lb_setPoint.setBounds(1170, 302,60 , 30);

        lb_circle = new JLabel(new ImageIcon("pic\\Altitude_Indicator.png"));
        pane.add(lb_circle,0);
        lb_circle.setBounds(10, 150,200, 200);

        lb_status = new JLabel(new ImageIcon("pic\\Text_Bar_Red.png"));
        pane.add(lb_status,0);
        lb_status.setBounds(220, 630, 800, 50);

        lb_text = new JLabel();
        //  lb_text.setText("Wait connect from Application on Phone!");
        lb_text.setBounds(420, 630, 800, 50);
        lb_text.setFont(new Font("Serif", Font.BOLD, 20));
        //   lb_text.setForeground(Color.WHITE);
        pane.add(lb_text,0);


        lb_picture = new JLabel(new ImageIcon("pic\\1009.jpg"));
        pane.add(lb_picture,0);
        lb_picture.setBounds(220, 10, 800, 600);

        bt_start = createButton("bt_start", "pic\\bt_start_Normal.png", 60 , 570, 100 ,100);
        bt_right = createButton("bt_right","pic\\bt_right_Disable.png", 1160 , 110, 65 ,65);       
        bt_left = createButton("bt_left","pic\\bt_left_Disable.png", 1060 , 110, 65 ,65);       
        bt_forward = createButton("bt_forward","pic\\bt_forward_Disable.png", 1110 , 55, 65 ,65);       
        bt_backward = createButton("bt_backward","pic\\bt_backward_Disable.png", 1110, 160, 65, 65);
        bt_up = createButton("bt_up","pic\\bt_up_Disable.png", 1105, 315, 60, 80);
        bt_down = createButton("bt_down","pic\\bt_down_Disable.png", 1105, 435, 60, 80);
        bt_rotateLeft = createButton("bt_rotateLeft","pic\\bt_rotateLeft_Disable.png", 1050, 380, 60, 60);
        bt_rotateRight = createButton("bt_rotateRight","pic\\bt_rotateRight_Disable.png", 1165, 380, 60, 60);
        bt_minimize =  createButton("bt_minimize","pic\\bt_minimize_Normal.png", 1135, 10, 40, 40);
        bt_exit =  createButton("bt_exit","pic\\bt_exit_Normal.png", 1185, 10, 40, 40);
        frame.add(pane);  

        try {

            frame.setIconImage(ImageIO.read(new File("pic\\bt_exit_Normal.png")));
        } catch (IOException ex1) {

            ex1.printStackTrace();
        }
    }

    /*
     * This method is used to create a button in frame base on position, path of icon button
     */
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

    /*
     * This class is extended JLabel uses to override method paintComponent to draw attitude indicator.
     */
    /*    public class AILabel extends JLabel {

        private static final long serialVersionUID = 1L;
        Image image;
        public double PitchAngle = 0;   // Phi
        public double RollAngle = 0;    // Theta

        public AILabel() throws IOException{

            image = ImageIO.read(new File("pic\\ai3.png"));
            this.setBounds(30, 16,163, 330);
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

    public class HeightLabel extends JLabel {

        private static final long serialVersionUID = 1L;
        Image image;
        public double PitchAngle = 0;   // Phi
        public double RollAngle = 0;    // Theta

        public HeightLabel() throws IOException{

            image = ImageIO.read(new File("pic\\Height_Ruler.png"));
            this.setBounds(60, -4600,100, 5200);
        }

        @Override
        public void paintComponent(Graphics g) {

            Point ptBoule = new Point(60, -4600);
            Point ptRotation = new Point(110, 5200);
            InstrumentControl is = new InstrumentControl();
            is.RotateAndTranslate(g, image, RollAngle, (double) 0, ptBoule, 
                    (int)(PitchAngle*5200/104), ptRotation, 1);
        }
    }*/

    public KeyListener keyListener = new KeyListener() {

        @Override
        public void keyTyped(KeyEvent arg0) {
            // TODO Auto-generated method stub

        }

        @Override
        public void keyReleased(KeyEvent arg0) {

            if(Control.ffSetting && Control.svSetting && Control.start == 1){

                int command = arg0.getKeyCode();           //Get key code of pressed key
                Control.cmct.setCommand(KeyEvent.VK_R);
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
            } 
        }

        @Override
        public void keyPressed(KeyEvent arg0) {

            if(Control.ffSetting && Control.svSetting && Control.start == 1){

                int command = arg0.getKeyCode();                //Get key code of pressed key

                if(command != KeyEvent.VK_ENTER)
                    Control.cmct.setCommand(command);               //Send command to phone via TCP socket

                switch(command){

                    case KeyEvent.VK_RIGHT:
                        bt_rotateRight.setIcon(new ImageIcon("pic\\bt_rotateRight_Clicked.png"));
                        break;

                    case KeyEvent.VK_LEFT:
                        bt_rotateLeft.setIcon(new ImageIcon("pic\\bt_rotateLeft_Clicked.png"));
                        break;

                    case KeyEvent.VK_UP:
                        bt_up.setIcon(new ImageIcon("pic\\bt_up_Clicked.png"));
                        if(firstUP){
                            lb_height.setPoint = 1;
                            firstUP = false;
                        }else{
                            if(lb_height.setPoint <= 98.5)

                                lb_height.setPoint += 0.25;
                        }
                        lb_setPoint.setText(Double.toString(lb_height.setPoint));
                       // frame.repaint();
                        break;

                    case KeyEvent.VK_DOWN:
                        bt_down.setIcon(new ImageIcon("pic\\bt_down_Clicked.png"));
                        if(lb_height.setPoint >= 0.25)

                            lb_height.setPoint -= 0.25;

                        lb_setPoint.setText(Double.toString(lb_height.setPoint));
                       // frame.repaint();
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
        }
    };

    MouseListener mouseListener = new MouseListener() {

        @Override
        public void mousePressed(MouseEvent e) {

            JButton button = (JButton)e.getComponent();

            if(button == bt_exit || button == bt_minimize)

                button.setIcon(new ImageIcon("pic\\"
                        + e.getComponent().getName()+"_Clicked.png"));

            if(Control.ffSetting && Control.svSetting && Control.start == 1){

                button.setIcon(new ImageIcon("pic\\"
                        + e.getComponent().getName()+"_Clicked.png"));

                if(button == bt_backward){

                    Control.cmct.setCommand(KeyEvent.VK_S);
                }else if(button == bt_forward){

                    Control.cmct.setCommand(KeyEvent.VK_W);
                }else if(button == bt_left){

                    Control.cmct.setCommand(KeyEvent.VK_A);
                }else if(button == bt_right){

                    Control.cmct.setCommand(KeyEvent.VK_D);
                }else if(button == bt_down){

                    if(lb_height.setPoint >= 0.5)

                        lb_height.setPoint -= 0.5;

                    lb_setPoint.setText(Double.toString(lb_height.setPoint));
                    frame.repaint();
                    Control.cmct.setCommand(KeyEvent.VK_DOWN);
                }else if(button == bt_up){

                    if(lb_height.setPoint <= 98.5)

                        lb_height.setPoint += 0.5;

                    lb_setPoint.setText(Double.toString(lb_height.setPoint));
                    frame.repaint();
                    Control.cmct.setCommand(KeyEvent.VK_UP);
                }else if(button == bt_rotateLeft){

                    Control.cmct.setCommand(KeyEvent.VK_LEFT);
                }else if(button == bt_rotateRight){

                    Control.cmct.setCommand(KeyEvent.VK_RIGHT);
                }
            }

            if(button == bt_start){

                if(Control.ffSetting && Control.svSetting){

                    Control.cmct.setCommand(KeyEvent.VK_ENTER);

                    if(Control.start == 0){

                        Control.start = 1;
                        bt_start.setIcon(new ImageIcon("pic\\bt_start_Clicked.png"));
                        bt_rotateRight.setIcon(new ImageIcon("pic\\bt_rotateRight_Normal.png"));
                        bt_rotateLeft.setIcon(new ImageIcon("pic\\bt_rotateLeft_Normal.png"));
                        bt_up.setIcon(new ImageIcon("pic\\bt_up_Normal.png"));
                        bt_down.setIcon(new ImageIcon("pic\\bt_down_Normal.png"));
                        bt_right.setIcon(new ImageIcon("pic\\bt_right_Normal.png"));
                        bt_left.setIcon(new ImageIcon("pic\\bt_left_Normal.png"));
                        bt_forward.setIcon(new ImageIcon("pic\\bt_forward_Normal.png"));
                        bt_backward.setIcon(new ImageIcon("pic\\bt_backward_Normal.png"));
                    } else {

                        Control.start = 0;
                        bt_start.setIcon(new ImageIcon("pic\\bt_stop_Clicked.png"));
                        bt_rotateRight.setIcon(new ImageIcon("pic\\bt_rotateRight_Disable.png"));
                        bt_rotateLeft.setIcon(new ImageIcon("pic\\bt_rotateLeft_Disable.png"));
                        bt_up.setIcon(new ImageIcon("pic\\bt_up_Disable.png"));
                        bt_down.setIcon(new ImageIcon("pic\\bt_down_Disable.png"));
                        bt_right.setIcon(new ImageIcon("pic\\bt_right_Disable.png"));
                        bt_left.setIcon(new ImageIcon("pic\\bt_left_Disable.png"));
                        bt_forward.setIcon(new ImageIcon("pic\\bt_forward_Disable.png"));
                        bt_backward.setIcon(new ImageIcon("pic\\bt_backward_Disable.png"));

                    }
                } else if( Control.svSetting == false){

                    frame.repaint();
                    JOptionPane.showMessageDialog(frame, "Please check connection with Appplication on Android!",
                            "Connection error", JOptionPane.ERROR_MESSAGE);
                }else{

                    frame.repaint();
                    JOptionPane.showMessageDialog(frame, "Please check connection with FUFO!",
                            "Connection error", JOptionPane.ERROR_MESSAGE);

                }
            }
            frame.repaint();
        }

        @Override
        public void mouseReleased(MouseEvent e) {

            JButton button = (JButton) e.getComponent();

            if(button == bt_exit){ 

                frame.dispose();
                System.exit(0);
            }

            if(button == bt_minimize) frame.setState ( Frame.ICONIFIED );
            if(Control.cmct != null)
                Control.cmct.setCommand(KeyEvent.VK_R);
            if(Control.ffSetting && Control.svSetting &&Control.start == 1){

                ((JButton) e.getComponent()).setIcon(new ImageIcon("pic\\"
                        + e.getComponent().getName()+"_Normal.png"));
                bt_start.setIcon(new ImageIcon("pic\\bt_stop_Normal.png"));
            }

            if(Control.start == 0){

                bt_start.setIcon(new ImageIcon("pic\\bt_start_Normal.png"));
            }
            frame.repaint();
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
    public void setButtonDisable(){

        Control.start = 0;
        bt_rotateRight.setIcon(new ImageIcon("pic\\bt_rotateRight_Disable.png"));
        bt_rotateLeft.setIcon(new ImageIcon("pic\\bt_rotateLeft_Disable.png"));
        bt_up.setIcon(new ImageIcon("pic\\bt_up_Disable.png"));
        bt_down.setIcon(new ImageIcon("pic\\bt_down_Disable.png"));
        bt_right.setIcon(new ImageIcon("pic\\bt_right_Disable.png"));
        bt_left.setIcon(new ImageIcon("pic\\bt_left_Disable.png"));
        bt_forward.setIcon(new ImageIcon("pic\\bt_forward_Disable.png"));
        bt_backward.setIcon(new ImageIcon("pic\\bt_backward_Disable.png"));
    }
}


class MoveMouseListener implements MouseListener, MouseMotionListener {

    JComponent target;
    Point start_drag;
    Point start_loc;

    public MoveMouseListener(JComponent target) {

        this.target = target;
    }

    public JFrame getFrame(Container target) {

        if (target instanceof JFrame) {

            return (JFrame) target;
        }
        return getFrame(target.getParent());
    }

    Point getScreenLocation(MouseEvent e) {

        Point cursor = e.getPoint();
        Point target_location = this.target.getLocationOnScreen();
        return new Point((int) (target_location.getX() + cursor.getX()),
                (int) (target_location.getY() + cursor.getY()));
    }

    public void mouseClicked(MouseEvent e) {
    }

    public void mouseEntered(MouseEvent e) {
    }

    public void mouseExited(MouseEvent e) {
    }

    public void mousePressed(MouseEvent e) {

        this.start_drag = this.getScreenLocation(e);
        this.start_loc = this.getFrame(this.target).getLocation();
    }

    public void mouseReleased(MouseEvent e) {
    }

    public void mouseDragged(MouseEvent e) {

        Point current = this.getScreenLocation(e);
        Point offset = new Point((int) current.getX() - (int) start_drag.getX(),
                (int) current.getY() - (int) start_drag.getY());
        JFrame frame = this.getFrame(target);
        Point new_location = new Point(
                (int) (this.start_loc.getX() + offset.getX()), (int) (this.start_loc
                        .getY() + offset.getY()));
        frame.setLocation(new_location);
        frame.repaint();
    }

    public void mouseMoved(MouseEvent e) {
    }
}