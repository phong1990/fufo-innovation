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

    Button  bt_Fwd, bt_Bwd, bt_Rgt, 
    bt_Lft, bt_Up, bt_Dwn, bt_Nkdh, bt_Kdh, bt_Start;
    public static RadioButton rd_Computer,rd_Phone;
    public FrameLayout preview;
    RadioGroup rd_Group;
    TableLayout tb_LO;
    VideoControl vdct;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tab_control);

        bt_Fwd = (Button)findViewById(R.id.bt_fwd);
        bt_Bwd = (Button)findViewById(R.id.bt_bwd);
        bt_Rgt = (Button)findViewById(R.id.bt_rgt);
        bt_Lft = (Button)findViewById(R.id.bt_lft);
        bt_Up = (Button)findViewById(R.id.bt_up);
        bt_Dwn = (Button)findViewById(R.id.bt_dwn);
        bt_Nkdh = (Button)findViewById(R.id.bt_nkdt);
        bt_Kdh = (Button)findViewById(R.id.bt_kdh);
        bt_Start = (Button)findViewById(R.id.bt_start);
        rd_Group = (RadioGroup)findViewById(R.id.radioGroup);
        rd_Computer = (RadioButton)findViewById(R.id.rd_computer);
        rd_Phone = (RadioButton)findViewById(R.id.rd_phone);
        tb_LO = (TableLayout)findViewById(R.id.tb_layout);
        preview = (FrameLayout) findViewById(R.id.camera_preview);

        rd_Group.setOnCheckedChangeListener(this);
        bt_Fwd.setOnClickListener(Control.cmct);
        bt_Bwd.setOnClickListener(Control.cmct);
        bt_Rgt.setOnClickListener(Control.cmct);
        bt_Lft.setOnClickListener(Control.cmct);
        bt_Up.setOnClickListener(Control.cmct);
        bt_Dwn.setOnClickListener(Control.cmct);
        bt_Nkdh.setOnClickListener(Control.cmct);
        bt_Kdh.setOnClickListener(Control.cmct);
        bt_Start.setOnClickListener(Control.cmct);
        tb_LO.setVisibility(4);

        vdct = new VideoControl(this);
    }

    /**
     * [Explain the description for this method here].
     * @param arg0
     * @param arg1
     * @see android.widget.RadioGroup.OnCheckedChangeListener#onCheckedChanged(android.widget.RadioGroup, int)
     */
    @Override
    public void onCheckedChanged(RadioGroup arg0, int arg1) {

        // TODO Auto-generated method stub
        try{
            if(Control.ffSetting == 0){
                
                Toast.makeText(this, "Please check Bluetooth connection!", Toast.LENGTH_SHORT).show(); 
                rd_Group.clearCheck();
            }else{
                
                if(arg0.getCheckedRadioButtonId() == R.id.rd_computer){
                    
                    if(Control.svSetting == 0){
                        
                        Toast.makeText(this, "Please check Server connection!", Toast.LENGTH_SHORT).show(); 
                        rd_Computer.setChecked(false);
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