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

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import com.mortennobel.imagescaling.ResampleOp;
import com.mortennobel.imagescaling.AdvancedResizeOp.UnsharpenMask;
/**
 * @author khoinguyen67
 *
 */
public class Test {

    /**
     * @param args
     * @throws IOException 
     */
  /*  public static void main(String[] args) throws IOException {
            File f = new File("pic\\1005.jpg");
            BufferedImage src = ImageIO.read(f);
            
            ResampleOp resampleOp = new ResampleOp (800,600);
        //    resampleOp.setUnsharpenMask(UnsharpenMask.VerySharp);
            BufferedImage rescaled = resampleOp.filter(src, null);
            
            ImageIO.write(rescaled, "JPG", 
                            new File("F:\\0776171_L77.jpg"));
    }*/
    public static void main(String[] args) throws IOException {
        int pitchAngle = 50;
        int rollAngle = 10;
        String statusMessage = null;
    statusMessage = Integer.toString(pitchAngle)+"," + Integer.toString(rollAngle) ;
    System.out.println(statusMessage);
    }
}






