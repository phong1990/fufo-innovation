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

import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;

import android.app.Activity;
import android.app.ExpandableListActivity;
import android.app.ListActivity;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.BaseExpandableListAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ExpandableListAdapter;
import android.widget.ExpandableListView;
import android.widget.ExpandableListView.ExpandableListContextMenuInfo;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import aop.control.PerseusAndroid.BTDev;

/**
 * @author khoinguyen67
 *
 */
public class SettingActivity extends ExpandableListActivity implements OnItemClickListener{
    String                      LOG_TAG                 = "FUFO";
    final static String         FUFO_BTADDR             = "00:12:02:15:60:12";
    String         m_szAppTitle            = "FUFOAndroid";
    ProgressDialog              m_progDlg;
    final      int             REQUEST_CONNECT_DEVICE  = 1,
    REQUEST_ENABLE_BT       = 2;
    
    //-- Bluetooth functionality --//
    
    //BTNative                  m_BT;                   //obsolete
    final static int            MAX_DEVICES             = 50;
     
    BluetoothAdapter            m_BluetoothAdapter;
    boolean                     m_ASDKScanRunning       = false;
    int                         m_nDiscoverResult       = -1;
    int                         m_nRoboDev              = -1;
    final Handler               m_Handler               = new Handler();    //used for discovery thread, etc
    // Intent request codes
    BluetoothSocket             m_btSck;                                    //used to handle Android<->Robot communication
    private static final UUID   SPP_UUID                = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    Thread                      m_hReadThread;
    Thread click;
    int idLVFirstItem;
    
    ListView m_lvSearch;
    View ipView;
    View ffView;
    Button bt_Connect, bt_Stop, bt_Search;
    EditText et_IpServer, et_Port;
    TextView tv_ServerStatus;
    ExpandableListAdapter mAdapter;
    int flag = 0;
    ArrayList<String> mArrayAdapter;
    
    class BTDev {
        String  m_szName;
        String  m_szAddress;
        int     m_nBTDEVType; //if 1, it's the Perseus ROBOT, if 0 it's a regular device
        
        
        BTDev(String _name, String _address) {
            m_szName = _name; m_szAddress = _address;  
        }
        BTDev(String _name, String _address, int _type) {
            m_szName = _name; m_szAddress = _address; m_nBTDEVType = _type;  
        }
    }
    BTDev   BTDevs[];
    int     BTCount;
       
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d("FUFO", "chuan bi vao1 " );
        // Set up our adapter
        mAdapter = new MyExpandableListAdapter();
        setListAdapter(mAdapter);
        registerForContextMenu(getExpandableListView());

        /*        et_IpServer = (EditText)findViewById(0x7f060011);
        et_Port = (EditText)findViewById(R.id.port);
        bt_Connect = (Button)findViewById(R.id.bt_Connect);
        bt_Stop = (Button)findViewById(R.id.bt_Stop);
        bt_Search= (Button)findViewById(R.id.bt_Search);
   //     tv_ServerStatus = (TextView)(ipView.findViewById(0x7f06000e));
         */        Log.d("FUFO", "chuan bi vao111 " );
         //    ipView.setOnClickListener(onClickBt);
         
         //m_BT = new BTNative();
         BTDevs = new BTDev[MAX_DEVICES]; 
         
          m_BluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
         if (m_BluetoothAdapter == null) {
             // Device does not support Bluetooth
             Toast.makeText(this, "Bluetooth is not available", Toast.LENGTH_LONG).show();
             finish();
             return;
         }
       
         if (!m_BluetoothAdapter.isEnabled()) {
             Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
             startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
         }
         // Register for broadcasts when a device is discovered
         IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
         this.registerReceiver(mReceiver, filter);

