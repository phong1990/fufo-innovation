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

import java.awt.EventQueue;

import javax.swing.JFrame;
import java.awt.BorderLayout;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.OverlayLayout;
import javax.swing.SwingConstants;
import java.awt.FlowLayout;
import java.awt.Component;
import java.awt.Color;
import net.miginfocom.swing.MigLayout;
import java.awt.LayoutManager;

/**
 * @author khoinguyen67
 *
 */
public class AOC {

    private JFrame frmFufo;
    private JPanel panel_1;
    private JLabel lblFramePicture;

    /**
     * Launch the application.
     */
    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    AOC window = new AOC();
                    window.frmFufo.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    /**
     * Create the application.
     */
    public AOC() {
        initialize();
    }

    /**
     * Initialize the contents of the frame.
     */
    private void initialize() {
        frmFufo = new JFrame();
        frmFufo.setTitle("FUFO");
        frmFufo.getContentPane().setBackground(Color.WHITE);
        frmFufo.setBounds(100, 100, 339, 401);
        frmFufo.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        FlowLayout flowLayout_1 = new FlowLayout(FlowLayout.CENTER, 0, 0);
        flowLayout_1.setAlignOnBaseline(true);
        frmFufo.getContentPane().setLayout(flowLayout_1);
        frmFufo.setVisible(true);
        frmFufo.setSize(340,400);
        JPanel panel = new JPanel();
        panel.setSize(320, 240);
        frmFufo.getContentPane().add(panel,BorderLayout.NORTH);
        LayoutManager overlay = new OverlayLayout(panel);
        panel.setLayout(overlay);
        JLabel lblBi = new JLabel(new ImageIcon("C:\\Users\\khoinguyen67\\Pictures\\Picture1.png")); 
   //     lblBi.setHorizontalAlignment(SwingConstants.RIGHT);
     //   lblBi.setVerticalAlignment(SwingConstants.TOP);
      //  lblBi.setBounds(250,100,10,10);
     //   lblBi.setAlignmentX(0.5f);
      //  lblBi.setAlignmentY(0.5f);
        panel.add(lblBi);
        lblFramePicture = new JLabel("");
        lblFramePicture.setBounds(0, 0, 320, 240);
       lblFramePicture.setIcon(new ImageIcon("C:\\Users\\khoinguyen67\\Dropbox\\Project\\FUFO\\Pictures2\\1009.jpg"));
        lblFramePicture.setAlignmentX(0.1f);
        lblFramePicture.setAlignmentY(0.5f);
        panel.add(lblFramePicture);

        JPanel panel_3 = new JPanel();
        FlowLayout flowLayout = (FlowLayout) panel_3.getLayout();
        flowLayout.setVgap(0);
        frmFufo.getContentPane().add(panel_3);
        
        panel_1 = new JPanel();
        panel_3.add(panel_1);
        panel_1.setLayout(new MigLayout("", "[50px][50px][50px]", "[27px][27px][27px]"));
        
        JButton btnFront = new JButton("");
        btnFront.setIcon(new ImageIcon("C:\\Users\\khoinguyen67\\Pictures\\upu.png"));
        panel_1.add(btnFront, "cell 1 0,growx,aligny top");
        
        JButton btnLeft = new JButton("");
        btnLeft.setIcon(new ImageIcon("C:\\Users\\khoinguyen67\\Pictures\\left.png"));
        panel_1.add(btnLeft, "cell 0 1,grow");
        
        JButton btnRight = new JButton("");
        btnRight.setIcon(new ImageIcon("C:\\Users\\khoinguyen67\\Pictures\\right.png"));
        panel_1.add(btnRight, "cell 2 1,grow");
        
        JButton btnBack = new JButton("");
        btnBack.setIcon(new ImageIcon("C:\\Users\\khoinguyen67\\Pictures\\downd.png"));
        panel_1.add(btnBack, "cell 1 2,growx,aligny center");
        
        JPanel panel_2 = new JPanel();
        panel_3.add(panel_2);
        
        JButton btnUp = new JButton("");
        btnUp.setAlignmentX(Component.RIGHT_ALIGNMENT);
        btnUp.setAlignmentY(Component.TOP_ALIGNMENT);
        btnUp.setIcon(new ImageIcon("C:\\Users\\khoinguyen67\\Pictures\\up.png"));
        
        JButton btnDown = new JButton("");
        btnDown.setAlignmentX(Component.RIGHT_ALIGNMENT);
        btnDown.setBackground(Color.LIGHT_GRAY);
        btnDown.setAlignmentY(Component.BOTTOM_ALIGNMENT);
        btnDown.setHorizontalAlignment(SwingConstants.TRAILING);
        btnDown.setIcon(new ImageIcon("C:\\Users\\khoinguyen67\\Pictures\\down.png"));
        btnDown.setSelectedIcon(new ImageIcon("C:\\Users\\khoinguyen67\\Pictures\\down.png"));
        btnDown.setVerticalAlignment(SwingConstants.BOTTOM);
        panel_2.setLayout(new MigLayout("", "[120px]", "[42px][42px]"));
        panel_2.add(btnUp, "cell 0 0,alignx center,aligny top");
        panel_2.add(btnDown, "cell 0 1,alignx center,aligny bottom");
        
        JPanel panel_4 = new JPanel();
        panel_4.setForeground(Color.GREEN);
        frmFufo.getContentPane().add(panel_4,BorderLayout.SOUTH);
        panel_4.setBackground(Color.GREEN);
        panel_4.setLayout(new FlowLayout(FlowLayout.CENTER, 120, 5));
       // panel_4.set
        
        JLabel lblConnectedToFufo = new JLabel("Connected to FUFO!");
        lblConnectedToFufo.setHorizontalAlignment(SwingConstants.CENTER);
        panel_4.add(lblConnectedToFufo);
    //    frmFufo.add(panel,BorderLayout.NORTH);
        
    }

    public JLabel getLblNewLabel() {
        return lblFramePicture;
    }
}
