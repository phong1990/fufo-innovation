package aop.control;

import java.io.FileOutputStream;
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
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import aop.command.CommandControl;
import aop.status.StatusControl;

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

    Button bt_ConnectSV, bt_ConnectFF;
    EditText et_IpServer, et_AddressBluetooth;
    TextView tv_StatusSV, tv_StatusFF;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tab_setting);

        bt_ConnectSV = (Button)findViewById(R.id.bt_ConnectSV);
        bt_ConnectFF = (Button)findViewById(R.id.bt_ConnectFF);
        et_IpServer = (EditText)findViewById(R.id.et_IPServer);
        et_AddressBluetooth = (EditText)findViewById(R.id.et_AddressBluetooth);
        tv_StatusSV = (TextView)findViewById(R.id.tv_StatusSV);
        tv_StatusFF = (TextView)findViewById(R.id.tv_StatusFF);
        
        bt_ConnectSV.setOnClickListener(onClickBt);
        bt_ConnectFF.setOnClickListener(onClickBt);
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

                if(v.getId() == bt_ConnectSV.getId() ){
                    
                    if(Control.svSetting == 0){                        
                    ipServer = et_IpServer.getText().toString();                
                    serverAddr = InetAddress.getByName(ipServer);
                    tcpSocket = new Socket(serverAddr, 8888);
                    Control.svSetting = 1; 
                    bt_ConnectSV.setText("Stop");
                    tv_StatusSV.setText("Connected!");
                    tv_StatusSV.setTextColor(Color.GREEN);
                    et_IpServer.setEnabled(false); 
                    Control.cmct.commandSocket = tcpSocket;
                    Control.stct.statusSocket = tcpSocket;
                  //  Control.stct.start();
                } else {
                    tcpSocket.close();
                    tcpSocket = null;
                    Control.svSetting = 0;
                    bt_ConnectSV.setText("Connect");
                    tv_StatusSV.setText("Disconnected!");
                    tv_StatusSV.setTextColor(Color.RED);
                    et_IpServer.setEnabled(true); 
                }


                 
                } else if (v.getId() == bt_ConnectFF.getId()){

                    if(Control.ffSetting == 0){                        
                        bt_ConnectFF.setEnabled(false);
                        addressBlueTooth = et_AddressBluetooth.getText().toString();                
                        bluetoothDevice = bluetoothAdapter.getRemoteDevice(addressBlueTooth);
                        bluetoothSocket = bluetoothDevice.createRfcommSocketToServiceRecord(SPP_UUID);
                        bluetoothSocket.connect(); 
                        Control.ffSetting = 1; 
                        bt_ConnectFF.setEnabled(true);
                        bt_ConnectFF.setText("Stop");
                        tv_StatusFF.setText("Connected!");
                        tv_StatusFF.setTextColor(Color.GREEN);
                        et_AddressBluetooth.setEnabled(false); 
                        bluetoothSocket.getOutputStream().write('h');
                        Control.cmct.bluetoothSocket = bluetoothSocket;
                        if(Control.stct.bluetoothSocket == null) ghifileThread();
                    } else {
                        bluetoothSocket.close();
                        bluetoothSocket = null;
                        Control.ffSetting = 0;
                        bt_ConnectFF.setText("Connect");
                        tv_StatusFF.setText("Disconnected!");
                        tv_StatusFF.setTextColor(Color.RED);
                        et_AddressBluetooth.setEnabled(true); 
                    }
                }
    
            }catch(Exception e){
                Toast.makeText(SettingActivity.this, e.getMessage(), Toast.LENGTH_SHORT).show();
                bt_ConnectFF.setEnabled(true);
            }
        }
    };
    
    @Override
    public void onBackPressed() {
    // do something on back.
        System.exit(0);
    return;
    }
    
    // Worker functions
    Thread ghifile;
    void ghifileThread()
    {
     
        ghifile = new Thread() {
            public void run() 
            {
                while (true) 
                {
                    byte buf[] = null;
                     Log.i("FUFO", "StartReadThread: Data received:"+ "day");
                    try {
                    
                        // Read from the InputStream
                        byte[] buffer = new byte[1024]; 
                        int bread = bluetoothSocket.getInputStream().read(buffer);
                        buf = new byte[bread];
                        System.arraycopy(buffer, 0, buf, 0, bread);
                        writeToFile(buf);
                        
                       
                        // Send the obtained bytes to the UI Activity

                        Log.i(LOG_TAG, "StartReadThread: Data received:"+ "day2");
                    } catch (IOException e) {
                        Log.d(LOG_TAG, "StartReadThread: disconnected", e);
                    }                    
                }
            }
        };
   //     ghifile.start();
        Control.stct.bluetoothSocket = bluetoothSocket;
        Log.d(LOG_TAG, "StartReadThread: stct");
        Control.stct.start();
        Log.d(LOG_TAG, "StartReadThread: start");
    }
    public static void writeToFile(byte[] buffer){
        String state = android.os.Environment.getExternalStorageState();
        try{
        if(state.equals(android.os.Environment.MEDIA_MOUNTED))   
        { 
            String sdcard_path = Environment.getExternalStorageDirectory().getAbsolutePath(); 
            String file_path = sdcard_path; 
            Log.d("FUFO",file_path);
                FileOutputStream os = new FileOutputStream(file_path + "/" + "status.txt",true);
                os.write(buffer);
                os.close(); 
        }
    }catch(Exception e){
        e.getMessage();
    }
    }
}