         // Register for broadcasts when discovery has finished
         filter = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
         this.registerReceiver(mReceiver, filter); 

    }

    // The BroadcastReceiver that listens for discovered devices and
    // changes the title when discovery is finished
    public final BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
                        
            // When discovery finds a device
            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                // Get the BluetoothDevice object from the Intent
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                //if (device.getBondState() != BluetoothDevice.BOND_BONDED) // If it's already paired, skip it, because it's been listed already
                //-- ignore duplicates
                boolean duplicate = false;
                for (int j=0;j<BTCount;j++)
                    if (BTDevs[j].m_szAddress.compareTo(device.getAddress()) == 0) { duplicate = true; break; }
                if (duplicate)
                    ; //this is a duplicate
                else
                {
                    if (device.getAddress().compareTo(FUFO_BTADDR) == 0)
                        BTDevs[BTCount] = new BTDev(device.getName(), device.getAddress(), 1);
                    else
                        BTDevs[BTCount] = new BTDev(device.getName(), device.getAddress(), 0);
                    BTCount++;
                }
                
            // When discovery is finished
            } else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)) {
                m_ASDKScanRunning = false; 
            }
        }
    };  

    @Override
    public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3) {

            int nIndex = -1, nCounter = 0;
            for (int i=0;i<BTCount;i++)
            {
                if (arg2 == nCounter) {
                    nIndex = i;
                    break;
                }
                nCounter++;
            }
            // connect to 
            if (BTDevs[nIndex].m_nBTDEVType == 1)
            {
                //connect to ROBOT
                Connect(nIndex);
                StartReadThread(nIndex);
            }
            else 
                Toast.makeText(getBaseContext(), 
                        "This is not FUFO", Toast.LENGTH_SHORT).show();


        }
        
    
    
    // put the /BTDEvs in the listview
    void PopulateLV()
    {
        ArrayList<Device> m_Devices = new ArrayList<Device>();
        Device device = null;
        for (int i=0;i<BTCount;i++) {
            if (BTDevs[i].m_szAddress.compareTo(PerseusAndroid.ROBO_BTADDR) == 0) {
                BTDevs[i].m_nBTDEVType = 1;
                m_nRoboDev = i;
                device = new Device(BTDevs[i].m_szName, 
                        BTDevs[i].m_szAddress, 
                        BTDevs[i].m_nBTDEVType,
                        0, 
                        idLVFirstItem+i);
            }
            else 
                BTDevs[i].m_nBTDEVType = 0;

            if (device != null){
            m_Devices.add(device);
            i = BTCount;
            }
        }
    CustomAdapter lvAdapter =  new CustomAdapter(this, m_Devices);
    if (lvAdapter!=null) m_lvSearch.setAdapter(lvAdapter);
    if (m_nRoboDev >= 0)
        Toast.makeText(getBaseContext(), "ROBO found as " + BTDevs[m_nRoboDev].m_szAddress, 
                Toast.LENGTH_LONG).show();
    }
    
