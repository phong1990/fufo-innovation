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
        
        if(Control.svSetting == 0) 
            rd_Computer.setEnabled(false);
        
        if(Control.ffSetting == 0) 
           // rd_Phone.setEnabled(false);
        
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
            if(arg0.getCheckedRadioButtonId() == R.id.rd_computer){
                tb_LO.setVisibility(4); 
                Control.cmct.controlMode = 1;
                Log.d("FUFO","rd_computer pressed");
                vdct.startStream();
                Log.d("FUFO","rd_computer pressed2");
                if(Control.cmct.bluetoothSocket != null){
                    Control.cmct.bluetoothSocket.getOutputStream().write('c');
                }
                
            }
            else {
                tb_LO.setVisibility(0);
                Control.cmct.controlMode = 2;
                Log.d("FUFO","rd_phone pressed");
                vdct.stopStream();
                if(Control.cmct.bluetoothSocket != null){
                    Control.cmct.bluetoothSocket.getOutputStream().write('n');
                }
                Log.d("FUFO","rd_Phone pressed2");
                
            }
        }catch(Exception e){

        }
    }
}