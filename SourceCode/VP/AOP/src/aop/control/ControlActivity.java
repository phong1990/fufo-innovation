package aop.control;

import java.io.IOException;

import aop.video.*;
import android.app.Activity;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TableLayout;
import android.widget.Toast;

/**
 * @author khoinguyen67
 *
 */
public class ControlActivity extends Activity implements OnCheckedChangeListener {

    Button  bt_forward, bt_backward, bt_right, 
    bt_left, bt_up, bt_down, bt_rotateLeft, bt_rotateRight, bt_start;
    public static RadioButton rd_computer,rd_phone;
    public FrameLayout preview;
    RadioGroup rd_group;
    TableLayout tb_LO;
    VideoControl vdct;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tab_control);

        bt_forward = (Button)findViewById(R.id.bt_fwd);
        bt_backward = (Button)findViewById(R.id.bt_bwd);
        bt_right = (Button)findViewById(R.id.bt_rgt);
        bt_left = (Button)findViewById(R.id.bt_lft);
        bt_up = (Button)findViewById(R.id.bt_up);
        bt_down = (Button)findViewById(R.id.bt_dwn);
        bt_rotateLeft = (Button)findViewById(R.id.bt_nkdt);
        bt_rotateRight = (Button)findViewById(R.id.bt_kdh);
        bt_start = (Button)findViewById(R.id.bt_start);
        rd_group = (RadioGroup)findViewById(R.id.radioGroup);
        rd_computer = (RadioButton)findViewById(R.id.rd_computer);
        rd_phone = (RadioButton)findViewById(R.id.rd_phone);
        tb_LO = (TableLayout)findViewById(R.id.tb_layout);
        preview = (FrameLayout) findViewById(R.id.camera_preview);

        rd_group.setOnCheckedChangeListener(this);
        bt_forward.setOnClickListener(onClickBt);
        bt_backward.setOnClickListener(onClickBt);
        bt_right.setOnClickListener(onClickBt);
        bt_left.setOnClickListener(onClickBt);
        bt_up.setOnClickListener(onClickBt);
        bt_down.setOnClickListener(onClickBt);
        bt_rotateLeft.setOnClickListener(onClickBt);
        bt_rotateRight.setOnClickListener(onClickBt);
        bt_start.setOnClickListener(onClickBt);
        tb_LO.setVisibility(4);

        vdct = new VideoControl(this);
    }
    
    @Override
    public void onCheckedChanged(RadioGroup arg0, int arg1) {

        try{
            
            if(Control.ffSetting == 0){
                
                Toast.makeText(this, "Please check Bluetooth connection!", Toast.LENGTH_SHORT).show(); 
                rd_group.clearCheck();
                return;
            }else{
                
                if(arg0.getCheckedRadioButtonId() == R.id.rd_computer){
                    
                    if(Control.svSetting == 0){
                         
                        Toast.makeText(this, "Please check Server connection!", Toast.LENGTH_SHORT).show();
                        rd_computer.setChecked(false);
                        tb_LO.setVisibility(4);
                        Control.cmct.controlMode = 0;
                        
                    }else{

                        tb_LO.setVisibility(4); 
                        Control.cmct.controlMode = 1;
                        
                        if(Control.cmct.bluetoothSocket != null){
                            
                            Control.cmct.bluetoothSocket.getOutputStream().write('c');
                            Log.d("FUFO","da gui ki tu c");
                        }
                        Log.d("FUFO","before stream");
                        vdct.startStream();
                    }
                }
                else {
                    
                    tb_LO.setVisibility(0);
                    Control.cmct.controlMode = 2;
                    Log.d("FUFO","rd_phone pressed");
                    
                    if(Control.cmct.bluetoothSocket != null){
                        
                        Control.cmct.bluetoothSocket.getOutputStream().write('n');
                        Log.d("FUFO","da gui ki tu n");
                    }
                    Log.d("FUFO","rd_Phone pressed2");
                    vdct.stopStream();
                }
            }
        }catch(Exception e){

        }
    }
    
    @Override
    public void onBackPressed() {
    // do something on back.
        try {
            if  (Control.stct.bluetoothSocket!= null)                        
            Control.stct.bluetoothSocket.close();
            if  (Control.cmct.bluetoothSocket!= null)
            Control.cmct.bluetoothSocket.close();
            Control.whileCommand = false;
            Control.whileStatus = false;
        } catch (IOException ex) {
            // TODO Auto-generated catch block
            ex.printStackTrace();
        }
       
      //  Control.stct.stop();
      //  Control.cmct.stop();
       // Control.cmctbluetoothSocket.close();
       // tcpSocket.close();
        System.exit(0);
    return;
    }
    
    public View.OnClickListener onClickBt = new View.OnClickListener() {

        @Override
        public void onClick(View v) {
            // TODO Auto-generated method stub
     
       int  buttonID = v.getId();
        switch (buttonID){
            case R.id.bt_lft:
                Control.controlByte = 'a'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_fwd:
                Control.controlByte = 'w'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_rgt:
                Control.controlByte = 'd'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_bwd:
                Control.controlByte = 's'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_up:
                Control.controlByte = 'o'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_dwn:
                Control.controlByte = 'p'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_start:
                Control.controlByte = 'f'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_nkdt:
                Control.controlByte = 'n'; 
                //                sendCommandToFUFO();
                break;
            case R.id.bt_kdh:
                Control.controlByte = 'k'; 
                //                sendCommandToFUFO();
                break;
        }
    }
};
}