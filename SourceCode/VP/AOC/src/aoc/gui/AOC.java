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
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;

import net.miginfocom.swing.MigLayout;
import java.awt.LayoutManager;
import java.awt.geom.Line2D;

/**
 * This class is used to create GUI.
 * 
 * @author khoinguyen67
 */
public class AOC {

    public static JFrame frmFufo;
    public JPanel panel_1;
    public static JLabel lblFramePicture;
    public JLabel lblConnectedToFufo;
    public JPanel panel_4;
    public byte command;
    public int key;
    public ImageIcon imic;
    public static ControlPanel panel;
    /**
     * Create the application.
     */
    public AOC() {

        frmFufo = new JFrame();
        frmFufo.setTitle("FUFO");
        frmFufo.getContentPane().setBackground(Color.WHITE);
        frmFufo.setBounds(100, 100, 339, 401);
        frmFufo.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        FlowLayout flowLayout_1 = new FlowLayout(FlowLayout.CENTER, 0, 0);
        // flowLayout_1.setAlignOnBaseline(true);
        frmFufo.getContentPane().setLayout(flowLayout_1);
        // frmFufo.setVisible(true);
        frmFufo.setSize(340, 405);

        panel = new ControlPanel();
        panel.setSize(320, 240);
        frmFufo.getContentPane().add(panel, BorderLayout.NORTH);
        LayoutManager overlay = new OverlayLayout(panel);
        panel.setLayout(overlay);

        JLabel lblBi = new JLabel(new ImageIcon("pic\\Picture1.png"));
        panel.add(lblBi);
        lblFramePicture = new JLabel("");
        // lblFramePicture.setBounds(0, 0, 320, 240);
        imic = new ImageIcon("pic\\1009.jpg");
        lblFramePicture.setIcon(imic);
        lblFramePicture.setAlignmentX(0.5f);
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
        btnFront.setIcon(new ImageIcon("pic\\upu.png"));
        panel_1.add(btnFront, "cell 1 0,growx,aligny top");

        JButton btnLeft = new JButton("");
        btnLeft.setIcon(new ImageIcon("pic\\left.png"));
        panel_1.add(btnLeft, "cell 0 1,grow");

        JButton btnRight = new JButton("");
        btnRight.setIcon(new ImageIcon("pic\\right.png"));
        panel_1.add(btnRight, "cell 2 1,grow");

        JButton btnBack = new JButton("");
        btnBack.setIcon(new ImageIcon("pic\\downd.png"));
        panel_1.add(btnBack, "cell 1 2,growx,aligny center");

        JPanel panel_2 = new JPanel();
        panel_3.add(panel_2);

        JButton btnUp = new JButton("");
        btnUp.setAlignmentX(Component.RIGHT_ALIGNMENT);
        btnUp.setAlignmentY(Component.TOP_ALIGNMENT);
        btnUp.setIcon(new ImageIcon("pic\\up.png"));

        JButton btnDown = new JButton("");
        btnDown.setAlignmentX(Component.RIGHT_ALIGNMENT);
        btnDown.setAlignmentY(Component.BOTTOM_ALIGNMENT);
        btnDown.setIcon(new ImageIcon("pic\\down.png"));

        panel_2.setLayout(new MigLayout("", "[120px]", "[42px][42px]"));
        panel_2.add(btnUp, "cell 0 0,alignx center,aligny top");
        panel_2.add(btnDown, "cell 0 1,alignx center,aligny bottom");

        panel_4 = new JPanel();
        frmFufo.getContentPane().add(panel_4, BorderLayout.SOUTH);
        panel_4.setBackground(Color.RED);
        panel_4.setLayout(new FlowLayout(FlowLayout.CENTER, 160, 5));

        lblConnectedToFufo = new JLabel("Disconnected!");
        lblConnectedToFufo.setHorizontalAlignment(SwingConstants.CENTER);
        panel_4.add(lblConnectedToFufo);
        frmFufo.setVisible(true);
    }
    public void paint(Graphics g) {

        Line2D line1 = new Line2D.Double(0, 0, 200, 200);

        Graphics2D graph = (Graphics2D) g;
        graph.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        graph.dispose();
        System.out.println("in duong thang");
        graph.setPaintMode();
        graph.setPaint(Color.green);
        graph.draw(line1);
        frmFufo.setVisible(true);
        System.out.print("in duong thang xong");
        g.drawLine(10, 20, 300, 310);

        
          Graphics g2 = AOC.panel.getGraphics(); g.setColor(Color.RED); g.drawLine(0,0,200,200);
          AOC.panel.setVisible(true); AOC.frmFufo.setVisible(true);
          
         System.out.print("in duong thang xong");
         
    }

    /*
     * public static void main(String[] args) { AOC aoc = new AOC(); aoc.frmFufo.setVisible(true);
     * aoc.frmFufo.addKeyListener(aoc); }
     */

    public class ControlPanel extends JPanel {

        @Override
        public void paint(Graphics g) {
            super.paint(g);
            Line2D line1 = new Line2D.Double(100, 120, 220, 120);
            Graphics2D graph = (Graphics2D) g;
            graph.setPaint(Color.green);
            graph.draw(line1);
        }
    }
}