/** Bluetooth Functions **/
    
    // not Blocking, uses events
    int ASDKDiscoverBluetoothDevices()
    {
        Log.d(LOG_TAG,"da vo ham ASDKDiscoverBluetoothDevices1");
        if (m_BluetoothAdapter.isDiscovering()) {
            Log.d(LOG_TAG,"da vo ham ASDKDiscoverBluetoothDevices2");
            m_BluetoothAdapter.cancelDiscovery();
        }
        Log.d(LOG_TAG,"da vo ham ASDKDiscoverBluetoothDevices3");
        int current_devs = BTCount;
        // Request discover from BluetoothAdapter
        if (!m_BluetoothAdapter.startDiscovery()) return -1; //error
        
        m_ASDKScanRunning = true;

        //  blocking operation:wait to complete
        while (m_ASDKScanRunning);
        Log.d(LOG_TAG,"da vo ham ASDKDiscoverBluetoothDevices3");
        return BTCount - current_devs;
    }

    final Runnable mUpdateResultsDiscover = new Runnable() {
        public void run() {
            doneDiscoverBluetoothDevices();
        }
    };
    protected void startDiscoverBluetoothDevices() {
        // Show Please wait dialog
        m_progDlg = ProgressDialog.show(this,
                m_szAppTitle, "Scanning, please wait",
                true);
        
        // Fire off a thread to do some work that we shouldn't do directly in the UI thread
        Thread t = new Thread() {
            public void run() 
            {
                Log.d(LOG_TAG,"da vo ham startDiscoverBluetoothDevices");
                // blocking operation
                    m_nDiscoverResult = ASDKDiscoverBluetoothDevices();
                //show results
                m_Handler.post(mUpdateResultsDiscover);
            }
        };
        t.start();
    }
    
    private void doneDiscoverBluetoothDevices() 
    {
        m_progDlg.dismiss();
        if (m_nDiscoverResult == -1)
            Toast.makeText(getBaseContext(), "Bluetooth ERROR (is bluetooth on?)", Toast.LENGTH_LONG).show();
        else if (m_nDiscoverResult == 0)
            Toast.makeText(getBaseContext(), "No Bluetooth devices found", Toast.LENGTH_LONG).show();
        else {
            m_nRoboDev = -1;
            // populate
            PopulateLV();
        }
    }
    int Connect(int nIndex)
    {
        if (nIndex >= BTCount || nIndex<0) return -1; //invalid device
        
        //ANDROID SDK IMPLEMENTATION
        //--connect serial port
        BluetoothDevice ROBOBTDev = m_BluetoothAdapter.getRemoteDevice(BTDevs[nIndex].m_szAddress);
        try {
            m_btSck = ROBOBTDev.createRfcommSocketToServiceRecord(SPP_UUID);
        } catch (IOException e1) {
            // TODO Auto-generated catch block
            e1.printStackTrace();
        }
        try { //This is a blocking call and will only return on a successful connection or an exception
            m_btSck.connect();  
            Log.d("FUFO", "da connect bt");
        } catch (IOException e) {
             // Close the socket
             try { m_btSck.close();} catch (IOException e2) { e2.printStackTrace();}
             return -2; 
         }
        return 0;
    }
    int Disconnect(int nIndex)
    {
        if (nIndex >= BTCount || nIndex<0) return -1; //invalid device
        
        // DISCONNECT ASDK SOCKETS
        if (m_btSck != null) {
            try {
                m_btSck.close();
            } catch (IOException e) {
                // TODO Auto-generated catch block
            }
            m_btSck = null;
        }
        return 0;
    }

    // Worker functions
    int StartReadThread(final int nIndex)
    {
        // signal connect event for this BT dev
        ConnectionEvent(1,nIndex,null);
        
        m_hReadThread = new Thread() {
            public void run() 
            {
                while (true) 
                {
                    byte buf[] = null;
                     Log.i("FUFO", "StartReadThread: Data received:"+ "day");
                    try {
                    
                        // Read from the InputStream
                        byte[] buffer = new byte[1024]; 
                        int bread = m_btSck.getInputStream().read(buffer);
                        buf = new byte[bread];
                        System.arraycopy(buffer, 0, buf, 0, bread);
                       
                        

                        // Send the obtained bytes to the UI Activity

                        Log.i(LOG_TAG, "StartReadThread: Data received:"+ bread);
                    } catch (IOException e) {
                        Log.d(LOG_TAG, "StartReadThread: disconnected", e);
                    } 
                    
                    // signal disconnect event
                    if (buf == null)
                    {
                        ConnectionEvent(2,nIndex, null);
                        break;
                    }
                    else //signal incoming data
                    {
                        ConnectionEvent(3,nIndex, buf);
                    }
                }
            }
        };
        m_hReadThread.start();
        return 0;
    }
 // Worker event function called on various events
    int ConnectionEvent(int type, int nDevId, byte buf[])
    {
        if (nDevId >= BTCount)return -1;
        
      /*  if (type == 1) { //connected
            m_tabHost.post(new Runnable() { public void run() {m_tabHost.setCurrentTab(1);} });
        }
        if (type == 2) { //disconnect
            // DISCONNECT NATIVE SOCKETS
            //Toast.makeText(this, "Disconnected from ROBO", Toast.LENGTH_LONG).show();
            Disconnect(nDevId);
            
            m_tabHost.post(new Runnable() { public void run() {m_tabHost.setCurrentTab(0);} });
        }*/
        if (type == 3) { 
            if (buf.length == 0) return -1;
            
            int nTHeader = buf[0]& 0xFF; 
            int nTType = (nTHeader >>> 4) & 0xF;    //transaction type
            int nTParam = (nTHeader) & 0xF;     //transaction parameters
            
            
        }
        return 0;
    }

    
    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenuInfo menuInfo) {
        menu.setHeaderTitle("Sample menu");
        menu.add(0, 0, 0, R.string.expandable_list_sample_action);
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        ExpandableListContextMenuInfo info = (ExpandableListContextMenuInfo) item.getMenuInfo();

        String title = ((TextView) info.targetView).getText().toString();

        int type = ExpandableListView.getPackedPositionType(info.packedPosition);
        if (type == ExpandableListView.PACKED_POSITION_TYPE_CHILD) {
            int groupPos = ExpandableListView.getPackedPositionGroup(info.packedPosition); 
            int childPos = ExpandableListView.getPackedPositionChild(info.packedPosition); 
            Toast.makeText(this, title + ": Child " + childPos + " clicked in group " + groupPos,
                    Toast.LENGTH_SHORT).show();
            return true;
        } else if (type == ExpandableListView.PACKED_POSITION_TYPE_GROUP) {
            int groupPos = ExpandableListView.getPackedPositionGroup(info.packedPosition); 
            Toast.makeText(this, title + ": Group " + groupPos + " clicked", Toast.LENGTH_SHORT).show();
            return true;
        }

        return false;
    }

    /**
     * A simple adapter which maintains an ArrayList of photo resource Ids. 
     * Each photo is displayed as an image. This adapter supports clearing the
     * list of photos and adding a new photo.
     *
     */
    public class MyExpandableListAdapter extends BaseExpandableListAdapter implements OnItemClickListener {
        // Sample data set.  children[i] contains the children (String[]) for groups[i].
        private String[] groups = { "  Server Setting", "  FUFO Setting" };
        private String[][] children = {
                { "Arnold" },
                { "Ace"}
        };

        public Object getChild(int groupPosition, int childPosition) {
            return children[groupPosition][childPosition];
        }

        public long getChildId(int groupPosition, int childPosition) {
            return childPosition;
        }

        public int getChildrenCount(int groupPosition) {
            return children[groupPosition].length;
        }

        public TextView getGenericView() {
            // Layout parameters for the ExpandableListView
            AbsListView.LayoutParams lp = new AbsListView.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT, 64);

            TextView textView = new TextView(SettingActivity.this);
            textView.setLayoutParams(lp);
            // Center the text vertically
            textView.setGravity(Gravity.CENTER_VERTICAL | Gravity.LEFT);
            // Set the text starting position
            textView.setPadding(36, 0, 0, 0);
            return textView;
        }

        public View getChildView(int groupPosition, int childPosition, boolean isLastChild,
                View convertView, ViewGroup parent) {
            LayoutInflater inflater = (LayoutInflater) getApplicationContext().getSystemService
            (Context.LAYOUT_INFLATER_SERVICE);
            if(flag == 0){
                ipView =inflater.inflate(R.layout.tab_setting_child_item_ipserver, parent, false);  
                bt_Connect = (Button)(ipView.findViewById(0x7f060012));
                bt_Stop = (Button)(ipView.findViewById(0x7f060014));
                bt_Connect.setOnClickListener(onClickBt);
                bt_Stop.setOnClickListener(onClickBt);
                flag = 1;
            }
            ffView =inflater.inflate(R.layout.tab_setting_child_item_fufo, parent, false);  
             bt_Search = (Button)(ffView.findViewById(0x7f06000f));
             bt_Search.setOnClickListener(onClickBt);
             m_lvSearch = (ListView)(ffView.findViewById(0x7f060010));
             idLVFirstItem = 0x7f060010;
             m_lvSearch.setOnItemClickListener(this);
            if(groupPosition == 0) return ipView;
            else return ffView;
        }

        public Object getGroup(int groupPosition) {
            return groups[groupPosition];
        }

        public int getGroupCount() {
            return groups.length;
        }

        public long getGroupId(int groupPosition) {
            return groupPosition;
        }

        public View getGroupView(int groupPosition, boolean isExpanded, View convertView,
                ViewGroup parent) {
            TextView textView = getGenericView();
            textView.setText(getGroup(groupPosition).toString());
            textView.setTextSize(15);
            //  textView.setTextColor(Color.RED);
            return textView;
        }

        public boolean isChildSelectable(int groupPosition, int childPosition) {
            return true;
        }

        public boolean hasStableIds() {
            return true;
        }

        @Override
        public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3) {

                int nIndex = -1, nCounter = 0;
                for (int i=0;i<BTCount;i++)
                {
                    if (arg2 == nCounter) {
                        nIndex = i;
                        break;
                    }
                    nCounter++;
                }
                // connect to 
                if (BTDevs[nIndex].m_nBTDEVType == 1)
                {
                    //connect to ROBOT
                    Connect(nIndex);
                    StartReadThread(nIndex);
                }
                else 
                    Toast.makeText(getBaseContext(), 
                            "This is not FUFO", Toast.LENGTH_SHORT).show();


            }

    }

    public View.OnClickListener onClickBt = new View.OnClickListener() {

        @Override
        public void onClick(View v) {
            // TODO Auto-generated method stub
            Log.d("FUFO", "chuan bi vao 3  " +v.getId() + "  " +bt_Connect.getId() ); 
            try{
                Log.d("FUFO", "vao");
                if(v.getId() == bt_Connect.getId()){
                    et_IpServer = (EditText)(ipView.findViewById(0x7f060011));
                    String ipServer = et_IpServer.getText().toString();
                    Log.d("FUFO", "vao" + ipServer);
                    et_Port = (EditText)(ipView.findViewById(0x7f060013));
                    int port = Integer.parseInt(et_Port.getText().toString());
                    Log.d("FUFO", "vao1");
                    InetAddress serverAddr = InetAddress.getByName(ipServer);
                    Log.d("FUFO", "vao2 :" + ipServer + port );
                    Socket tcpSocket = new Socket(serverAddr, port);
                    tv_ServerStatus = (TextView)(ipView.findViewById(0x7f06000e));
                    tv_ServerStatus.setText("Connected!");
                    tv_ServerStatus.setTextColor(Color.GREEN);
                    et_IpServer.setEnabled(false); 
                    et_Port.setEnabled(false); 
                    bt_Connect.setEnabled(false); 
                    bt_Stop.setEnabled(true);
                }else if (v.getId() == bt_Stop.getId()){
                    tv_ServerStatus.setText("Disconnected!");
                    tv_ServerStatus.setTextColor(Color.RED);
                    et_IpServer.setEnabled(true); 
                    et_Port.setEnabled(true); 
                    bt_Connect.setEnabled(true); 
                    bt_Stop.setEnabled(false);
                }
                else if (v.getId() == bt_Search.getId()){
                    startDiscoverBluetoothDevices();
                    Log.d("FUFO", "bt_Search pressed");
                }
            }catch(Exception e){

            }
        }
    };

}