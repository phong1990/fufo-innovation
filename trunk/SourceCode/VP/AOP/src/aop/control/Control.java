package aop.control;

import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.OutputStream;

import android.app.TabActivity;
import android.content.Intent;
import android.content.res.Resources;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TabHost;
import android.widget.TableLayout;
import android.widget.TextView;
import aop.command.CommandControl;
import aop.control.R.color;

public class control extends TabActivity{

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        Log.d("FUFO", "hehe 2");
        Resources res = getResources(); // Resource object to get Drawables
        TabHost tabHost = getTabHost();  // The activity TabHost
        TabHost.TabSpec spec;  // Resusable TabSpec for each tab
        Intent intent;  // Reusable Intent for each tab

        // Create an Intent to launch an Activity for the tab (to be reused)
        intent = new Intent().setClass(this, SettingActivity.class);

        // Initialize a TabSpec for each tab and add it to the TabHost
        spec = tabHost.newTabSpec("setting").setIndicator("Setting",
                          res.getDrawable(R.drawable.ic_tab_setting))
                      .setContent(intent);
        tabHost.addTab(spec);
        
        // Do the same for the other tabs
        intent = new Intent().setClass(this, ControlActivity.class);
        spec = tabHost.newTabSpec("control").setIndicator("Control",
                          res.getDrawable(R.drawable.ic_tab_control))
                      .setContent(intent);
        tabHost.addTab(spec);
        tabHost.setCurrentTab(0);

        
     /*   Thread cmct = new CommandControl();
        cmct.start();*/
    }

}