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
package aoc.video;

import java.net.DatagramPacket;

/**
 * @author khoinguyen67
 */
public class UDPpackage {

    DatagramPacket udpPackage;
    static int pacNum = -128;
    byte[] frameBuffer = new byte[15000];
    byte[] pacBuffer = new byte[15001];
    static byte test;

    public UDPpackage() {
    }

    public UDPpackage(DatagramPacket udpPackage) {
        this.udpPackage = udpPackage;
    }

    /*
     * public static void main(String arg[]){
     * 
     * UDPpackage upk = new UDPpackage(); upk.setPackage(-124); upk.getPacNum(upk.pacBuffer);
     * 
     * 
     * }
     */
    public void setPackage(int pacNum) {

        Integer in = new Integer(pacNum);
        test = in.byteValue();
        System.out.println(frameBuffer.length);
        byte[] temp = new byte[4];
        temp[0] = test;
        System.arraycopy(frameBuffer, 0, pacBuffer, 0, frameBuffer.length);
        System.arraycopy(temp, 0, pacBuffer, 15000, 1);
    }

    public void getPacNum(byte[] pacBuffer) {

        Byte test = new Byte(pacBuffer[15000]);
        pacNum = test.intValue();
        System.out.println(pacNum);
    }

    public void getFrameBuffer(byte[] pacBuffer) {

    }

}
