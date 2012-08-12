package aoc.gui;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Point;
import java.awt.geom.AffineTransform;

/**
 * @author khoinguyen67
 * This class show methods to draw attitude indicator and height indicator on screen
 */
public class InstrumentControl {


    public void RotateImage(Graphics pe, Image img, double alpha, Point ptImg, Point ptRot, float scaleFactor)
    {
        double beta = 0;    // Angle between the Horizontal line and the line (Left upper corner - Rotation point)
        double d = 0;       // Distance between Left upper corner and Rotation point)       
        float deltaX = 0;   // X componant of the corrected translation
        float deltaY = 0;   // Y componant of the corrected translation

        // Compute the correction translation coeff
        if (ptImg != ptRot) {

            if (ptRot.x != 0) {
                beta = Math.atan((double)ptRot.y / (double)ptRot.x);
            }

            d = Math.sqrt((ptRot.x * ptRot.x) + (ptRot.y * ptRot.y));

            // Computed offset
            deltaX = (float)(d * (Math.cos(alpha - beta) - Math.cos(alpha) * Math.cos(alpha + beta) - Math.sin(alpha) * Math.sin(alpha + beta)));
            deltaY = (float)(d * (Math.sin(beta - alpha) + Math.sin(alpha) * Math.cos(alpha + beta) - Math.cos(alpha) * Math.sin(alpha + beta)));
        }

        // Rotate image support
        Graphics2D g2 = (Graphics2D) pe;        
        AffineTransform at = new AffineTransform();
        at.setToRotation(alpha);
        g2.setTransform(at);

        // Dispay image
        int x = (int)((ptImg.x + deltaX) * scaleFactor);
        int y = (int)((ptImg.y + deltaY) * scaleFactor);
        int width = (int)(img.getWidth(null) * scaleFactor);
        int height = (int)(img.getHeight(null) * scaleFactor);
        g2.drawImage(img, x, y, width, height,null);

        // Put image support as found
        at.setToRotation(-alpha);
        g2.setTransform(at);
    }

    /*  <summary>
     Translate an image on line with a specified distance and a spcified angle
     </summary>
     <param name="pe">The paint area event where the image will be displayed</param>
     <param name="img">The image to display</param>
     <param name="deltaPx">The translation distance in pixel</param>
     <param name="alpha">The angle of translation direction in radian</param>
     <param name="ptImg">The location of the left upper corner of the image to display in the paint area in nominal situation</param>
     <param name="scaleFactor">Multiplication factor on the display image</param>*/

    public void TranslateImage(Graphics pe, Image img, int deltaPx, float alpha, Point ptImg, float scaleFactor)
    {

        // Computed offset
        int deltaX = (int)(deltaPx * (Math.sin(alpha)));
        int deltaY = (int)(- deltaPx * (Math.cos(alpha)));
        int x = (int)((ptImg.x + deltaX) * scaleFactor);
        int y = (int)((ptImg.y + deltaY) * scaleFactor);
        int width = (int)(img.getWidth(null) * scaleFactor);
        int height = (int)(img.getHeight(null) * scaleFactor);
        // Dispay image
        pe.drawImage(img, x, y, width, height,null);
    }

    /*  <summary>
     Rotate an image an apply a translation on the rotated image and the display it
     </summary>
     <param name="pe">The paint area event where the image will be displayed</param>
     <param name="img">The image to display</param>
     <param name="alphaRot">The angle of rotation in radian</param>
     <param name="alphaTrs">The angle of translation direction in radian, expressed in the rotated image coordonate system</param>
     <param name="ptImg">The location of the left upper corner of the image to display in the paint area in nominal situation</param>
     <param name="ptRot">The location of the rotation point in the paint area</param>
     <param name="deltaPx">The translation distance in pixel</param>
     <param name="ptRot">The location of the rotation point in the paint area</param>
     <param name="scaleFactor">Multiplication factor on the display image</param>*/
    public void RotateAndTranslate(Graphics pe, Image img, Double alphaRot, Double alphaTrs, Point ptImg, int deltaPx, Point ptRot, float scaleFactor)
    {

        double beta = 0;
        double d = 0;
        float deltaXRot = 0;
        float deltaYRot = 0;
        float deltaXTrs = 0;
        float deltaYTrs = 0;

        // Rotation
        if (ptImg != ptRot)
        {
            // Internals coeffs
            if (ptRot.x != 0)
            {
                beta = Math.atan((double)ptRot.y / (double)ptRot.x);
            }

            d = Math.sqrt((ptRot.x * ptRot.x) + (ptRot.y * ptRot.y));

            // Computed offset
            deltaXRot = (float)(d * (Math.cos(alphaRot - beta) - Math.cos(alphaRot) * Math.cos(alphaRot + beta) - Math.sin(alphaRot) * Math.sin(alphaRot + beta)));
            deltaYRot = (float)(d * (Math.sin(beta - alphaRot) + Math.sin(alphaRot) * Math.cos(alphaRot + beta) - Math.cos(alphaRot) * Math.sin(alphaRot + beta)));
        }

        // Translation

        // Computed offset
        deltaXTrs = (float)(deltaPx * (Math.sin(alphaTrs)));
        deltaYTrs = (float)(- deltaPx * (-Math.cos(alphaTrs)));

        // Rotate image support
        Graphics2D g2 = (Graphics2D) pe;
        AffineTransform at = new AffineTransform();
        at.setToRotation(alphaRot);
        g2.setTransform(at);

        // Dispay image
        int x = (int)((ptImg.x + deltaXRot + deltaXTrs) * scaleFactor);
        int y = (int)((ptImg.y + deltaYRot + deltaYTrs) * scaleFactor);
        int width = (int)(img.getWidth(null) * scaleFactor);
        int height = (int)(img.getHeight(null) * scaleFactor);
        g2.drawImage(img, x, y, width, height,null);

        // Put image support as found
        at.setToRotation(-alphaRot);
        g2.setTransform(at);
    }
}
