package aop.control;

import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.util.UUID;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

/**
 * @author khoinguyen67
 *
 */
public class SettingActivity extends Activity{

    Socket tcpSocket ;
    String ipServer, addressBlueTooth;
    public static InetAddress serverAddr;
    String  LOG_TAG  = "FUFO";
    final int REQUEST_CONNECT_DEVICE  = 1,
    REQUEST_ENABLE_BT       = 2;

    BluetoothDevice   bluetoothDevice;
    BluetoothAdapter  bluetoothAdapter;
    BluetoothSocket   bluetoothSocket;         
    private static final UUID SPP_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    Button bt_connectSV, bt_connectFF;
    EditText et_ipServer, et_addressBluetooth;
    TextView tv_statusSV, tv_statusFF;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tab_setting);

        bt_connectSV = (Button)findViewById(R.id.bt_ConnectSV);
        bt_connectFF = (Button)findViewById(R.id.bt_ConnectFF);
        et_ipServer = (EditText)findViewById(R.id.et_IPServer);
        et_addressBluetooth = (EditText)findViewById(R.id.et_AddressBluetooth);
        tv_statusSV = (TextView)findViewById(R.id.tv_StatusSV);
        tv_statusFF = (TextView)findViewById(R.id.tv_StatusFF);

        bt_connectSV.setOnClickListener(onClickBt);
        bt_connectFF.setOnClickListener(onClickBt);
        Control.cmct.setPriority(10);
        Control.cmct.start();

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (bluetoothAdapter == null) {
            // Device does not support Bluetooth
            Toast.makeText(this, "Bluetooth is not available", Toast.LENGTH_SHORT).show();
            finish();
            return;
        }

        if (!bluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
    }

    /* @Override
    public void onConfigurationChanged(Configuration newConfig){
        super.onConfigurationChanged(newConfig);
        setContentView(R.layout.tab_setting);
    }*/

    int Disconnect()
    {

        // DISCONNECT ASDK SOCKETS
        if (bluetoothSocket != null) {
            try {
                bluetoothSocket.close();
            } catch (IOException e) {
                // TODO Auto-generated catch block
            }
            bluetoothSocket = null;
        }
        return 0;
    }

    public View.OnClickListener onClickBt = new View.OnClickListener() {

        @Override
        public void onClick(View v) {
            // TODO Auto-generated method stub

            try{

                if(v.getId() == bt_connectSV.getId() ){

                    if(Control.svSetting == 0){                        
                        ipServer = et_ipServer.getText().toString();                
                        serverAddr = InetAddress.getByName(ipServer);
                        tcpSocket = new Socket(serverAddr, 8888);
                        Control.svSetting = 1; 
                        bt_connectSV.setText("Stop");
                        tv_statusSV.setText("Connected!");
                        tv_statusSV.setTextColor(Color.GREEN);
                        et_ipServer.setEnabled(false); 
                        Control.cmct.commandSocket = tcpSocket;
                        Control.stct.statusSocket = tcpSocket;
                        //  Control.stct.start();
                        if(Control.ffSetting == 1){
                            tcpSocket.getOutputStream().write("ff1\r\n".getBytes());
                        }

                    } else {
                        tcpSocket.close();
                        tcpSocket = null;
                        Control.svSetting = 0;
                        bt_connectSV.setText("Connect");
                        tv_statusSV.setText("Disconnected!");
                        tv_statusSV.setTextColor(Color.RED);
                        et_ipServer.setEnabled(true); 
                    }



                } else if (v.getId() == bt_connectFF.getId()){

                    if(Control.ffSetting == 0){        
                        
                        Log.d("FUFO","da vo nut button");
                        bt_connectFF.setEnabled(false);
                        addressBlueTooth = et_addressBluetooth.getText().toString();                
                        bluetoothDevice = bluetoothAdapter.getRemoteDevice(addressBlueTooth);
                        bluetoothSocket = bluetoothDevice.createRfcommSocketToServiceRecord(SPP_UUID);
                        Log.d("FUFO","da vo nut button1");
                        bluetoothSocket.connect(); 
                        Log.d("FUFO","da vo nut button2");
                        Control.ffSetting = 1; 
                        //    checkError.start();
                        bt_connectFF.setEnabled(true);
                        bt_connectFF.setText("Stop");
                        tv_statusFF.setText("Connected!");
                        tv_statusFF.setTextColor(Color.GREEN);
                        et_addressBluetooth.setEnabled(false); 
                        bluetoothSocket.getOutputStream().write('h');
                        Control.cmct.bluetoothSocket = bluetoothSocket;
                        if(Control.stct.bluetoothSocket == null) {
                            // ghifileThread();
                            Control.stct.bluetoothSocket = bluetoothSocket;
                            Log.d(LOG_TAG, "StartReadThread: stct");
                            
                            Control.stct.start();
                            Log.d(LOG_TAG, "StartReadThread: start");
                        }
                        if(Control.svSetting == 1){
                            tcpSocket.getOutputStream().write("ff1\r\n".getBytes());
                        }
                    } else {
                        bluetoothSocket.close();
                        bluetoothSocket = null;
                        Control.ffSetting = 0;
                        bt_connectFF.setText("Connect");
                        tv_statusFF.setText("Disconnected!");
                        tv_statusFF.setTextColor(Color.RED);
                        et_addressBluetooth.setEnabled(true); 
                    }
                }

            }catch(Exception e){
                Toast.makeText(SettingActivity.this, e.getMessage(), Toast.LENGTH_SHORT).show();
                bt_connectFF.setEnabled(true);
            }
        }
    };

    @Override
    public void onBackPressed() {

        // do something on back.
        try{
          //  Control.stct.stop();
         //   Control.cmct.stop();
            if(bluetoothSocket != null)
            bluetoothSocket.close();
            tcpSocket.close();
            if  (Control.stct.bluetoothSocket!= null)                        
                Control.stct.bluetoothSocket.close();
                if  (Control.cmct.bluetoothSocket!= null)
                Control.cmct.bluetoothSocket.close();
                Control.whileCommand = false;
                Control.whileStatus = false;
        }catch(Exception e){

        }
        System.exit(0);
        return;
    }

    Thread checkError = new Thread(){
        public void run(){
            try {
                while(true){
                    sleep(1000); 
                    if(Control.svSetting == 1 && Control.ffSetting == 1){
                        Control.svSetting = 0;
                        Control.ffSetting = 0;
                    }else if (Control.svSetting == 0){
                        /*ProgressDialog dialog = ProgressDialog.show(SettingActivity.this, "", 
                          "Auto fix connecting. Please wait...", true);
                  dialog.show();*/
                        
                        tcpSocket = new Socket(serverAddr, 8888);
                        Control.svSetting = 1; 
                        Control.cmct.commandSocket = tcpSocket;
                        Control.stct.statusSocket = tcpSocket;
                    }else if (Control.ffSetting == 0){
                        
                        bluetoothSocket.connect(); 
                        Control.ffSetting = 1; 
                        Control.cmct.bluetoothSocket = bluetoothSocket;
                        Control.stct.bluetoothSocket = bluetoothSocket;
                    }else{
                        tcpSocket = new Socket(serverAddr, 8888);
                        Control.svSetting = 1; 
                        Control.cmct.commandSocket = tcpSocket;
                        Control.stct.statusSocket = tcpSocket;
                        
                        bluetoothSocket.connect(); 
                        Control.ffSetting = 1; 
                        Control.cmct.bluetoothSocket = bluetoothSocket;
                        Control.stct.bluetoothSocket = bluetoothSocket;
                    }

                }
            } catch (Exception ex) {
                // TODO Auto-generated catch block
                ex.printStackTrace();
            }
        }
    };
}