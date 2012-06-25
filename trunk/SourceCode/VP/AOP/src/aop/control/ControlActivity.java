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
package aop.control;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Toast;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TableLayout;
import android.widget.TextView;

/**
 * @author khoinguyen67
 *
 */
public class ControlActivity extends Activity implements OnCheckedChangeListener {
    Button  bt_Fwd, bt_Bwd, bt_Rgt, 
    bt_Lft, bt_Up, bt_Dwn, bt_Nkdh, bt_Kdh, bt_Start;
   public static RadioButton rd_Computer,rd_Phone;
    RadioGroup rd_Group;
    TableLayout tb_LO;
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

        
    }
    View.OnClickListener testOnClick = new View.OnClickListener() {
        
        @Override
        public void onClick(View v) {
            // TODO Auto-generated method stub
            Log.d("FUFO", "Fwd button pressed!1" + v.getId());
            if(v.getId() == 0x7f020003){
                
                Log.d("FUFO", "Fwd button pressed!2");
            }
        }
    };
    /**
     * [Explain the description for this method here].
     * @param arg0
     * @param arg1
     * @see android.widget.RadioGroup.OnCheckedChangeListener#onCheckedChanged(android.widget.RadioGroup, int)
     */
    @Override
    public void onCheckedChanged(RadioGroup arg0, int arg1) {
        Log.d("FUFO", "radio button pressed!");
        // TODO Auto-generated method stub
        try{
          if(arg0.getCheckedRadioButtonId() == 0x7f060001){
              Log.d("FUFO", "computer radio button pressed!");
          tb_LO.setVisibility(4); 
          Log.d("FUFO", "computer radio button pressed1!");
          
              Control.cmct.controlMode = 1;
              if(Control.cmct.bluetoothSocket != null){
                  Control.cmct.bluetoothSocket.getOutputStream().write('c');
              }
        }
        else {
            tb_LO.setVisibility(0);
            if(Control.cmct.bluetoothSocket != null){
                Control.cmct.bluetoothSocket.getOutputStream().write('n');
            }
            Control.cmct.controlMode = 2;
        }
    }catch(Exception e){
        
    }
}
}