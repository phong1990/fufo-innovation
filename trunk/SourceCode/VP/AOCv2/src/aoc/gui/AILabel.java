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

import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JLabel;

/**
 * @author khoinguyen67
 *
 */
public class AILabel extends JLabel {

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