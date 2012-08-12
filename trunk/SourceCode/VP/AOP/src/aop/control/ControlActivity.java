package aop.control;

import aop.video.*;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
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
        bt_forward.setOnClickListener(Control.cmct);
        bt_backward.setOnClickListener(Control.cmct);
        bt_right.setOnClickListener(Control.cmct);
        bt_left.setOnClickListener(Control.cmct);
        bt_up.setOnClickListener(Control.cmct);
        bt_down.setOnClickListener(Control.cmct);
        bt_rotateLeft.setOnClickListener(Control.cmct);
        bt_rotateRight.setOnClickListener(Control.cmct);
        bt_start.setOnClickListener(Control.cmct);
        tb_LO.setVisibility(4);

        vdct = new VideoControl(this);
    }
    
    @Override
    public void onCheckedChanged(RadioGroup arg0, int arg1) {

        try{
            
            if(Control.ffSetting == 0){
                
                Toast.makeText(this, "Please check Bluetooth connection!", Toast.LENGTH_SHORT).show(); 
                rd_group.clearCheck();
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
        System.exit(0);
    return;
    }
}