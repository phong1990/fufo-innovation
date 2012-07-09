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
package aoc.gui;

import java.awt.Dimension;
import java.awt.Image;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.AbstractButton;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JPanel;

/**
 * @author khoinguyen67
 *
 */
public class NewGUI {
    JFrame frame;
    JLayeredPane pane;
    JLabel lb_background, lb_circle, lb_status, lb_picture, lb_ai;
    JButton bt_start, bt_right, bt_left, bt_forward, bt_backward, 
            bt_up, bt_down, bt_rotateLeft, bt_rotateRight;
    JPanel panel;
    public NewGUI(){
       frame = new JFrame();
       frame.setSize(1240 , 690);
       frame.setTitle("FUFO APP");
       
       pane = new JLayeredPane();
       pane.setPreferredSize(new Dimension(1240 , 690));
       
       lb_background = new JLabel(new ImageIcon("pic\\interface.png"));
       pane.add(lb_background,1);
       lb_background.setBounds(0, 0, 1240 , 690);
       
      
       
       lb_ai = new JLabel(new ImageIcon("pic\\ai2.png"));
       pane.add(lb_ai,0);
       lb_ai.setBounds(10, 150,200, 200);
       
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
       bt_right = createButton("bt_right","pic\\bt_right_Normal.png", 1160 , 110, 65 ,65);       
       bt_left = createButton("bt_left","pic\\bt_left_Normal.png", 1060 , 110, 65 ,65);       
       bt_forward = createButton("bt_forward","pic\\bt_forward_Normal.png", 1110 , 55, 65 ,65);       
       bt_backward = createButton("bt_backward","pic\\bt_backward_Normal.png", 1110, 160, 65, 65);
       bt_up = createButton("bt_up","pic\\bt_up_Normal.png", 1105, 315, 60, 80);
       bt_down = createButton("bt_down","pic\\bt_down_Normal.png", 1105, 435, 60, 80);
       bt_rotateLeft = createButton("bt_rotateLeft","pic\\bt_rotateLeft_Normal.png", 1050, 380, 60, 60);
       bt_rotateRight = createButton("bt_rotateRight","pic\\bt_rotateRight_Normal.png", 1165, 380, 60, 60);
       frame.add(pane);
       
    
       
    }
    MouseListener listener = new MouseListener() {
        
        @Override
        public void mousePressed(MouseEvent e) {
            // TODO Auto-generated method stub

            ((JButton) e.getComponent()).setIcon(new ImageIcon("pic\\"
                                    + e.getComponent().getName()+"_Clicked.png"));

        }
        
        @Override
        public void mouseReleased(MouseEvent e) {
            // TODO Auto-generated method stub
            ((JButton) e.getComponent()).setIcon(new ImageIcon("pic\\"
                                    + e.getComponent().getName()+"_Normal.png"));

        //    bt_start.setIcon(new ImageIcon("pic\\bt_start_Normal.png"));
        // bt_start.repaint( 60 , 450, 100 ,100);
      //      bt_start.repaint( bt_start.getBounds());
       //   System.out.println(bt_start.getB);

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
    public JButton createButton(String text, String path, int x, int y, int width, int height){
        JButton button = new JButton( new ImageIcon(path));
        pane.add(button, 0);
        button.setName(text);
        button.setBounds(x , y, width , height);
        button.setContentAreaFilled(false);
        button.setBorder(BorderFactory.createEmptyBorder());
        button.addMouseListener(listener);
        return button;
    }
    public static void main(String arg[]){
        NewGUI gui = new NewGUI();
     /*   //Create and set up the content pane.
        JComponent newContentPane = new LayeredPaneDemo();
        newContentPane.setOpaque(true); //content panes must be opaque
        gui.frame.setContentPane(newContentPane);*/
        gui.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        gui.frame.pack();
        gui.frame.setVisible(true);
    }
    
    
}
