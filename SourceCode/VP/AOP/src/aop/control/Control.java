package aop.control;

import java.net.InetAddress;
import java.net.Socket;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import aop.command.CommandControl;
import aop.control.R.color;
import aop.video.VideoControl;

public class Control extends Activity {
    
    CommandControl cmct;
    VideoControl vdct; 
    EditText ipServer,etport;
    TextView message,status;
    Socket tcpSocket;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.client);
        ipServer = (EditText)findViewById(R.id.ipServer);
        etport = (EditText)findViewById(R.id.port);
        Button Connect = (Button)findViewById(R.id.Connect);
        message = (TextView)findViewById(R.id.message);
        status = (TextView)findViewById(R.id.status);
        Connect.setOnClickListener(btConnectOnClickListener);
    }

    Button.OnClickListener btConnectOnClickListener
    = new Button.OnClickListener(){

        @Override
        public void onClick(View arg0) {
            // TODO Auto-generated method stub
            
            String hostname = ipServer.getText().toString();
            int port = Integer.parseInt(etport.getText().toString());
            try{
                InetAddress serverAddr = InetAddress.getByName(hostname);
                
                tcpSocket = new Socket(serverAddr, port);
                status.setText("Connected!");
                status.setTextColor(Color.GREEN);
                
                cmct = new CommandControl(tcpSocket);
                cmct.start();
                
                vdct = new VideoControl(Control.this);
               // vdct.start();
                
            }catch(Exception e){
                
            }
            
        }
    };
}